#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int f(int x)
{
	if(x <= 1)
		return 1;
	return x * f(x - 1);
}
int g(int x)
{
	if( x <=2 )
		return 1;
	return g(x - 1) + g(x - 2);
}
int main(int argc, char *argv[])
{
	int pid1,pid2;
	int pipe1[2];
	int pipe2[2];
	int x,y; 
	
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

	if((pid1=fork()) <0)
	{
		perror("process not create");
		exit(EXIT_FAILURE);
	}
	else if(pid1 == 0)
	{
		close(pipe1[1]);
		close(pipe2[0]);
			
		read(pipe1[0],&x,sizeof(int));
		//read(pipe1[0],&y,sizeof(int));
		int t = f(x);
		printf("pid1__%d\n",t);
		write(pipe2[1],&x,sizeof(int));
		close(pipe1[0]);
		close(pipe2[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe1[0]);
		close(pipe2[1]);
		x = 1;
		y = 2;
		int t = f(x) + g(y);
		write(pipe1[1],&x,sizeof(int));
		printf("pid1_fa_%d\n",t);
		read(pipe2[0],&y,sizeof(int));
		close(pipe1[1]);
		close(pipe2[0]);
	}
	

	if((pid2=fork()) <0)
	{
		perror("process not create");
		exit(EXIT_FAILURE);
	}
	else if(pid2 == 0)
	{
		close(pipe1[1]);
		close(pipe2[0]);
		
		read(pipe1[0],&y,sizeof(int));
		int t = g(y);
		printf("pid2__%d\n",t);
		write(pipe2[1],&y,sizeof(int));
		close(pipe1[0]);
		close(pipe2[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipe1[0]);
		close(pipe2[1]);
		x = 1;
		y = 2;
		int t = f(x) + f(y);
		printf("pid2_fa:%d\n",t);
		write(pipe1[1],&y,sizeof(int));
		read(pipe2[0],&x,sizeof(int));
		
		close(pipe1[1]);
		close(pipe2[0]);
	}
	return EXIT_SUCCESS;
}
