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

void reversecal(stack *s, char *t){
    int i , len = strlen(t);

    for(i=0; i<len; i++){
        if(!penuh(s)){
            pushStack(s, t[i]);
        }else{
            break;
        }
    }

    printf("Setelah dibalik : ");
    while(!kosong(s)){
        printf("%c", popStack(s));
    }
}

int main(){
    stack s;
    char kalimat[MAX], x = 'y';

    printf("===== Membalik Kalimat =====\n");
    
    while(x == 'y' || x == 'Y'){
        printf("Masukkan kalimat : ");
        fgets(kalimat, sizeof(kalimat), stdin);
        kalimat[strcspn(kalimat, "\n")] = '\0';
        inisialisasi(&s);
        reversecal(&s, kalimat);
        printf("\nulangi program? (y/t) : ");
        scanf(" %c", &x);
    }

    return 0;
}