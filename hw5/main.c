#include <stdio.h>
#include <stdlib.h>

typedef struct my_mm{
    int mm[10];
    int count;
}my_mm_t;
int g_mem[10];
my_mm_t mms;

int* my_calloc(int n, int size){
    mms.count++;
    int np = 0;
    for(int i = 0; i < 10; i++){
        (g_mem[i] == 0)? (np++):(np=0);
        if(np == n*size){
            for(int j = i-np+1; j < i+1; j++){
                g_mem[j] = mms.count; 
            }
            for(int k = 0; k < 10; k++){
                (g_mem[k]!=0)? (mms.mm[k] = 1):(mms.mm[k] = 0);
                printf("%d",mms.mm[k]);
            }
            printf("\n");
            return &g_mem[i];
        }
    }
    for(int k = 0; k < 10; k++){
        (g_mem[k]!=0)? (mms.mm[k] = 1):(mms.mm[k] = 0);
        printf("%d",mms.mm[k]);
    }
    printf(" <-Out of space\n");
    return NULL;
}


void my_free(int* p){
    int count = 0;
    for(int i = 0; i < 10; i++){
        if(g_mem[i]==*p){
            g_mem[i] = 0;
        }
        (g_mem[i]!=0)? (mms.mm[i] = 1):(mms.mm[i] = 0);
        printf("%d",mms.mm[i]);
    }
    printf("\n");
}

int main(){
    int* np1 = my_calloc(1,1);
    int* np2 = my_calloc(1,2);
    int* np3 = my_calloc(1,3);
    int* np4 = my_calloc(1,4);
    my_free(np1);
    my_free(np4);
    int* np5 = my_calloc(1,5);
    return 0;
}
