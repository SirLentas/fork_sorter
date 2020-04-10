#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "MyRecord.h"
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "quick.h"
#include "heap.h"
#include <sys/time.h>
#include <signal.h>



int main(int argc, char** argv){
    struct timeval t1, t2;
    double elapsedTime;
    gettimeofday(&t1, NULL);

    int i, sum = 0;

    int numOfrecords=atoi(argv[1]);
    int field=atoi(argv[3]);
    MyRecord* aa=(MyRecord*)malloc(numOfrecords*sizeof(MyRecord));
    MyRecord rc;
    int rsize;

    for (int i=0; i<numOfrecords ; i++) {
        rsize=read(0,&rc,sizeof(MyRecord));
        aa[i]=rc;
    }
    if(strcmp(argv[2],"-h")==0){
        heapSort(aa,numOfrecords,field);
    }else{
        quicksort(aa, 0, numOfrecords-1,field);
    }
    for (int i=0; i<numOfrecords ; i++) {
        write(1,&aa[i],sizeof(MyRecord));
    }


    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    write(3,&elapsedTime,sizeof(double));
    kill(getppid(),SIGUSR2);
    free(aa);

}
