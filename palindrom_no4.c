#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

typedef struct{
    int top;
    char word[MAX];
}stack;

void inisialisasi(stack *s){
    s->top = 0;
}

int penuh(stack *s){
    return s->top == MAX;
}

int kosong(stack *s){
    return s->top == 0;
}

void pushStack(stack *s, char x){
    if(penuh(s)){
        printf("Stack Penuh");
        return;
    }else{
        s->word[s->top] = x;
        s->top++;
    }
}

char popStack(stack *s){
    if(kosong(s)){
        printf("Stack kosong");
        return '\0';
    }else{
        s->top--;
        return s->word[s->top];
    }
}

void checkPalindrom(stack *s, char *t){
    int palindrom = 1, i; 

    int len = strlen(t);
    for(i=0; i<len; i++){
        if(!penuh(s)){
            pushStack(s, t[i]);
        }else{
            break;
        }
    }

    for(i=0; i<len; i++){
        if(s->word[i] != t[len-i-1]){
            palindrom = 0;
            break;
        }
    }

    if(palindrom){
        printf("Kalimat tersebut adalah palindrom");
    }else{
        printf("Kalimat tersebut bukan palindrom");
    }
}

int main(){
    stack s;
    char kalimat[MAX];

    printf("===== Cek Palindrom =====\n");
    printf("Masukkan kalimat : ");
    fgets(kalimat, sizeof(kalimat), stdin);
    kalimat[strcspn(kalimat, "\n")] = '\0';

    inisialisasi(&s);
    checkPalindrom(&s, kalimat);

    return 0;
}