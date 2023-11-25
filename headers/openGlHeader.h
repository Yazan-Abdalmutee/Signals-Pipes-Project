	
#include <GL/glut.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#define y_axis0 0.5
#define y_axis1 0.6  // this for y axis of [Team1] & [VS] & [Team2]
#define y_axis2 0.4  // this for y axis of [Score1]  & [Score2]
#define y_axis3 -0.4 // this for y axis of [Winner/Draw]
void finalWinner();
void drawFirework();
void signal_catcher(int the_sig);
void display();
void updateScore();
bool finished = false;
char winner[50];
char team1_score_str[10];
char team2_score_str[10];

char team1_player1_score_str[10];
char team1_player2_score_str[10];

char team2_player1_score_str[10];
char team2_player2_score_str[10];

char rounds_str[10];
void readData();
int counter=0;
