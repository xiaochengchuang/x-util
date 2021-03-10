#include <stdlib.h>
#include <stddef.h>

void *XMemAlloc(size_t size)
{
    return malloc(size);
}

void *XMemAllocSafe(size_t size)
{
    void *addr;
    if (size <= 0)
    {
        return NULL;
    }
    addr = XMemAlloc(size);
    if (addr)
    {
        memset(addr, 0, size);
    }
    return addr;
}

void *XMemCalloc(size_t n, size_t size)
{
    return XMemAllocSafe(n * size);
}

void XMemFree(void *addr)
{
    if (addr)
    {
        free(addr);
    }
}