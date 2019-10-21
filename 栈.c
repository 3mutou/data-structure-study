#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100;    //宏定义 用STACK_INIT_SIZE来表示100，下同理
#define STACKINCERMENT 10;
typedef struct {
	int *base;  //栈底指针，在栈构造之前和销毁之后值为：NULL
	int *top;   //栈顶指针
	int stacksize;   //当前已分配的储存空间，以使用的类型大小为单位
}L,*SqStack;         //typedef struct L,*SqStack.定义之后可用L来定义结构体变量，用SqStack来定义结构体变量
int InitStack(SqStack S) {       //创建新的栈
	S->base = (int *)malloc(100 * sizeof(int));   //利用malloc函数来分配储存空间
	if (!S->base) {               //S->base为空，分配空间失败，发出提示
		printf("存储分配失败");
	}
	S->top = S->base;      //栈顶指针指向栈底
	S->stacksize = STACK_INIT_SIZE;   //起始大小
	return 0;
}
void Push(SqStack S, int e) {         //压栈函数
	if (S->top - S->base >= S->stacksize) {     //在输入元素前判断栈是否为满，防止栈溢出。
		S->base = (int *)realloc(S->base, (S->stacksize + 10) * sizeof(int));  //如果栈满，则利用realloc函数重新分配空间，并将第一个指针指向的内存区域的值复制到新的内存区域;
		if (!S->base) exit(1);      //分配存储失败则退出程序
		S->top = S->base + S->stacksize;  //调整栈顶指针的指向
		S->stacksize += STACKINCERMENT;   //储存空间增加
	}
	*(S->top++) = e;  //存入值
}
int StackEmpty(SqStack S) {    //判断栈是否为空的函数， 若空返回1
	if (S->top == S->base) return 1;
	else return 0;

}
void Pop(SqStack S, int *e)    //出栈函数
{
	if (S->top == S->base) 
		printf("栈为空");
	*e = *--S->top;  //将栈顶元素值赋给e,并将栈顶指向前一个元素
}
void conversion(SqStack S) {    //进制转换函数
	int e=0;
	int N;
	printf("请输入非负十进制整数：");
	scanf_s("%d", &N);
	printf("%d(10)=", N);
	//利用进制转换原则将数据压入栈中，并实现输出
	while (N) {           
		Push(S, N % 8);     
		N = N / 8;
	}
	while (!StackEmpty(S)) {  //栈中元素输出结束，停止循环
		Pop(S, &e);
		printf("%d", e);
	}
	printf("(8)");
} 
int main()     //主函数实现函数的调用
{
	SqStack point;
	point = (SqStack)malloc(sizeof(L));
	InitStack(point);
	conversion(point);
	free(point);
	system("pause");
	return 0;
}
