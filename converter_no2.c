#include <stdio.h>
#include <math.h>
#define MAX 15

typedef struct{
    int item[MAX];
    int count;
} stack;

void inisialisasiStack(stack *s){
    s->count = 0;
}

int kosong(stack *s){
    return s->count == 0;
}

int penuh(stack *s){
    return s->count == MAX;
}

void stackPush(stack *s, int c){
    if(penuh(s)){
        printf("Stack penuh\n");
    }else{
        s->item[s->count] = c;
        s->count++;
    }
}

int stackPop(stack *s){
    if(kosong(s)){
        printf("Stack kosong\n");
        return '\0';
    }else{
        s->count--;
        return s->item[s->count];
    }
}

void biner(stack *s, int des){
    int x;

    while(des > 0){
        x = des % 2;
        stackPush(s, x);
        des = des / 2;
    }

    printf("Hasil biner : ");

    while(!kosong(s)){
        x = stackPop(s);
        printf("%d", x);
    }

    printf("\n");
}

void octal(stack *s, int des){
    int x;

    while(des > 0){
        x = des % 8;
        stackPush(s, x);
        des = des / 8;
    }

    printf("Hasil oktal : ");

    while(!kosong(s)){
        x = stackPop(s);
        printf("%d", x);
    }

    printf("\n");
}

void heksa(stack *s, int des){
    int x;

    while(des > 0){
        x = des % 16;
        stackPush(s, x);
        des = des / 16;
    }

    printf("Hasil heksa : ");

    while(!kosong(s)){
        if(!kosong(s)){
            x = stackPop(s);
            if(x>=10){
                printf("%c", 'A' + (x-10));
            }else{
                printf("%d", x);
            }
        }else{
            x = stackPop(s);
            printf("%d", x);
        }
    }
}

int main(){
    stack s;
    int des;
    char x = 'y';

    printf("===== Konversi Bilangan Desimal =====\n");

    while(x == 'y' || x == 'Y'){
        printf("Masukkan bilangan desimal: ");
        scanf("%d", &des);
    
        inisialisasiStack(&s);
        biner(&s, des);
        inisialisasiStack(&s);
        octal(&s, des);
        inisialisasiStack(&s);
        heksa(&s, des);
        printf("\nTekan 'y' untuk mengulang, tekan tombol lain untuk keluar: ");
        scanf(" %c", &x);
    }

    printf("Terima kasih\n");
    return 0;
}