#include <stdio.h>

void test()
{
	typedef int STData;
	//struct stack1
	//{
	//	int arr[N];//静态数组
	//	int top;//栈顶
	//}ST;
	typedef struct Stack
	{
		int* a;
		int top;
		int capicty;
	}ST;
	void STInit(ST * ps);//初始化栈表
	void STDestroy(ST * ps);//销毁栈表
	void STpush(ST * ps, STData x);//压栈，在栈顶压入一个元素
	void STpop(ST * ps);//出栈，在栈顶弹出一个元素。
	STData STTop(ST * ps);//访问栈顶元素
	int STSize(ST * ps);
	bool STEmpty(ST * ps);//
	//#include "stackl.h"
	void STInit(ST * ps)//初始化栈表
	{
		assert(ps);//判断结构体指针不为NULL；
		//一上来可以给栈表初始化容量
		ps->a = (STData*)malloc(sizeof(STData) * 4);
		if (ps->a == NULL)//判断是否开辟成功
		{
			perror("malloc");
		}
		//初始话容量为4
		ps->capicty = 4;
		ps->top = 0;//top=0 表示的是指向栈顶元素的下一个位置
		//top如果为-1，则表示栈顶元素的位置
	}
	void STDestroy(ST * ps)//销毁栈表
	{
		assert(ps);
		free(ps->a);
		ps->a = NULL;
		ps->capicty = 0;
		ps->top = 0;

	}
	void STpush(ST * ps, STData x)//压栈，在栈顶压入一个元素--在压入之前也要考虑是否需要增容
	{
		assert(ps);//断言判断
		if (ps->top == ps->capicty)
		{
			//增容
			STData* tmp = (STData*)realloc(ps->a, sizeof(STData) * ps->capicty * 2);
			if (tmp == NULL)
			{
				perror("realloc");
			}
			ps->a = tmp;
			ps->capicty *= 2;
		}
		ps->a[ps->top] = x;//将元素压入栈顶，一开始top是0，当元素进去后，再让top指向该栈顶元素后一个位置
		ps->top++;
	}
	bool STEmpty(ST * ps)
	{
		assert(ps);
		return ps->top == 0;
	}

	void STpop(ST * ps)//出栈，在栈顶弹出一个元素。
	{
		assert(ps);
		//删除元素之前要检查栈表是否还有元素可删
		assert(!STEmpty(ps));//当栈表为NULL是断言
		ps->top--;

	}
	int STSize(ST * ps)//计算栈表长度
	{
		assert(ps);
		return ps->top;
		//top的长度就是栈表的长度
	}
	STData STTop(ST * ps)//访问栈顶元素
	{
		assert(ps);
		return ps->a[ps->top - 1];
	}
	bool isValid(char* s)
	{
		ST st;
		STInit(&st);
		while (*s)
		{
			if (*s == '(' || *s == '{' || *s == '[')
			{
				//入栈
				STpush(&st, *s);

			}
			else
			{
				//如果为右括号就需要将之与栈顶括号进行比较
				if (STEmpty(&st))
					return false;
				char top = STTop(&st);
				STpop(&st);
				if ((*s == ')' && top != '(')
					|| (*s == ']' && top != '[')
					|| (*s == '}' && top != '{'))
				{
					return false;
				}
			}
			++s;
		}
		bool ret = STEmpty(&st);
		STDestroy(&st);
		return ret;
	}
}
int main()
{
	test();
	return 0;
}