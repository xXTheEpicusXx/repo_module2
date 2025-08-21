#include <sys/msg.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define MAX_LEN 100
#define SERVER_ID 10

int client_ID = 0;
int msqid = 0;

typedef struct msgbuf
{
    long mtype;
    int src_ID;
    char mtext[MAX_LEN];
} msgbuf;

void sendMessage(char *text)
{
    msgbuf m;
    m.mtype = SERVER_ID;
    m.src_ID = client_ID;
    strncpy(m.mtext, text, MAX_LEN);
    msgsnd(msqid, &m, sizeof(msgbuf) - sizeof(long), 0);
}

void receiveMessage()
{
    msgbuf m;
    msgrcv(msqid, &m, sizeof(msgbuf) - sizeof(long), client_ID, IPC_NOWAIT);
    printf("User%d: %s", m.src_ID, m.mtext);
}

int main(int argc, char *argv[])
{
    client_ID = atoi(argv[1]);
    key_t key = ftok(".", 1);
    char buffer[MAX_LEN];
    msqid = msgget(key, 0666);

    if (fork() == 0) // отдельный процесс для приема
    {
        receiveMessage();
        exit(0);
    }

    while (1)
    {
        fgets(buffer, MAX_LEN, stdin);
        sendMessage(buffer);
        if (strcmp(buffer, "shutdown") == 0)
        {
            break;
        }
    }
}
