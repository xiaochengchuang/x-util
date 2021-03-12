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

char *XMemStrdup(const char *str)
{
    char *result;
    int len;
    if (str == NULL)
    {
        return NULL;
    }

    len = strlen(str);
    result = (char *)XMapMalloc(len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    strncpy(result, str, len);
    result[len] = '\0';
    return result;
}

char *XMemStrndup(const char *str, size_t n)
{
    char *result;
    int len;
    if (str == NULL)
    {
        return NULL;
    }

    len = strlen(str);
    len = len > n ? n : len;
    result = (char *)XMapMalloc(len + 1);
    if (result == NULL)
    {
        return NULL;
    }

    strncpy(result, str, len);
    result[len] = '\0';
    return result;
}