#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char *buffer;
    size_t size;
    size_t capacity;
    size_t position;
} MemoryFile;

MemoryFile *memfile_open(size_t initial_capacity) {
    MemoryFile *memfile = (MemoryFile *)malloc(sizeof(MemoryFile));
    memfile->buffer = (unsigned char *)malloc(initial_capacity);
    memfile->size = 0;
    memfile->capacity = initial_capacity;
    memfile->position = 0;
    return memfile;
}

size_t memfile_write(const void *ptr, size_t size, size_t count, MemoryFile *memfile) {
    size_t total_size = size * count;
    if (memfile->position + total_size > memfile->capacity) {
        memfile->capacity = (memfile->position + total_size) * 2;
        memfile->buffer = (unsigned char *)realloc(memfile->buffer, memfile->capacity);
    }
    memcpy(memfile->buffer + memfile->position, ptr, total_size);
    memfile->position += total_size;
    if (memfile->position > memfile->size) {
        memfile->size = memfile->position;
    }
    return count;
}

void memfile_close(MemoryFile *memfile) {
    free(memfile->buffer);
    free(memfile);
}

int main() {
    MemoryFile *memfile = memfile_open(1024);
    const char *text = "Hello, world!";
    memfile_write(text, sizeof(char), strlen(text), memfile);

    // Use the buffer
    fwrite(memfile->buffer, sizeof(char), memfile->size, stdout);

    memfile_close(memfile);
    return 0;
}
