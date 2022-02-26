//
//  main.c
//  App4 - Heap Corruption pattern
//
//  Copyright (c) 2015 - 2022 Software Diagnostics Services. All rights reserved.
//
//  Build:
//
//      gcc main.c -pthread -static -o App4 
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void proc()
{
    sleep(1);
	
    char *p1 = (char *) malloc (256);
    char *p2 = (char *) malloc (256);
    char *p3 = (char *) malloc (256);
    char *p4 = (char *) malloc (256);
    char *p5 = (char *) malloc (256);
    char *p6 = (char *) malloc (256);
    char *p7 = (char *) malloc (256);
    
    free(p6);
    free(p4);
    free(p2);
    
    strcpy(p2, "Hello Crash2! Hello Crash2! Hello Crash2! Hello Crash2! Hello Crash2!");
    strcpy(p4, "Hello Crash4! Hello Crash4! Hello Crash4! Hello Crash4! Hello Crash4! Hello Crash4!");
    strcpy(p6, "Hello Crash6! Hello Crash6! Hello Crash6! Hello Crash6! Hello Crash6! Hello Crash6! Hello Crash6!");
    
    p2 = (char *) malloc (256);
    p4 = (char *) malloc (256);
    p6 = (char *) malloc (256);
    
    sleep(300);
    
    free (p7);
    free (p6);
    free (p5);    
    free (p4);
    free (p3);
    free (p2);
    free (p1);

    sleep(-1);
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
THREAD_DECLARE(two,sleep(-1))
THREAD_DECLARE(three,proc())
THREAD_DECLARE(four,sleep(-1))
THREAD_DECLARE(five,sleep(-1))

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
