#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#define NUM_CHILDREN 5
#define MIN 1
#define MAX 100
int send_msg(int pid, int signal);
void winnerInTheRound();
void winnerInTheCompettive();
void signal_catcher(int the_sig);
float read_file(int pid);
void sigsetFunction();
void gccFunction();
void pipeCheckFunction();
void cleanKillFunction();
float read_file(int pid);
void sigsetFunction();
void gccFunction();
void pipeCheckFunction();
void cleanKillFunction();
int send_msg(int pid, int signal);
void winnerInTheRound();
void winnerInTheCompettive();
void fileOpenGl();
void signal_catcher(int the_sig);
int flag_file1 = 1, flag_file2 = 1, flag_file3 = 1, flag_file4 = 1;
int childrenPid[5];
int parent_to_child[1][2], child_to_parent[1][2];
float randomValues[4];
char msg[50], msg2[50];
char filename[20];
pid_t pid;
int seed = 0;
