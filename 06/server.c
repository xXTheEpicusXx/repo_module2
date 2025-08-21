#include <sys/msg.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10
#define MAX_LEN 100
#define SERVER_ID 10

int users[MAX_SIZE] = {0};
int msqid = 0;

typedef struct msgbuf
{
    long mtype;
    int src_ID;
    char mtext[MAX_LEN];
} msgbuf;

void sendBroadcastMessage(msgbuf m)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (users[i] != 0)
        {
            msgsnd(msqid, &m, sizeof(msgbuf) - sizeof(long), 0);
        }
    }
}

void exitHandler()
{

    printf("\nСервер %d отключен\n", SERVER_ID);
    if (msqid != -1)
    {
        msgctl(msqid, IPC_RMID, NULL);
    }
    exit(0);
}

int main()
{
    key_t key = ftok(".", 1);
    msqid = msgget(key, IPC_CREAT | 0666);
    while (1)
    {

        msgbuf msg;
        msgrcv(msqid, &msg, sizeof(msgbuf) - sizeof(long), SERVER_ID, 0);
        if (strcmp(msg.mtext, "shutdown") == 0)
        {
            for (int i = 0; i < MAX_SIZE; i++)
            {
                if (users[i] == msg.src_ID)
                {
                    users[i] = 0;
                    printf("Клиент %d отключен\n", msg.src_ID);
                    break;
                }
            }
        }
        else
        {
            int isNew = 1;
            for (int i = 0; i < MAX_SIZE; i++)
            {
                if (users[i] == msg.src_ID)
                {
                    isNew = 0;
                    break;
                }
            }
            if (isNew)
            {
                for (int i = 0; i < MAX_SIZE; i++)
                {
                    if (users[i] == 0)
                    {
                        users[i] = msg.src_ID;
                        printf("Клиент %d подключен\n", msg.src_ID);
                        break;
                    }
                }
            }
        }
        sendBroadcastMessage(msg);
    }
}
