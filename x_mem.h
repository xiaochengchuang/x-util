#ifndef X_MEM_H
#define X_MEM_H

#include <stddef.h>

#define XMemFreeSafe(addr) \
    do                     \
    {                      \
        XMemFree(addr);    \
        addr = NULL;       \
    } while (0)

#ifdef __cplusplus
extern "C"
{
#endif

void *XMemAlloc(size_t size);

void *XMemAllocSafe(size_t size);

void *XMemCalloc(size_t n, size_t size);

void XMemFree(void *addr);

#ifdef __cplusplus
}
#endif

#endif //X_MEM_H