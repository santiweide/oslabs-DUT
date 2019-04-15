#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int f(int x)
{
	if(x < 2)
		return 1;
	return x * f(x - 1);
}
int main(int argc, char *argv[])
{
	int pid;
	int pipe1[2];
	int pipe2[2];
	int x ; 
	
	if(pipe(pipe1) < 0)
	{
		perror("pipe not create");
		exit(EXIT_FAILURE);
	} 
	if(pipe(pipe2) < 0)
	{
		perror("pipe not create");
		exit(EXIT_FAILURE);
	}

	if((pid=fork()) <0)
	{
		perror("process not create");
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
	{
		close(pipe1[1]);
		close(pipe2[0]);
		
	
		read(pipe1[0],&x,sizeof(int));
		int t = f(x);
		
		printf("child %d read: %d\n",getpid(),x);
		write(pipe2[1],&t,sizeof(int));
	
		close(pipe1[0]);
		close(pipe2[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe1[0]);
		close(pipe2[1]);
		x = 3;
		write(pipe1[1],&x,sizeof(int));
		read(pipe2[0],&x,sizeof(int));
		printf("parent %d read: %d\n",getpid(),x++);
		
		close(pipe1[1]);
		close(pipe2[0]);
	}
	

	return EXIT_SUCCESS;
}
