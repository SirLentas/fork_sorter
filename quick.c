#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MyRecord.h"



void swap(void* a, void* b, int s){
    void* tmp = malloc(s);
    memcpy(tmp, a, s);
    memcpy(a, b, s);
    memcpy(b, tmp, s);
    free(tmp);
}

int partition (MyRecord arr[], int low, int high, int field)
{
    MyRecord pivot = arr[high]; 
    int i = (low - 1);  
    for (int j = low; j <= high- 1; j++)
    {
        if(field==1){
            if (arr[j].custid<=pivot.custid)
            {
                i++;    
                swap(&arr[i], &arr[j],sizeof(arr[j]));
            }
        }else if(field==3){
            if (strcmp(arr[j].FirstName,pivot.FirstName)<=0)
            {
                i++;    
                swap(&arr[i], &arr[j],sizeof(arr[j]));
            }

        }else if(field==2){
            if (strcmp(arr[j].LastName,pivot.LastName)<=0)
            {
                i++;    
                swap(&arr[i], &arr[j],sizeof(arr[j]));
            }
        }else if(field==4){
            if (strcmp(arr[j].Street,pivot.Street)<=0)
            {
                i++;    
                swap(&arr[i], &arr[j],sizeof(arr[j]));
            }
        }else if(field==5){
            if (arr[j].HouseID<=pivot.HouseID)
            {
                i++;    
                swap(&arr[i], &arr[j],sizeof(arr[j]));
            }
            
        }else if(field==6){
            if (strcmp(arr[j].City,pivot.City)<=0)
            {
                i++;    
                swap(&arr[i], &arr[j],sizeof(arr[j]));
            }
        }else if(field==7){
            if (strcmp(arr[j].postcode,pivot.postcode)<=0)
            {
                i++;    
                swap(&arr[i], &arr[j],sizeof(arr[j]));
            }
        }else if(field==8){
            if (arr[j].amount<=pivot.amount)
            {
                i++;    
                swap(&arr[i], &arr[j],sizeof(arr[j]));
            }
        }
    }
    swap(&arr[i + 1], &arr[high],sizeof(arr[high]));
    return (i + 1);
}

void quicksort(MyRecord a[], int p, int r, int field)    
{
    if(p < r)
    {
        int q;
        q = partition(a, p, r, field);
        quicksort(a, p, q-1, field);
        quicksort(a, q+1, r, field);
    }
}



