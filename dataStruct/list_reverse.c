/* 
   ����Ķ���������

   ������ת��Ҫ��Ϊ���¼��ַ�����
   ������ת-��ͷ�ڵ�

   ����1���洢���򷨡�����������Ϊ����(�������ṹ)��Ȼ�������������������з�ת��
   ʹ��C�����е��������洢ʱ��Ҫ��֪������Ĵ�С��������Ҫ���벻С�������ȴ�С�����飬����Ҫ�������ν��д�ȡ��ʱ��Ϳռ�Ч�ʶ�����
   ʹ��C++ STL �е�stack, vector�ṹ�����㣬����Ҫ��֪������Ĵ�С������C++�б�������STL list, û��ʲô��ʵ����

   ����2��ָ�뷴ת����ʹ������ָ�����������������ӵ���з�ת��

   ����3��ͷ�巨���ӵ�2���ڵ㵽��N���ڵ㣬������ڵ���뵽��1���ڵ�(head�ڵ�)֮����󽫵�һ���ڵ�Ų���±�ı�β��

   ����4�� �ݹ鷨��������������ʵ�ַ����Ǵӵ�һ��������ȡͷ��֮���Ԫ�أ�����ڶ�������ͷ��֮����󷵻صڶ�������

   ����5�� ͷ�巨��������ͷ�����뺯�������Խ�Ԫ�ز�������ͷ֮��ֱ�ӵ���ͷ�����뺯��ʵ�֡�
   */

#include <stdio.h>
#include <stdlib.h>
//#include <iostream>
//#include <stack>

//using namespace std;

//C ������ struct ListNode* next; ��struct����ʡ�ԣ������Ҳ������ͣ�C++����
//C�������ýṹ��ǰ�߱���� struct��struct structName structPara;
//ListNode ��һ�ֶ���
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
	//��������ͷ���
	Node *head;
	head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
	head->data = -1;

	//��[1,10]��������
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

	PrintList(head); /*���ԭʼ����*/
	/*��������*/
	head = ListReverse1(head);

	PrintList(head); /*�������������*/
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

//ʹ��C++ stack
/*����Ϊ�ջ�ֻ��һ��Ԫ����ֱ�ӷ���*/
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

//2 ָ�뷴ת��
List ListReverse2(List head)
{
	if(head->next == NULL || head->next->next == NULL)
	{
		return head; /*����Ϊ�ջ�ֻ��һ��Ԫ����ֱ�ӷ���*/
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
	/*��ʱpָ��ԭʼ�������һ��Ԫ�أ�Ҳ����ת�������ı�ͷԪ��*/
	head->next->next = NULL; /*��������β*/
	head->next = p; /*��������ͷ*/
	return head;
}
// 3 ͷ�巨
List ListReverse3(List head)
{
	if(head->next == NULL || head->next->next == NULL)
	{
		return head; /*����Ϊ�ջ�ֻ��һ��Ԫ����ֱ�ӷ���*/
	}
	// h->p->q
	Node *t, *p, *q;
	p = head->next;
	q = head->next->next;
	// h->p->NULL�� pΪβָ��
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

// 4 �ݹ鷨
List ReverseRecursion(List head, List newHead)
{
	if (head->next == NULL)
	{
		return newHead;
	}
	else {
		List p;
		// head ��ȥ��p
		p = head->next;
		head->next = head->next->next;
		// newHead �м���p
		p->next = newHead->next;
		newHead->next = p;
		//�ݹ����
		ReverseRecursion(head, newHead);
	}
}

List ListReverse4(List head)
{
	if(head->next == NULL || head->next->next == NULL)
	{
		return head; /*����Ϊ�ջ�ֻ��һ��Ԫ����ֱ�ӷ���*/
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
