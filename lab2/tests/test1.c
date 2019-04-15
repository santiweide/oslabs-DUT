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
	int pid1;
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
		do{
            read(pipe1[0],&x,sizeof(int));
            printf("f_x(%d)\t%d\n",x,f(x));
            x ++;
            write(pipe2[1],&x,sizeof(int));
        }while(x <= 10);
        close(pipe2[1]);
		close(pipe1[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
	    int pid2 = fork();
	    if(pid2 <0)
        {
            perror("process not create");
            exit(EXIT_FAILURE);
        }
        else if(pid2 == 0)
        {
            close(pipe2[1]);
            close(pipe1[0]);
            do{
                write(pipe1[1],&x,sizeof(int));
                read(pipe2[0],&x,sizeof(int));
                printf("f_y(%d)\t%d\n",x,g(x));
                x ++;
            }while(x <= 10);
            close(pipe2[0]);
            close(pipe1[1]);
            exit(EXIT_SUCCESS);
        }
	    else
        {
            x = 1;
            y = 2;
            exit(EXIT_SUCCESS);
        }
	}
	return EXIT_SUCCESS;
}
