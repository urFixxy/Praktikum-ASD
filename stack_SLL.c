#include <stdio.h>
#include <stdlib.h>

typedef struct simpul Node;
struct simpul{
    int item;
    Node* next;
};

typedef struct tumpukan Stack;
struct tumpukan{
    Node* top;
    int count;
};

void init(Stack* s){
    s->top = NULL;
    s->count = 0;
}

int empty(Stack* s){
    return s->top == NULL;
}

void push(Stack* s, int x){
    Node* new = (Node*)malloc(sizeof(Node));
    if(new == NULL){
        printf("Alokasi memori gagal\n");
        return;
    }
    new->item = x;
    new->next = s->top;
    s->top = new;
    s->count++;
}

void pop(Stack* s){
    if(empty(s)){
        printf("Stack kosong\n");
        return;
    }
    Node* temp = s->top;
    s->top = s->top->next;
    free(temp);
    s->count--;
}

void print(Stack* s){
    Node* temp = s->top;
    if(empty(s)){
        printf("Stack kosong\n");
        return;
    }else{
        printf("Isi stack: ");
        while(temp != NULL){
            printf("%d ", temp->item);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main(){
    int input, choice;
    char loop = 'y';
    Stack s;

    init(&s);
    puts("=====Program Stack SLL=====");
    while(loop == 'y' || loop == 'Y'){
        puts("1. Push");
        puts("2. Pull");
        puts("3. Cetak");
        printf("Pilihan: "); scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Masukkan angka: "); scanf("%d", &input);
                push(&s, input);
                break;
            case 2:
                pop(&s);
                break;
            case 3:
                print(&s);
                break;
            default:
                puts("Pilihan tidak valid");
                break;
        }
        
        fflush(stdin);
        printf("Lanjutkan? (y/n): "); scanf("%c", &loop);
        fflush(stdin);
    }
}