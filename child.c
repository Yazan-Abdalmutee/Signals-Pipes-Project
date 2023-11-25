#include "headers/childHeaders.h"
int main(int argc, char **argv)
{ // number of arguments , array of the values of arguments

    if (argc != 2)
    {

        printf("Please check the number of arguments argc=[%d]\n", argc);
        fflush(stdout);
        exit(-1);
    }

    child_id = getpid();
    ChildNum = atoi(argv[1]);

    // printf("\nHello From Child%d pid = %d File\n", ChildNum, child_id);
    fflush(stdout);
    if (sigset(2, signal_catcher) == -1)
    {
        perror("Sigset can not set SIGINT");
        fflush(stdout);
        exit(SIGINT);
    }

    if (sigset(3, signal_catcher) == -1)
    {
        perror("Sigset can not set SIGINT");
        fflush(stdout);
        exit(SIGINT);
    }

    while (1)
    {
        pause(); // Wait for SIGUSR1 signal from parent
    }
}
void ReadFile()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
      
    }
    else
    {
        perror("getcwd() error");
        fflush(stdout);
        exit(1);
    }

    strcat(cwd, "/Range.txt");
    FILE *inFile = fopen(cwd, "r");
    if (inFile == NULL)
    {
        perror("Error opening file");
        fflush(stdout);
        exit(1);
    }

    else
    {
        if (fscanf(inFile, "%d,%d", &MIN, &MAX) != 2)
        {
            printf("\n[%d]Error: invalid file format --> Please write (Minimum value, Maximum value) format\n", getpid());
            fflush(stdout);
            fclose(inFile);
        }
    }
}
void signal_catcher(int the_sig)
{
    if (the_sig == 2)
    {

        keepSending = 1;
        ReadFile();
        create_file();
    }

    else if (the_sig == 3)
    {
        keepSending = 0;
    }

    else
    {
        printf("[Error] I got unknown Signal = [%d]", the_sig);
        fflush(stdout);
    }
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
void create_file()
{

    char filename[10]; // buffer for filename string
    FILE *pidFile;
    sprintf(filename, "%d.txt", child_id); // 1.txt  or  2.txt

    if (access(filename, F_OK) == 0)
    {
        // If the file exists, remove it
        if (remove(filename) != 0)
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
    pidFile = fopen(filename, "w");

    if (pidFile == NULL)
    {
        perror("Error creating file");
        fflush(stdout);
        exit(-2);
    }

    // to find and write the random value on child file

    RAND = rand_float(MIN, MAX);
    fprintf(pidFile, "%f\n", RAND);
    fclose(pidFile);
    int signal_type;

    if (ChildNum == 0)
    {
        signal_type = 2;
    }

    else if (ChildNum == 1)
    {
        signal_type = 3;
    }

    else if (ChildNum == 2)
    {
        signal_type = 10;
    }

    else if (ChildNum == 3)
    {
        signal_type = 12;
    }
    else
    {

        printf("\n[Error] I got unknown ChildNum = [%d]\n", ChildNum);
        fflush(stdout);
    }


    while (keepSending)
    {

        if (kill(getppid(), signal_type) != 0)
        {
            printf("\nFailed to send signal [%d] to parent\n", signal_type);
            fflush(stdout);
        }
        else
        {
        }
        sleep(1);

        // Send a signal for the parent that he is done
    }
}