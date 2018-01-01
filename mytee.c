/* make tee command, 박제혁, 01039215234 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#define MAX_BUF 256

int main(int argc, char* argv[]){
	int fd, read_size, write_size, opt;
	char buf[MAX_BUF];
	off_t offset = SEEK_SET;	//옵션 적용을 위한 offset

	while((opt = getopt(argc, argv, "a")) != -1) {
		switch(opt) {
			case 'a':		//tee -a file_name 옵션 적용한 경우
			offset = SEEK_END;
			argv[1] = argv[2];
            		break;

			case '?': printf("그런 옵션은 없습니다.\n"); break;
		}
    	}
	fd = open(argv[1], O_RDWR | O_CREAT);
	if(fd < 0) { printf("파일 열기를 실패했습니다.\n"); exit(-1); }
	
	lseek(fd, 0, offset);

	read_size = read(STDIN_FILENO, buf, MAX_BUF);

	write(STDOUT_FILENO, buf, read_size);   	//터미널에 출력
	write(fd, buf, read_size);			//파일에 출력			

	close(fd);
	return 0;
}
