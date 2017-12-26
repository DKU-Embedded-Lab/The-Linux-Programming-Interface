# The-Linux-Programming-Interface
스터디 발표하는날까지 미리 알려드린 연습문제 코딩후 github에commit 해주세요

각자 이름으로 branch 만들어 관리해주세요.


## Git 에 코드 올리는법

1. Github clone

		git clone https:/https://github.com/DKU-Embedded-Lab/The-Linux-Programming-Interface.git 

2. Branch 생성 (각자 이름 Branch 생성) 

		git checkout -b [Branch name]

	Branch 리스트 확인
		
		git branch 

	작업 Branch 변경 
		
		git checkout [Branch name]

3. 작성한 소스코드 add

		git add [Source code name]
 	
	해당 디렉토리 전부 add

		git add *

4. Commit 메세지 작성 ex) git commit -m "First Commit"

		git commit -m "[Commit Message]"

5. github push

		git push origin [Branch name]
