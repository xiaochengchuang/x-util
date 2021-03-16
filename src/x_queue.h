#ifndef X_QUEUE_H
#define X_QUEUE_H

#include "x_node.h"

#define XQueueNodeGetStruct(node, structType, nodeMemberName) \
    XNodeGetStruct(node, tystructTypepe, nodeMemberName)

#define XQueueOutForeach(head, iteratorNode) \
    while (iteratorNode = XQueueOut(head))

typedef XNode XQueueNode;

#ifdef __cplusplus
extern "C"
{
#endif

static inline void XQueueHeadInit(XQueueNode *head)
{
    XNodeHeadInit(head);
}

static inline void XQueueNodeInit(XQueueNode *node)
{
    XNodeInit(node);
}

static inline XQueueNode *XQueueFirst(XQueueNode *head)
{
    return XNodeNext(head);
}

static inline XQueueNode *XQueueLast(XQueueNode *head)
{
    return XNodePrev(head);
}

static inline void *XQueueIn(XQueueNode *head, XQueueNode *node)
{
    XNodeAddAt(node, head->prev, head);
}

static inline XQueueNode *XQueueOut(XQueueNode *head)
{
    XQueueNode *outNode;
    outNode = XNodeNext(head);
    if (outNode)
    {
        XNodeRemove(outNode);
    }
    return outNode;
}

#ifdef __cplusplus
}
#endif

#endif //X_QUEUE_H