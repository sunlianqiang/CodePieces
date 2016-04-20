/* 
   链表的定义有两种

   单链表反转主要分为以下几种方法：
   单链表反转-带头节点

   方法1：存储逆序法。将单链表储存为数组(或其他结构)，然后按照数组的索引逆序进行反转。
   使用C语言中的数组来存储时需要先知道数组的大小，而且需要申请不小于链表长度大小的数组，并需要遍历两次进行存取；时间和空间效率都不高
   使用C++ STL 中的stack, vector结构更方便，不需要先知道链表的大小，但是C++中本来就有STL list, 没有什么现实意义

   方法2：指针反转法。使用三个指针遍历单链表，逐个链接点进行反转。

   方法3：头插法。从第2个节点到第N个节点，依次逐节点插入到第1个节点(head节点)之后，最后将第一个节点挪到新表的表尾。

   方法4： 递归法。传入两个链表，实现方法是从第一个链表中取头部之后的元素，插入第二个链表头部之后，最后返回第二个链表。

   方法5： 头插法，定义了头部插入函数，可以将元素插入链表头之后；直接调用头部插入函数实现。
   */

#include <stdio.h>
#include <stdlib.h>
//#include <iostream>
//#include <stack>

//using namespace std;

//C 语言中 struct ListNode* next; 的struct不能省略，否则找不到类型，C++可以
//C语言想用结构体前边必须加 struct，struct structName structPara;
//ListNode 另一种定义
///typedef struct ListNode{
///	int data;
///	struct ListNode* next;
///}Node, *List;

struct ListNode{
	int data;
	struct ListNode* next;
};
typedef struct ListNode Node;
typedef struct ListNode *List;

void PrintList(List head);
List ListReverse1(List head);
List ListReverse2(List head);
List ListReverse3(List head);
List ListReverse4(List head);
List ListReverse5(List head);

int main()
{
	//分配链表头结点
	Node *head;
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	head->data = -1;

	//将[1,10]加入链表
	Node *p, *q;
	p = head;
	for(int i = 1; i <= 10; i++)
	{
		q = (Node *)malloc(sizeof(Node));
		q->data = i;
		q->next = NULL;
		p->next = q;
		p = q;
	}

	PrintList(head); /*输出原始链表*/
	/*逆序链表*/
	head = ListReverse1(head);

	PrintList(head); /*输出逆序后的链表*/
	return 0;
}

List ListReverse1(List head)
{
	if(head->next == NULL || head->next->next == NULL)
	{
		return head; 
	}

	int arr[100] = {0};

	Node *p = head->next;
	int ai = 0;

	while(NULL != p)
	{
		arr[ai++] = p->data;
		p = p->next;
	}

	p = head->next;

	while (NULL != p)
	{
		p->data = arr[--ai];
		p = p->next;
	}

	return head;
}

//使用C++ stack
/*链表为空或只有一个元素则直接返回*/
/*
List ListReverse1(List head)
{
	if(head->next == NULL || head->next->next == NULL)
	{
		return head; 
	}

	stack<int> stkList;
	List pNode = head->next;
	while(pNode!=NULL) {
		stkList.push(pNode->data);
		pNode=pNode->next;
	}

	pNode=head->next;
	while(pNode!=NULL) {
		pNode->data = stkList.top();
		stkList.pop();
		pNode = pNode->next;
	}
	return head;
}
*/

//2 指针反转法
List ListReverse2(List head)
{
	if(head->next == NULL || head->next->next == NULL)
	{
		return head; /*链表为空或只有一个元素则直接返回*/
	}
	// h->p->q
	Node *t = NULL, *p, *q;
	p = head->next;
	q = head->next->next;
	while(q != NULL)
	{
		// h->p->q->t->NULL
		t = q->next;
		// h->p<-q t->NULL
		q->next = p;
		p = q;
		q = t;
	}
	//h->...->p q->NULL
	/*此时p指向原始链表最后一个元素，也是逆转后的链表的表头元素*/
	head->next->next = NULL; /*设置链表尾*/
	head->next = p; /*调整链表头*/
	return head;
}
// 3 头插法
List ListReverse3(List head)
{
	if(head->next == NULL || head->next->next == NULL)
	{
		return head; /*链表为空或只有一个元素则直接返回*/
	}
	// h->p->q
	Node *t, *p, *q;
	p = head->next;
	q = head->next->next;
	// h->p->NULL， p为尾指针
	p->next=NULL;
	while(q != NULL)
	{
		// h->p->q->t->NULL
		t = q->next;
		// h->p<-q t->NULL
		q->next=p;
		head->next = q;
		p = head->next;
		q = t;
	}

	return head;
}

// 4 递归法
List ReverseRecursion(List head, List newHead)
{
	if (head->next == NULL)
	{
		return newHead;
	}
	else {
		List p;
		// head 中去掉p
		p = head->next;
		head->next = head->next->next;
		// newHead 中加上p
		p->next = newHead->next;
		newHead->next = p;
		//递归调用
		ReverseRecursion(head, newHead);
	}
}

List ListReverse4(List head)
{
	if(head->next == NULL || head->next->next == NULL)
	{
		return head; /*链表为空或只有一个元素则直接返回*/
	}
	else {
		List newHead = (List)malloc(sizeof(Node));
		newHead->next = NULL;
		ReverseRecursion(head, newHead);
	}
}

List ListInsertSecond(List head, Node *tmp)
{
	Node *p = head->next;
	head->next = tmp;
	tmp->next = p;
}

List ListReverse5(List head)
{
	if (NULL == head->next || NULL == head->next->next)
		return head;

	Node * p = head->next;
	head->next = NULL;
	while (NULL != p)
	{
		Node *q = p->next;
		ListInsertSecond(head, p);
		p = q;
	}

	return head;
}

void PrintList(List head)
{

	Node* p = head->next;
	while(p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
} 
