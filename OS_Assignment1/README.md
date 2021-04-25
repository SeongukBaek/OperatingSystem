# OS Programming Assignment 1

1. Allow any program to be monitored as the command line argument.

Currently, it is hardcoded to run only the '`date`' command. You should modify the program above so that any program can be specified as command-line arguments.

```sh
example1) $ ./myptrace ps -ef

example2) $ ./myptrace ls
```

 

2. Identify which system calls are called, not just the count and print the statistic at the end.

Currently, it prints out only the total number of system calls invoked by the date program. You should modify the program so that it show the number of invocation per each system call in a sorted list.

```sh
example)
$ ./myptrace date
Sun Apr 25 16:39:00 KST 2021
*Total number of syscalls: 42*
   *8 mmap*
   *6 fstat*
   *6 close*
   *4 open*
   *4 mprotect*
   *3 read*
   *3 brk*
   *3 access*
   *1 write*
   *1 munmap*
   *1 lseek*
   *1 arch_prctl*
   *1 execve*
```

In order to implement, you should find a way to extract the system call number. Study **`PTRACE_GETREGS`** option of the `ptrace` for this. Also you should consider using '`struct user_regs_struct`'

 

3. Code and program name should be `myptrace.c` and `myptrace`