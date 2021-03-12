#ifndef X_MAP_H
#define X_MAP_H

#include <stdbool.h>

#include "x_list.h"

#define X_MAP_UPDATE 1
#define X_MAP_SUCCESS 0
#define X_MAP_NOT_FOUND -1
#define X_MAP_NO_MEM -2
#define X_MAP_ERR_ARG -2

struct _XMap;
typedef struct _XMap XMap;
typedef struct _XMap XMapPair;

#ifdef __cplusplus
extern "C"
{
#endif

XMap *XMapNew();

void XMapDelete(XMap *map);

int XMapPut(XMap *map, const char *key, const void *value);

int XMapGet(XMap *map, const char *key, void **outValue);

bool XMapIsContains(XMap *map, const char *key);

int XMapRemove(XMap *map, const char *key);

XMapPair *XMapGetFirstPair(XMap *map);

XMapPair *XMapPairGetNext(XMapPair *mapPair);

const char *XMapPairGetKey(XMapPair *mapPair);

void *XMapPairGetValue(XMapPair *mapPair);

#ifdef __cplusplus
}
#endif

#endif //X_MAP_H