//快速查找链表中间节点
#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
	int data;
	struct Node *next;
}Node,*point;
void creatlist(point passNode) {
	point headnode;
	headnode = passNode;
	for (int i = 0; i < 20; i++) {
		point newNode;
		newNode = (point)malloc(sizeof(Node));
		newNode->next = NULL;
		newNode->data = rand();
		newNode->next = headnode->next;
		headnode->next = newNode;
	}
}
void printList(point passNode) {
	point printNode;
	printNode = passNode;
	for (int i = 0; i < 20; i++) {
		printNode = printNode->next;
		printf("%d,", printNode->data);
	}
}
int findmidNode(point passNode) {
	point pass, mid;
	mid = pass = passNode;
	while (pass->next) {
		mid= mid->next;
		pass = pass->next;
		pass = pass->next;
	}
	printf("%d", mid->data);
	return 0;
}
int main() {
	point Node;
	Node = (point)malloc(sizeof(Node));
	Node->data = NULL; Node->next = NULL;
	creatlist(Node);
	printList(Node);
	findmidNode(Node);
	system("pause");
	return 0;
}
