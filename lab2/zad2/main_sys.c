#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>


int file1;
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
    file1 = open(file, O_RDONLY);
    if(file1 == -1){
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

    while((read(file1,buffer,bufsize))>0){
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
    close(file1);
    free(buffer);
    printf("Quantity of symbols: %d\n",sym_count);
    printf("Quantity of verses: %d\n",ver_count);
    en_time = times(&en_cpu);
    save_timer("sys");
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
        printf("%s\n",f1);
        printf("%s\n",f2);
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
