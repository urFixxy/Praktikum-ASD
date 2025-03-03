#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

typedef struct{
    char input[MAX];
    int tos;
}stack;

void inisialisasi(stack *s){
    s->tos = 0;
}

int penuh(stack *s){
    return s->tos == MAX;
}

int kosong(stack *s){
    return s->tos == 0;
}

void pushstack(stack *s, char x){
    if(penuh(s)){
        printf("Stack Penuh");
        return;
    }else{
        s->input[s->tos] = x;
        s->tos++;
    }
}

char popstack(stack *s){
    if(kosong(s)){
        printf("Stack kosong");
        return '\0';
    }else{
        s->tos--;
        return s->input[s->tos];
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

int tes(stack *s, char t[]){
    int i, len = strlen(t);
    int operatorLast = 1;

    for(i=0; i<len; i++){
        if(t[i] == ' ') continue;

        if(operand(t[i])){
            operatorLast = 0;
        }else if(operator(t[i])){
            if(operatorLast){
                printf("Notasi infix salah, operand tidak lengkap\n");
                exit (0);
            }
            operatorLast = 1;
        }else if(t[i] =='('){
            if(!operatorLast){
                printf("Notasi infix salah, operator tidak lengkap\n");
                exit (0);
            }
            pushstack(s, t[i]);
            operatorLast = 1;
        }else if(t[i] == ')'){
            if(kosong(s)){
                printf("Notasi infix salah, kurung tidak lengkap\n");
                exit (0);
            }
            if(operatorLast){
                printf("Notasi infix salah, operand tidak lengkap\n");
                exit (0);
            }
            popstack(s);
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

void intopos(stack *s, char infix[]){
    int i, len = strlen(infix);
    
    printf("Notasi postfix : ");
    for(i=0; i<len; i++){
        switch(infix[i]){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                printf("%c", infix[i]);
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                if(kosong(s) || degree(infix[i]) > degree(s->input[s->tos-1])){
                    pushstack(s, infix[i]);
                }else{
                    do{
                        printf("%c", popstack(s));
                    }while(degree(infix[i]) <= degree(s->input[s->tos-1]));
                    pushstack(s, infix[i]);
                }
                break;
            case '(':
                pushstack(s, infix[i]);
                break;
            case ')':
                while(s->input[s->tos-1] != '('){
                    printf("%c", popstack(s));
                }
                if(s->input[s->tos-1] == '(')
                    popstack(s);
                break;  
            default:
                puts("Invalid infix notation");
                exit(0);
        }

    }

    while(!kosong(s)){
        printf("%c", popstack(s));
    }
}

int main(){
    stack s;
    char infix[MAX], repeat = 'y';

    printf("===== Program Tes Notasi Infix =====\n");

    while(repeat == 'y' || repeat == 'Y'){
        fflush(stdin);
        printf("Masukkan notasi infix : ");
        fgets(infix, sizeof(infix), stdin);
        infix[strcspn(infix, "\n")] = '\0';

        inisialisasi(&s);
        tes(&s, infix);
        intopos(&s, infix);

        printf("\nUlangi program? (y/t) : ");
        scanf(" %c", &repeat);
    }

    puts("Terima kasih telah menggunakan program ini");
    return 0;
}