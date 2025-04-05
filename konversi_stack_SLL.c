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

int pop(Stack* s){
    Node* temp = s->top;
    int y;
    if(empty(s)){
        printf("Stack kosong\n");
        return -1;
    }

    y = temp->item;
    s->top = s->top->next;
    free(temp);
    s->count--;
    return y;
}

void tobiner(Stack *s, int x){
    int temp;
    while(x != 0){
        temp = x % 2;
        push(s, temp);
        x /= 2;
    }
}

void tooctal(Stack *s, int x){
    int temp;
    while(x != 0){
        temp = x % 8;
        push(s, temp);
        x /= 8;
    }
}

void tohexa(Stack *s, int x){
    int temp;
    while(x != 0){
        temp = x % 16;
        push(s, temp);
        x /= 16;
    }
}

void print(Stack* s, int choice){
    Node* temp = s->top;
    if(empty(s)){
        printf("Stack kosong\n");
        return;
    }else{
        while(!empty(s)){
            int val = pop(s);
            if(choice == 3 && val >= 10){
                printf("%c", val - 10 + 'A');
            }else{
                printf("%d", val);
            }
        }        
    }
    printf("\n");
}

int main(){
    int desimal, choice;
    char loop = 'y';
    Stack s;

    puts("=====Program Konversi Stack SLL=====");
    init(&s);
    while(loop == 'y' || loop == 'Y'){
        puts("1. Konversi desimal ke biner");
        puts("2. Konversi desimal ke oktal");
        puts("3. Konversi desimal ke heksadesimal");
        printf("Pilihan: "); scanf("%d", &choice);
        
        switch(choice){
            case 1:
                printf("Masukkan bilangan desimal: "); scanf("%d", &desimal);
                tobiner(&s, desimal);
                break;
            case 2:
                printf("Masukkan bilangan desimal: "); scanf("%d", &desimal);
                tooctal(&s, desimal);
                break;
            case 3:
                printf("Masukkan bilangan desimal: "); scanf("%d", &desimal);
                tohexa(&s, desimal);
                break;
            default:
                printf("Pilihan tidak tersedia\n");
        }

        puts("Hasil konversi:");
        print(&s, choice);
        
        fflush(stdin);
        printf("Lanjutkan? (y/n): "); scanf("%c", &loop);
        fflush(stdin);
    }
}