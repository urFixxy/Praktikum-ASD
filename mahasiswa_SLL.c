#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mahasiswa mhs;
struct mahasiswa {
    long long nrp;
    char name[100];
    char class[100];
    mhs *next;
};

mhs *head = NULL;
mhs *new;

void mhs_alocation(){
    new = (mhs*)malloc(sizeof(mhs));
    if(new == NULL){
        printf("Alocation failed\n");
        exit(1);
    }else{
        printf("NRP: ");
        scanf("%lld", &new->nrp);
        fflush(stdin);
        printf("Nama: ");
        fgets(new->name, sizeof(new->name), stdin);
        new->name[strcspn(new->name, "\n")] = '\0';
        fflush(stdin);
        printf("Kelas: ");
        fgets(new->class, sizeof(new->class), stdin);
        new->class[strcspn(new->class, "\n")] = '\0';
        fflush(stdin);
        new->next = NULL;
    }
}

void Auto_insert(){
    mhs_alocation();
    if(head == NULL){
        head = new;
    }else{
        mhs *p = head;
        mhs *before;
        while(p->next != NULL && p->nrp < new->nrp){
            before = p;
            p = p->next;
        }

        if(p->nrp == new->nrp){
            printf("Data sudah ada\n");
            free(new);
            return;
        }

        if(p == head && p->nrp > new->nrp){
            new->next = p;
            head = new;
        }else if(p->next == NULL && p->nrp < new->nrp){
            p->next = new;
            new->next = NULL;
        }else{
            before->next = new;
            new->next = p;
        }
    }
}

void Update(long long x){
    mhs *p = head;
    while(p != NULL && p->nrp != x){
        p = p->next;
    }
    if(p == NULL){
        printf("Data tidak ditemukan\n");
    }else{
        printf("Update data:\n");
        printf("NRP: ");
        scanf("%lld", &p->nrp);
        fflush(stdin);
        printf("Name: ");
        fgets(p->name, sizeof(p->name), stdin);
        p->name[strcspn(p->name, "\n")] = '\0';
        fflush(stdin);
        printf("Class: ");
        fgets(p->class, sizeof(p->class), stdin);
        p->class[strcspn(p->class, "\n")] = '\0';
        fflush(stdin);
    }
}

void Remove(long long x){
    mhs *p = head;
    mhs *before;
    while(p != NULL && p->nrp != x){
        before = p;
        p = p->next;
    }
    if(p == NULL){
        printf("Data tidak ditemukan\n");
    }else{
        if(p == head){
            head = p->next;
            free(p);
            p = NULL;
        }else if(p->next == NULL){
            before->next = NULL;
            free(p);
            p = NULL;
        }else{
            before->next = p->next;
            free(p);
            p = NULL;
        }
    }
}

void Show(){
    mhs *p = head;
    printf("\nData mahasiswa:\n");
    printf("========================\n");
    while(p != NULL){
        printf("NRP: %lld\n", p->nrp);
        printf("Nama: %s\n", p->name);
        printf("Kelas: %s\n", p->class);
        p = p->next;
        printf("========================\n");
    }
    printf("\n");
}

int main(){
    int choice;
    char loop;
    long long nrp;

    puts("=====Program Mhasiswa SLL=====");
    do{
        puts("1. Input");
        puts("2. Update");
        puts("3. Hapus");
        puts("4. Cetak");
        printf("Masukkan pilihan: "); scanf("%d", &choice);

        switch(choice){
            case 1:
                Auto_insert();
                break;
            case 2:
                printf("NRP: ");
                scanf("%lld", &nrp);
                Update(nrp);
                break;
            case 3:
                printf("NRP: ");
                scanf("%lld", &nrp);
                Remove(nrp);
                break;
            case 4:
                Show();
                break;
            default:
                printf("Pilihan tidak tersedia\n");
        }

        fflush(stdin);
        printf("Lanjutkan? (y/n): "); scanf(" %c", &loop);
        fflush(stdin);
    }while(loop == 'y' || loop == 'Y');

    printf("Program Selesai");
    return 0;
}