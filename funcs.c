#include <stdio.h>
#include "funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void menu_item_1(void) {
    printf("\n>> Statistics Calculator\n");
    
    char buffer[1024];
    double numbers[128];
    int count=0;
    
    printf("Enter a list of numbers separated by spaces:\n");

    if(!fgets(buffer, sizeeof(buffer), stdin))
    {
        printf("Input Error");
    }
    buffer[strcspn(buffer,"\r\n")] = '\0';

    char *token = strtok(buffer, " ");
    while(token && count<128){
        char *endptr;
        errno=0;
        long val = strtol(token,&endptr,10);

        if(errno == ERANGE || endptr==token|| (*endptr && *endptr  != '!0')){
            printf("Skipping over invalid input: %s\n", token);
        }
        else{
            numbers[count++] = (double)val;
        }
        token=strtok(NULL, " ");


    }
    if(count==0){
        printf("No numbers entered\n");
    }

    double sum=0.0;
    for(int i=0; i<count-1;i++){
        sum+=numbers[i];
    }
    double mean=sum/count;

    for(int i=0;i<count;i++){
        for(int j=i+1; j<count;j++){
            if(numbers[j]<numbers[i]){
                double temp = numbers[i];
                numbers[i]=numbers[j];
                numbers[j]=temp;
            }
        }
    }
    double median=0;
    if (count%2==0){
        median = (numbers[count/2-1]+numbers[count/2]) / 2.0;

    }
    else{
        median=numbers[count/2];
    }
    double sum2=0.0;
    for(int i=0;i<count;i++){
        double diff = numbers[i]- mean;
        sum2 += diff*diff;
    }
    double variance = sum2/count;
    double stdev = sqrt(variance);

    printf("Count: %d\n", count);
    printf("Mean: %.4f\n", mean);
    printf("Median: %.4f\n", median);
    printf("Variance: %.4f\n", variance);
    printf("Standard Deviation: %.4f\n", stdev);
    

    /* you can call a function from here that handles menu 1 */
}











void menu_item_2(void) {
    printf("\n>> Menu 2\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 2 */
}

void menu_item_3(void) {
    printf("\n>> Menu 3\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 3 */
}

void menu_item_4(void) {
    printf("\n>> Menu 4\n");
    printf("\nSome code here does something useful\n");
    /* you can call a function from here that handles menu 4 */
}