#ifndef MEMORY_H
#define MEMORY_H
#include <stddef.h>

void* memset(void* ptr, int c, size_t size);
void* memcpy(void* dest, void* src, int len);
int memcmp(void* s1, void* s2, int count);

#endif
