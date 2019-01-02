#include"common.h"
#include<stdio.h>
#include<pthread.h>
int msgid = 0;
void* Receive(void* arg){
	char buff[1024] = {0};
	fflush(stdout);
	ReceiveMessage(msgid,buff,_SERVER_);
	printf("Server#%s\n",buff);
}

void* Send(void* arg){
	char buff[1024] = {0};
	printf("Client#");
	fflush(stdout);
	ssize_t s = read(1,buff,sizeof(buff));
	buff[s-1] = 0;
	SendMessage(msgid,buff,_CLIENT_);
}

int main(){
	key_t key = ftok(PATHNAME,PROJNAME);
	if(key < 0){
		perror("ftok");
		return 1;
	}
	msgid = GetMessage(key);
	pthread_t c1,c2;
	for(int i=0; i<10; ++i){
		pthread_create(&c1,NULL,Send,NULL);
		pthread_create(&c2,NULL,Receive,NULL);
		pthread_join(c1,NULL);//等待线程结束
		pthread_join(c2,NULL);
	}
	return 0;
}
