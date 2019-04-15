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
    int turn = 3;

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
        read(pipe1[0],&x,sizeof(int));
        printf("f(x)\t%d\n",f(x));

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
            read(pipe2[0],&y,sizeof(int));
            printf("f(y)\t%d\n",g(y));
            close(pipe2[0]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(pipe1[0]);
            close(pipe2[0]);
            scanf("%d%d",&x,&y);
            write(pipe2[1],&y,sizeof(int));
            write(pipe1[1],&x,sizeof(int));
            printf("f(x,y)\t%d\n",f(x) + g(y));
            close(pipe2[1]);
            close(pipe1[1]);
        }
	}
	return EXIT_SUCCESS;
}
