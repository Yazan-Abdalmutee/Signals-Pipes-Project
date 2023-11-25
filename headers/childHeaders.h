
#include <stdio.h>
	
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
int MIN, MAX, ChildNum, msg, keepSending;
pid_t child_id;
float RAND;

// functions
void signal_catcher(int);
void create_file();
void Resent_message(int);
float rand_float(int, int);
