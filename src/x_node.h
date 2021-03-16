#ifndef X_NODE_H
#define X_NODE_H

#include <stddef.h>

#define XNodeOffsetOf(structType, nodeMember) \
    ((size_t) & ((nodeMember *)0)->nodeMember)
#define XNodeGetStruct(node, structType, nodeMemberName) \
    (structType *)((node) == NULL ? NULL : ((char *)(node) - XNodeOffsetOf(structType, nodeMemberName)))

struct _XNode
{
    int isHead;          /*indicates whether it is a head node*/
    struct _XNode *prev; /*point to prev node*/
    struct _XNode *next; /*point to next node*/
};

typedef struct _XNode XNode;

#ifdef __cplusplus
extern "C"
{
#endif

static inline void XNodeHeadInit(XNode *head)
{
    head->next = head->prev = head;
    head->isHead = 1;
}

static inline void XNodeInit(XNode *node)
{
    node->next = node->prev = NULL;
    node->isHead = 0;
}

static inline int XNodeIsHead(XNode *node)
{
    return node->isHead;
}

static inline XNode *XNodeNext(XNode *node)
{
    return (node->next == NULL || node->next->isHead) ? NULL : node->next;
}

static inline XNode *XNodePrev(XNode *node)
{
    return (node->prev == NULL || node->prev->isHead) ? NULL : node->prev;
}

static inline void XNodeAddAt(XNode *node, XNode *prevNode, XNode *nextNode)
{
    node->prev = prevNode;
    node->next = nextNode;
    if (prevNode)
    {
        prevNode->next = node;
    }
    if (nextNode)
    {
        nextNode->prev = node;
    }
}

static inline void XNodeRemove(XNode *node)
{
    XNode *prevNode, *nextNode;
    prevNode = node->prev;
    nextNode = node->next;
    if (prevNode)
    {
        prevNode->next = nextNode;
    }
    if (nextNode)
    {
        nextNode->prev = prevNode;
    }
    node->prev = NULL;
    node->next = NULL;
}

#ifdef __cplusplus
}
#endif

#endif //X_NODE_H