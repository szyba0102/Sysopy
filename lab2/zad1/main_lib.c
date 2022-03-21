#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>
#include <sys/stat.h>

FILE *file1;
FILE *file2;
FILE *report_file;
clock_t st_time, en_time;
struct tms st_cpu, en_cpu;

void create_file_report()
{
    char file_name[] = "pomiar_zad_1.txt";
    report_file = fopen(file_name, "a");
    fprintf(report_file, "%30s\t\t%15s\t%15s\t%15s\n",
            "Name",
            "Real [s]",
            "User [s]",
            "System [s]");
}

double time_difference(clock_t t1, clock_t t2){
    return ((double)(t2 - t1) / sysconf(_SC_CLK_TCK));
}

void save_timer(char *name)
{
    double real_time = time_difference(st_time,en_time);
    double user_time = time_difference(st_cpu.tms_utime,en_cpu.tms_utime);
    double system_time = time_difference(st_cpu.tms_stime,en_cpu.tms_stime);
    fprintf(report_file, "%30s:\t\t%15f\t%15f\t%15f\t\n",
            name,
            real_time,
            user_time,
            system_time);

}

int rewrite(char *file1_name,char *file2_name){
    st_time = times(&st_cpu);
    file1 = fopen(file1_name, "r");
    file2 = fopen(file2_name, "w");
    if(file1 == NULL){
        fprintf(stderr, "Cant open first file\n");
        exit(-1);
    }
    if(file2 == NULL){
        fprintf(stderr, "Cant open second file\n");
        exit(-1);
    }
    const char s[3] = "\n";
    char *token;
    char *buffer;
    size_t bufsize = 256;
    buffer = (char *)malloc(bufsize * sizeof(char));
    int i = 0;
    while(fread(buffer,sizeof(char),bufsize,file1)){
        token = strtok(buffer, s);

        while( token != NULL ) {
            while((i<strlen(token)-3) && (isspace(token[i]))){
                i += 1;
            }
            if(i != strlen(token)-3){
                fwrite(token,sizeof(char),strlen(token),file2);
            }
            token = strtok(NULL, s);
            i = 0;
        }
    }
    fclose(file1);
    fclose(file2);
    free(buffer);
    en_time = times(&en_cpu);
    save_timer("lib");
    return 1;
}


int main(int argc, char *argv[]){
    create_file_report();
    if(argc == 1){
        char f1[100];
        char f2[100];
        printf("First file name:\n");
        scanf("%99s",f1);
        printf("Second file name:\n");
        scanf("%99s",f2);
        rewrite(f1,f2);
    }
    else if(argc<3){
        fprintf(stderr, "Wrong number of arguments\n");
        exit(-1);
    }
    else{
        rewrite(argv[1],argv[2]);
    }
    return 1;
}
