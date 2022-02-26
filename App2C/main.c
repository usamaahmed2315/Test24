//
//  main.c
//  App2C - Shows NULL code pointer exception
//
//  Copyright (c) 2015 - 2022 Software Diagnostics Services. All rights reserved.
//
//  Build:
//
//  	gcc main.c -pthread -static -o App2C
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void procA()
{
    sleep(2);

    int *p = NULL;

    *p = 1;
}

void procB()
{
    sleep(1);

    void (*pf)() = NULL;
    
    pf();
}

#define THREAD_DECLARE(num,func) void bar_##num()\
{\
func;\
}\
\
void foo_##num()\
{\
bar_##num();\
}\
\
void * thread_##num (void *arg)\
{\
foo_##num();\
\
return 0;\
}

THREAD_DECLARE(one,sleep(-1))
THREAD_DECLARE(two,procA())
THREAD_DECLARE(three,sleep(-1))
THREAD_DECLARE(four,procB())
THREAD_DECLARE(five,sleep(-1))

#define THREAD_CREATE(num) {pthread_t threadID_##num; pthread_create (&threadID_##num, NULL, thread_##num, NULL);}

int main(int argc, const char * argv[])
{
    THREAD_CREATE(one)
    THREAD_CREATE(two)
    THREAD_CREATE(three)
    THREAD_CREATE(four)
    THREAD_CREATE(five)    
    
    sleep(3);
    return 0;
}
