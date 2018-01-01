#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int my_dup(int oldfd);
int my_dup2(int oldfd, int newfd);

int main(){
char *fname = "result.txt";
int fd1, fd2;

if((fd1 = creat(fname, 0666))<0){
        printf("creat error\n");
        return 1;
}

printf("First one is on the screen\n");
fd2 = my_dup2(fd1, 1);

printf("Second on is in this file\n");
printf("fd2:%d\n", fd2);

return 0;
}

int my_dup(int oldfd){

return fcntl(oldfd, F_DUPFD, 0);
}


int my_dup2(int oldfd, int newfd){
int errno, flag;

flag=fcntl(oldfd, F_GETFL);
if(flag == -1){
        errno=EBADF;
        strerror(errno);
        return -1;
}

if(flag == fcntl(newfd, F_GETFL)){
        return newfd;
}

close(newfd);

return my_dup(oldfd);
}
