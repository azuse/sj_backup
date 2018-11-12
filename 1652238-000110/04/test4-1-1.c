#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;
    char mtext[255];
};

int main() {   
    int msg_id = msgget(411, IPC_CREAT | 0666);
    if (msg_id != -1) {
        struct msgbuf mybuf;
        mybuf.mtype = 1;
        strcpy(mybuf.mtext, "I'm send process.\n");
        
        if (msgsnd(msg_id, &mybuf, sizeof(mybuf.mtext), 0)) 
            printf("success\n");            
        else
            perror("msgsnd:");
    } else {
        perror("msgget:");
    }

    return 0;
}
