#define CNT 64

#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
int flag_a=0, fd, readLen, writeLen1, writeLen2;
int temp;
char *buf[CNT];


if(argc <2 || argc >4){
        printf("%s -x file or %s file\n",argv[0], argv[0]);
        exit(EXIT_FAILURE);
}

while((temp = getopt(argc, argv, "a"))!=-1){
        switch(temp){
                case 'a': flag_a=1;
                        break;
        }
}

fd = open(argv[1+flag_a], O_RDWR | O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);

if(fd==-1){
        perror("open");
        exit(1);
}

if(flag_a){
        lseek(fd,0,SEEK_END);
}

readLen = read(STDIN_FILENO, buf, CNT);
if(readLen == -1){
        perror("read");
        exit(EXIT_FAILURE);
}

writeLen1=write(fd, buf, readLen);
writeLen2=write(STDOUT_FILENO, buf, readLen);

if(writeLen1 < 0 || writeLen2 < 0){
        perror("write");
}

exit(1);
}
