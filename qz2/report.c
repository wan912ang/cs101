#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct lotto_record{
    int lotto_no;
    int lotto_receipt;
    int emp_id;
    char lotto_date[32];
    char lotto_time[32];
}lotto_record_t;

typedef struct lotto_copy{
    int copy_date;
    int copy_no;
    int copy_group;
    int copy_receipt;
    char cp_date[32];
}lotto_copy_t;

typedef struct lotto_total{
    int total_date;
    int total_no;
    int total_group;
    int total_receipt;
}lotto_total_t;

int main(){
    FILE* rfp = fopen("records.bin", "r");
    char line_ch;
    int count = 0;
    while((line_ch = fgetc(rfp)) != EOF){
        count++;
    }
    int total_record = count/sizeof(lotto_record_t);
    fclose(rfp);

    rfp = fopen("records.bin", "r");
    lotto_record_t tmp[total_record];
    lotto_copy_t copy[total_record];
    lotto_total_t total;
    fread(&tmp, sizeof(lotto_record_t), total_record, rfp);

    for(int i = 0; i < total_record; i++){
        total.total_date++;
        strcpy(copy[i].cp_date,tmp[i].lotto_date);
        copy[i].copy_no = tmp[i].lotto_no;
        copy[i].copy_receipt = tmp[i].lotto_receipt;
        copy[i].copy_group = tmp[i].lotto_receipt/55;
    }
    int i,j,document = 0;
    for(i = 0; i < total_record; i++){
        document = i + 1;
        for(j= i+1; j < total_record; j++){
            if(strcmp(copy[j].cp_date,tmp[i].lotto_date)==0){
                copy[i].copy_no = copy[j].copy_no;
                copy[i].copy_group += copy[j].copy_group;
                copy[i].copy_receipt += copy[j].copy_receipt;
            }
            else break;
        }
        if(j == total_record-1){
            break;
        }
        else i = j - 1;
    }
    fclose(rfp);

    FILE* wfp = fopen("report.txt", "w+");
    fprintf(wfp,"========= lotto649 Report =========\n");
    fprintf(wfp,"- Date ------ Num. ------ Receipt -\n");
    for(int i = 0; i < document ; i++){
        fprintf(wfp,"%s      %d/%d             %d\n",copy[i].cp_date,
                                                   copy[i].copy_no,
                                                   copy[i].copy_group,
                                                   copy[i].copy_receipt);
        total.total_no += copy[i].copy_no;
        total.total_group += copy[i].copy_group;
        total.total_receipt += copy[i].copy_receipt;
    }
    fprintf(wfp,"-----------------------------------\n");
    total.total_date = document;
    fprintf(wfp,"       %d      %d/%d             %d\n",total.total_date,
                                                   total.total_no,
                                                   total.total_group,
                                                   total.total_receipt);
    time_t now = time(0);
    char local_date[32];
    strftime(local_date, 32, "%Y%m%d", localtime(&now));
    fprintf(wfp,"========= %s Printed ========\n", local_date);
    fclose(wfp);

    return 0;
}