#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _SERVER_ 1
#define _CLIENT_ 2
#define PATHNAME "/home/xcli"
#define PROJNAME 0

typedef struct msgbuf{
    long mtype;
    char mtext[1024];
} msgbuf;

int MessageCommon(key_t key,int flag)
{
    int ret = 0;
    if(ret = msgget(key,flag)== -1)
    {
        perror("mesget:\n");
        exit(-1);
    }
    return ret;
}
//创建全新的消息队列(服务端)
int CreateMessage(key_t qid)
{
    return MessageCommon(qid,IPC_CREAT|IPC_EXCL|0666);
}
int GetMessage(key_t qid)
{
	return MessageCommon(qid,IPC_CREAT);
}
//消息队列的删除
void DestoryMessage(int msgid)
{
    if(msgctl(msgid,IPC_RMID,NULL) == -1)
    {
        perror("msgctl");
        exit(-4);
    }
}
void SendMessage(int msgid,const char* msg,int who)
{
    msgbuf buf;
    buf.mtype = who;
    strcpy(buf.mtext,msg);
    if(msgsnd(msgid,&buf,sizeof(buf.mtext),0))
    {	
		DestoryMessage(msgid);
        perror("msgsnd");
        exit(-2);
    }

}
void ReceiveMessage(int msgid,char* msg,int who)
{
    msgbuf buf;
    if(msgrcv(msgid,&buf,sizeof(buf.mtext),who,0)==-1)
    {
        perror("msgrcv");
        DestoryMessage(msgid);
        exit(-3);

    }
    strcpy(msg,buf.mtext);

}

