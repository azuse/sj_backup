#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

struct msgbuf
{
    long mtype;
    char mtext[255];
};

int main()
{
    struct msgbuf mybuf;

    int sned_id = msgget(411, IPC_CREAT | 0666);
    if (sned_id != -1)
    {
        mybuf.mtype = 1;
        strcpy(mybuf.mtext, "I'm test2-4-1.\n");
        int sndret = msgsnd(sned_id, &mybuf, sizeof(mybuf.mtext), 0);
        if (sndret == 0)
            printf("test2-4-1 msgsnd success, msgsnd return %d\n", sndret);
        else
            perror("msgsnd:");
    }
    else
    {
        perror("msgget:");
    }

    int recv_id = msgget(412, IPC_CREAT | 0666);
    if (msgrcv(recv_id, &mybuf, sizeof(mybuf.mtext), 2, 0) != -1)
    {
        printf("test2-4-1 read success: %s\n", mybuf.mtext);
        if (msgctl(recv_id, IPC_RMID, 0) != -1)
            printf("test2-4-1 delete msg success\n");
    }
    else
    {
        perror("test2-4-1 read error:");
    }
    if (msgctl(recv_id, IPC_RMID, 0) != -1)
        printf("delete msg success\n");
    return 0;
}
