#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct msgbuf {
    long mtype;
    char mtext[255];
};

int main() {
    int msg_id = msgget(411, IPC_CREAT | 0666);
    if (msg_id != -1) {
        struct msgbuf mybuf;
        if (msgrcv(msg_id, &mybuf, sizeof(mybuf.mtext), 0, IPC_NOWAIT) != -1) { 
            printf("read success: %s\n", mybuf.mtext);
            if (msgctl(msg_id, IPC_RMID, 0) != -1)
                printf("delete msg success\n");
        } else {
            perror("msgsnd:");
        }

    } else {
        perror("msgget:");
    }

    return 0;
}