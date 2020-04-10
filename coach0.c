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
#include "quick.h"
#include <signal.h>

double cnt=0;
void counter();
int main(int argc, char** argv)
{
    struct timeval t1, t2;
    double elapsedTime;
    double time;
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


    int p[2];
    int pr[2];
    int pt[2];
    int rsize;
    MyRecord rc;

    if (pipe(p)==-1) { perror("pipe call"); exit(1);}
    if (pipe(pr)==-1) { perror("pipe call"); exit(1);}
    if (pipe(pt)==-1) { perror("pipe call"); exit(1);}

    MyRecord* xx=(MyRecord*)malloc(numOfrecords*sizeof(MyRecord));

    for (i=0; i<numOfrecords; i++) {
        fread(&rec, sizeof(rec), 1, fpb);
        xx[i]=rec;
    }




    fclose (fpb);


    wait(NULL);
    int kid = fork();

    if(kid==0){
        char *arg[2];
        arg[0] = "./sorter";
        char str[12];
        sprintf(str, "%d", numOfrecords);
        arg[1] = str;
        arg[2] = argv[2];
        arg[3] = argv[3];
        // char str2[12];
        // sprintf(str2, "%d", kid);
        // arg[4] = str2;
        arg[4] = NULL;
        dup2(p[0],0);
        dup2(pr[1],1);
        dup2(pt[1],3);



        execvp(arg[0],arg);
        exit(1);
    }else if(kid==-1){
        perror("fork"); exit(1);
    }else{
        signal(SIGUSR2,counter);
        for(i=0;i<numOfrecords;i++){
            write(p[1], &xx[i], sizeof(MyRecord));

        }
        close(p[1]);
        FILE * pFile;
        char * str3 = (char *) malloc(1 + strlen(argv[1])+ strlen(argv[3]) );
        strcpy(str3, argv[1]);
        strcat(str3, argv[3]);



        pFile = fopen (str3, "w");
        MyRecord* a1=(MyRecord*)malloc(numOfrecords*sizeof(MyRecord));
        for (i=0; i<numOfrecords ; i++) {
            rsize=read(pr[0],&rc,sizeof(MyRecord));

            a1[i]=rc;

        }

        while( (waitpid(kid, &status, WNOHANG)) == 0 ){
            sleep(1);
        }

        for (int i=0; i<numOfrecords ; i++) {

            fprintf(pFile,"%ld %s %s  %s %d %s %s %-9.2f\n", \
            a1[i].custid, a1[i].LastName, a1[i].FirstName, \
            a1[i].Street, a1[i].HouseID, a1[i].City, a1[i].postcode, \
            a1[i].amount);
        }
        read(pt[0],&time,sizeof(double));
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

        write(3,&time,sizeof(double)); //xronos sorter
        write(3,&elapsedTime,sizeof(double)); //xronos coach

        write(3,&cnt,sizeof(double));
        //printf("%g \n",cnt);
        fclose(pFile);
        free(a1);

        free(xx);
    }
}

void counter(){
  cnt++;
}
