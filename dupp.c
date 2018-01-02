#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>


int dupp(int oldfd){
    int newfd = fcntl(oldfd, F_DUPFD);
    if(newfd != -1) 
        return newfd;
    return -1;
}

int dupp2(int oldfd, int newfd){
    int flags;
    flags = fcntl(oldfd, F_GETFL);
    if(flags == -1)
        return -1;

    if (oldfd == newfd)
        return newfd;
    if(fcntl(newfd, F_GETFL) != -1){
        close(newfd);
        newfd = fcntl(oldfd, F_DUPFD, newfd);
        if(newfd != -1)
            return newfd;
        return -1;
    }
}

int main(){
    int fd, newfd;
    fd = open("duptest.c", O_CREAT | O_RDWR, 0744);
    newfd = dupp(fd);
    printf("fd = %d \n newfd = %d\n", fd, newfd);
   
    newfd = dupp2(1, 2);
    printf("newfd2 = %d\n", newfd);
    return 0;
}
