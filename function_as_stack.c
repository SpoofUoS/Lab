// Created by: Spoof_UoS

/*
    함수스택으로 만드는 스택 원리
    
    1. push
    -> function에서 stack을 호출한다.
    -> stack 함수에서 function 함수를 다시 호출한다.

    2. pop
    -> function 함수를 return 한다.
    -> return 하고나면 stack 함수에서 이전 값들을 복원하여 다시 return 한다.
    -> 다시 function 함수로 복귀

    3. program counter
    -> c언어에서 프로그램 카운터를 사용할 수 없다.
    -> goto와 현재 상태를 저장하는 변수(prog.jmp_case)를 통해 프로그램 카운터를 간접 표현한다.
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int element;

typedef struct progress{
    element top;
    int depth;
    int index;
    int end;
    int jmp_case;
}progress;

void stack(char* s, element n, progress* p);
void function(char* s, progress* p);
int prec(char op);

int main(void)
{
    char* s = "3-(2*(7*81)-2/3)"; //(3+7)*(4+6)+9*8 // 37+46+*98*+ // 3-(2*(7*81)-2/3)

    /* progress as program counter */
    progress prog; prog.depth = 0; prog.index = 0; prog.end = strlen(s); prog.top = -1; prog.jmp_case = 0; 
    progress* p = &prog;

    printf("before: %s\n", s);

    printf("after: "); function(s, p); printf("\n");

    return 0;
}

void stack(char* s, element n, progress* p)
{
    element prev = p->top;
    p->top = n;
    p->depth++;
    function(s, p);
    p->depth--;
    p->top = prev;
    return;
}

int prec(char op) 
{
    switch (op)
    {
    case '(': case ')': return 0;
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    }
    return -1;
}

void function(char* s, progress* p)
{
    char tmp;
    first:
    switch (p->jmp_case)
    {
    case 1:
        goto jmp_case_1;
    case 2:
        goto jmp_case_2;
    case 4:
        return;
    default:
        break;
    }
    if(p->index != p->end)
    {
        char c = s[p->index++];

        switch (c)
        {
        case '+': case '-': case '*': case '/':
            jmp_case_1:
            while(p->depth != 0 && prec(c) <= prec(p->top))
            {
                tmp = p->top;
                printf("%c", tmp);
                p->jmp_case = 1;
                return;
            }
            p->jmp_case = -1;
            stack(s, s[p->index-1], p); // 2번째 인자 값에 c를 넣으면 과거에 index를 기반으로 했던 c 값이 들어있어 잘못된 결과가 나온다.
            goto first;

        case '(':
            stack(s, c, p);
            goto first;

        case ')':
            p->jmp_case = 2;
            jmp_case_2:
            while(p->top != '(')
            {
                tmp = p->top;
                printf("%c", tmp);
                p->jmp_case = 2;
                return;
            }
            p->jmp_case = -1;
            return;

        default:
            printf("%c", c);
            goto first;
        }
    }

    else
    {
        while(p->depth != 0)
        {
            p->jmp_case = -1;
            tmp = p->top;
            printf("%c", tmp);
            return;
        }
        p->jmp_case = 4;
        goto first;
    }
    goto first;
}