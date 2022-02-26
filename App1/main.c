//
//  main.c
//  App1 - Normal application with multiple threads
//
//  Copyright (c) 2015 - 2022 Software Diagnostics Services. All rights reserved.
//
//  Build:
//
//  	gcc main.c -pthread -static -o App1
//  	gcc main.c -pthread -o App1.shared
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define THREAD_DECLARE(num) void bar_##num()\
{\
    sleep(-1);\
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

THREAD_DECLARE(one)
THREAD_DECLARE(two)
THREAD_DECLARE(three)
THREAD_DECLARE(four)
THREAD_DECLARE(five)

#define THREAD_CREATE(num) {pthread_t threadID_##num; pthread_create (&threadID_##num, NULL, thread_##num, NULL);}

int main(int argc, const char * argv[])
{
    THREAD_CREATE(one)
    THREAD_CREATE(two)
    THREAD_CREATE(three)
    THREAD_CREATE(four)
    THREAD_CREATE(five)    
    
    sleep(-1);
    return 0;
}
