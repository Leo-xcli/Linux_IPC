#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
int main()
{		
	int pipe_fd[2];//pipe_fd[0]:read pipe pipe_fd[1]:write pipe
	pid_t pid;
	char buf_r[128];
	char buf_w[128];
	char * p_wbuf;
	int r_num,count;
	memset(buf_r,0,sizeof(buf_r));
	if(pipe(pipe_fd)<0)
	{
		printf("pipe create error\n");	
	}
	if((pid=fork())==0)//chird
	{	
		while(1)
		{	
			sleep(1);
			if(r_num=read(pipe_fd[0],buf_r,sizeof(buf_r)))
			{
				printf("%d number read form the pipe %s \n",r_num,buf_r);
				if(!strcmp(buf_r,"exit"))
				{	
					close(pipe_fd[0]);
					close(pipe_fd[1]);
					exit(0);
				}
			}
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(0);
		
	}
	else if(pid>0)//father
	{	
		printf("please enter thr data\n");
		scanf("%s",buf_w);
		if(write(pipe_fd[1],buf_w,sizeof(buf_w))!= -1)
		{
			printf("send success\n");
		}
		sleep(2);
		waitpid(pid,NULL,0);//wait child exit;
		printf("child exit\n");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(0);
	}
	
	return 0;
}
