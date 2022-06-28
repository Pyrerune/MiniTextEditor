#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "buffer.h"

char* buffer;
char null = 0;
long size = 0;
int fd = -1;
long counter = 0;


void f_init(char* filename)
{
    if (filename == NULL)
    {
        char file[] = "temp.XXXXXX";
        fd = mkstemp(file);
    }
    else
    {
        fd = open(filename, O_RDWR | O_CREAT, 666);
    }
}

void b_add(char e)
{
    if (counter > size)
    {
        b_resize(255);
    }
    *(buffer + counter) = e;
    counter++;
}

void b_del()
{
    if (counter == 0)
    {
        printf("Error: b_del() went out of bounds");
        exit(1);
    }
    counter--;
    *(buffer + counter) = null;
}

void b_delf()
{
    if (counter + 1 > size)
    {
        printf("Error: b_del() went out of bounds");
        exit(1);
    }
    *(buffer + counter + 1) = null;
}

void b_deli(int d)
{
    *(buffer + d) = null;
}

void b_free()
{
    munmap(buffer, size);
    close(fd);
}

void b_resize(int bytes)
{
    ftruncate(fd, size + bytes);
    buffer = mremap(buffer, size, size + bytes, MREMAP_MAYMOVE);
    size += bytes;
}

void b_init(char* filename)
{
    f_init(filename);
    struct stat file;

    if (fstat(fd, &file) == -1)
    {
        perror("Error getting file size.\n");
    }
    else
    {
        size = file.st_size;
        if (size == 0)
        {
            ftruncate(fd, 255);
            size = 255;
        } else {
            counter = size;
        }
        buffer = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

        if (buffer == MAP_FAILED)
        {
            perror("Failed to map file in memory.  \n");
            exit(-1);
        }
    }
}
