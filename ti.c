#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char* argv[]){

    char buf[100];
    int res;
    int fd = open("test.txt", O_CREAT | O_RDWR | O_EXCL, 0744);
    if(fd == -1){
        if(argc > 1)
            if(strcmp(argv[1], "-a") == 0)
            fd = open("test.txt", O_RDWR | O_APPEND);
        else
            fd = open("test.txt", O_RDWR | O_TRUNC);
    }
     res = read(0, buf, 100);
       if(res > 99)
           buf[99] = '\0';
     write(fd, buf, res);
     write(1, buf, res);



    return 0;
}
