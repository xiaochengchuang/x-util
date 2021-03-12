#ifndef X_LIST_H
#define X_LIST_H

#include "x_node.h"

#define XListNodeGetStruct(node, structType, nodeMemberName) \
    XNodeGetStruct(node, structType, nodeMemberName)

#define XListForeach(head, iteratorNode)  \
    for (iteratorNode = XListFirst(head); \
         iteratorNode != NULL;            \
         iteratorNode = XListNext(iteratorNode))

/* safe for XListRemove */
#define XListForeachSafe(head, iteratorNode, tmpNode)                                                        \
    for (iteratorNode = XListFirst(head), tmpNode = (iteratorNode == NULL ? NULL : XListNext(iteratorNode)); \
         iteratorNode != NULL;                                                                               \
         iteratorNode = tmpNode, tmpNode = (iteratorNode == NULL ? NULL : XListNext(iteratorNode)))

typedef XNode XListNode;

#ifdef __cplusplus
extern "C"
{
#endif

static inline void XListHeadInit(XListNode *head)
{
    XNodeHeadInit(head);
}

static inline void XListNodeInit(XListNode *node)
{
    XNodeInit(node);
}

static inline int XListNodeIsHead(XListNode *node)
{
    return XNodeIsHead(node);
}

static inline XListNode *XListFirst(XListNode *head)
{
    return XNodeNext(head);
}

static inline XListNode *XListLast(XListNode *head)
{
    return XNodePrev(head);
}

static inline XListNode *XListNext(XListNode *node)
{
    return XNodeNext(node);
}

static inline XListNode *XListPrev(XListNode *node)
{
    return XNodePrev(node);
}

static inline void XListAddTail(XListNode *head, XListNode *node)
{
    XNodeAddAt(node, head->prev, head);
}

static inline void XListAddHead(XListNode *head, XListNode *node)
{
    XNodeAddAt(node, head, head->next);
}

static inline void XListAdd(XListNode *head, XListNode *node)
{
    XListAddTail(head, node);
}

static inline void XListRemove(XListNode *node)
{
    XNodeRemove(node);
}

#ifdef __cplusplus
}
#endif

#endif //X_LIST_H