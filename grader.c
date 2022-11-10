#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int split(char line[128], int ngrades);

int validateID(char line[128]);

int validateCommandline(int argc, char **argv);

int main(int argc, char **argv)
{
    remove("averages.txt"); // tries to remove existing averages text file
    validateCommandline(argc, argv);
    FILE *filePointer;
    filePointer = fopen(argv[3], "r");
    int nstudents = atoi(argv[1]);
    int ngrades = atoi(argv[2]);
    FILE *outputPointer = fopen("averages.txt", "w");
    printf("Input file. Opening.\n");
    printf("Output file. Opening.\n");
    char line[128];
    printf("Checking data.\n");
    printf("Computing averages.\n");
    for (int i = 0; i < nstudents; i++) // iterates through the lines for however many students there are
    {
        char line[128];
        fgets(line, 128, filePointer); // gets line from file
        int studentid = validateID(line);
        int score = split(line, ngrades);
        fprintf(outputPointer, " %d %d\n", studentid, score); // writes data to file
    }
    fclose(filePointer);
    fclose(outputPointer);
    printf("Input file. Closing.\n");
    printf("Output file. Closing.\n");
}

int validateID(char line[128])
{
    int index = 1;
    char studentid[7];
    int validID = 1;
    do
    { // procures the student ID and validates that it is the right length
        if (index < 9)
        {
            studentid[index - 1] = line[index];
            index++;
        }
        else
        {
            validID = 0;
        }
    } while (line[index] != ' ');
    if (validID == 1)
    {
        return atoi(studentid);
    }
    else
    {
        return 0;
    }
}

int validateCommandline(int argc, char **argv)
{
    int valid = 1;
    int nstudents;
    int ngrades;
    int x;
    char *filename;
    if (!(nstudents = atoi(argv[1]))) // checks that
    {
        valid = 0;
    }
    if (!(ngrades = atoi(argv[2])))
    {
        valid = 0;
    }
    if (!(filename = argv[3]))
    {
        valid = 0;
    }
    if (x = atoi(argv[4]))
    {
        valid = 0;
    }
    if (valid == 0)
    {
        printf("Incorrect arguments given. Expecting nStudents nGrades fileName. Exiting.\n");
        exit(0);
    }
    if (nstudents < 0 || nstudents > 100)
    {
        printf("Requires 1 to 100 students. Exiting.\n");
        exit(0);
    }
    if (ngrades < 1 || ngrades > 8)
    {
        printf("Requires 1 to 8 grades. Exiting.\n");
        exit(0);
    }
    FILE *filePointer;
    if (!(filePointer = fopen(argv[3], "r")))
    { // checks if file exists
        printf("Input file does not exist. Exiting.\n");
        exit(0);
    }
    return 0;
}

int split(char line[128], int ngrades)
{
    int total = 0;
    int amount = 0;
    int index = 1;
    char studentid[7];
    int validID = 1;
    do
    {
        if (index < 9)
        {
            studentid[index - 1] = line[index];
            index++;
        }
        else
        {
            validID = 0;
        }
    } while (line[index] != ' ');
    if (validID == 1)
    {
        int intID = atoi(studentid);
        if (intID >= 2022000 && intID <= 2022099)
        {
        }
        else
        {
            validID = 0;
        }
    } // repeats the validation pro
    if (validID == 1)
    {
        int divider = 0;
        int numAmount = 0;
        int numIndex = 0;
        char num[64];
        index++;
        do
        {
            if (line[index] == ' ' || line[index] == '\n')
            {
                int score = atoi(num);
                if ((score < 0 || score > 100) && score != -1)
                {
                    printf("Found an invalid grade: id %d grade %d. Exiting.\n", atoi(studentid), score);
                    exit(0);
                }
                if (score < 20 && score != -1)
                { // rounds outliers to stop them affecting the average
                    printf("Correcting student %d grade %d\n", atoi(studentid), score);
                    score = 20;
                }
                else if (score > 90)
                {
                    printf("Correcting student %d grade %d\n", atoi(studentid), score);
                    score = 90;
                }
                if (score != -1)
                {
                    total = total + score;
                    divider++;
                }
                memset(num, 0, 64);
                numIndex = 0;
                amount++;
                numAmount++;
            }
            else
            {
                num[numIndex] = line[index];
                numIndex++;
            }
            index++;
        } while (numAmount < ngrades);

        float average = (float)total / (float)divider; // calculates the average score in decimal form
        int finalAvg = (int)average;
        if ((average - finalAvg) >= 0.5)
        { // rounds to the nearest whole number
            finalAvg++;
        }
        return finalAvg;
    }
    else
    {
        printf("Found an invalid student id: %s. Exiting.\n", studentid);
        exit(0);
        remove("averages.txt");
    }
}