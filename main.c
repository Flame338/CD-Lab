#include <stdio.h>

char input[63];
char *cursor;
char stack[64];
int top;

int parse();

int main() {
	stack[0] = '$';
	top = 0;
	printf("Input String to be parsed: ");
	scanf("%s", input);
	cursor = input;
	printf("Stack     Input     Op\n");
	printf("----------------------\n");
	printf("%-10s %-10s Shift\n", stack, cursor);

	while(*cursor != '\0'){
		parse();
	}	

	if(*cursor == '\0') {
		printf("----------------------\n");
		printf("String parsed successfully.\n");
	} else {
		printf("----------------------\n");
		printf("Error.\n");
	}
	return 0;
}

int parse() {
	if(stack[top] == '$' || stack[top] == '(' || stack[top] == 'L' || stack[top] == ',') {
		top += 1;
		stack[top] = *cursor;
		cursor += sizeof(char);
		printf("%-10s %-10s Shift\n", stack, cursor);
	} else if(stack[top - 2] == '(' && stack[top - 1] == 'L' && stack[top] == ')') {
		stack[top - 2] = '\0';
		stack[top - 1] = '\0';
		stack[top] = '\0';
		top -= 3;
		printf("%-10s %-10s Reduce using S -> (L)\n", stack, cursor);
		top += 1;
		cursor += sizeof(char);
		stack[top] = *cursor;
	} else if(stack[top -2] == 'L' && stack[top - 1] == ',' && stack[top] == 'S') {
		stack[top - 2] = '\0';
		stack[top - 1] = '\0';
		stack[top] = '\0';
		top -= 3;
		printf("%-10s %-10s Reduce using L -> L,S\n", stack, cursor);
		top += 1;
		cursor += sizeof(char);
		stack[top] = *cursor;
	} else if(stack[top] == 'a') {
		stack[top] = 'S';
		printf("%-10s %-10s Reduce using S -> a\n", stack, cursor);
	} else if(stack[top] == 'S') {
		stack[top] = 'L';
		printf("%-10s %-10s Reduce using L -> S\n", stack, cursor);
		top += 1;
		cursor += sizeof(char);
		stack[top] = *cursor;
	} 

	if(stack[top] == '$') {
		stack[top] = '\0';
		return 1;
	}
	return 0;
}
