/* 
   单链表反转主要分为以下几种方法：
   单链表反转-带头节点

   方法1：存储逆序法。将单链表储存为数组，然后按照数组的索引逆序进行反转。

   方法2：指针反转法。使用三个指针遍历单链表，逐个链接点进行反转。

   方法3：头插法。从第2个节点到第N个节点，依次逐节点插入到第1个节点(head节点)之后，最后将第一个节点挪到新表的表尾。

   方法4： 递归法。
   */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>

using namespace std;

typedef struct ListNode{
	int data;
	struct ListNode* next;
}Node, *List;

/*
struct ListNode{
	int data;
	ListNode* next;
};
typedef ListNode Node;
typedef ListNode *List;
*/

void PrintList(List head);
List ReverseList1(List head);
List ReverseList2(List head);
List ReverseList3(List head);
List ReverseList4(List head);

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
	head = ReverseList4(head);

	PrintList(head); /*输出逆序后的链表*/
	return 0;
}


List ReverseList1(List head)
{
	if(head->next == NULL || head->next->next == NULL)
	{
		return head; /*链表为空或只有一个元素则直接返回*/
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
//2 指针反转法
List ReverseList2(List head)
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
List ReverseList3(List head)
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
List ReverseList4(List head)
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
