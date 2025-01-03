#ifndef HEAP_H
#define HEAP_H


#define HEAP_SIZE 104857600
#define HEAP_BLOCK_SIZE 4096
#define HEAP_START_ADDRESS 0xD0000000

#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define HEAP_BLOCK_TABLE_ENTRY_FREE  0x00

#define HEAP_BLOCK_HAS_NEXT 0b10000000
#define HEAP_BLOCK_IS_FIRST 0b01000000

#include <stdint.h>
#include <stddef.h>
#include "../../../../libk/stdiok.h"

typedef uint8_t HEAP_BLOCK_TABLE_ENTRY;

struct heap_table{
    HEAP_BLOCK_TABLE_ENTRY* entries;
    size_t total_blocks;
};

struct heap
{
    struct heap_table* table;
    void* start_address;
};

void heap_init();
void* kmalloc(size_t size);
void kfree(void* ptr);
void* kzalloc(size_t size);
void heap_contract(struct heap *heap);
bool heap_expand(struct heap *heap, size_t size);
void test_heap_shrink_and_reuse();

#endif
