#include "hack.h"

#include <stdio.h>

int main () {
    char* prog = NULL;
    size_t cnt = uploadprogramm(&prog, "PSD.COM");

    printf("%lu\n", proghash(prog, cnt));
    return 0;
}