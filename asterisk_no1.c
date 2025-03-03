#include <stdio.h>
#include <string.h>
#define MAX 50

typedef struct{
    char input[MAX];
    int tos;
}data;

void inisialisasi(data *s){
    s->tos = 0;
}

int penuh(data *s){
    return s->tos == MAX;
}

int kosong(data *s){
    return s->tos == 0;
}

void push(data *s, char x){
    if(penuh(s)){
        printf("Stack Penuh");
        return;
    }else{
        s->input[s->tos] = x;
        s->tos++;
    }
}

char pop(data *s){
    if(kosong(s)){
        printf("Stack kosong");
        return '\0';
    }else{
        s->tos--;
        return s->input[s->tos];
    }
}

void process(data *s, char *t){
    int i, len = strlen(t);

    printf("Hasil : ");

    for(i=0; i<len; i++){
        if(!penuh(s)){
            if(t[i] != '*'){
                push(s, t[i]);
            }else if(t[i] == '*'){
                if(!kosong(s)){
                    printf("%c", pop(s));
                }else{
                    printf("Stack Kosong");
                }
            }
        }else{
            printf("Stack Penuh");
            break;
        }
    }
}

int main(){
    data s;
    char words[MAX];

    printf("===== Program Stack Asterisk =====\n");

    printf("Masukkan karakter : ");
    fgets(words, sizeof(words), stdin);
    words[strcspn(words, "\n")] = '\0';

    inisialisasi(&s);
    process(&s, words);

    return 0;
}