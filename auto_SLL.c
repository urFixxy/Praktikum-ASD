#include <stdio.h>
#include <stdlib.h>

typedef struct simpul Node;
struct simpul{
    int data;
    Node* next;
};

Node* head = NULL;
Node* new;

void Node_alocation(int x){
    new = (Node*)malloc(sizeof(Node));
    if(new == NULL){
        printf("Alokasi memori gagal\n");
        exit(1);
    }else{
        new->data = x;
        new->next = NULL;
    }
}

void Free_node(Node* p){
    free(p);
    p = NULL;
}

void Auto_insert(int x){
    Node_alocation(x);
    if(head == NULL){
        head = new;
    }else{
        Node* p = head;
        Node* before;
        while(p->next != NULL && p->data < x){
            before = p;
            p = p->next;
        }

        if(p == head && p->next != NULL){
            new->next = p;
            head = new;
        }else if(p->next == NULL){
            p->next = new;
            new->next = NULL;
        }else{
            before->next = new;
            new->next = p;
        }
    }
}

void Remove(int x){
    Node* p = head;
    Node* before;
    while(p != NULL && p->data != x){
        before = p;
        p = p->next;
    }

    if(p == NULL){
        printf("Data tidak ditemukan\n");
    }else if(p == head){
        head = p->next;
        Free_node(p);
    }else if(p->next == NULL){
        before->next = NULL;
        Free_node(p);
    }else{
        before->next = p->next;
        Free_node(p);
    }
}

void Show(){
    Node* p = head;
    while(p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    int input, choice;
    char loop = 'y';

    puts("=====Program Auto SLL=====");
    while(loop == 'y' || loop == 'Y'){
        puts("1. Sisip");
        puts("2. Hapus");
        printf("Masukkan proses : "); scanf("%d", &choice);
        
        switch(choice){
            case 1:
            printf("Masukkan data untuk disisipkan : "); scanf("%d", &input);
            Auto_insert(input);
            break;
            case 2:
            printf("Masukkan data untuk dihapus : "); scanf("%d", &input);
            Remove(input);
            break;
            default:
            printf("Opsi tidak tersedia\n");
            break;
        }

        Show();
        printf("Lanjutkan? (y/n) : "); scanf(" %c", &loop);
        fflush(stdin);
    }

    printf("Final data : \n");
    Show();

    return 0;
}