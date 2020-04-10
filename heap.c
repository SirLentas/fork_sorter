#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MyRecord.h"


void heapswap(void* a, void* b, int s){
    void* tmp = malloc(s);
    memcpy(tmp, a, s);
    memcpy(a, b, s);
    memcpy(b, tmp, s);
    free(tmp);
}
  

void heapify(MyRecord arr[], int n, int i, int field) 
{ 
    int largest = i; 
    int l = 2*i + 1; 
    int r = 2*i + 2; 
    if(field==1){
        if (l < n && arr[l].custid > arr[largest].custid)
        {
            largest = l;
        }
        if (r < n && arr[r].custid > arr[largest].custid)
        {
            largest = r;
        }
        if (largest != i) 
        { 
            heapswap(&arr[i],&arr[largest],sizeof(arr[i])); 
            heapify(arr, n, largest, field); 
        } 
    }else if(field==3){
        if (l < n && strcmp(arr[l].FirstName,arr[largest].FirstName)>0)
        {
            largest = l;
        }
        if (r < n && strcmp(arr[r].FirstName,arr[largest].FirstName)>0)
        {
            largest = r;
        }
        if (largest != i) 
        { 
            heapswap(&arr[i],&arr[largest],sizeof(arr[i])); 
            heapify(arr, n, largest, field); 
        } 
    }else if(field==2){
        if (l < n && strcmp(arr[l].LastName,arr[largest].LastName)>0)
        {
            largest = l;
        }
        if (r < n && strcmp(arr[r].LastName,arr[largest].LastName)>0)
        {
            largest = r;
        }
        if (largest != i) 
        { 
            heapswap(&arr[i],&arr[largest],sizeof(arr[i])); 
            heapify(arr, n, largest, field); 
        } 
    }else if(field==4){
        if (l < n && strcmp(arr[l].Street,arr[largest].Street)>0)
        {
            largest = l;
        }
        if (r < n && strcmp(arr[r].Street,arr[largest].Street)>0)
        {
            largest = r;
        }
        if (largest != i) 
        { 
            heapswap(&arr[i],&arr[largest],sizeof(arr[i])); 
            heapify(arr, n, largest, field); 
        } 
    }else if(field==5){
        if (l < n && arr[l].HouseID > arr[largest].HouseID)
        {
            largest = l;
        }
        if (r < n && arr[r].HouseID > arr[largest].HouseID)
        {
            largest = r;
        }
        if (largest != i) 
        { 
            heapswap(&arr[i],&arr[largest],sizeof(arr[i])); 
            heapify(arr, n, largest, field); 
        } 
        
    }else if(field==6){
        if (l < n && strcmp(arr[l].City,arr[largest].City)>0)
        {
            largest = l;
        }
        if (r < n && strcmp(arr[r].City,arr[largest].City)>0)
        {
            largest = r;
        }
        if (largest != i) 
        { 
            heapswap(&arr[i],&arr[largest],sizeof(arr[i])); 
            heapify(arr, n, largest, field); 
        } 
    }else if(field==7){
        if (l < n && strcmp(arr[l].postcode,arr[largest].postcode)>0)
        {
            largest = l;
        }
        if (r < n && strcmp(arr[r].postcode,arr[largest].postcode)>0)
        {
            largest = r;
        }
        if (largest != i) 
        { 
            heapswap(&arr[i],&arr[largest],sizeof(arr[i])); 
            heapify(arr, n, largest, field); 
        } 
    }else if(field==8){
        if (l < n && arr[l].amount> arr[largest].amount)
        {
            largest = l;
        }
        if (r < n && arr[r].amount > arr[largest].amount)
        {
            largest = r;
        }
        if (largest != i) 
        { 
            heapswap(&arr[i],&arr[largest],sizeof(arr[i])); 
            heapify(arr, n, largest, field); 
        } 
    }
} 

void heapSort(MyRecord arr[], int n, int field) 
{ 
    
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i, field); 
  
    
    for (int i=n-1; i>=0; i--) 
    { 
        heapswap(&arr[0],&arr[i],sizeof(arr[i])); 
        heapify(arr, i, 0, field); 
    } 
}
