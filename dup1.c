#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#define MAX_BUFFER 1024

int my_dup(int oldfd);

int main(int argc, char* argv[])

{
        int fd1, fd2, read_size;
        char buffer[MAX_BUFFER];

        if(argc != 2 || strcmp(argv[1], "-help") == 0){
                printf("USAGE : dup file_name\n");
                exit(-1);
        }

        fd1 = open(argv[1], O_WRONLY | O_CREAT, 0x700);
        if(fd1 < 0){
                printf("%s open error errno : %d", argv[1], errno);
                exit(-1);
        }

        fd2 = my_dup(fd1); //copy fd1 to fd2
        if(fd2 < 0){ //error handling
                printf("copy error errno : %d",errno);
                exit(-1);
        }

        read_size = read(STDIN_FILENO, buffer, MAX_BUFFER); /*error handling...*/
        write(fd2, buffer, read_size); /*error handling...*/
        close(fd1); /*error handling...*/
        close(fd2); /*error handling...*/
        return 0;
}

int my_dup(int oldfd)
{
        return fcntl(oldfd, F_DUPFD, 0); //copy oldfd to newfd
}
