#ifndef TEST_H_
#define TEST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <unistd.h>

#define Test(x) void x()
#define STest(x) static void x()

#ifdef __cplusplus
#define CXXTest(nspace, x) void nspace::x()
extern "C" {
#endif
void timer_register(const char *name, void (*fct)());
void test_register(const char *name, void (*fct)());
void assert_true(bool test);
void assert_false(bool test);
int run_test(int ac, char **av);
#ifdef __cplusplus
}
#endif

#endif