#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define MAX_BUFFER 1024

int my_dup2(int oldfd, int newfd);

int main(int argc, char* argv[])
{
        int fd1, fd2, read_size;
        char buffer[MAX_BUFFER];

        if(argc != 2 || strcmp(argv[1], "-help") == 0){
                printf("USAGE : dup2 file_name\n");
                exit(-1);
        }

        fd1 = open(argv[1], O_WRONLY | O_CREAT, 0x700);
        if(fd1 < 0){
                printf("%s open error errno : %d\n", argv[1], errno);
                exit(-1);
        }

        fd2 = my_dup2(fd1, 4);
        printf("new file descriptor is : %d\n",fd2);

        read_size = read(STDIN_FILENO, buffer, MAX_BUFFER); /*errpr handling...*/
        write(fd2, buffer, read_size);/*errpr handling...*/
        close(fd1);/*errpr handling...*/
        close(fd2);/*errpr handling...*/

        return 0;
}

int my_dup2(int oldfd, int newfd)
{
        int valid, result;

        valid = fcntl(oldfd, F_GETFL);
        if(valid <0){
                printf("invalid file descriptor\n");
                errno = EBADF;
                return -1;
        }

        if(oldfd == newfd)
                return oldfd;
        else{
                close(newfd);
                result = fcntl(oldfd, F_DUPFD, newfd);
                return result;
        }
}
