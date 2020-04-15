#ifndef XMALLOC_H
#define XMALLOC_H

void *__xmalloc(size_t size, char *file, int line);
#define xmalloc(SIZE) __xmalloc(SIZE, __FILE__, __LINE__)

void __xfree(void *mem, char *file, int line);
#define xfree(MEM) __xfree(MEM, __FILE__, __LINE__)

void xmalloc_status();

#endif // XMALLOC_H
