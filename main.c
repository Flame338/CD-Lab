#include <stdio.h>
#include <string.h>

char input[64], stack[64], letter[64], var = 'Z';
int bracketStack[32], stackTop = -1;
int lcount = -1, bcount = -1;

int operator(char ch);
int precedence(char ch);
void stackClear(char ch);
void printStack();
void clear();

int main() {
	stack[++stackTop] = '$';
	printf("Input a string: ");
	scanf("%s", input);
	int length = strlen(input);

	for(int i=0;i<length;i++) {
		char ch = input[i];
		if(operator(ch) == 1) {
			continue;
		}
		letter[++lcount] = ch;
	}

	if(stack[stackTop] != '$') {
		while(stack[stackTop] != '$') {
			printStack();	
		}
	}
	return 0;
}

int operator(char ch) {
	if(ch == '(') {
		stack[++stackTop] = ch;
		return 1; 
	}
	if(ch == ')') {
		stackClear(')');
		return 1;
	}
	if(precedence(ch) == 0) {
		return 0;
	}
	if(precedence(ch) <= precedence(stack[stackTop])) {
		stackClear(ch);
	}	
	stack[++stackTop] = ch;
	return 1;
}

int precedence(char ch) {
	switch(ch) {
		case '/':
		case '*': return 2;
		case '+':
		case '-': return 1;
		case '$': return -1;
		default: return 0;
	}
}

void stackClear(char ch) {
	if(ch == ')') {
		while(stack[stackTop] != '(') {
			printStack();
		}
		stack[stackTop--] = '\0';
	}
	while(precedence(ch) <= precedence(stack[stackTop])) {
		printStack();
	}
}

void printStack() {
	char temp1 = letter[lcount-1];
	char temp2 = letter[lcount];
	printf("%c := %c %c %c;\n", var, temp1, stack[stackTop], temp2);
	stack[stackTop--] = '\0';
	letter[lcount--] = '\0'; 
	letter[lcount] = var--;
}


