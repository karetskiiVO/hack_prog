#include "hack.h"

#include <stdio.h>

int main () {
    char* prog = NULL;
    size_t cnt = uploadprogramm(&prog, "PASSWORD.COM");

    printf("%s\n%lu\n", prog, proghash(prog, cnt));
    return 0;
}