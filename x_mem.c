#include "x_mem.h"

void *XMemAlloc(size_t size)
{
    if (size == 0)
    {
        return NULL;
    }

    return malloc(size);
}

void *XMemAllocSafe(size_t size)
{
    void *addr;
    if (size == 0)
    {
        return NULL;
    }

    addr = XMemAlloc(size);
    if (addr != NULL)
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
    if (addr != NULL)
    {
        free(addr);
    }
}