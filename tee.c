/*Dankook Univ dep of software*/
/*KangMinGu 2018-01-01*/
/*beat6744@nate.com*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define MAX_BUFFER 1024
#define FILE_SIZE 32
#define TRUE 1
#define FALSE 0

int main(int argc, char* argv[])
{
        int option, fd, read_size, have_opt = FALSE;
        int whence = SEEK_SET;
        char buffer[MAX_BUFFER];
        char file_name[FILE_SIZE];

        while((option = getopt(argc, argv, "a:")) != -1) {
                switch(option) {
                case 'a':
                        whence = SEEK_END;
                        strcpy(file_name, optarg);
                        have_opt = TRUE;
                        break;
                case '?':
                        printf("USAGE : tee (-a) file_name\n");
                        exit(-1);
                        break;
                }
        }

        if(have_opt != TRUE)
                strcpy(file_name, argv[1]);
       
	fd = open(file_name, O_WRONLY); //open file write only
        if(fd < 0) { //error handling
                printf("%s open error errno : %d\n", file_name, errno);
                exit(-1);
        }
        lseek(fd, 0, whence); // offset handling
	
        read_size = read(STDIN_FILENO, buffer, MAX_BUFFER);
        if(read_size < 0) { //error handling
                printf("read error from STDIN errno : %d\n", errno);
                exit(-1);
        }
	
        if(write(STDOUT_FILENO, buffer, read_size) <0) { //write data to STDOUT
                printf("write error to STDOUT errno : %d\n", errno);
                exit(-1);
        }
        if(write(fd, buffer, read_size) <0) { //write data to file
                printf("write error to %s errno : %d\n", file_name, errno);
                exit(-1);
        }

        if(close(fd) <0) { //close file
                printf("close error errno : %d\n", errno);
                exit(-1);
        }
        return 0;
}
