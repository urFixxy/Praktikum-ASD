#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX 20

typedef struct{
    int top;
    char input[MAX];
}stack_char;

typedef struct{
    int top;
    int output[MAX];
}stack_int;

void inisialisasi(stack_char *s){
    s->top = 0;
}

void inisialisasi_int(stack_int *s){
    s->top = 0;
}

bool penuh(stack_char *s){
    return s->top == MAX;
}

bool kosong(stack_char *s){
    return s->top == 0;
}

bool penuh_int(stack_int *s_int){
    return s_int->top == MAX;
}

bool kosong_int(stack_int *s_int){
    return s_int->top == 0;
}

void pushstack_char(stack_char *s, char x){
    if(penuh(s)){
        printf("Stack Penuh");
    }else{
        s->input[s->top] = x;
        s->top++;
    }
}

int popstack_char(stack_char *s){
    if(kosong(s)){
        printf("Stack kosong");
        return '\0';
    }else{
        s->top--;
        return s->input[s->top];
    }
}

void pushstack_int(stack_int *s_int, int x){
    if(penuh_int(s_int)){
        printf("Stack Penuh");
    }else{
        s_int->output[s_int->top] = x;
        s_int->top++;
    }
}

int popstack_int(stack_int *s_int){
    if(kosong_int(s_int)){
        printf("Stack kosong");
        return '\0';
    }else{
        s_int->top--;
        return s_int->output[s_int->top];
    }
}

int operand(char t){
    if(t >= '0' && t <= '9')
        return 1;
    else
        return 0;
}

int operator(char t){
    if(t == '+' || t == '-' || t == '*' || t == '/' || t == '^')
        return 1;
    else
        return 0;
}

int degree(char x){
    if(x == '^')
        return 3;
    else if(x == '*' || x == '/')
        return 2;
    else if(x == '+' || x == '-')
        return 1;
    else if(x == '(')
        return 0;
    else
        return -1;
}

int tes(stack_char *s, char infix[]){
    int i, len = strlen(infix);
    int operatorLast = 1;

    for(i=0; i<len; i++){
        if(infix[i] == ' ') continue;

        if(operand(infix[i])){
            operatorLast = 0;
        }else if(operator(infix[i])){
            if(operatorLast){
                printf("Notasi infix salah, operand tidak lengkap\n");
                exit (0);
            }
            operatorLast = 1;
        }else if(infix[i] =='('){
            if(!operatorLast){
                printf("Notasi infix salah, operator tidak lengkap\n");
                exit (0);
            }
            pushstack_char(s, infix[i]);
            operatorLast = 1;
        }else if(infix[i] == ')'){
            if(kosong(s)){
                printf("Notasi infix salah, kurung tidak lengkap\n");
                exit (0);
            }
            if(operatorLast){
                printf("Notasi infix salah, operand tidak lengkap\n");
                exit (0);
            }
            popstack_char(s);
            operatorLast = 0;
        }else{
            printf("Notasi infix salah, karakter tidak valid\n");
            exit (0);
        }
    }

    if(operatorLast){
        printf("Notasi infix salah, operand tidak lengkap\n"); exit (0);
    }
    
    if(!kosong(s)){
        printf("Notasi infix salah, kurung tidak lengkap\n"); exit (0);
    }

    printf("Notasi infix benar\n"); 
    return 1;
}

void intopos(stack_char *s, char infix[], char postfix[]){
    int i, j=0, len = strlen(infix);
    char temp;

    printf("Notasi postfix: ");
    for (i=0; i<len; i++) {
        if(operand(infix[i])) {
            while(i<len && operand(infix[i])) {
                printf("%c", infix[i]);
                postfix[j++] = infix[i];
                i++;
            }
            postfix[j++] = ' ';
            i--; 
        }else{
            switch (infix[i]) {
                case '+': case '-': case '*': case '/': case '^':
                    while(!kosong(s) && degree(infix[i]) <= degree(s->input[s->top-1])) {
                        temp = popstack_char(s);
                        printf("%c", temp);
                        postfix[j++] = temp;
                        postfix[j++] = ' ';
                    }
                    pushstack_char(s, infix[i]);
                    break;
                case '(':
                    pushstack_char(s, infix[i]);
                    break;
                case ')':
                    while(!kosong(s) && s->input[s->top-1] != '(') {
                        temp = popstack_char(s);
                        printf("%c", temp);
                        postfix[j++] = temp;
                        postfix[j++] = ' ';
                    }
                    if(!kosong(s) && s->input[s->top-1] == '(') {
                        popstack_char(s);
                    }
                    break;
                default:
                    printf("\nInvalid infix notation\n");
                    exit(0);
            }
        }
    }

    while (!kosong(s)) {
        temp = popstack_char(s);
        printf("%c", temp);
        postfix[j++] = temp;
        postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}


void result(stack_int *s_int, char postfix[]){
    int i, x, y, z, len = strlen(postfix);

    printf("\nHasilnya : ");
    for(i=0; i<len; i++){
        if(postfix[i] == ' ') continue;
        if(operand(postfix[i])){
            int num = 0;
            while (i < len && operand(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            pushstack_int(s_int, num);
            i--;
        }else{
            x = popstack_int(s_int);
            y = popstack_int(s_int);

            switch(postfix[i]){
                case '+':
                    z = y + x; break;
                case '-':
                    z = y - x; break;
                case '*':
                    z = y *x; break;
                case '/':
                    if(x == 0){
                        printf("Devide by zero");
                        exit (0);
                    }else{
                        z = y / x;
                    }
                    break;
                case '^':
                    z = (int)pow(y, x);
                    break;
                default:
                    printf("Unknown operator");
                    exit (0);
            }
        pushstack_int(s_int, z);
        }
    }

    printf("%d", popstack_int(s_int));
}

int main(){
    stack_char s;
    stack_int s_int;
    char infix[MAX], postfix[MAX], repeat = 'y';

    printf("=====INTEGRATED PROGRAM=====\n");

    while(repeat == 'y' || repeat == 'Y'){
        printf("Masukkan notasi infix: ");
        fgets(infix, sizeof(infix), stdin);
        infix[strcspn(infix, "\n")] = '\0';

        inisialisasi(&s);
        tes(&s, infix);
        inisialisasi_int(&s_int);
        intopos(&s, infix, postfix);
        result(&s_int, postfix);

        printf("\nApa ingin memasukkan data lagi? ");
        scanf("%c", &repeat);
        fflush(stdin);
    }

    printf("Terima kasih telah menggunakan program ini\n");
    return 0;
}