1. Just write -> make
2. ./tfind -t 3 dir1 file
3. You can see correct result.
4. Any other command
	./tfind -t 5 dir1 apple
	./tfind -t 6 dir1 kiwi
	./tfind -t 1 dir1/dir2 file

All file contain keword "file".

--Script--
안녕하세요
제이름은 신예준입니다
제가 만든 tfind program에 대해 설명하겠습니다.
먼저 디렉토리 예제는 과제설명란과 똑같이 만들었습니다. 그리고 파일의 첫번째 줄에는 파일 이름이 있고
각 파일의 두번째 줄에는 각각 특정 단어가 포함됩니다. 

먼저 파일에 있는 특정 단어를 찾기위해 디렉토리를 열고 읽는 함수를 보겠습니다.
이 함수는 디렉토리를 열고 읽어서 디렉토리 안의 엔트리가 파일인지 디렉토리인지 파악합니다. 디렉토리라면 재귀함수를 이용해 그 디렉토리를 열고 안에 파일이 있는지 찾습니다. 파일을 찾으면 큐에 저장합니다. 

각 threads는 큐에 저장된 파일의 경로와 이름을 열고 특정 줄에서 단어를 찾는 task를 수행하게 됩니다.
먼저 사용자가 tread의 수와 디렉토리 이름, 찾고 싶은 단어를 입력합니다.
thread 수가 16개를 넘어서면 프로그램을 종료합니다.
이제 thread는 일을 시작하는데 thread의 critical session은 mutex lock으로 보호되어 있습니다.
큐에 있는 파일이름을 이용해 하나씩 task를 수행하고 수행이 끝나면 일을 수행한 파일이름을 큐에서 지웁니다.
이렇게 서로 같은 큐에 접근하는 것이 아니라 서로 병렬적으로 일을 수행하게 됩니다. 

이제 프로그램 수행하는 예시를 보겠습니다.
먼저 make를 명령하여 컴파일 합니다.
그리고 프로그램을 실행합니다. 

모든 파일은 file이라는 단어를 포함하므로 먼저 dir1에서 file을 찾아보겠습니다.
thread수는 3개로 해보겠습니다.
./tfind -t 5 dir1 file
다음은 dir2에서 찾아보겠습니다.
./tfind -t 1 dir1/dir2 file 

다음은 thread 수를 다르게 한 예시를 보겠습니다.
./tfind -t 1 dir1 file
./tfind -t 10 dir1 file 

thread수가 10개인 것이 1개인 것보다 느립니다.
예상대로라면 thread 수가 10개 인 것이 병렬적으로 차리하기 때문에 더빨라야 하지만 결과는 다르게 나왔습니다.
아마 thread를 create하는데 시간이 걸린 것 같습니다. 

다른 단어도 찾아보겠습니다
./tfind -t 2 dir1 apple
./tfind -t 7 dir1 apple


./tfind -t 5 dir1/dir3 doctor 

여기까지 제 프로그램 설명이었습니다.
감사합니다.

-- Script ENG version --
Hello
My name is Shin Yejun.
I will explain about the t-find program that I made.
First, I created the directory exactly like the homework description example. And the first line of the file has a file name.
The other line of each file contains a specific word. 

Let's look at the function to open the directory and to find specific words in the file.
This function opens and reads the directory to determine whether the entry in directory is a file or a directory. If it is a directory, use the recursive function to open it and find the file inside. If you find the file, function store the file name in the queue. 

Each threads opens the path and file name stored in the queue and performs a task to find the word in a specific line.
And, Let's look at the main.
First, user input the number of threads, the directory name, and the word user want to find.
Exit the program when the number of threads is over 16.
And thread create through function.
Now the thread starts work named threaded_work , and the critical session of thread is protected by a mutex lock.

Perform tasks one by one using the file name in the queue and remove the file name from the queue when the task is complete.
Threads approach the same queue, but they didn't access same source and they work parallel to each other. 

Now, let's look at how the program works.
First, compile by commanding make.
And run the program. 

All files contain the word file, so let's look for the file in dir1 first.
I'll go with five threads.
./tfind -t 5 dir1 file
you can see  the total number of the regular text files, the total number of found lines, the sum of all execution time.

I'll look it up in dir2.
./tfind -t 1 dir1/dir2 file 

Let's look at different number of threads.
./tfind -t 1 dir1 file
./tfind -t 10 dir1 file 

10 threads are slower than 1 thread.
As expected, 10 threads should be faster because they operate in parallel, but the result was different.
Maybe it took time to create a thread. 

I'll look for another word.
./tfind -t 2 dir1 apple
./tfind -t 7 dir1 apple


./tfind -t 5 dir1/dir3 doctor

That was my program description.
Thank you.
