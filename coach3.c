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
    double time1,time2,time3,time4,time5,time6,time7,time8;

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
    int p3[2];
    int p3r[2];
    int p4[2];
    int p4r[2];
    int p5[2];
    int p5r[2];
    int p6[2];
    int p6r[2];
    int p7[2];
    int p7r[2];
    int p8[2];
    int p8r[2];
    int p1t[2];
    int p2t[2];
    int p3t[2];
    int p4t[2];
    int p5t[2];
    int p6t[2];
    int p7t[2];
    int p8t[2];
    int rsize;
    MyRecord rc;

    if (pipe(p1)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p1r)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p2)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p2r)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p3)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p3r)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p4)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p4r)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p5)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p5r)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p6)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p6r)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p7)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p7r)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p8)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p8r)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p1t)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p2t)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p3t)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p4t)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p5t)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p6t)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p7t)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p8t)==-1) { perror("pipe call"); exit(1);}

    int stop1=numOfrecords/16;
    int stop2=numOfrecords/8;
    int stop3=numOfrecords*3/16;
    int stop4=numOfrecords/4;
    int stop5=numOfrecords*6/16;
    int stop6=numOfrecords/2;
    int stop7=numOfrecords*12/16;

    MyRecord* xx=(MyRecord*)malloc(numOfrecords*sizeof(MyRecord));


    for (i=0; i<numOfrecords ; i++) {
        fread(&rec, sizeof(rec), 1, fpb);
        xx[i]=rec;
    }

    fclose (fpb);
   ;
    wait(NULL);
    int sorter1 = fork();

    if(sorter1==0){

        char *arg[2];
        arg[0] = "./sorter";
        char str[12];
        sprintf(str, "%d", stop1);
        arg[1] = str;
        arg[2] =argv[2];
        arg[3] = argv[3];
        arg[4] = NULL;
        dup2(p1[0],0);
        dup2(p1r[1],1);
        dup2(p1t[1],3);


        execvp(arg[0],arg);
        exit(1);

    }else if(sorter1==-1){
        perror("fork"); exit(1);
    }else{
        int sorter2 = fork();
        if(sorter2==0){

            char *arg[2];
            arg[0] = "./sorter";
            char str[12];
            sprintf(str, "%d", stop2-stop1);
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
            int sorter3 = fork();
            if(sorter3==0){
                char *arg[2];
                arg[0] = "./sorter";
                char str[12];
                sprintf(str, "%d", stop3-stop2);
                arg[1] = str;
                arg[2] =argv[2];
                arg[3] = argv[3];
                arg[4] = NULL;
                dup2(p3[0],0);
                dup2(p3r[1],1);
                dup2(p3t[1],3);


                execvp(arg[0],arg);
                exit(1);

            }else if(sorter3==-1){
                perror("fork"); exit(1);
            }else{
                int sorter4 = fork();
                if(sorter4==0){

                    char *arg[2];
                    arg[0] = "./sorter";
                    char str[12];
                    sprintf(str, "%d", stop4-stop3);
                    arg[1] = str;
                    arg[2] =argv[2];
                    arg[3] = argv[3];
                    arg[4] = NULL;
                    dup2(p4[0],0);
                    dup2(p4r[1],1);
                    dup2(p4t[1],3);


                    execvp(arg[0],arg);
                    exit(1);

                }else if(sorter4==-1){
                    perror("fork"); exit(1);
                }else{
                    int sorter5 = fork();
                    if(sorter5==0){

                        char *arg[2];
                        arg[0] = "./sorter";
                        char str[12];
                        sprintf(str, "%d", stop5-stop4);
                        arg[1] = str;
                        arg[2] =argv[2];
                        arg[3] = argv[3];
                        arg[4] = NULL;
                        dup2(p5[0],0);
                        dup2(p5r[1],1);
                        dup2(p5t[1],3);


                        execvp(arg[0],arg);
                        exit(1);

                    }else if(sorter5==-1){
                        perror("fork"); exit(1);
                    }else{
                        int sorter6 = fork();
                        if(sorter6==0){

                            char *arg[2];
                            arg[0] = "./sorter";
                            char str[12];
                            sprintf(str, "%d", stop6-stop5);
                            arg[1] = str;
                            arg[2] =argv[2];
                            arg[3] = argv[3];
                            arg[4] = NULL;
                            dup2(p6[0],0);
                            dup2(p6r[1],1);
                            dup2(p6t[1],3);


                            execvp(arg[0],arg);
                            exit(1);

                        }else if(sorter6==-1){
                            perror("fork"); exit(1);
                        }else{
                            int sorter7 = fork();
                            if(sorter7==0){

                                char *arg[2];
                                arg[0] = "./sorter";
                                char str[12];
                                sprintf(str, "%d", stop7-stop6);
                                arg[1] = str;
                                arg[2] =argv[2];
                                arg[3] = argv[3];
                                arg[4] = NULL;
                                dup2(p7[0],0);
                                dup2(p7r[1],1);
                                dup2(p7t[1],3);


                                execvp(arg[0],arg);
                                exit(1);

                            }else if(sorter7==-1){
                                perror("fork"); exit(1);
                            }else{
                                signal(SIGUSR2,counter);
                                int sorter8 = fork();
                                if(sorter8==0){

                                    char *arg[2];
                                    arg[0] = "./sorter";
                                    char str[12];
                                    sprintf(str, "%d", numOfrecords-stop7);
                                    arg[1] = str;
                                    arg[2] =argv[2];
                                    arg[3] = argv[3];
                                    arg[4] = NULL;
                                    dup2(p8[0],0);
                                    dup2(p8r[1],1);
                                    dup2(p8t[1],3);

                                    execvp(arg[0],arg);
                                    exit(1);

                                }else if(sorter8==-1){
                                    perror("fork"); exit(1);
                                }else{
                                   for (i=0; i<numOfrecords ; i++) {

                                        if(i<stop1){
                                            write(p1[1],&xx[i],sizeof(MyRecord));
                                        }else if(i<stop2){
                                            write(p2[1],&xx[i],sizeof(MyRecord));
                                        }else if(i<stop3){
                                            write(p3[1],&xx[i],sizeof(MyRecord));
                                        }else if(i<stop4){
                                            write(p4[1],&xx[i],sizeof(MyRecord));
                                        }else if(i<stop5){
                                            write(p5[1],&xx[i],sizeof(MyRecord));
                                        }else if(i<stop6){
                                            write(p6[1],&xx[i],sizeof(MyRecord));
                                        }else if(i<stop7){
                                            write(p7[1],&xx[i],sizeof(MyRecord));
                                        }else{
                                            write(p8[1],&xx[i],sizeof(MyRecord));
                                        }
                                    }
                                    close(p1[1]);
                                    close(p2[1]);
                                    close(p3[1]);
                                    close(p4[1]);
                                    close(p5[1]);
                                    close(p6[1]);
                                    close(p7[1]);
                                    close(p8[1]);

                                    FILE * pFile;
                                    char * str3 = (char *) malloc(1 + strlen(argv[1])+ strlen(argv[3]) );
                                    strcpy(str3, argv[1]);
                                    strcat(str3, argv[3]);



                                    pFile = fopen (str3, "w");

                                    MyRecord* a1=(MyRecord*)malloc(stop1*sizeof(MyRecord));
                                    MyRecord* a2=(MyRecord*)malloc((stop2-stop1)*sizeof(MyRecord));
                                    MyRecord* a3=(MyRecord*)malloc((stop3-stop2)*sizeof(MyRecord));
                                    MyRecord* a4=(MyRecord*)malloc((stop4-stop3)*sizeof(MyRecord));
                                    MyRecord* a5=(MyRecord*)malloc((stop5-stop4)*sizeof(MyRecord));
                                    MyRecord* a6=(MyRecord*)malloc((stop6-stop5)*sizeof(MyRecord));
                                    MyRecord* a7=(MyRecord*)malloc((stop7-stop6)*sizeof(MyRecord));
                                    MyRecord* a8=(MyRecord*)malloc((numOfrecords-stop7)*sizeof(MyRecord));
                                    MyRecord* a12=(MyRecord*)malloc(stop2*sizeof(MyRecord));
                                    MyRecord* a34=(MyRecord*)malloc((stop4-stop2)*sizeof(MyRecord));
                                    MyRecord* a56=(MyRecord*)malloc((stop6-stop4)*sizeof(MyRecord));
                                    MyRecord* a78=(MyRecord*)malloc((numOfrecords-stop6)*sizeof(MyRecord));
                                    MyRecord* a1234=(MyRecord*)malloc(stop4*sizeof(MyRecord));
                                    MyRecord* a5678=(MyRecord*)malloc((numOfrecords-stop4)*sizeof(MyRecord));

                                    MyRecord* final=(MyRecord*)malloc(numOfrecords*sizeof(MyRecord));
                                    int i1=0;
                                    int i2=0;
                                    int i3=0;
                                    int i4=0;
                                    int i5=0;
                                    int i6=0;
                                    int i7=0;
                                    int i8=0;

                                    for (i=0; i<numOfrecords ; i++) {
                                        if(i<stop1){
                                            rsize=read(p1r[0],&rc,sizeof(MyRecord));
                                            a1[i1]=rc;
                                            i1++;
                                        }else if(i<stop2){
                                            rsize=read(p2r[0],&rc,sizeof(MyRecord));
                                            a2[i2]=rc;
                                            i2++;
                                        }else if(i<stop3){
                                            rsize=read(p3r[0],&rc,sizeof(MyRecord));
                                            a3[i3]=rc;
                                            i3++;
                                        }else if(i<stop4){
                                            rsize=read(p4r[0],&rc,sizeof(MyRecord));
                                            a4[i4]=rc;
                                            i4++;
                                        }else if(i<stop5){
                                            rsize=read(p5r[0],&rc,sizeof(MyRecord));
                                            a5[i5]=rc;
                                            i5++;
                                        }else if(i<stop6){
                                            rsize=read(p6r[0],&rc,sizeof(MyRecord));
                                            a6[i6]=rc;
                                            i6++;
                                        }else if(i<stop7){
                                            rsize=read(p7r[0],&rc,sizeof(MyRecord));
                                            a7[i7]=rc;
                                            i7++;
                                        }else{
                                            rsize=read(p8r[0],&rc,sizeof(MyRecord));
                                            a8[i8]=rc;
                                            i8++;
                                        }
                                    }
                                    while( (waitpid(sorter1, &status, WNOHANG)) == 0 ){
                                        sleep(1);
                                    }
                                    while( (waitpid(sorter2, &status, WNOHANG)) == 0 ){
                                        sleep(1);
                                    }
                                    while( (waitpid(sorter3, &status, WNOHANG)) == 0 ){
                                        sleep(1);
                                    }
                                    while( (waitpid(sorter4, &status, WNOHANG)) == 0 ){
                                        sleep(1);
                                    }
                                    while( (waitpid(sorter5, &status, WNOHANG)) == 0 ){
                                        sleep(1);
                                    }
                                    while( (waitpid(sorter6, &status, WNOHANG)) == 0 ){
                                        sleep(1);
                                    }
                                    while( (waitpid(sorter7, &status, WNOHANG)) == 0 ){
                                        sleep(1);
                                    }
                                    while( (waitpid(sorter8, &status, WNOHANG)) == 0 ){
                                        sleep(1);
                                    }
                                    int field=atoi(argv[3]);
                                    merge(a1,a2,a12,field,stop1,stop2);
                                    merge(a3,a4,a34,field,stop3-stop2,stop4-stop2);
                                    merge(a5,a6,a56,field,stop5-stop4,stop6-stop4);
                                    merge(a7,a8,a78,field,stop7-stop6,numOfrecords-stop6);
                                    merge(a12,a34,a1234,field,stop2,stop4);
                                    merge(a56,a78,a5678,field,stop6-stop4,numOfrecords-stop4);
                                    merge(a1234,a5678,final,field,stop4,numOfrecords);
                                    for ( i=0; i<numOfrecords ; i++) {

                                        fprintf(pFile,"%ld %s %s  %s %d %s %s %-9.2f\n", \
                                        final[i].custid, final[i].LastName, final[i].FirstName, \
                                        final[i].Street, final[i].HouseID, final[i].City,final[i].postcode, \
                                        final[i].amount);
                                    }
                                    read(p1t[0],&time1,sizeof(double));
                                    read(p2t[0],&time2,sizeof(double));
                                    read(p3t[0],&time3,sizeof(double));
                                    read(p4t[0],&time4,sizeof(double));
                                    read(p5t[0],&time5,sizeof(double));
                                    read(p6t[0],&time6,sizeof(double));
                                    read(p7t[0],&time7,sizeof(double));
                                    read(p8t[0],&time8,sizeof(double));
                                    gettimeofday(&t2, NULL);
                                    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
                                    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms

                                    write(3,&time1,sizeof(double));
                                    write(3,&time2,sizeof(double));
                                    write(3,&time3,sizeof(double));
                                    write(3,&time4,sizeof(double));
                                    write(3,&time5,sizeof(double));
                                    write(3,&time6,sizeof(double));
                                    write(3,&time7,sizeof(double));
                                    write(3,&time8,sizeof(double));
                                    write(3,&elapsedTime,sizeof(double));
                                    write(3,&cnt,sizeof(double));

                                    fclose(pFile);
                                    free(a1);
                                    free(a2);
                                    free(a3);
                                    free(a4);
                                    free(a5);
                                    free(a6);
                                    free(a7);
                                    free(a8);
                                    free(a12);
                                    free(a34);
                                    free(a56);
                                    free(a78);
                                    free(a1234);
                                    free(a5678);
                                    free(final);


                                    free(xx);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void counter(){
  cnt++;
}
