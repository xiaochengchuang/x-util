#ifndef X_STACK_H
#define X_STACK_H

#include "x_node.h"

#define XStackNodeGetStruct(node, structType, nodeMemberName) \
    XNodeGetStruct(node, structType, nodeMemberName)

#define XStackPopForeach(head, iteratorNode) \
    while (iteratorNode = XStackPop(head))

typedef XNode XStackNode;

#ifdef __cplusplus
extern "C"
{
#endif

static inline void XStackHeadInit(XStackNode *head)
{
    XNodeHeadInit(head);
}

static inline void XStackNodeInit(XStackNode *node)
{
    XNodeInit(node);
}

static inline XStackNode *XStackTop(XStackNode *head)
{
    return XNodeNext(head);
}

static inline void *XStackPush(XStackNode *head, XStackNode *node)
{
    XNodeAddAt(node, head, head->next);
}

static inline XStackNode *XStackPop(XStackNode *head)
{
    XStackNode *outNode;
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

#endif //X_STACK_H