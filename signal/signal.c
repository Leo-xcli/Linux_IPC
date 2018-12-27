#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void sig_child(int signo)
{		
		
		printf("child terminated\r\n");
}
int main( void )
{
    pid_t childpid;
    int status;
    int retval;
    
    childpid = fork();
    if ( -1 == childpid )
    {
        perror( "fork()" );
        exit( EXIT_FAILURE );
    }
    else if ( 0 == childpid )
    {
		signal(SIGUSR1,sig_child);//注册一个信号
        sleep( 100 );//让子进程睡眠，看看父进程的行为	
        exit(EXIT_SUCCESS);
    }
    else
    {
        if ( 0 == (waitpid( childpid, &status, WNOHANG )))//等待子进程退出，但是不阻塞
        {	
			sleep(1);
            retval = kill( childpid,SIGUSR1 );//给子进程发送SIGUSR1信号
            
            if ( retval )
            {
                puts( "kill failed." );
                perror( "kill" );
                waitpid( childpid, &status, 0 );
            }
            else
            {
                printf( "%d killed\n", childpid );
            }
            
        }
    }
    
    exit(EXIT_SUCCESS);
}