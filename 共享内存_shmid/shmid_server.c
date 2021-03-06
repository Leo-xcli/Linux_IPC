#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>

/*
//创建共享内存
int shmget(key_t key, size_t size, int shmflg);
//挂接共享内存
void *shmat(int shm_id, const void *shm_addr, int shmflg);
//去关联，将共享内存从当前进程分离
int shmdt(const void *shm_addr);
//共享内存控制函数
int shmctl(int shm_id, int cmd, struct shmid_ds *buf);
*/
#define PATHNAME "."
#define PROJ_ID 0x12345
int creatShm(int size);
int getShm();
int destoryShm(int shmid);

int CommShm(int size,int flags)
{
	int key=ftok(PATHNAME,PROJ_ID);
	if(key<0)
	{	
		perror("ftok");
		return -1;
	}
	int shmid = shmget(key,size,flags);
	if(shmid<0)
	{
		perror("shmid");
		return -2;
	}
	return shmid;
}
int creatShm(int size)
{
	return CommShm(size,IPC_CREAT|IPC_EXCL|0666);
}
int destoryShm(int shmid)
{
	if(shmctl(shmid,IPC_RMID,NULL)<0)
	{
		perror("shmctl");
		return -1;
	}
	return 0;
}
int main()
{
	int count = 0;
	int shmid = creatShm(1024);
	sleep(2);
	char *buf = shmat(shmid,NULL,0);
	while(count<4096)
    { 
        buf[count] = 'A'+count%26;
        sleep(2);
        count++;
        buf[count] = '\0';
    }
    shmdt(buf);
    sleep(5);
    destoryShm(shmid);
	return 0;
}
