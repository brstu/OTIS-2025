#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Старт: PID=%d, PPID=%d\n", getpid(), getppid());

    if (fork() == 0) { printf("0 → 1: PID=%d, PPID=%d\n", getpid(), getppid()); exit(0); }
    if (fork() == 0) {
        printf("0 → 2: PID=%d, PPID=%d\n", getpid(), getppid());
        if (fork() == 0) { printf("2 → 4: PID=%d, PPID=%d\n", getpid(), getppid()); exit(0); }
        if (fork() == 0) { printf("2 → 5: PID=%d, PPID=%d\n", getpid(), getppid()); exit(0); }
        wait(NULL); wait(NULL); printf("Завершение 2: PID=%d\n", getpid()); exit(0);
    }
    if (fork() == 0) {
    if (fork() == 0) {
        printf("0 → 3: PID=%d, PPID=%d\n", getpid(), getppid());
        if (fork() == 0) {
            printf("3 → 6: PID=%d, PPID=%d\n", getpid(), getppid());
            execlp("df", "df", "-h", NULL);
            perror("exec"); exit(1);
        }
        wait(NULL); printf("Завершение 3: PID=%d\n", getpid()); exit(0);
    }

    wait(NULL); wait(NULL); wait(NULL);
    printf("Завершение 0: PID=%d\n", getpid());
    return 0;
}}