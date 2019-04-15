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
	if( x <= 2 )
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
    pid1 = fork();
	if(pid1 <0)
	{
		perror("process not create");
		exit(EXIT_FAILURE);
	}
	else if(pid1 == 0)
	{
		close(pipe1[1]);
		close(pipe2[0]);
		close(pipe2[1]);
        do{
            read(pipe1[0],&x,sizeof(int));
            printf("pid:%d\tf(x)\t%d\n",getpid(),f(x));
            x ++;
        }while(x <= 5 && y <= 5);
		close(pipe1[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
	    pid2 = fork();
        if(pid2 <0)
        {
            perror("process not create");
            exit(EXIT_FAILURE);
        }
        else if(pid2 == 0)
        {
            close(pipe1[0]);
            close(pipe1[1]);
            close(pipe2[1]);
            do{
                read(pipe2[0],&y,sizeof(int));
                printf("pid:%d\tf(y)\t%d\n",getpid(),g(y));
                y ++;
            }while(x <= 5 && y <= 5);
            close(pipe2[0]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(pipe1[0]);
            close(pipe2[0]);
            x = 1;
            y = 1;
            do
            {
                write(pipe2[1],&y,sizeof(int));
                write(pipe1[1],&x,sizeof(int));
                printf("pid:%d\tf(x,y)\t%d\n",getpid(),f(x) + g(y));
                x ++;
                y ++;
                read(pipe2[0],&y,sizeof(int));
                read(pipe1[0],&x,sizeof(int));
            }while(x <= 5 && y <= 5);
            close(pipe2[1]);
            close(pipe1[1]);
        }
	}
	return EXIT_SUCCESS;
}
