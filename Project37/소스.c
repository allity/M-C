#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct StackNode {
	element M;
	struct StackNode *link;
} StackNode;

typedef struct {
	StackNode *top;
	int length;
} LinkedStackType;

int p = 0;

int is_empty(LinkedStackType start);
int safety_check(LinkedStackType *start, int num);
void state(LinkedStackType *start, int num);
int command(LinkedStackType *start, int num);
int move1(LinkedStackType *start, int M, int C, int num);
int com(LinkedStackType *start, int num);
int move2(LinkedStackType *start, int M, int C, int num);
void init(LinkedStackType *start);
void push(LinkedStackType *start, element M);
element pop(LinkedStackType *start);
element peek(LinkedStackType *start);

int is_empty(LinkedStackType start)
{
	if (start.top = NULL)
		return 1;
	else
		return 0;
}
int safety_check(LinkedStackType *start, int num)
{
	LinkedStackType store;
	store = *start;
	int i, countM = 0, countC = 0;
	int a[1000];
	for (i = 0; i < store.length; i++)
	{
		a[i] = peek(&store);
		store.top = store.top->link;
	}
	for (i = 0; i < start->length; i++)
	{
		if (a[i] == 0)
			countM++;
		else
			countC++;
	}
	if (countM >= countC && ((num - countM) >= (num - countC) || (num - countM == 0)))
	{
		state(start, num);
		return 1;
	}
	else if (countM == 0 || countC)
	{
		state(start, num);
		return 1;
	}
	else
	{
		printf("실패!\n");
		return 0;
	}
}
void state(LinkedStackType *start, int num)
{
	LinkedStackType store;
	store = *start;
	int i;
	int countM = 0;
	int countC = 0;
	int a[1000];
	for (i = 0; i < store.length; i++)
	{
		a[i] = peek(&store);
		store.top = store.top->link;
	}
	for (i = 0; i < start->length; i++)
	{
		if (a[i] == 0)
			countM++;
		else
			countC++;
	}
	for (i = 0; i < num - countM; i++)
		printf("M");
	for (i = 0; i < num - countC; i++)
		printf("C");

	printf("__강~물__");

	for (i = 0; i < countM; i++)
		printf("M");
	for (i = 0; i < countC; i++)
		printf("C");
	printf("\n");
	if (countM == 0 && countC == 0)
		p = 1;
}
int command(LinkedStackType *start, int num)
{
	int M, C;
	printf("선교사 몇명과 식인종 몇명이 건널것인가(예 : 1 1 or 0 2)>>");
	scanf("%d %d", &M, &C);
	return move1(start, M, C, num);
}
int move1(LinkedStackType *start, int M, int C, int num)
{
	int i, count = 0;
	if (C == 2)
	{
		pop(start);
		pop(start);
	}
	else if (C == 1 && M == 1)
	{
		pop(start);
		while (peek(start) != 0)
		{
			pop(start);
			count++;
		}
		pop(start);
		for (i = 0; i < count; i++)
			push(start, 1);
	}
	
	else
	{
		while (peek(start) != 0)
		{
			pop(start);
			count++;
		}
		pop(start);
		pop(start);
		for (i = 0; i < count; i++)
		{
			push(start, 1);
		}
	}
	return safety_check(start, num);
}
int com(LinkedStackType *start, int num)
{
	int M, C;
	printf("돌아갈 선교사와 식인종의 수는?(예 : 1 1 or 0 2)>>");
	scanf("%d %d", &M, &C);
	return move2(start, M, C, num);
}
int move2(LinkedStackType *start, int M, int C, int num)
{
	int i, count = 0;
	StackNode s, t;
	if (C == 2)
	{
		push(start, 1);
		push(start, 1);
	}
	else if (C == 1 && M == 1)
	{
		while (peek(start) != 0)
		{
			pop(start);
			count++;
		}
		push(start, 0);
		push(start, 1);
		for (i = 0; i < count; i++)
			push(start, 1);
	}
	else if (C == 1)
	{
		push(start, 1);
	}
	else if (M == 1)
	{
		while (peek(start) != 0)
		{
			pop(start);
			count++;
		}
		push(start, 0);
		for (i = 0; i < count; i++)
			push(start, 1);
	}
	else
	{
		while (peek(start) != 0)
		{
			pop(start);
			count++;
		}
		push(start, 0);
		push(start, 0);
		for (i = 0; i < count; i++)
			push(start, 1);
	}
	return safety_check(start, num);
}
void init(LinkedStackType *start)
{
	start->top = NULL;
	start->length = 0;
}
void push(LinkedStackType *start, element M)
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "메모리 할당에러\n");
		return;
	}
	else {
		temp->M = M;
		temp->link = start->top;
		start->top = temp;
		start->length++;
	}
}
element pop(LinkedStackType *start)
{
	if (is_empty(*start)) {
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	else {
		StackNode *temp = start->top;
		int M = temp->M;
		start->top = start->top->link;
		free(temp);
		start->length--;
		return M;
	}
}
element peek(LinkedStackType *start)
{
	if (is_empty(*start)) {
		fprintf(stderr, "스택이 비어있음\n");
		exit(1);
	}
	else {
		return start->top->M;
	}
}

void main()
{
	LinkedStackType start;
	int i;
	int num;
	int answer1, answer2;
	init(&start);
	printf("선교사와 식인종의 수를 입력하시오>>");
	scanf("%d", &num);
	for (i = 0; i < num; i++)
		push(&start, 0);
	for (i = 0; i < num; i++)
		push(&start, 1);
	state(&start, num);
	do
	{
		answer1 = command(&start, num);
		if (answer1 == 0)
			return 0;
		if (p == 1)
		{
			printf("성공!!!!!!!!!!!\n");
			return 0;
		}
		answer2 = com(&start, num);
		if (answer2 == 0)
			return 0;
	} while (answer1 == 1 && answer2 == 1);

	return 0;
}
