#include <stdlib.h>
#include <stdio.h>

#include "xmalloc.h"

#define MAX_MALLOC_NOT_FREE 255

struct xmalloc_s
{
    char *fileName;
    int line;
    void *ptr;
    size_t size;
} gMallocs[MAX_MALLOC_NOT_FREE] = {0};

void* __xmalloc(size_t size, char* file, int line)
{
    int i;
    void* mem = malloc(size);
    if(mem == 0)
        fprintf(stderr, "(xmalloc) Error : malloc error in file %s at line %d.\n", file, line);

    for(i=0; i<MAX_MALLOC_NOT_FREE; i++)
    {
        if(gMallocs[i].ptr == 0)
        {
            gMallocs[i].fileName = file;
            gMallocs[i].line = line;
            gMallocs[i].ptr = mem;
            gMallocs[i].size = size;
            break;
        }
    }

    if(i == MAX_MALLOC_NOT_FREE)    
        fprintf(stderr, "(xmalloc) Warning : xmalloc is full.\n");
    // else
    //     fprintf(stderr, "(xmalloc) Info: new malloc [%d][0x%p][%d][%s][%d]\n",
    //             i, gMallocs[i].ptr, gMallocs[i].size, 
    //             gMallocs[i].fileName, gMallocs[i].line);
    
    return mem;
}

void __xfree(void *mem, char* file, int line)
{
    int i;

    for(i=0; i<MAX_MALLOC_NOT_FREE; i++)
    {
        if(gMallocs[i].ptr == mem)
        {
            gMallocs[i].ptr = 0;
            break;
        }
    }

    if(i == MAX_MALLOC_NOT_FREE)
        fprintf(stderr, "(xmalloc) Error : free - can't find 0x%p in file %s at line %d.\n", mem, file, line);
    // else
    //     fprintf(stderr, "(xmalloc) Info : free of ptr 0x%p [%d] in file %s at line %d.\n", mem, i, file, line);

    free(mem);
}

void xmalloc_status()
{
    int i;
    fprintf(stderr, "(xmalloc) Status of current malloc:\n");

    for(i=0; i<MAX_MALLOC_NOT_FREE; i++)
    {
        if(gMallocs[i].ptr != 0)
        {
            fprintf(stderr, "[%d][0x%p][%d][%s][%d]\n",
                i, gMallocs[i].ptr, gMallocs[i].size, 
                gMallocs[i].fileName, gMallocs[i].line);
        }
    }

    fprintf(stderr, "(xmalloc) End of status.\n");
   
}