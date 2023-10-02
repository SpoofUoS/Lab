// Created by: Spoof_UoS

/*
    함수스택으로 만드는 스택 원리
    
    1. push
    -> function에서 넣고자 하는 값을 인자 값으로 다시 function을 호출한다.
    -> 호출한 부분으로 jump 한다.

    2. pop
    -> function 함수를 return 한다.

    3. program counter
    -> c언어에서 프로그램 카운터를 사용할 수 없다.
    -> goto와 현재 상태를 저장하는 변수(progress.jmp_case, progress.index)를 통해 프로그램 카운터를 간접 표현한다.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int element;

typedef struct progress{
    int index;
    int end;
    int jmp_case;
}progress;

void function(element n, char* s, progress* p);
int prec(char op);

int main(void)
{
    char* s = "(3+7)*(4+6)+9*8"; //(3+7)*(4+6)+9*8 // 37+46+*98*+ //

    /* progress as program counter */
    progress prog; prog.index = 0; prog.end = strlen(s); prog.jmp_case = 0;
    progress* p = &prog;

    printf("before: %s\n", s);

    printf("after: "); function(-1, s, p); printf("\n");

    return 0;
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

void function(element n, char* s, progress* p)
{
    element prev;
    first:
    switch (p->jmp_case)
    {
    case 1:
        goto jmp_case_1;
    case 2:
        goto jmp_case_2;
    case 3:
        goto stack;
    case 4:
        return;
    default:
        goto function;
        break;
    }

    /* stack part */
    stack:
    p->jmp_case = -1;
    function(n, s, p);
    return;

    /* function part */
    function:

    if(p->index != p->end)
    {
        char c = s[p->index++];

        switch (c)
        {
        case '+': case '-': case '*': case '/':
            jmp_case_1:
            while(n != -1 && prec(s[p->index-1]) <= prec(n))
            {
                printf("%c", n);
                p->jmp_case = 1;
                return;
            }
            p->jmp_case = 3;
            function(s[p->index-1], s, p);
            goto first;

        case '(':
            p->jmp_case = 3;
            function(c, s, p);
            goto first;

        case ')':
            p->jmp_case = 2;
            jmp_case_2:
            while(n != '(')
            {
                printf("%c", n);
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
        while(n != -1)
        {
            p->jmp_case = -1;;
            printf("%c", n);
            return;
        }
        p->jmp_case = 4;
        goto first;
    }
    goto first;
}