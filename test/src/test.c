#include "test.h"

struct test_map
{
    char *name;
    void (*fct)();
    struct test_map *next;
};

struct test_map *unitTest = NULL;

void test_register(const char *name, void (*fct)())
{
    struct test_map *tmp = unitTest;
    struct test_map *prev = unitTest;
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
        unitTest = newNode;
    else
        prev->next = newNode;
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

static void destroy_test_map(struct test_map *node)
{
    free(node->name);
    if (node->next != NULL)
        destroy_test_map(node->next);
    free(node);
}

static bool test_run_test(struct test_map *node)
{
    printf("%s%s%s\n", "\033[1;37mRunning test \"\033[1;34m", node->name, "\033[1;37m\"");
    sleep(1);
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

int run_test(int ac, char **av)
{
    unsigned int fail = 0;
    unsigned int success = 0;
    unsigned int nbTest = 0;
    if (ac > 1)
    {
        for (int n = 1; n < ac; ++n)
        {
            struct test_map *tmp = unitTest;
            while (tmp != NULL)
            {
                if (strcmp(tmp->name, av[n]) == 0)
                {
                    if (test_run_test(tmp))
                        ++success;
                    else
                        ++fail;
                    ++nbTest;
                    tmp = NULL;
                }
                else
                    tmp = tmp->next;
            }
        }
    }
    else
    {
        struct test_map *tmp = unitTest;
        while (tmp != NULL)
        {
            if (test_run_test(tmp))
                ++success;
            else
                ++fail;
            ++nbTest;
            tmp = tmp->next;
        }
    }
    if (nbTest != 0)
    {
        int percent = (success * 100) / nbTest;
        if (percent <= 33)
            printf("%s", "\033[1;31m");
        else if (percent <= 66)
            printf("%s", "\033[1;33m");
        else
            printf("%s", "\033[1;32m");
        printf("%d%% test passed (%d/%d)\033[0m\n", percent, success, nbTest);
        destroy_test_map(unitTest);
        return fail;
    }
    printf("%s\n", "\033[1;31mNo test selected\033[0m");
    destroy_test_map(unitTest);
    return 1;
}