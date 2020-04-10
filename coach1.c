#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "MyRecord.h"
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include "merge.h"
#include <signal.h>

double cnt=0;
void counter();



int main(int argc, char** argv)
{
    struct timeval t1, t2;
    double elapsedTime;
    double time1,time2;

    gettimeofday(&t1, NULL);

    FILE *fpb;
    MyRecord rec;
    long lSize;
    int numOfrecords, i;
    int  status;
    int coachNumber;
    

    fpb = fopen (argv[1],"rb");
    if (fpb==NULL) {
            return 1;
        }

    numOfrecords=atoi(argv[4]);


    int p1[2];
    int p1r[2];
    int p2[2];
    int p2r[2];
    int p1t[2];
    int p2t[2];
    int rsize;
    MyRecord rc;

    if (pipe(p1)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p1r)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p2)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p2r)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p1t)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p2t)==-1) { perror("pipe call"); exit(1);}
    MyRecord* xx=(MyRecord*)malloc(numOfrecords*sizeof(MyRecord));

    int stop1=numOfrecords/2;

    for (i=0; i<numOfrecords ; i++) {
        fread(&rec, sizeof(rec), 1, fpb);
        xx[i]=rec;
    }



    fclose (fpb);


    wait(NULL);
    int sorter1 = fork();

    if(sorter1==0){

        char *arg[2];
        arg[0] = "./sorter";
        char str[12];
        sprintf(str, "%d", stop1);
        arg[1] = str;
        arg[2] = argv[2];
        arg[3] = argv[3];
        arg[4] = NULL;
        dup2(p1[0],0);
        dup2(p1r[1],1);
        dup2(p1t[1],3);


        execvp(arg[0],arg);
        exit(1);
        //printf("\n\n\n");
    }else if(sorter1==-1){
        perror("fork"); exit(1);
    }else{
        int sorter2 = fork();
        if(sorter2==0){

            char *arg[2];
            arg[0] = "./sorter";
            char str[12];
            sprintf(str, "%d", numOfrecords-stop1);
            arg[1] = str;
            arg[2] =argv[2];
            arg[3] = argv[3];
            arg[4] = NULL;
            dup2(p2[0],0);
            dup2(p2r[1],1);
            dup2(p2t[1],3);


            execvp(arg[0],arg);
            exit(1);

        }else if(sorter2==-1){
            perror("fork"); exit(1);
        }else{
            signal(SIGUSR2,counter);
            for(i=0;i<numOfrecords;i++){
                if(i<stop1){
                    write(p1[1],&xx[i],sizeof(MyRecord));
                }else{
                    write(p2[1],&xx[i],sizeof(MyRecord));
                }
            }
            close(p1[1]);
            close(p2[1]);
            FILE * pFile;


            char * str3 = (char *) malloc(1 + strlen(argv[1])+ strlen(argv[3]) );
            strcpy(str3, argv[1]);
            strcat(str3, argv[3]);



            pFile = fopen (str3, "w");
            MyRecord* a1=(MyRecord*)malloc(stop1*sizeof(MyRecord));
            MyRecord* a2=(MyRecord*)malloc((numOfrecords-stop1)*sizeof(MyRecord));
            MyRecord* final=(MyRecord*)malloc(numOfrecords*sizeof(MyRecord));
            int i1=0;
            int i2=0;
            for (i=0; i<numOfrecords ; i++) {
                if(i<stop1){
                    rsize=read(p1r[0],&rc,sizeof(MyRecord));
                    a1[i1]=rc;
                    i1++;
                }else{
                    rsize=read(p2r[0],&rc,sizeof(MyRecord));
                    a2[i2]=rc;
                    i2++;
                }
            }
            while( (waitpid(sorter1, &status, WNOHANG)) == 0 ){
                sleep(1);
            }
            while( (waitpid(sorter2, &status, WNOHANG)) == 0 ){
                sleep(1);
            }
            int field=atoi(argv[3]);
            merge(a1,a2,final,field,stop1,numOfrecords);


            for ( i=0; i<numOfrecords ; i++) {
                fprintf(pFile,"%ld %s %s  %s %d %s %s %-9.2f\n", \
                final[i].custid, final[i].LastName, final[i].FirstName, \
                final[i].Street, final[i].HouseID, final[i].City,final[i].postcode, \
                final[i].amount);
            }
            read(p1t[0],&time1,sizeof(double));
            read(p2t[0],&time2,sizeof(double));
            gettimeofday(&t2, NULL);
            elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
            elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

            write(3,&time1,sizeof(double));
            write(3,&time2,sizeof(double));
            write(3,&elapsedTime,sizeof(double));
            write(3,&cnt,sizeof(double));

            fclose(pFile);

            free(xx);
            free(str3);
            free(a1);
            free(a2);
            free(final);
        }
    }
}
void counter(){
  cnt++;
}
