#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Node_Groot.h"

int main() {
	setlocale(LC_ALL, "Rus");
	FILE* VD;
	VD = fopen("VD.txt", "r");
	int size = 0;
	char* Expression;
	fseek(VD, 0, SEEK_END);
	size = ftell(VD);// узнаём длину строки
	Expression = (char*)malloc(size * sizeof(char));//выделяем память для массива 
	fseek(VD, 0, SEEK_SET);
	char value;
	int i = 0;
	// считываем из файла в массив данные
	while (fscanf(VD, "%c", &value) != EOF){ 
		Expression[i] = value;
		i++;
	}
	printf("Expression: ");
	for (int i = 0; i < size; i++) {
		printf("%c", Expression[i]);
	}
	printf("\n");
	Node* Groot = NULL;
	Groot = MakeTree(Expression, 0, size - 1);
	Print_pre(Groot);
	printf("\n");
	Print_in(Groot);
	printf("\n");
	Print_post(Groot);
	printf("\n");
	printf("Rezult: %6.2f", CalcTree(Groot));
	fclose(VD);
}