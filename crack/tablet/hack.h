#pragma once

#include <stdlib.h>

size_t proghash (const char* buf, size_t cnt);

size_t uploadprogramm (char** buf, const char* filename);

bool isnothacked (const char* prog);

