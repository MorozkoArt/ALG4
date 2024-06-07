#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Node_Groot.h"

Node* New(int num, char sign)
{
	Node* p = (Node*)malloc(sizeof(Node));
	p->num = num;
	p->sign = sign;
	p->right = NULL;
	p->left = NULL;
	return p;
}

int Prior(int a)
{
	switch (a)
	{
	case 42:
	case 47:
		return 3;
	case 43:
	case 45:
		return 2;
	case 40:
		return 0;
	case 41:
		return 1;
	default: return 10;
	}
}

Node* MakeTree(char* Expression, int first, int last)
{
	int k = -1, Min = 100, prior;
	int nest = 0;
	Node* T = New(0, '0');
	//заносим в звено дерева число
	if (first == last)
	{
		T->num = Expression[first] - '0';
		T->left = NULL;
		T->right = NULL;
		return T;
	}
	//поиск операции минимального приоритета вне скобок
	for (int i = first; i < last; i++)
	{
		prior = Prior(Expression[i]);
		if (prior == 0) nest++;
		else if (prior == 1) nest--;
		else if (prior <= Min && nest == 0)
		{
			Min = prior;
			k = i;
		}
	}
	if (Min == 100) // заходим в скобки, отрезая их, если не нашли операцию
		return MakeTree(Expression, first + 1, last - 1);
	T->sign = Expression[k];
	T->left = MakeTree(Expression, first, k - 1);
	T->right = MakeTree(Expression, k + 1, last);
	return T;
}

void Print_pre(Node* v)
{
	if (v == NULL) return;
	if (v->left != NULL && v->right != NULL)
		printf("%c ", v->sign);
	else
		printf("%.0f ", v->num);
	Print_pre(v->left);
	Print_pre(v->right);
}

void Print_in(Node* v)
{
	if (v == NULL) return;
	Print_in(v->left);
	if (v->left != NULL && v->right != NULL)
		printf("%c ", v->sign);
	else
		printf("%.0f ", v->num);
	Print_in(v->right);
}

void Print_post(Node* v)
{
	if (v == NULL) return;
	Print_post(v->left);
	Print_post(v->right);
	if (v->left != NULL && v->right != NULL)
		printf("%c ", v->sign);
	else
		printf("%.0f ", v->num);
}

float CalcTree(Node* Tree)
{
	float num1, num2;
	if (Tree->left == NULL)
		return Tree->num;
	num1 = CalcTree(Tree->left);
	num2 = CalcTree(Tree->right);
	switch (Tree->sign) {
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1 * num2;
	case '/': return num1 / num2;
	}
	return 32767;
}