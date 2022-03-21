#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>


FILE *file1;
FILE *report_file;
clock_t st_time, en_time;
struct tms st_cpu, en_cpu;

void create_file_report()
{
    char file_name[] = "pomiar_zad_2.txt";
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

int sym_counter(char *symbol,char *file){
    create_file_report();
    st_time = times(&st_cpu);
    file1 = fopen(file, "r");
    if(file1 == NULL){
        fprintf(stderr, "Cant open file\n");
        exit(-1);
    }
    int sym_count = 0;
    int ver_count = 0;
    const char s[3] = "\n";
    char *token1;
    int check = 0;
    char *buffer;
    size_t bufsize = 256;
    buffer = (char *)malloc(bufsize * sizeof(char));

    while(fread(buffer,sizeof(char),bufsize,file1)){
        token1 = strtok(buffer, s);
        while( token1 != NULL ) {
            for(int i=0; i< strlen(token1)-3; i++){
                if(token1[i] == *symbol){
                    sym_count += 1;
                    check += 1;
                }
            }
            if(check>0){
                ver_count += 1;
            }
            token1 = strtok(NULL, s);
            check = 0;
        }
    }
    fclose(file1);
    free(buffer);
    printf("Quantity of symbols: %d\n",sym_count);
    printf("Quantity of verses: %d\n",ver_count);
    en_time = times(&en_cpu);
    save_timer("lib");
    return 1;
}


int main(int argc, char *argv[]){
    if(argc == 1){
        char f1[100];
        char f2[100];
        printf("Symbol:\n");
        scanf("%99s",f1);
        printf("File:\n");
        scanf("%99s",f2);
        sym_counter(f1,f2);
    }
    else if(argc <3){
        fprintf(stderr, "Wrong number of arguments\n");
        exit(-1);
    }
    else{
        sym_counter(argv[1],argv[2]);
    }
    return 1;
}

