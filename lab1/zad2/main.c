#include "library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>


clock_t st_time, en_time;
struct tms st_cpu, en_cpu;
FILE *report_file;

void create_file_report()
{
    char file_name[] = "raport2.txt";
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

void save_timer(char *name, FILE *file)
{
    double real_time = time_difference(st_time,en_time);
    double user_time = time_difference(st_cpu.tms_utime,en_cpu.tms_utime);
    double system_time = time_difference(st_cpu.tms_stime,en_cpu.tms_stime);
    fprintf(file, "%30s:\t\t%15f\t%15f\t%15f\t\n",
            name,
            real_time,
            user_time,
            system_time);
}

int stop_timer_operation(char *argv[], int i, int argc)
{
    if (i + 1 >= argc)
    {
        fprintf(stderr, "end timer wasn't given arguments\n");
        return -1;
    }

    en_time = times(&en_cpu);
    char *timer_name = argv[i + 1];
    save_timer(timer_name, report_file);
    return 0;
}


int main(int argc, char *argv[]){

    create_file_report();
    int i=1;
    while(i < argc){
        if(!strcmp(argv[i], "create_table")){
            if(i+1>= argc){
            printf("no size of table was given");
            return -1;
            }
            int size = atoi(argv[i+1]);
            create_table(size);
            i += 2;
        }
        else if(!strcmp(argv[i], "wc_files")){
            int k = i + 1;
            int size;
            while(k<argc && !(!strcmp(argv[k],"create_table") || !strcmp(argv[k],"wc_files") ||  !strcmp(argv[k],"remove_block") || !strcmp(argv[k],"wc_files")
                              || !strcmp(argv[k],"rewrite") || !strcmp(argv[k],"start") || !strcmp(argv[k],"stop"))){
                k += 1;
            }
            char **tab_of_args = (char**) calloc(k,sizeof(char*));
            if(k == i){
                fprintf(stderr, "function wc_files wasn't given arguments");
                return -1;
            }
            else{
                i += 1;
                size = k-i;
                int counter = 0;
                while(i<k){
                    tab_of_args[counter] = argv[i];
                    counter += 1;
                    i += 1;
                }
            }
            int check  =  wc_files(size,tab_of_args);
            if(check<0){
                fprintf(stderr, "function wc_files returned error\n");
                return -1;
            }
        }
        else if(!strcmp(argv[i], "remove_block")){
            if(i+1>=argc){
                fprintf(stderr,"no index was given");
                return -1;
            }
            int check = remove_block(atoi(argv[i+1]));
            if(check<0){
                fprintf(stderr, "function wc_files returned error\n");
                return -1;
            }
            i += 2;
        }
        else if(!strcmp(argv[i], "rewrite")){
            int inx = rewrite();
            if(inx < 0){
                fprintf(stderr, "function rewrite returned error\n");
                return -1;
            }
            i += 1;
        }
        else if (!strcmp(argv[i], "start"))
        {
            st_time = times(&st_cpu);
            i += 1;
        }
        else if (!strcmp(argv[i], "stop"))
        {
            stop_timer_operation(argv, i, argc);
            i += 2;
        }
        else{
            fprintf(stderr, "comand is unknown\n");
            return -1;
        }
    }
    return 0;
}
