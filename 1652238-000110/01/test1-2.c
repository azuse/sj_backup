#define _POSIX_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <error.h>
#include <stdlib.h>

int main() {
  char *send ="Hello";
  char buf[80];
  int  p1[2], p2[2];

  if (pipe(p1) != 0)
    perror("first pipe() failed");
  else if (pipe(p2) != 0)
    perror("second pipe() failed");
  else if (fork() == 0) {
    //close(p1[1]);
    //close(p2[0]);
    if (read(p1[0], buf, sizeof(buf)) == -1)
      perror("read() error in parent");
    else {
      printf("child read %s\n", buf);
      if (write(p2[1], buf, strlen(buf)+1) == -1)
        perror("write() error in child");
      else
        printf("child wirte %s\n", send);
    }
    exit(0);
  }
  else {
    //close(p1[0]);
    //close(p2[1]);
    printf("parent is writing '%s' to pipe 1\n", send);
    if (write(p1[1], send, strlen(send)+1) == -1)
      perror("write() error in parent");
    else if (read(p2[0], buf, sizeof(buf)) == -1)
      perror("read() error in parent");
    else printf("parent read '%s' from pipe 2\n", buf);
  }
  return 0;
}