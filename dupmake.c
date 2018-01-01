/* make dup(), dup2() using fcntl(), 박제혁, 01039215234 */
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

int mydup(int oldfd){					//dup() 구현
	return fcntl(oldfd, F_DUPFD, 2);
}

int mydup2(int oldfd, int newfd){			//dup2() 구현
	if(oldfd == newfd){
		if(fcntl(oldfd, F_GETFL) == -1)
			return -1;
		return oldfd;
	}

	fcntl(oldfd, F_DUPFD, newfd);

	return newfd;
}

int main(void){
	int oldfd, newfd;

	newfd = mydup(1);							//newfd = dup(1);
	printf("mydup(1) newfd: %d\n", newfd);
    	newfd = mydup(1);							//1번 더 수행
    	printf("mydup(1) newfd: %d\n", newfd);
	
	newfd = mydup2(1, 2);						//newfd	= dup2(1, 2);
	printf("mydup2(1, 2) newfd: %d\n", newfd);
	newfd = mydup2(1, 2);						//1번 더 수행
    	printf("mydup2(1, 2) newfd: %d\n", newfd);

	return 0;
}
