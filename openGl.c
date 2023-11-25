#include "headers/openGlHeader.h"
#include "headers/parentOpengl.h"
int main(int argc, char **argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("^^ Random Game ^^");
    glutTimerFunc(0, updateScore, 0);
    glutDisplayFunc(display);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutMainLoop();
    return 0;
}
void drawFirework()
{
    int numParticles = 50;
    float speed = 0.5f;
    float lifespan = 2.0f;
    float gravity = -0.1f;
    float friction = 0.99f;

    // draw explosion
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < numParticles; i++)
    {
        glVertex3f(0.0f, 0.0f, 0.0f);

        float vx = (float)rand() / RAND_MAX * 2.0f - 1.0f;
        float vy = (float)rand() / RAND_MAX * 2.0f - 1.0f;
        float vz = (float)rand() / RAND_MAX * 2.0f - 1.0f;
        float speedFactor = (float)rand() / RAND_MAX * speed;
        float lifespanFactor = (float)rand() / RAND_MAX * lifespan;

        float ax = 0.0f;
        float ay = gravity;
        float az = 0.0f;

        for (int j = 0; j < 60; j++)
        {
            speedFactor *= friction;
            lifespanFactor -= 0.02f;
            vx += ax;
            vy += ay;
            vz += az;
            glPointSize(lifespanFactor);
            glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
            glVertex3f(vx * speedFactor, vy * speedFactor, vz * speedFactor);
        }
    }
    glEnd();
}
void display()
{
    if (rounds <= numOfRounds)
    {

        // Clear the window
        glClear(GL_COLOR_BUFFER_BIT);

        // Set color for Rounds
        glColor3f(0.0, 0.0, 1.0);
        glRasterPos2f(-0.16, 0.3);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Round: ");
        sprintf(rounds_str, "%d", rounds);
        glutBitmapString(((void *)&glutBitmapTimesRoman24), rounds_str);

        // Set color for Team1
        glColor3ub(255, 165, 0); // #FFA500

        // Draw header
        glRasterPos2f(-0.94, y_axis1);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Team One");

        // Set color for Player1 and Player2
        glColor3f(1.0, 0.0, 0.0); // Red

        // Draw player scores
        glRasterPos2f(-0.9, y_axis2);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Player 1");
        glRasterPos2f(-0.6, y_axis2);
        sprintf(team1_player1_score_str, "%.2f", team1_player1_score);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, team1_player1_score_str);

        glRasterPos2f(-0.9, y_axis2 - 0.15);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Player 2");
        glRasterPos2f(-0.6, y_axis2 - 0.15);
        sprintf(team1_player2_score_str, "%.2f", team1_player2_score);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, team1_player2_score_str);

        // Set color for Total
        glColor3ub(0, 128, 0); // #008000

        // Draw total score
        glRasterPos2f(-0.9, y_axis2 - 0.3);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Total");
        glRasterPos2f(-0.6, y_axis2 - 0.3);
        sprintf(team1_score_str, "%.2f", team1_sum);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, team1_score_str);

        glColor3ub(0, 191, 255); // #FFA500
        glRasterPos2f(0.35, y_axis1);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Team Two");
        glColor3f(1.0, 0.0, 0.0); // reddd
        glRasterPos2f(0.4, y_axis2);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Player1 ");
        glRasterPos2f(0.7, y_axis2);
        sprintf(team2_player1_score_str, "%.2f", team2_player1_score);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, team2_player1_score_str);

        glRasterPos2f(0.4, y_axis2 - 0.15);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Player2 ");
        glRasterPos2f(0.7, y_axis2 - 0.15);
        sprintf(team2_player2_score_str, "%.2f", team2_player2_score);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, team2_player2_score_str);

        glColor3ub(0, 128, 0); // #008000
        glRasterPos2f(0.4, y_axis2 - 0.3);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Total ");
        glRasterPos2f(0.7, y_axis2 - 0.3);
        sprintf(team2_score_str, "%.2f", team2_sum);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, team2_score_str);

        // Set color for VS
        glColor3ub(255, 165, 0); // #FFA500

        glRasterPos2f(-0.1, y_axis0);

        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "VS");

        // Check score and set color for winner
        if (team1_sum > team2_sum)
        {
            glColor3ub(255, 165, 0); // #FFA500
            glRasterPos2f(-0.25, y_axis3);
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Team One Wins!");
        }
        else if (team2_sum > team1_sum)
        {
            glColor3ub(0, 191, 255); // #FFA500
            glRasterPos2f(-0.25, y_axis3);
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Team Two Wins!");
        }
        else
        {
            glColor3ub(0, 0, 139); // #00008B
            glRasterPos2f(-0.25, y_axis3);
            glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Draw!");
        }

        glColor3f(1.0, 1.0, 0.0);
        glRasterPos2f(-0.9, y_axis3);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Score: ");
        sprintf(team1_score_str, "%.2f", team1_score);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, team1_score_str);

        glColor3f(1.0, 1.0, 0.0);
        glRasterPos2f(0.4, y_axis3);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Score: ");
        sprintf(team2_score_str, "%.2f", team2_score);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, team2_score_str);
        if (rounds == numOfRounds)
            rounds += 1;
        // Swap buffers
        glutSwapBuffers();
    }
    else
    {
        sleep(3);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0); // Red

        finalWinner();
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, winner);
        drawFirework();
        glutSwapBuffers();


    }
    counter+=1;
}
void finalWinner()
{
    char c[100];
    if (team1_score > team2_score)
    {
        sprintf(c, "!!! Team One Is The Winner With Score %.2f - %.2f !!!", team1_score, team2_score);
        strcpy(winner, c);
        glRasterPos2f(-0.6, 0.3);
    }
    else if (team1_score < team2_score)
    {
        sprintf(c, "!!! Team Two Is The Winner With Score %.2f - %.2f !!!", team2_score, team1_score);

        strcpy(winner, c);
        glRasterPos2f(-0.6, 0.3);
    }
    else
    {
        strcpy(winner, "!!! DRAW !!!");
        glRasterPos2f(-0.18, 0.3);
    }
}
void updateScore()
{
        if (rounds < numOfRounds && counter!=0)
    {
        readData();
    }
    glutPostRedisplay();
    glutTimerFunc(0, updateScore, 0);
    

}
void readData()
{

    FILE *fp;
    char buffer[100];

    fp = fopen("openGlData.txt", "r");
while(fp==NULL)
{    
    
        fp = fopen("openGlData.txt", "r");

 }

    fgets(buffer, 100, fp);

    sscanf(buffer, "%d,%d,%f,%f,%f,%f,%f,%f,%f,%f\n", &numOfRounds, &rounds, &team1_player1_score, &team1_player2_score, &team2_player1_score, &team2_player2_score, &team1_sum, &team2_sum, &team1_score, &team2_score);

    fclose(fp);
}
