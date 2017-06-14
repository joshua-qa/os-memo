#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF_SIZE   1024

int main(void) {
    char sourceFileName[100], targetFileName[100], buff[BUFF_SIZE];
    int fd, t_fd;
    ssize_t rd_size;

    printf("input source file name: ");
    scanf("%s", sourceFileName);

    printf("%s\n", sourceFileName);
    
    printf("input target file name: ");
    scanf("%s", targetFileName);

    printf("%s\n", targetFileName);
    
    fd = open(sourceFileName, O_RDWR, 0644);
    if(fd > 0) {
        fputs("file open ok\n", stdout);

        if( 0 < (t_fd = open(targetFileName, O_RDWR))) {
            fputs("target file exist error!\n", stderr);
            exit(1);
        } else {
            creat(targetFileName, 0644);
            t_fd = open(targetFileName, O_RDWR);
            while(0 < (rd_size = read(fd, buff, BUFF_SIZE-1))) {
                buff[rd_size] = '\0';
                write(t_fd, buff, strlen(buff));
            }

            close(fd);
            close(t_fd);
        }
    } else {
        printf("%d %s", fd, sourceFileName);
        fputs("file open error!\n", stderr);
        exit(1);
    }

    fputs("file write complete\n", stdout);
}