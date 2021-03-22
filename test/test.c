#include "test.h"

struct elapsed_time
{
    unsigned int minute;
    unsigned int second;
    unsigned int millisecond;
    unsigned int microsecond;
};

struct time_for
{
    clock_t clock;
    unsigned int time;
    struct elapsed_time elapsed;
};

struct timer
{
    struct time_for cpu;
    struct time_for user;
};

struct test_map
{
    char *name;
    void (*fct)();
    struct test_map *next;
};

struct map
{
    struct test_map *map;
    unsigned int size;
};

struct map unitTest = {NULL, 0};
struct map timeTest = {NULL, 0};

static void add_to_test_map(struct map *map, const char *name, void (*fct)())
{
    struct test_map *tmp = map->map;
    struct test_map *prev = map->map;
    while (tmp != NULL)
    {
        if (strcmp(tmp->name, name) == 0)
        {
            tmp->fct = fct;
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    struct test_map *newNode = (struct test_map *)malloc(sizeof(struct test_map));
    if (newNode == NULL)
        return;
    newNode->next = NULL;
    newNode->fct = fct;
    if ((newNode->name = strdup(name)) == NULL)
    {
        free(newNode);
        return;
    }
    if (prev == NULL)
        map->map = newNode;
    else
        prev->next = newNode;
    ++map->size;
}

void test_register(const char *name, void (*fct)())
{
    add_to_test_map(&unitTest, name, fct);
}

void timer_register(const char *name, void (*fct)())
{
    add_to_test_map(&timeTest, name, fct);
}

void assert_true(bool test)
{
    if (test == false)
        exit(1);
}

void assert_false(bool test)
{
    if (test == true)
        exit(1);
}

static void destroy_map(struct test_map *node)
{
    free(node->name);
    if (node->next != NULL)
        destroy_map(node->next);
    free(node);
}

static bool test_run_test(struct test_map *node)
{
    int sig = -1;
    int pid = fork();
    if (pid != 0)
        wait(&sig);
    if (pid == 0)
    {
        if (node->fct)
        {
            node->fct();
            exit(0);
        }
        else
            exit(1);
    }
    if (sig == 0)
        return true;
    return false;
}

static void start_timer(struct timer *timer)
{
    timer->cpu.time = 0;
    timer->user.time = 0;
    timer->user.clock = times(NULL);
    timer->cpu.clock = clock();
}

static struct elapsed_time generate_from(unsigned int time)
{
    struct elapsed_time elapsed;
    elapsed.minute = time / 60000000;
    time = time - (elapsed.minute * 60000000);
    elapsed.second = time / 1000000;
    time = time - (elapsed.second * 1000000);
    elapsed.millisecond = time / 1000;
    time = time - (elapsed.millisecond * 1000);
    elapsed.microsecond = time;
    return elapsed;
}

static void stop_timer(struct timer *timer)
{
    clock_t cpu = clock();
    clock_t user = times(NULL);
    timer->cpu.time = (unsigned int)(((double)(cpu - timer->cpu.clock) / CLOCKS_PER_SEC) * 1000000);
    timer->user.time = (unsigned int)((double)(user - timer->user.clock) * 10000);
    timer->cpu.elapsed = generate_from(timer->cpu.time);
    timer->user.elapsed = generate_from(timer->user.time);
}

static void print_elapsed(struct elapsed_time elapsed)
{
    printf("%um%us%ums%uμs\n", elapsed.minute, elapsed.second, elapsed.millisecond, elapsed.microsecond);
}

static bool execute_timer_test(struct test_map *node)
{
    struct timer timer;
    printf("%s%s%s\n", "\033[1;37mRunning timer \"\033[1;34m", node->name, "\033[1;37m\"");
    start_timer(&timer);
    test_run_test(node);
    stop_timer(&timer);
    printf("User time: ");
    print_elapsed(timer.user.elapsed);
    printf("CPU time: ");
    print_elapsed(timer.cpu.elapsed);
    return true;
}

static bool execute_unit_test(struct test_map *node)
{
    printf("%s%s%s\n", "\033[1;37mRunning test \"\033[1;34m", node->name, "\033[1;37m\"");
    if (test_run_test(node))
    {
        printf("%s\n", "\033[0;32m----------------");
        printf("%s\n", "| Test succeed |");
        printf("%s\n", "----------------\033[0m");
        return true;
    }
    printf("%s\n", "\033[0;31m---------------");
    printf("%s\n", "| Test failed |");
    printf("%s\n", "---------------\033[0m");
    return false;
}

static int treat_unit_test_result(unsigned int success, unsigned int fail)
{
    unsigned int nbTest = success + fail;
    int percent = (success * 100) / nbTest;
    if (percent <= 33)
        printf("%s", "\033[1;31m");
    else if (percent <= 66)
        printf("%s", "\033[1;33m");
    else
        printf("%s", "\033[1;32m");
    printf("%d%% test passed (%d/%d)\033[0m\n", percent, success, nbTest);
    return fail;
}

static int run_test_map(int ac, char **av, struct test_map *map, const char *type,
                        bool (*execute_test)(struct test_map *),
                        int (*treat_result)(unsigned int, unsigned int))
{
    unsigned int fail = 0;
    unsigned int success = 0;
    if (ac > 1)
    {
        for (int n = 1; n < ac; ++n)
        {
            struct test_map *tmp = map;
            while (tmp != NULL)
            {
                if (strcmp(tmp->name, av[n]) == 0)
                {
                    if (execute_test(tmp))
                        ++success;
                    else
                        ++fail;
                    tmp = NULL;
                }
                else
                    tmp = tmp->next;
            }
        }
    }
    else
    {
        struct test_map *tmp = map;
        while (tmp != NULL)
        {
            if (execute_test(tmp))
                ++success;
            else
                ++fail;
            tmp = tmp->next;
        }
    }
    if ((fail + success) != 0)
    {
        if (treat_result != NULL)
            return treat_result(success, fail);
        return 0;
    }
    printf("\033[1;31mNo %s selected\033[0m\n", type);
    return 1;
}

int run_test(int ac, char **av)
{
    int ret = 1;
    if (unitTest.size != 0)
    {
        ret = run_test_map(ac, av, unitTest.map, "test", &execute_unit_test, &treat_unit_test_result);
        destroy_map(unitTest.map);
        unitTest.size = 0;
    }
    if (timeTest.size != 0)
    {
        run_test_map(ac, av, timeTest.map, "timer", &execute_timer_test, NULL);
        destroy_map(timeTest.map);
        timeTest.size = 0;
    }
    return ret;
}