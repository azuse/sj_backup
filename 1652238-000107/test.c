#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/prctl.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <malloc.h>
#include <stdarg.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAXLINE 100
extern char **environ;
static char **g_main_Argv = NULL;	/* pointer to argument vector */
static char *g_main_LastArgv = NULL; /* end of argv */

static void sig_child(int signo);

int readconf();

void setproctitle_init(int argc, char **argv, char **envp)
{
	int i;

	for (i = 0; envp[i] != NULL; i++) // calc envp num
		continue;
	environ = (char **)malloc(sizeof(char *) * (i + 1)); // malloc envp pointer

	for (i = 0; envp[i] != NULL; i++)
	{
		environ[i] = malloc(sizeof(char) * strlen(envp[i]));
		strcpy(environ[i], envp[i]);
	}
	environ[i] = NULL;

	g_main_Argv = argv;
	if (i > 0)
		g_main_LastArgv = envp[i - 1] + strlen(envp[i - 1]);
	else
		g_main_LastArgv = argv[argc - 1] + strlen(argv[argc - 1]);
}

void daemon_by_hand()
{
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
	}
	else
		exit(0);
	//skip setsid
	//setsid();

	//fork twice
	pid = fork();
	if (pid == 0)
	{
	}
	else
		exit(0);

	chdir("/");
	umask(0);

	int j = open("/dev/null", O_RDWR);
	dup2(j, 0);
	dup2(j, 1);
	dup2(j, 2);

	signal(SIGCHLD, SIG_IGN);
}

int main(int argc, char *argv[])
{
	time_t start_t, now_t;
	time(&start_t);
	int diff_t;

	daemon_by_hand();
	signal(SIGCHLD, sig_child);

	char argv_buf[MAXLINE] = {0}; // save argv paramters
	int i;
	for (i = 1; i < argc; i++)
	{
		strcat(argv_buf, argv[i]);
		strcat(argv_buf, " ");
	}
	//修改argv[0]所指向的内存空间的内容
	setproctitle_init(argc, argv, environ);

	char pid_name[MAXLINE];
	time(&now_t);
	diff_t = difftime(now_t, start_t);
	snprintf(pid_name, 30, "./test [main %02d:%02d:%02d]", diff_t / 3600, (diff_t % 3600 - diff_t % 60) / 60, diff_t % 60);
	prctl(PR_SET_NAME, pid_name);
	strcpy(g_main_Argv[0], pid_name);

	char inbuf[MAXLINE];
	int pid_val = readconf();
	
	printf("%d", pid_val);
	fflush(stdout);

	int pid;
	int myson[10];
	for (i = 0; i < pid_val; i++)
	{
		pid = fork();
		switch (pid)
		{
		case -1:
		{
			printf("fork failed/n");
			fflush(stdout);
			exit(0);
		}
		case 0:
		{
			prctl(PR_SET_PDEATHSIG, SIGHUP);
			time(&start_t);
			time(&now_t);
			diff_t = difftime(now_t, start_t);
			snprintf(pid_name, 30, "./test [sub-%02d %02d:%02d:%02d]", i, diff_t / 3600, (diff_t % 3600 - diff_t % 60) / 60, diff_t % 60);
			prctl(PR_SET_NAME, pid_name);
			strcpy(g_main_Argv[0], pid_name);
			break;
		}
		default:
		{
		}
		}
		if (pid == 0)
			break;
		else
		{
			myson[i] = pid;
			time(&now_t);
			diff_t = difftime(now_t, start_t);
			snprintf(pid_name, 30, "./test [main %02d:%02d:%02d]", diff_t / 3600, (diff_t % 3600 - diff_t % 60) / 60, diff_t % 60);
			prctl(PR_SET_NAME, pid_name);
			strcpy(g_main_Argv[0], pid_name);
		}
		sleep(1);
	}

	while (1)
	{
		if (pid == 0)
		{
			time(&now_t);
			diff_t = difftime(now_t, start_t);
			snprintf(pid_name, 30, "./test [sub-%02d %02d:%02d:%02d]", i, diff_t / 3600, (diff_t % 3600 - diff_t % 60) / 60, diff_t % 60);
			prctl(PR_SET_NAME, pid_name);
			strcpy(g_main_Argv[0], pid_name);
		}
		else
		{
			time(&now_t);
			diff_t = difftime(now_t, start_t);
			snprintf(pid_name, 30, "./test [main %02d:%02d:%02d]", diff_t / 3600, (diff_t % 3600 - diff_t % 60) / 60, diff_t % 60);
			prctl(PR_SET_NAME, pid_name);
			strcpy(g_main_Argv[0], pid_name);
			for (i = 0; i < 10; i++)
			{
				if (kill(myson[i], 0) == -1)
				{
					pid = fork();
					if (pid == 0)
					{

						prctl(PR_SET_PDEATHSIG, SIGHUP);
						time(&start_t);
						break;
					}
					else
					{
						myson[i] = pid;
					}
				}
			}
		}
		//printf("1652238\n");
		fflush(stdout);
		sleep(1);
	};
	for (i = 0; environ[i] != NULL; i++)
		free(environ[i]);

	return 0;
}

static void sig_child(int signo)
{
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		printf("child %d exited with signal %d\n", pid, signo);
		fflush(stdout);
	}
}