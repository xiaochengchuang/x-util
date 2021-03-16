#include <string.h>

#include "x_list.h"
#include "x_map.h"

#ifdef X_MAP_USE_X_MEM
#include "x_mem.h"
#include "x_mem_str.h"
#define XMapMalloc XMemAlloc
#define XMapCalloc XMemCalloc
#define XMapFree XMemFree
#define XMapStrdup XMemStrdup
#else
#include <stdlib.h>
#define XMapMalloc malloc
#define XMapCalloc calloc
#define XMapFree free
#define XMapStrdup strdup
#endif

struct _XMap
{
    XListNode list;
    char *key;
    void *value;
};

XMap *XMapNew()
{
    XMap *map;
    map = (XMap *)XMapCalloc(1, sizeof(XMap));
    if (map != NULL)
    {
        XListHeadInit(&map->list);
    }
    return map;
}

int XMapPut(XMap *map, const char *key, const void *value)
{
    char *keyCopy;
    XMap *mapTmp;
    XListNode *head, *node;

    if (map == NULL || key == NULL)
    {
        return X_MAP_ERR_ARG;
    }

    head = &map->list;
    XListForeach(head, node)
    {
        mapTmp = XListNodeGetStruct(node, XMap, list);
        if (strcmp(key, mapTmp->key) == 0)
        {
            mapTmp->value = value;
            return X_MAP_UPDATE;
        }
    }

    mapTmp = (XMap *)XMapCalloc(1, sizeof(XMap));
    if (mapTmp == NULL)
    {
        return X_MAP_NO_MEM;
    }

    keyCopy = XMapStrdup(key);
    if (keyCopy == NULL)
    {
        XMapFree(mapTmp);
        return X_MAP_NO_MEM;
    }

    XListNodeInit(&mapTmp->list);
    mapTmp->key = keyCopy;
    mapTmp->value = value;
    XListAddTail(head, &mapTmp->list);
    return X_MAP_SUCCESS;
}

int XMapGet(XMap *map, const char *key, void **outValue)
{
    XMap *mapTmp;
    XListNode *head, *node;

    if (map == NULL || key == NULL || outValue == NULL)
    {
        return X_MAP_ERR_ARG;
    }

    head = &map->list;
    XListForeach(head, node)
    {
        mapTmp = XListNodeGetStruct(node, XMap, list);
        if (strcmp(key, mapTmp->key) == 0)
        {
            *outValue = mapTmp;
            return X_MAP_SUCCESS;
        }
    }
    *outValue = NULL;
    return X_MAP_NOT_FOUND;
}

bool XMapIsContains(XMap *map, const char *key)
{
    void *outValue;
    if (map == NULL || key == NULL)
    {
        return X_MAP_ERR_ARG;
    }
    return XMapGet(map, key, &outValue) == X_MAP_SUCCESS ? true : false;
}

int XMapRemove(XMap *map, const char *key)
{
    XMap *mapTmp;
    XListNode *head, *node, *tmpNode;

    if (map == NULL || key == NULL)
    {
        return X_MAP_ERR_ARG;
    }

    head = &map->list;
    XListForeachSafe(head, node, tmpNode)
    {
        mapTmp = XListNodeGetStruct(node, XMap, list);
        if (strcmp(key, mapTmp->key) == 0)
        {
            XListRemove(node);
            XMapFree(mapTmp->key);
            XMapFree(mapTmp);
            return X_MAP_SUCCESS;
        }
    }

    return X_MAP_NOT_FOUND;
}

void XMapDelete(XMap *map)
{
    XMap *mapTmp;
    XListNode *head, *node, *tmpNode;

    if (map == NULL)
    {
        return X_MAP_ERR_ARG;
    }

    head = &map->list;
    XListForeachSafe(head, node, tmpNode)
    {
        mapTmp = XListNodeGetStruct(node, XMap, list);
        XListRemove(node);
        XMapFree(mapTmp->key);
        XMapFree(mapTmp);
    }

    XMapFree(map);
    return X_MAP_SUCCESS;
}

int XMapGetFirstPair(XMap *map, XMapPair **outMapPair)
{
    XListNode *firstNode;
    XMapPair *result = NULL;

    if (outMapPair == NULL)
    {
        return X_MAP_ERR_ARG;
    }

    if (mapPair == NULL)
    {
        outMapPair = NULL;
        return X_MAP_ERR_ARG;
    }

    firstNode = XListFirst(&map->list);
    if (firstNode == NULL)
    {
        *outMapPair = NULL;
        return X_MAP_NOT_FOUND;
    }

    *outMapPair = (XMapPair *)(XListNodeGetStruct(firstNode, XMap, list));
    return X_MAP_SUCCESS;
}

int XMapPairGetNext(XMapPair *mapPair, XMapPair **outMapPair)
{
    XListNode *nextNode;
    XMapPair *result = NULL;

    if (outMapPair == NULL)
    {
        return X_MAP_ERR_ARG;
    }

    if (mapPair == NULL)
    {
        outMapPair = NULL;
        return X_MAP_ERR_ARG;
    }

    nextNode = XListNext(&mapPair->list);
    if (nextNode == NULL)
    {
        *outMapPair = NULL;
        return X_MAP_NOT_FOUND;
    }

    *outMapPair = (XMapPair *)(XListNodeGetStruct(nextNode, XMapPair, list));
    return X_MAP_SUCCESS;
}

int XMapPairGetKey(XMapPair *mapPair, char **outKey)
{
    if (outKey == NULL)
    {
        return X_MAP_ERR_ARG;
    }

    if (mapPair == NULL)
    {
        outMapPair = NULL;
        return X_MAP_ERR_ARG;
    }

    *outKey = mapPair->key;
    return X_MAP_SUCCESS;
}

int XMapPairGetValue(XMapPair *mapPair, void **outValue)
{
    if (outValue == NULL)
    {
        return X_MAP_ERR_ARG;
    }

    if (mapPair == NULL)
    {
        outMapPair = NULL;
        return X_MAP_ERR_ARG;
    }

    *outValue = mapPair->value;
    return X_MAP_SUCCESS;
}