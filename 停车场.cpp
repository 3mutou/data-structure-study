#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#define CloseTime 1440
typedef int Status;
int n;
int CustomerNum;
//�������ݽṹ
typedef struct {
	int ArrivalTime;    //����ͣ������ʱ��
	int leavetime;      //�뿪ͣ������ʱ��
}QElemType;
typedef struct QNode {
	QElemType data;     
	struct QNode *next;
}QNode, *QueuePtr;
typedef struct {
	QueuePtr front; //��ͷָ��
	QueuePtr rear;  //��βָ��
}LinkQueue;
QElemType customer;
LinkQueue point3;   //����
//�¼������ݽṹ
typedef struct {
	int OccurTime;  //��ǰ�¼�����ʱ��
	int NType;      //ֻ������ֵ��0Ϊ��ͣ������1Ϊ�뿪ͣ����
}Event, ElemType; //Ԫ������
typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;    //����������
typedef LinkList EventList;
EventList ev; //�¼���
Event     en; //�¼�
//����ջ�����ݽṹ
typedef struct {
	QElemType *base;  //ջ��ָ�룬��ջ����֮ǰ������֮��ֵΪ��NULL
	QElemType *top;   //ջ��ָ��
	int stacksize;   //��ǰ�ѷ���Ĵ���ռ䣬��ʹ�õ����ʹ�СΪ��λ
}L, *SqStack;
SqStack point1, point2;
int cmp(int a, int b)
{
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}
//�����¼�����
Status OrderInsert(LinkList &L, ElemType e, int(*compare)(int, int))
{
	LinkList s;
	LinkList p = L;
	if (p->next == NULL)  //û��Ԫ����ֱ�Ӳ���
	{
		s = (LinkList)malloc(sizeof(LNode));
		s->next = NULL;
		s->data = e;
		p->next = s;
	}
	else
	{
		while (compare(e.OccurTime, p->next->data.OccurTime) != -1)//��a���ڵ�ǰ�¼�֮ǰһֱ������һλ
		{
			p = p->next;
			if (p->next == NULL)
			{
				s = (LinkList)malloc(sizeof(LNode));
				s->data = e; s->next = p->next;
				p->next = s;
				return 1;
			}
		}
		s = (LinkList)malloc(sizeof(LNode));
		s->data = e; s->next = p->next;           //���뵱ǰ���֮��
		p->next = s;
	}
	return 1;
}
//ջ���ܺ���
Status InitStack(SqStack S) {       //�����µ�ջ
	S->base = (QElemType *)malloc(n * sizeof(QElemType));   //����malloc���������䴢��ռ�
	if (!S->base) {               //S->baseΪ�գ�����ռ�ʧ�ܣ�������ʾ
		printf("�洢����ʧ��");
	}
	S->top = S->base;      //ջ��ָ��ָ��ջ��
	S->stacksize = n;   //��ʼ��С
	return 0;
}
//�ж�ջ�Ƿ����������򷵻�1
Status  FullStack(SqStack S) {
	if (S->top - S->base == S->stacksize) return 1;
	else return 0;
}
Status Push(SqStack S, QElemType *e) {         //ѹջ����
	if (S->top - S->base >= S->stacksize) {     //������Ԫ��ǰ�ж�ջ�Ƿ�Ϊ������ֹջ�����
		printf("ջ����");  return 1;
	}
	else  *(S->top++) = *e;  //����ֵ
	return 0;
}
Status StackEmpty(SqStack S) {    //�ж�ջ�Ƿ�Ϊ�յĺ����� ���շ���1
	if (S->top == S->base) return 1;
	else return 0;
}
Status Pop(SqStack S, QElemType *e)    //��ջ����
{
	if (S->top == S->base) {
		printf("ջΪ��");  return 1;
	}
	else  *e = *--S->top;  return 0; //��ջ��Ԫ��ֵ����e,����ջ��ָ��ǰһ��Ԫ��
}
Status Push2(SqStack S, QElemType *e)
{
	if (S->top == S->base) {
		printf("ջΪ��"); return 1;
	}
	else *S->top++ = *e; return 0;
}
Status LengthStack(SqStack S)
{
	return S->top - S->base;
}
//��ͣ��ջ��Ѱ����Сleavetime��������leavetime������e���ص�ǰָ���ַ
Status FindMin(SqStack S, int *e)
{
	int i,i2=LengthStack(S);
	SqStack L = S;
	int t; *e = 1;
	t = S->top->leavetime;
	for (i = 0; i < LengthStack(S); L->top--, i++) {
		if (t > L->top->leavetime) {
			t = L->top->leavetime;
			*e = L->top - L->base;
		}
	}
	return t;
}
//�¼�������ع��ܺ���
//����һ���µĿ�����
Status ListCreate_L(LinkList &L)
{
	if (L == NULL)
	{
		L = (LinkList)malloc(sizeof(LNode));
		L->next = NULL;
		return 1;
	}
	else
		return 0;
}
//����һ������
Status ListDestroy_L(LinkList &L)
{
	LinkList p = L, s;
	while (p->next != NULL)
	{
		s = p; p = p->next;  free(s);
	}
	return 1;
}
//�ж�һ�������Ƿ�Ϊ��
int ListEmpty_L(LinkList L)
{
	if (L->next == NULL)
		return 1;
	else
		return 0;
}
//ɾ������ĵ�һ��Ԫ�أ�������e
Status ListDeleteFirst_L(LinkList &L, ElemType &e)
{
	LinkList s;
	LinkList p = L;
	s = p;
	p = p->next;
	e = p->data;
	s->next = p->next;
	//free(p);
	return 1;
}
//������غ���
//������
Status InitQueue_L(LinkQueue &Q)
{
	//����һ���ն���Q
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (Q.front == NULL) exit(0);
	Q.front->next = NULL;
	return 1;
}
Status DestroyQueue_L(LinkQueue &Q)
{
	//����һ������
	while (Q.front != NULL)
	{
		Q.rear = Q.front->next;  //��ʡ����
		free(Q.front);
		Q.front = Q.rear;
	}
	return 1;
}
Status EnQueue_L(LinkQueue &Q, QElemType e) {
	//����Ԫ��eΪQ���µĶ�βԪ��
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(0);
	p->data = e;  p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return 1;
}
Status DeQueue_L(LinkQueue &Q, QElemType &e)
{
	//�����в��� ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK
	//���򷵻�ERROR
	QueuePtr p;
	if (Q.rear == Q.front) return 0;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	return 1;
}
//�ж϶����Ƿ�Ϊ��
int QueueEmpty_L(LinkQueue Q)
{
	if (Q.rear == Q.front)
		return 1;
	else
		return 0;
}

Status GetHeadQueue_L(LinkQueue Q, QElemType &e)
{
	e = Q.front->next->data;
	return 1;
}
//���в���ͣ��ջ����
//��ʼ������
void OpenForDay()
{
	CustomerNum=0;
	ListCreate_L(ev);               //��ʼ���¼�����Ϊ�ձ�
	en.OccurTime = 0; en.NType = 0; //�趨��һ���ͻ������¼�
	OrderInsert(ev, en, cmp);         //�����¼���
	InitQueue_L(point3); //�ÿն���
}//OpenForDay
	
void CustomerArrived(SqStack &S)
{
	//����ͻ������¼�  en.NType = 0;
	int durtime, intertime, t, *e, e1; e = &e1;
	ElemType tmp;
	QElemType *Qtmp, Qtmp1,Qtmp2; Qtmp = &Qtmp1;
	++CustomerNum;
	durtime = 1 + (int)(360.0*rand() / (RAND_MAX + 1.0)); //����ʱ��,�������0��359������
	intertime = 1 + (int)(60.0*rand() / (RAND_MAX + 1.0)); //��һ��������ʱ����
	t = en.OccurTime + intertime;  //��һ��������ʱ��
	if (!FullStack(S)) {
		if (t < CloseTime) //ͣ����һ�� �����¼���,ͣ��������û���ȴ���ֱ�Ӳ���ͣ��ջ���������Ⱥ�ջ
		{
			if (QueueEmpty_L(point3)) {    //ջ���������п�
				tmp.OccurTime = t;
				tmp.NType = 0;
				OrderInsert(ev, tmp, cmp);
				tmp.OccurTime = en.OccurTime + durtime;
				tmp.NType = 1;
				OrderInsert(ev, tmp, cmp);     //��ͣ��ջ��Ҫ��¼�뿪�¼�
				Qtmp1.ArrivalTime = t; Qtmp1.leavetime = t + durtime;
				Push(S, Qtmp);        //����ͣ��ջ
			}
				/*Qtmp2.ArrivalTime = FindMin(point1, e);
				Qtmp2.leavetime = FindMin(point1, e) + durtime;
				EnQueue_L(point3, Qtmp2);
			}*/
		}
	}
	else {                          //ջ�������м�¼����ͣ�����¼����������
		if (t < CloseTime) {
			tmp.OccurTime = t;
			tmp.NType = 0;
			OrderInsert(ev, tmp, cmp);
			Qtmp2.ArrivalTime = FindMin(point1,e);
			Qtmp2.leavetime = FindMin(point1,e) + durtime;  
			EnQueue_L(point3, Qtmp2);           //ջ�������в��գ�˳����
		}
	}
}
void CustomerDeparture(SqStack S, SqStack S2)
{
	//����ͻ��뿪�¼� ��en.Type>0;
	ElemType tmp;
	QElemType e, *e1; e.ArrivalTime = 0; e.leavetime = 0;
	e1 = &e;
	int t2 = 1,durtime;
	int *t; int i;
	t = &t2;
	if (QueueEmpty_L(point3)) {   //�ӿ�
		for (i = 0; i < LengthStack(S) - *t; i++) {
			Pop(S, e1);
			Push(S2, e1);
		}
		Pop(S, e1);
		t2 = 0.05*(e.leavetime - e.ArrivalTime);
		printf("����ͣ����ʱ��:%d���뿪ͣ����ʱ��:%d��Ӧ�ɷ�:%d\n", e.ArrivalTime, e.leavetime, t2);
		while (!StackEmpty(S2)) {
			Pop(S2, e1); Push(S, e1);
		}
	}
	else {     //���в���ʱ������Ԫ�ز���
		FindMin(point1, t);
		durtime = point3.front->data.leavetime - point3.front->data.ArrivalTime;
		point3.front->data.ArrivalTime = FindMin(S, t); point3.front->data.leavetime = FindMin(S, t) + durtime;
		for (i = 0; i < LengthStack(S) - *t; i++) {
			Pop(S, e1);
			Push(S2, e1);
		}
		Pop(S, e1);
		t2 = 0.05*(e.leavetime - e.ArrivalTime);
		printf("����ͣ����ʱ��:%d���뿪ͣ����ʱ��:%d��Ӧ�ɷ�:%d\n", e.ArrivalTime, e.leavetime, t2);

		while (!StackEmpty(S2)) {
			Pop(S2, e1); Push(S, e1);
		}
		DeQueue_L(point3, customer); //���е���ͷ������ջ���ڴ�֮ǰ���谭�ĳ��Ƶ���һ��ջ
		e.ArrivalTime = customer.ArrivalTime; e.leavetime = customer.leavetime;
		Push2(S, e1);
		tmp.OccurTime = e.leavetime;
		tmp.NType = 1;
		OrderInsert(ev, tmp, cmp);
	}  //��ͣ��ջ��Ҫ��¼�뿪�¼�
}
void Bank_Simulation()
{
	ElemType tmp;
	OpenForDay();
	point1 = (SqStack)malloc(sizeof(L));
	point2 = (SqStack)malloc(sizeof(L));
	InitStack(point1); InitStack(point2);
	while (!ListEmpty_L(ev)) //�¼���ǿռ���ִ��
	{
		ListDeleteFirst_L(ev, tmp);
		en = tmp;
		if (en.NType == 0)
			CustomerArrived(point1);
		else
			CustomerDeparture(point1, point2);
	}
}
int main()
{
	printf("������ͣ����λ��:");
	scanf("%d", &n);
	srand((int)time(0));
	Bank_Simulation();
	system("pause");
	return 0;
}
