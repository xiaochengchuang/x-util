#ifndef X_MEM_STR_H
#define X_MEM_STR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

char *XMemStrdup(const char *str);

char *XMemStrndup(const char *str, size_t n);

#ifdef __cplusplus
}
#endif

#endif //X_MEM_STR_H