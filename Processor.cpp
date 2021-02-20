#include <ctype.h>
#include <sys\types.h>
#include <sys\stat.h>
#include "Enum.h"

#ifndef  _STACK_H
#define _STACK_H

#define TYPE double
#include "Stack.h"
#undef TYPE

#endif

#define rax registr[0]
#define rbx registr[1]
#define rcx registr[2]
#define rdx registr[3]

struct Proc
{
	double* commands;
	int IP;
	double* registr;
};

void CPU(char* input)
{
	Proc CPU;

	struct stat buff;
	stat(input, &buff);

	unsigned long size_of_input = buff.st_size;

	CPU.commands = (double*)calloc(size_of_input, sizeof(double));

	FILE* potok = fopen(input, "rb");

	int read_out = fread(CPU.commands, sizeof(double), size_of_input, potok);

	printf(">>> %d - readed\n\n", read_out);

	for (int i = 0; i <= read_out; i++)
	{
		printf("%.0lf ", CPU.commands[i]);
	}
	printf("\n");

	fclose(potok);

	CPU.IP = 0;

	Stack_double stk;
	stk.DUMP();
	for (int i = 0; /*i < size_of_input*/; i++)
	{
		switch ((int)CPU.commands[CPU.IP])
		{
			case CMD_PUSH: 
			{
				stk.Push(CPU.commands[CPU.IP + 1]);
				printf("push %.0lf\n", CPU.commands[CPU.IP + 1]);
				CPU.IP = CPU.IP + 2;
				
				break;
			}
			case CMD_ADD:
			{
				CPU.IP++;

				double a = stk.Pop();
				double b = stk.Pop();

				printf("add %.0lf %.0lf\n", a, b);

				double c = a + b;

				stk.Push(c);

				break;
			}
			case CMD_OUT:
			{
				CPU.IP++;

				double a = stk.Pop();

				printf("out %.0lf\n", a);

				stk.Push(a);

				break;
			}
			case CMD_MUL:
			{
				CPU.IP++;

				double a = stk.Pop();
				double b = stk.Pop();

				printf("mul %.0lf %.0lf\n", a, b);

				double c = a * b;

				stk.Push(c);

				break;
			}
			case CMD_SUB:
			{
				CPU.IP++;

				double a = stk.Pop();
				double b = stk.Pop();

				printf("sub %.0lf %.0lf\n", a, b);

				double c = a - b;

				stk.Push(c);

				break;
			}
			case CMD_DIV:
			{
				CPU.IP++;

				double a = stk.Pop();
				double b = stk.Pop();

				printf("div %.0lf %.0lf\n", a, b);

				double c = a / b;

				stk.Push(c);

				break;
			}
			case CMD_JMP:
			{
				printf("JUMP\n\n");

				CPU.IP = CPU.commands[CPU.IP + 1];

				break;
			}
			case CMD_END:
			{
				stk.DUMP();

				return;
			}
		}
	}
}

