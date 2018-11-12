#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct msgbuf
{
    long mtype;
    char mtext[255];
};

int main()
{
    struct msgbuf mybuf;

    int recv_id = msgget(411, IPC_CREAT | 0666);
    if (msgrcv(recv_id, &mybuf, sizeof(mybuf.mtext), 1, 0) != -1)
    {
        printf("test2-4-2 read success: %s\n", mybuf.mtext);
        if (msgctl(recv_id, IPC_RMID, 0) != -1)
            printf("test2-4-2 delete msg success\n");
    }
    else
    {
        perror("test2-4-2 msgcv error:");
    }
    if (msgctl(recv_id, IPC_RMID, 0) != -1)
        printf("delete msg success\n");


    struct msgbuf sndbuf;
    int sned_id = msgget(412, IPC_CREAT | 0666);
    if (sned_id != -1)
    {
        sndbuf.mtype = 2;
        strcpy(sndbuf.mtext, "I'm test2-4-2.\n");
        int sndret = msgsnd(sned_id, &sndbuf, sizeof(sndbuf.mtext), 0);
        if (sndret == 0)
            printf("test2-4-2 msgsnd success\n");
        else
        {
            perror("test2-4-2 msgsnd error:");
        }
    }
    else
    {
        perror("test2-4-2 msgget error:");
    }

    return 0;
}