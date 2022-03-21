#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int num_files = 0;
int num_dir = -1;
int num_slink = 0;
int num_char_dev = 0;
int num_block_dev = 0;
int num_fifo = 0;
int num_sock = 0;

int file_info(const char *filename, const struct stat *stats,int fileflags, struct FTW *pfwt)
{
    printf("NEW FILE INFORMATION:\n");
    printf("1.File name: ");
    printf("%s\n",filename);
    printf("2.Absolut filepath: ");
    char buf[256];
    char *res = realpath(filename, buf);
    printf("%s\n",res);

    printf("3.File type: ");
    if (S_ISREG(stats->st_mode)){
        num_files += 1;
        printf("file\n");
    }
    else if (S_ISDIR(stats->st_mode)){
        num_dir += 1;
        printf("dir\n");
    }
    else if (S_ISLNK(stats->st_mode)){
        num_slink += 1;
        printf("slink\n");
    }
    else if (S_ISCHR(stats->st_mode)){
        num_char_dev += 1;
        printf("char dev\n");
    }
    else if (S_ISBLK(stats->st_mode)){
        printf("block dev\n");
        num_block_dev += 1;
    }
    else if (S_ISFIFO(stats->st_mode)){
        num_fifo += 1;
        printf("fifo\n");
    }
    else if (S_ISSOCK(stats->st_mode)){
        num_sock += 1;
        printf("sock\n");
    }

    printf("4.File size: ");
    printf("%ld\n",stats->st_size);

    printf("5.Last acces: ");
    printf("%s",ctime(&stats->st_atime));

    printf("6.Last modification: ");
    printf("%s",ctime(&stats->st_mtime));

    printf("7.Nlinks: ");
    printf("%ld\n",stats->st_nlink);
    printf("\n");

    return 0;
}

int main(int argc, char *argv[]){
    int flags = FTW_PHYS;
    int fd_limit = 2;
    nftw(argv[1],
         file_info,
         fd_limit, flags);
    printf("Number of files: %d\n",num_files);
    printf("Number of directories: %d\n",num_dir);
    printf("Number of slink: %d\n",num_slink);
    printf("Number of char dev: %d\n",num_char_dev);
    printf("Number of block dev: %d\n",num_block_dev);
    printf("Number of fifo: %d\n",num_fifo);
    printf("Number of sock: %d\n",num_sock);
    return 1;
}
