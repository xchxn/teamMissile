#include <stdio.h>

typedef enum{
	lparen,rparen,plus,minus,times,divide,mod,eos,operand
}precedence;

int stacke[100];
precedence stackp[100];
char expr[100];

static int isp[]={0,19,12,12,13,13,13,0};
static int icp[]={20,19,12,12,13,13,13,0};

void pushe(int*,int);
void pushp(int*,precedence);
precedence popp(int*);
int pope(int*);
int eval(void);
precedence getToken(char*,int*);
char printToken(precedence);
void postfix(void);

int eval(void)
{
	precedence token;
	char symbol;
	int op1,op2;
	int n=0;
	int top=-1;
	token=getToken(&symbol,&n);
	while(token!=eos){
		if(token==operand) pushe(&top,symbol-'#');
		else{
			op2=pope(&top);
			op1=pope(&top);
			switch(token){
				case plus : pushe(&top,op1+op2); break;
				case minus : pushe(&top,op1-op2); break;
				case times : pushe(&top,op1*op2); break;
				case divide : pushe(&top, op1/op2); break;
				case mod : pushe(&top,op1%op2); break;
			}
		}
		token=getToken(&symbol,&n);
	}
	return pope(&top);
}
void postfix(void)
{
	char symbol;
	precedence token;
	int n=0;
	int top=0;
	stackp[0]=eos;
	for(token==getToken(&symbol,&n);token!=eos;token==getToken(&symbol,&n)){
		if(token==operand) printf("%c",symbol);
		else if (token==rparen){
			while(stackp[top]!=lparen) printToken(popp(&top));
			popp(&top);
		}
		else{
			while(isp[stackp[top]]>icp[token]) printToken(popp(&top));
			pushp(&top,token);
		}
	}
	while((token=popp(&top))!=eos) printToken(token);
}

void pushe(int *top,int item)
{
	if(*top>=99){
		printf("full!");
		return;
	}
	stacke[++(*top)]=item;
}
int pope(int *top)
{
	if(*top<0){
		printf("Empty!");
		return -1;
	}
	return stacke[(*top)--];
}
void pushp(int *top,precedence item)
{
	if(*top>=99){
		printf("Full!");
		return;
	}
	stackp[++(*top)]=item;
}
precedence popp(int *top)
{
	if(*top<0){
		printf("Empty!");
		return eos;
	}
	return stackp[(*top)--];
}
precedence getToken(char *symbol,int *n)
{
	*symbol=expr[(*n)++];
	switch (*symbol){
		case '(' : return lparen;
		case ')' : return rparen;
		case '+' : return plus;
		case '-' : return minus;
		case '*' : return times;
		case '/' : return divide;
		case '%' : return mod;
		case '#' : return eos;
		default : return operand;
	}
}
char printToken(precedence token)
{
	switch(token){
		case plus : return '+';
		case minus : return '-';
		case times : return '*';
		case divide : return '/';
		case mod : return '%';
		default : return ' ';
	}
}

int main(void)
{	
	int rst;
	scanf("%s",expr);
	postfix();
	printf("%s",expr);
	rst=eval();
	printf("%d",rst);
	return 0;
}
