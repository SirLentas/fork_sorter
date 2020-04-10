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



int main(int argc, char** argv)
{
    struct timeval t1, t2;
    double elapsedTime;
    gettimeofday(&t1, NULL);

    char* type1=NULL;
    char* column1=NULL;
    char* type2=NULL;
    char* column2=NULL;
    char* type3=NULL;
    char* column3=NULL;
    char* type4=NULL;
    char* column4=NULL;
    char* input=NULL;


    if(argc==3){
        for(int i=0;i<argc;i++){
            if(strcmp(argv[i],"-f")==0){
                input=argv[i+1];
                column1="1";
                type1="q";
            }
        }
    }else if(argc==5){
        for(int i=0;i<argc;i++){
            if(strcmp(argv[i],"-f")==0){
                input=argv[i+1];
            }else if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-q")==0){
                column1=argv[i+1];
                type1=argv[i];
            }
        }
    }else if(argc==7){
        for(int i=0;i<argc;i++){
            if(strcmp(argv[i],"-f")==0){
                input=argv[i+1];
            }else if((strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-q")==0) && column1==NULL){
                column1=argv[i+1];
                type1=argv[i];
            }else if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-q")==0){
                column2=argv[i+1];
                type2=argv[i];
            }
        }
    }else if(argc==9){
        for(int i=0;i<argc;i++){
            if(strcmp(argv[i],"-f")==0){
                input=argv[i+1];
            }else if((strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-q")==0) && column1==NULL){
                column1=argv[i+1];
                type1=argv[i];
            }else if((strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-q")==0) && column2==NULL){
                column2=argv[i+1];
                type2=argv[i];
            }else if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-q")==0){
                column3=argv[i+1];
                type3=argv[i];
            }
        }
    }else if(argc==11){
        for(int i=0;i<argc;i++){
            if(strcmp(argv[i],"-f")==0){
                input=argv[i+1];
            }else if((strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-q")==0) && column1==NULL){
                column1=argv[i+1];
                type1=argv[i];
            }else if((strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-q")==0) && column2==NULL){
                column2=argv[i+1];
                type2=argv[i];
            }else if((strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-q")==0) && column3==NULL){
                column3=argv[i+1];
                type3=argv[i];
            }else if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"-q")==0){
                column4=argv[i+1];
                type4=argv[i];
            }
        }
    }else{
        printf("Wrong delimeters\n");
        return -1;
    }


    FILE *fpb;
    MyRecord rec;
    long lSize;
    int numOfrecords, i;
    int  status;
    int coachNumber;
    MyRecord* aa;
    if (argc>11){
        return(1);
    }
    fpb = fopen (input,"rb");
    if (fpb==NULL) {
        return 1;
    }

    // check number of records
    fseek (fpb , 0 , SEEK_END);
    lSize = ftell (fpb);
    rewind (fpb);
    numOfrecords = (int) lSize/sizeof(rec);


    aa=(MyRecord*)malloc(numOfrecords*sizeof(MyRecord));


    int p[2];
    int pr[2];
    int p1s[2];
    int p2s[2];
    int p3s[2];
    int p4s[2];
    int rsize;
    MyRecord rc;

    if (pipe(p)==-1) { perror("pipe call"); exit(1);}
    if (pipe(pr)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p1s)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p2s)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p3s)==-1) { perror("pipe call"); exit(1);}
    if (pipe(p4s)==-1) { perror("pipe call"); exit(1);}

    double s31time=0,s32time=0,s33time=0,s34time=0,s35time=0,s36time=0,s37time=0,s38time=0,Co3time=0;
    double s21time=0,s22time=0,s23time=0,s24time=0,Co2time=0;
    double s11time=0,s12time=0,Co1time=0;
    double s01time=0,Co0time=0;
    double min0s=0,max0s=0,mo0s=0;
    double min1s=0,max1s=0,mo1s=0;
    double min2s=0,max2s=0,mo2s=0;
    double min3s=0,max3s=0,mo3s=0;

    double minc=0,maxc=0,moc=0;
    double signs1=0;
    double signs2=0;
    double signs3=0;
    double signs4=0;




    fclose (fpb);

    if(argc>=3){
        int coach0 = fork();
        if(coach0==0){
            char *arg[3];
            arg[0] = "./coach0";
            char str[12];
            sprintf(str, "%d", numOfrecords);
            arg[1] = input;//onoma arxeiou
            arg[2] = type1;//typos sort
            arg[3] = column1;//column id
            arg[4] = str;
            arg[5] = NULL;
            dup2(p[0],0);
            dup2(p1s[1],3);
            close(p[0]);
            close(p[1]);

            execvp(arg[0],arg);

        }else if(coach0==-1){
            perror("fork"); exit(1);
        }else if(argc>=7){
            int coach1 = fork();
            if(coach1==0){
                char *arg[2];
                arg[0] = "./coach1";
                char str[12];
                sprintf(str, "%d", numOfrecords);
                arg[1] = input;//onoma arxeiou
                arg[2] = type2;//typos sort
                arg[3] = column2;//column id
                arg[4] = str;
                arg[5] = NULL;
                dup2(p[0],0);
                dup2(p2s[1],3);
                close(p[0]);
                close(p[1]);

                execvp(arg[0],arg);

            }else if(coach1==-1){
                perror("fork"); exit(1);
            }else if(argc>=9){
                int coach2 = fork();
                if(coach2==0){
                    char *arg[2];
                    arg[0] = "./coach2";
                    char str[12];
                    sprintf(str, "%d", numOfrecords);
                    arg[1] = input;//onoma arxeiou
                    arg[2] = type3;//typos sort
                    arg[3] = column3;//column id
                    arg[4] = str;
                    arg[5] = NULL;
                    dup2(p[0],0);
                    dup2(p3s[1],3);
                    close(p[0]);
                    close(p[1]);

                    execvp(arg[0],arg);

                }else if(coach2==-1){
                    perror("fork"); exit(1);
                }else if(argc==11){
                    int coach3 = fork();
                    if(coach3==0){

                        char *arg[2];
                        arg[0] = "./coach3";
                        char str[12];
                        sprintf(str, "%d", numOfrecords);
                        arg[1] = input;//onoma arxeiou
                        arg[2] = type4;//typos sort
                        arg[3] = column4;//column id
                        arg[4] = str;
                        arg[5] = NULL;
                        dup2(p[0],0);
                        dup2(p4s[1],3);
                        close(p[0]);
                        close(p[1]);

                        execvp(arg[0],arg);

                    }else if(coach3==-1){
                        perror("fork"); exit(1);
                    }else{
                        //coordinator me 4 coaches
                        while((waitpid(coach3, &status, WNOHANG)) == 0 ){
                            sleep(1);
                        }
                        while((waitpid(coach2, &status, WNOHANG)) == 0 ){
                            sleep(1);
                        }
                        while((waitpid(coach1, &status, WNOHANG)) == 0 ){
                            sleep(1);
                        }
                        while((waitpid(coach0, &status, WNOHANG)) == 0 ){
                            sleep(1);
                        }


                        read(p4s[0],&s31time,sizeof(double));
                            min3s=s31time;
                            max3s=s31time;
                            mo3s=s31time;
                        read(p4s[0],&s32time,sizeof(double));
                            if(s32time<min3s){
                                min3s=s32time;
                            }
                            if(s32time>max3s){
                                max3s=s32time;
                            }
                            mo3s=mo3s+s32time;
                        read(p4s[0],&s33time,sizeof(double));
                            if(s33time<min3s){
                                min3s=s33time;
                            }
                            if(s33time>max3s){
                                max3s=s33time;
                            }
                            mo3s=mo3s+s33time;
                        read(p4s[0],&s34time,sizeof(double));
                            if(s34time<min3s){
                                min3s=s34time;
                            }
                            if(s34time>max3s){
                                max3s=s34time;
                            }
                            mo3s=mo3s+s34time;
                        read(p4s[0],&s35time,sizeof(double));
                            if(s35time<min3s){
                                min3s=s35time;
                            }
                            if(s35time>max3s){
                                max3s=s35time;
                            }
                            mo3s=mo3s+s35time;
                        read(p4s[0],&s36time,sizeof(double));
                            if(s36time<min3s){
                                min3s=s36time;
                            }
                            if(s36time>max3s){
                                max3s=s36time;
                            }
                            mo3s=mo3s+s36time;
                        read(p4s[0],&s37time,sizeof(double));
                            if(s37time<min3s){
                                min3s=s37time;
                            }
                            if(s37time>max3s){
                                max3s=s37time;
                            }
                            mo3s=mo3s+s37time;
                        read(p4s[0],&s38time,sizeof(double));
                            if(s38time<min3s){
                                min3s=s38time;
                            }
                            if(s38time>max3s){
                                max3s=s38time;
                            }
                            mo3s=mo3s+s38time;
                            mo3s=mo3s/8;

                        read(p4s[0],&Co3time,sizeof(double));
                            minc=Co3time;
                            maxc=Co3time;
                            moc=Co3time;

                        read(p3s[0],&s21time,sizeof(double));
                            min2s=s21time;
                            max2s=s21time;
                            mo2s=s21time;
                        read(p3s[0],&s22time,sizeof(double));
                            if(s22time<min2s){
                                min2s=s22time;
                            }
                            if(s22time>max2s){
                                max2s=s22time;
                            }
                            mo2s=mo2s+s22time;
                        read(p3s[0],&s23time,sizeof(double));
                            if(s23time<min2s){
                                min2s=s23time;
                            }
                            if(s23time>max2s){
                                max2s=s23time;
                            }
                            mo2s=mo2s+s23time;
                        read(p3s[0],&s24time,sizeof(double));
                            if(s24time<min2s){
                                min2s=s24time;
                            }
                            if(s24time>max2s){
                                max2s=s24time;
                            }
                            mo2s=mo2s+s24time;
                            mo2s=mo2s/4;

                        read(p3s[0],&Co2time,sizeof(double));
                            if(Co2time<minc){
                                minc=Co2time;
                            }
                            if(Co2time>maxc){
                                maxc=Co2time;
                            }
                            moc=moc+Co2time;

                        read(p2s[0],&s11time,sizeof(double));
                            min1s=s11time;
                            max1s=s11time;
                            mo1s=s11time;
                        read(p2s[0],&s12time,sizeof(double));
                            if(s12time<min1s){
                                min1s=s12time;
                            }
                            if(s12time>max1s){
                                max1s=s12time;
                            }
                            mo1s=mo1s+s12time;
                            mo1s=mo1s/2;

                        read(p2s[0],&Co1time,sizeof(double));
                            if(Co1time<minc){
                                minc=Co1time;
                            }
                            if(Co1time>maxc){
                                maxc=Co1time;
                            }
                            moc=moc+Co1time;

                        read(p1s[0],&s01time,sizeof(double));
                            min0s=s01time;
                            max0s=s01time;
                            mo0s=s01time;

                        read(p1s[0],&Co0time,sizeof(double));
                            if(Co0time<minc){
                                minc=Co0time;
                            }
                            if(Co0time>maxc){
                                maxc=Co0time;
                            }
                            moc=moc+Co0time;
                            moc=moc/4;



                        read(p1s[0],&signs1,sizeof(double));
                        read(p2s[0],&signs2,sizeof(double));
                        read(p3s[0],&signs3,sizeof(double));
                        read(p4s[0],&signs4,sizeof(double));
                    }
                }else{
                    //coordinator me 3 coaches
                    while((waitpid(coach2, &status, WNOHANG)) == 0 ){
                        sleep(1);
                    }
                    while((waitpid(coach1, &status, WNOHANG)) == 0 ){
                        sleep(1);
                    }
                    while((waitpid(coach0, &status, WNOHANG)) == 0 ){
                        sleep(1);
                    }


                    read(p3s[0],&s21time,sizeof(double));
                        min2s=s21time;
                        max2s=s21time;
                        mo2s=s21time;
                    read(p3s[0],&s22time,sizeof(double));
                        if(s22time<min2s){
                            min2s=s22time;
                        }
                        if(s22time>max2s){
                            max2s=s22time;
                        }
                        mo2s=mo2s+s22time;
                    read(p3s[0],&s23time,sizeof(double));
                        if(s23time<min2s){
                            min2s=s23time;
                        }
                        if(s23time>max2s){
                            max2s=s23time;
                        }
                        mo2s=mo2s+s23time;
                    read(p3s[0],&s24time,sizeof(double));
                        if(s24time<min2s){
                            min2s=s24time;
                        }
                        if(s24time>max2s){
                            max2s=s24time;
                        }
                        mo2s=mo2s+s24time;
                        mo2s=mo2s/4;
                    read(p3s[0],&Co2time,sizeof(double));
                        minc=Co2time;
                        maxc=Co2time;
                        moc=Co2time;

                    read(p2s[0],&s11time,sizeof(double));
                        min1s=s11time;
                        max1s=s11time;
                        mo1s=s11time;
                    read(p2s[0],&s12time,sizeof(double));
                        if(s12time<min1s){
                            min1s=s12time;
                        }
                        if(s12time>max1s){
                            max1s=s12time;
                        }
                        mo1s=mo1s+s12time;
                        mo1s=mo1s/2;
                    read(p2s[0],&Co1time,sizeof(double));
                        if(Co1time<minc){
                            minc=Co1time;
                        }
                        if(Co1time>maxc){
                            maxc=Co1time;
                        }
                        moc=moc+Co1time;

                    read(p1s[0],&s01time,sizeof(double));
                        min0s=s01time;
                        max0s=s01time;
                        mo0s=s01time;
                    read(p1s[0],&Co0time,sizeof(double));
                        if(Co0time<minc){
                            minc=Co0time;
                        }
                        if(Co0time>maxc){
                            maxc=Co0time;
                        }
                        moc=moc+Co0time;
                        moc=moc/3;

                    read(p1s[0],&signs1,sizeof(double));
                    read(p2s[0],&signs2,sizeof(double));
                    read(p3s[0],&signs3,sizeof(double));


                }
            }else{
                //coordinator me 2 coaches
                while((waitpid(coach1, &status, WNOHANG)) == 0 ){
                    sleep(1);
                }
                while((waitpid(coach0, &status, WNOHANG)) == 0 ){
                    sleep(1);
                }


                read(p2s[0],&s11time,sizeof(double));
                    min1s=s11time;
                    max1s=s11time;
                    mo1s=s11time;
                read(p2s[0],&s12time,sizeof(double));
                    if(s12time<min1s){
                        min1s=s12time;
                    }
                    if(s12time>max1s){
                        max1s=s12time;
                    }
                    mo1s=mo1s+s12time;
                    mo1s=mo1s/2;
                read(p2s[0],&Co1time,sizeof(double));
                    minc=Co1time;
                    maxc=Co1time;
                    moc=Co1time;

                read(p1s[0],&s01time,sizeof(double));
                    min0s=s01time;
                    max0s=s01time;
                    mo0s=s01time;
                read(p1s[0],&Co0time,sizeof(double));
                    if(Co0time<minc){
                        minc=Co0time;
                    }
                    if(Co0time>maxc){
                        maxc=Co0time;
                    }
                    moc=moc+Co0time;
                    moc=moc/2;

                    read(p1s[0],&signs1,sizeof(double));
                    read(p2s[0],&signs2,sizeof(double));
            }
        }else{
            //coordinator me 1 coach
            while((waitpid(coach0, &status, WNOHANG)) == 0 ){
                sleep(1);
            }


            read(p1s[0],&s01time,sizeof(double));
            min0s=s01time;
            max0s=s01time;
            mo0s=s01time;
            read(p1s[0],&Co0time,sizeof(double));
            minc=Co0time;
            maxc=Co0time;
            moc=Co0time;
            read(p1s[0],&signs1,sizeof(double));
        }

        printf("Coach0's time: %g ms\n",Co0time);
        printf("----------\n");
        printf("Sorter1's of coach0 time: %g ms\n",s01time);
        printf("----------\n");
        printf("Min time of a coach0's sorter: %g ms\n",min0s);
        printf("Max time of a coach0's sorter: %g ms\n",max0s);
        printf("Average time of coach0's sorters: %g ms\n",mo0s);
        printf("Signals received: %g\n",signs1);
        printf("\n============================================\n\nCoach1's time: %g ms\n",Co1time);
        printf("----------\n");
        printf("Sorter1's of coach1 time: %g ms\n",s11time);
        printf("Sorter2's of coach1 time: %g ms\n",s12time);
        printf("----------\n");
        printf("Min time of a coach1's sorter: %g ms\n",min1s);
        printf("Max time of a coach1's sorter: %g ms\n",max1s);
        printf("Average time of coach1's sorters: %g ms\n",mo1s);
        printf("Signals received: %g\n",signs2);
        printf("\n============================================\n\nCoach2's time: %g ms\n",Co2time);
        printf("----------\n");
        printf("Sorter1's of coach2 time: %g ms\n",s21time);
        printf("Sorter2's of coach2 time: %g ms\n",s22time);
        printf("Sorter3's of coach2 time: %g ms\n",s23time);
        printf("Sorter4's of coach2 time: %g ms\n",s24time);
        printf("----------\n");
        printf("Min time of a coach2's sorter: %g ms\n",min2s);
        printf("Max time of a coach2's sorter: %g ms\n",max2s);
        printf("Average time of coach2's sorters: %g ms\n",mo2s);
        printf("Signals received: %g\n",signs3);
        printf("\n============================================\n\nCoach3's time: %g ms\n",Co3time);
        printf("----------\n");
        printf("Sorter1's of coach3 time: %g ms\n",s31time);
        printf("Sorter2's of coach3 time: %g ms\n",s32time);
        printf("Sorter3's of coach3 time: %g ms\n",s33time);
        printf("Sorter4's of coach3 time: %g ms\n",s34time);
        printf("Sorter5's of coach3 time: %g ms\n",s35time);
        printf("Sorter6's of coach3 time: %g ms\n",s36time);
        printf("Sorter7's of coach3 time: %g ms\n",s37time);
        printf("Sorter8's of coach3 time: %g ms\n",s38time);
        printf("----------\n");
        printf("Min time of a coach3's sorter: %g ms\n",min3s);
        printf("Max time of a coach3's sorter: %g ms\n",max3s);
        printf("Average time of coach3's sorters: %g ms\n",mo3s);
        printf("Signals received: %g\n",signs4);
        gettimeofday(&t2, NULL);
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
        printf("\n============================================\n\nCoordinator's turnaround time: %g ms\n",elapsedTime);
        printf("----------\n");
        printf("Min time of a coach: %g ms\n",minc);
        printf("Max time of a coach: %g ms\n",maxc);
        printf("Average time of coaches: %g ms\n",moc);

        free(aa);
    }
}
