//
//  main.c
//  App0 - Exercise 0 - Testing Linux GDB
//
//  Copyright (c) 2015 - 2022 Software Diagnostics Services. All rights reserved.
//
//  Build:
//
//      gcc main.c -pthread -static -o App0
//

#include <stdlib.h>

void bar()
{
    abort();
}

void foo()
{
    bar();
}

int main(int argc, const char * argv[])
{
    foo();
    return 0;
}
