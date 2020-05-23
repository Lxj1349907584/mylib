#include "doubly_linked_list.h"

//创建链表
void ListInit(List *linkList, int dataSize, ListOps ops)
{
	linkList->head = NULL;
	linkList->tail = NULL;
	linkList->dataSize = dataSize;
	linkList->ops.dataCmp = ops.dataCmp;
	linkList->ops.dataDisplay = ops.dataDisplay;
	linkList->ops.seekByKey = ops.seekByKey;
	linkList->ops.dataAssign = ops.dataAssign;
}

//释放节点
void FreeNode(Node *node)
{
	free(node->data);
	free(node);
}

//判空
BOOL IsEmpty(const List *linkList)
{
	return (linkList->head == NULL) && (linkList->tail == NULL); 
}

//大小
size_t Size(const List *linkList)
{
	size_t nodes = 0;
	Node *node = NULL;
	for (node = linkList->head; node; node = node->next) {
		nodes++;
	}
	return nodes;
}

//从首部压入
void PushFront(List *linkList, void *data)
{
	Node *tmpNode = (Node*)malloc(sizeof(Node));
	tmpNode->data = malloc(linkList->dataSize);
	linkList->ops.dataAssign(tmpNode->data, data);
	tmpNode->prev = NULL;
	tmpNode->next = linkList->head;
	if (tmpNode->next != NULL) {
		tmpNode->next->prev = tmpNode;
	} else {
		linkList->tail = tmpNode;
	}
	linkList->head = tmpNode;
}

//从首部弹出
void PopFront(List *linkList)
{
	if (IsEmpty(linkList)) {
		return;
	} 
	Node *next = linkList->head->next;
	FreeNode(linkList->head);
	linkList->head = next;
	if (linkList->head != NULL) {
		linkList->head->prev = NULL;
	} else {
		linkList->tail = NULL;
	}
}

//获取首元素
void GetFront(List *linkList, void *outData) 
{
	if (IsEmpty(linkList)) {
		return; 
	}
	linkList->ops.dataAssign(outData, linkList->head->data);
}

//从尾部压入
void PushBack(List *linkList, void *data)
{
	Node *tmpNode = (Node*)malloc(sizeof(Node));
	tmpNode->data = malloc(linkList->dataSize);
	linkList->ops.dataAssign(tmpNode->data, data);
	tmpNode->prev = linkList->tail;
	tmpNode->next = NULL;
	if (tmpNode->prev != NULL) {
		tmpNode->prev->next = tmpNode;
	} else {
		linkList->head = tmpNode;
	}
	linkList->tail = tmpNode;
}

//从尾部弹出
void PopBack(List *linkList)
{
	if (IsEmpty(linkList)) {
		return;
	}
	Node *prev = linkList->tail->prev;
	FreeNode(linkList->tail);
	linkList->tail = prev;
	if (linkList->tail != NULL) {
		linkList->tail->next = NULL;
	} else {
		linkList->head = NULL;
	}
}

//获取尾巴元素
void GetBack(List *linkList, void *outData)
{
	if (IsEmpty(linkList)) {
		return;
	}
	linkList->ops.dataAssign(outData, linkList->tail->data);
}

void ShowList(const List *linkList)
{
	Node *node = NULL;
	for (node = linkList->head; node; node = node->next) {
		linkList->ops.dataDisplay(node->data);
	}
}

//清空
void Clear(List *linkList)
{
	while(IsEmpty(linkList) != TURE) {
		PopBack(linkList);
	}
}


//删除所有的匹配元素
void RemoveNode(List *linkList, void *data)
{
	Node *node = NULL;
	Node *next = NULL;
	for (node = linkList->head, next = NULL; node; node = next) {
		next = node->next;
		if (linkList->ops.dataCmp(node->data, data) == 0) {
			if (node->prev != NULL) {
				node->prev->next = node->next;
			} else {
				linkList->head = node->next;
			}
			
			if (node->next != NULL) {
				node->next->prev = node->prev;
			} else {
				linkList->tail = node->prev;
			}
			FreeNode(node);
		}
	}
}
