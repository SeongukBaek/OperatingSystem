#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/ptrace.h>

int main(int argc, char* argv[]) {
	pid_t pid;
        int count = 0;
        int waitstatus;
        int syscall_entry = 1;
	char *path = "/bin/";
	char *commands[1024];

	if (argc == 1) {
		puts("Usage wrong!");
		exit(1);
	}
        pid = fork();

        if (pid==0) {
                ptrace(PTRACE_TRACEME, NULL, NULL, NULL);
		strcat(path, argv[1]);
		//path complete
		printf("%s\n", path);
		for (int i=1;i<argc;i++) {
			commands[i-1]=argv[i];		
		}
		commands[argc-1]="\0";
		for (int i=0;i<argc;i++)
			printf("%s ", commands[i]);
		puts("");
		execv(path, commands);
        }
        else if (pid>0) {
                wait(&waitstatus);
                while (1) {
                        if (syscall_entry == 1) {
                                count++;
                                syscall_entry = 0;
                        }
                        else
                                syscall_entry = 1;
                        ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
                        wait(&waitstatus);
                        if (WIFEXITED(waitstatus))
                                break;
                }
        }
        else
                printf("fork error\n");
        printf("Total number of syscalls: %d\n", count);
        return 0;
}
