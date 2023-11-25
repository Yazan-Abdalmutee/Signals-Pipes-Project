#include "headers/parentHeaders.h"
#include"headers/parentOpengl.h"
int main(int argc, char **argv)
{
    int i, j;
    if (argc > 2)
    {
        printf("Please check the number of arguments argc that u passed=[%d]\n\n", argc - 1);
        fflush(stdout);
        exit(-1);
    }
    if (argc == 2)
    {
        numOfRounds = atoi(argv[1]);
    }
       gccFunction();
    sigsetFunction();

    pipeCheckFunction();

    // Fork child processes
    for (i = 0; i < NUM_CHILDREN; i++)
    {
        pid = fork();

        if (pid == -1)
        {
            perror("fork error");
            exit(-1);
        }
        if (pid > 0)
        {
            childrenPid[i] = pid;
        }

        else if (pid == 0 && i < 4)
        {

            // printf("\nIm the child with PID = [%d] \n",getpid());

            char path[50];
            sprintf(path, "../ProjectOne/child%d", i);
            char fileName[50];
            sprintf(fileName, "child%d", i);

            char str[10];
            sprintf(str, "%d", i);
            execlp(path, fileName, str, (char *)NULL);

            // execlp("/home/taherhasan/Desktop/project 1/child2", "child2","2",(char *) NULL);
            printf("\nError with execlp in pid = [%d]\n", getpid());
            fflush(stdout);
        }
        else if (pid == 0 && i == 4)
        {                                 // child 5     {
            close(parent_to_child[0][1]); // Close write end of parent-to-child pipe
            close(child_to_parent[0][0]); // Close read end of child-to-parent pipe
            while (1)
            {
                // Wait for the parent to send the numbers
                read(parent_to_child[0][0], msg, sizeof(msg));
                sscanf(msg, "%f,%f,%f,%f", &team1_player1_score, &team1_player2_score, &team2_player1_score, &team2_player2_score);
                team1_sum = (float)team1_player1_score + (float)team1_player2_score;
                team2_sum = (float)team2_player1_score + (float)team2_player2_score;
                sprintf(msg, "%.2f,%.2f", team1_sum, team2_sum);
                write(child_to_parent[0][1], msg, strlen(msg) + 1);
            }
        }
    }

    // pid for children 5 is newChildPid

    int pid = fork();
    int newChildPid = 0;
    if (pid == 0)
    {
        execlp("../ProjectOne/openglrun", "openglrun", 0, (char *)NULL);
        printf("\nError with execlp in pid = [%d]\n", getpid());
        fflush(stdout);

    }

    for (int k = 0; k < numOfRounds; k++)
    {
        rounds=k+1;
        if (k != 0)
            printf("\n\n\n");
        printf("ROUND: %d\n", k + 1);

        FILE *fp = fopen("Range.txt", "w");
        if (fp == NULL)
        {
            printf("Error opening filee\n");
            return 1;
        }
        fprintf(fp, "%d,%d", MIN, MAX);
        fclose(fp);

        // communication between children 1,2,3,4

        sleep(2);
        for (int i = 0; i < 4; i++)
        {
            send_msg(childrenPid[i], 2);
        }

        // flags

        while (flag_file1 || flag_file2 || flag_file3 || flag_file4)
            ;
        int teamNumber = 1, playerNumber = 1;
            flag_file1 = 1;
            flag_file2 = 1;
            flag_file3 = 1;
            flag_file4 = 1;
        for (int j = 0; j < 4; j++)
        {

            if (j == 2)
            {
                teamNumber += 1;
                playerNumber = 1;
            }
            randomValues[j] = read_file(childrenPid[j]);
            team1_player1_score=randomValues[0];
            team1_player2_score=randomValues[1];
            team2_player1_score=randomValues[2];
            team2_player2_score=randomValues[3];
            printf("\nTeam %d player %d randomValue=[%.2f]\n", teamNumber, playerNumber, randomValues[j]);
            playerNumber += 1;
            fflush(stdout);
        }

        // child 5 task: parent send ...
        sprintf(msg, "%f,%f,%f,%f", randomValues[0], randomValues[1], randomValues[2], randomValues[3]);
        write(parent_to_child[0][1], msg, strlen(msg) + 1);
        read(child_to_parent[0][0], msg, sizeof(msg));

        sscanf(msg, "%f,%f", &team1_sum, &team2_sum);
        printf("\nThe sum for random numbers for team1=[%.2f] , team2=[%.2f]\n", team1_sum, team2_sum);

        winnerInTheRound();
        fileOpenGl();
        
        sleep(4);

    } // end the loop
    winnerInTheCompettive();
    // Close pipes
    for (i = 0; i < NUM_CHILDREN; i++)
    {
        close(parent_to_child[i][1]);
        close(child_to_parent[i][0]);
    }

    cleanKillFunction();
    return 0;
}
float rand_float(int min, int max)
{

    time_t current_time;
    time(&current_time);
    pid_t pid = getpid();

    // set the seed for the random number generator
    srand(current_time + pid);

    // generate a random float number between 0 and 1
    float random_num = (float)rand() / ((float)RAND_MAX + 1) * (max - min) + min;

    return random_num;
}
void winnerInTheCompettive()
{
    printf("\n\n*******************************************************\n");
    if (team1_score > team2_score)
    {
        printf("\nTeam 1 win in the compettive with Score %.2f - %.2f\n", team1_score, team2_score);
        team1_score += 1;
    }
    else if (team1_score == team2_score)
    {
        printf("\nThe compettive ends Draw with result: %.2f - %.2f\n", team1_score, team2_score);
        team2_score += 0.5;
        team1_score += 0.5;
    }
    else
    {
        printf("\nTeam 2 win in the compettive with Score %.2f - %.2f\n", team1_score, team2_score);
        team1_score += 1;
    }
    printf("\n*******************************************************\n");
}
void winnerInTheRound()
{
    if (team1_sum > team2_sum)
    {
        printf("\nTeam 1 is the winner in this round\n");
        team1_score += 1;
    }
    else if (team1_sum == team2_sum)
    {
        printf("\nIts Draw\n");
        team1_score += 0.5;
        team2_score += 0.5;
    }
    else
    {
        printf("\nTeam 2 is the winner in this round\n");
        team2_score += 1;
    }
}
void cleanKillFunction()
{
    int ret, index = 0;
    while (index < 4)
    {
        send_msg(childrenPid[index], SIGKILL);

        sprintf(filename, "%d.txt", childrenPid[index]);
        ret = remove(filename);

        if (ret == 0)
        {
            // printf("\nFile: %s deleted successfully", filename);
            fflush(stdout);
        }
        else
        {
            printf("\n[Error]: unable to delete the file");
        }
        index++;
    }

    send_msg(childrenPid[4], SIGKILL);

    ret = remove("Range.txt");
    if (ret == 0)
    {
        //printf("\nFile: range.txt deleted successfully");
 
    }
    else
    {
        printf("Error: unable to delete the file Range.txt");
        fflush(stdout);
    }

    system("rm child0");
    system("rm child1");
    system("rm child2");
    system("rm child3");
    system("rm openglrun");
    system("rm openGlData.txt");

}
int send_msg(int pid, int signal)
{
    // printf("SEND MSG pid =%d  singal =%d\n",pid,signal);

    // Send the signal to the process with the specified PID

    if (kill(pid, signal) != 0)
    {
        printf("[Parent] Failed to send signal %d to process %d.\n", signal, pid);
    }
}
void signal_catcher(int the_sig)
{
    if (the_sig == 2)
    {
        flag_file1 = 0;
        send_msg(childrenPid[0], 3);
    }
    else if (the_sig == 3)
    {
        flag_file2 = 0;
        send_msg(childrenPid[1], 3);
    }
    else if (the_sig == 10)
    {
        flag_file3 = 0;
        send_msg(childrenPid[2], 3);
    }
    else if (the_sig == 12)
    {
        flag_file4 = 0;
        send_msg(childrenPid[3], 3);
    }
}
float read_file(int pid)
{
    FILE *fp;
    char buffer[10];
    char filename[10];
    sprintf(filename, "%d.txt", pid);
    fp = fopen(filename, "r");

    fgets(buffer, 10, fp);
    fclose(fp);
    return atof(buffer);
}
void sigsetFunction()
{

    if (sigset(2, signal_catcher) == -1)
    {
        perror("Sigset can not set SIGINT");
        exit(0);
    }

    if (sigset(3, signal_catcher) == -1)
    {
        perror("Sigset can not set SIGINT");
        exit(0);
    }
    if (sigset(10, signal_catcher) == -1)
    {
        perror("Sigset can not set SIGINT");
        exit(0);
    }

    if (sigset(12, signal_catcher) == -1)
    {
        perror("Sigset can not set SIGINT");
        exit(0);
    }
}
void gccFunction()
{
    system("gcc -o openglrun openGl.c -lglut -lGL -lm");
    if ((system("gcc child.c -o child0") != 0) || (system("gcc child.c -o child1") != 0) || (system("gcc child.c -o child2") != 0) || (system("gcc child.c -o child3")) || (system("clear") != 0))
    {
        perror("gcc childs");
        exit(0);
    }
 
}
void pipeCheckFunction()
{
    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        if (pipe(parent_to_child[i]) < 0 || pipe(child_to_parent[i]) < 0)
        {
            perror("pipe error");
            exit(EXIT_FAILURE);
        }
    }
}
void fileOpenGl()
{
    
    char filename[10]; // buffer for filename string
    FILE *file;

    if (access("openGlData.txt", F_OK) == 0)
    {
        // If the file exists, remove it
        if (remove("openGlData.txt") != 0)
        {
            // Error removing the file
            perror("Error removing file");
        }
        else
        {
            // printf("File removed successfully.\n");
        }
    }
    else
    {
        // printf("File does not exist.\n");
    }
    file = fopen("openGlData.txt", "w");

    // to find and write the random value on child file

    
    fprintf(file, "%d,%d,%f,%f,%f,%f,%f,%f,%f,%f\n",numOfRounds,rounds, team1_player1_score,team1_player2_score,team2_player1_score,team2_player2_score,team1_sum,team2_sum,team1_score,team2_score);
    fclose(file);
}
