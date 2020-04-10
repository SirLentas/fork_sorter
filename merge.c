#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MyRecord.h"
void merge(MyRecord a1[],MyRecord a2[],MyRecord final[], int field, int stop1, int numOfrecords){
    int i1=0;
    int i2=0;
    MyRecord b1;
    MyRecord b2;
    for (int i=0; i<numOfrecords ; i++) {
        if(field==1){
            if(i1<stop1)
                b1=a1[i1];
            if(i2<numOfrecords-stop1)
                b2=a2[i2];
            if(b1.custid<=b2.custid){
                final[i]=b1;
                i1++;
            }else{
                final[i]=b2;
                i2++;
            }
        }else if(field==3){
            if(i1<stop1)
                b1=a1[i1];
            if(i2<numOfrecords-stop1)
                b2=a2[i2];
            if(strcmp(b1.FirstName,b2.FirstName)<=0){
                final[i]=b1;
                i1++;
            }else{
                final[i]=b2;
                i2++;
            }
        }else if(field==2){
            if(i1<stop1)
                b1=a1[i1];
            if(i2<numOfrecords-stop1)
                b2=a2[i2];
            if(strcmp(b1.LastName,b2.LastName)<=0){
                final[i]=b1;
                i1++;
            }else{
                final[i]=b2;
                i2++;
            }
        }else if(field==4){
            if(i1<stop1)
                b1=a1[i1];
            if(i2<numOfrecords-stop1)
                b2=a2[i2];
            if(strcmp(b1.Street,b2.Street)<=0){
                final[i]=b1;
                i1++;
            }else{
                final[i]=b2;
                i2++;
            }
        }else if(field==5){
            if(i1<stop1)
                b1=a1[i1];
            if(i2<numOfrecords-stop1)
                b2=a2[i2];
            if(b1.HouseID<=b2.HouseID){
                final[i]=b1;
                i1++;
            }else{
                final[i]=b2;
                i2++;
            }
        }else if(field==6){
            
            if(i1<stop1)
                b1=a1[i1];
            if(i2<numOfrecords-stop1)
                b2=a2[i2];
            if(strcmp(b1.City,b2.City)<=0){
                final[i]=b1;
                i1++;
            }else{
                final[i]=b2;
                i2++;
            }
        }else if(field==7){
            if(i1<stop1)
                b1=a1[i1];
            if(i2<numOfrecords-stop1)
                b2=a2[i2];
            if(strcmp(b1.postcode,b2.postcode)<=0){
                final[i]=b1;
                i1++;
            }else{
                final[i]=b2;
                i2++;
            }
        }else if(field==8){
        
            if(i1<stop1)
                b1=a1[i1];
            if(i2<numOfrecords-stop1)
                b2=a2[i2];
            if(b1.amount<=b2.amount){
                final[i]=b1;
                i1++;
            }else{
                final[i]=b2;
                i2++;
            }
        }
    }
}