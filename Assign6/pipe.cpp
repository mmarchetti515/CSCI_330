//*******************************************************************
//
//  pipe.cpp
//  CSCI 330 Assignment 6
//
//  Michael Marchetti z1860574
//
//*******************************************************************

#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include <string.h>
using namespace std;

void setargv(char *command, char *argv[]);

int main()
{
    // array command 1/2 
    char command1[256], command2[256];
    char *argv1[6], *argv2[6];
    
    int pipefd[2], status = 0, rs = 0;
    pid_t pid;

    // next two groups retrieve command arguments, is repeated at the end to check for end
    // retrieve command 1, call setargv using command 1 as new param
    cout << "Enter command 1: ";
    cin.getline(command1, 256);
    setargv(command1, argv1);

    // retrieve command 2, call setargv using command 2 as a param
    cout << "Enter command 2: ";
    cin.getline(command2, 256);
    setargv(command2, argv2);

    // while loop performs function logic, will continue until "end" command given
    while (strcmp(command1, "end") != 0 && strcmp(command2, "end") != 0)
    {
        pid = fork();
        if (pid == -1) 
        {
            perror("fork"); // displays error message in the case of a fork error
            exit(1);
        }

        if (pid == 0)
        {
            rs = pipe(pipefd);
            if (rs == -1)
            {
                perror("pipe"); // displays error message in the case of a pipe error
                exit(1);
            }

            pid = fork();
            if (pid == -1)
            {
                perror("fork"); // displays error message in the case of a fork error
                exit(1);
            }

            if (pid == 0)
            {
                close(pipefd[1]);
                close(0);
                dup(pipefd[0]);
                close(pipefd[1]);

                rs =execvp(argv2[0], argv2);
                if (rs == -1)
                {
                    perror("exec"); // displays error message in the case of a exec error
                    exit(1);
                }
            }
            else
            {
                close(pipefd[0]);
                close(1);
                dup(pipefd[1]);
                close(pipefd[1]);

                rs = execvp(argv1[0], argv1);
                if (rs == -1)
                {
                    perror("exec"); // displays error message in the case of a exec error
                    exit(1);
                }

                pid = wait(&status); 
                if (pid == -1)
                { 
                    perror("wait"); // displays error message in the case of a wait error
                    exit(1);
                }
            }
        }

        pid = wait(&status);
        if (pid == -1) 
        { 
            perror("wait"); // displays error message in the case of a wait error
            exit(1);
        }

        // retrieve command 1, call setargv using command 1 as new param
        cout << "Enter command 1: ";
        cin.getline(command1, 256);
        setargv(command1, argv1);

        // retrieve command 2, call setargv using command 2 as a param
        cout << "Enter command 2: ";
        cin.getline(command2, 256);
        setargv(command2, argv2);
    }

    // exit successfully
    exit(0);
}

void setargv(char* command, char* argv[])
{
    // 
    char *token;
    token = strtok(command, " ");
    
    int count = 0;
    // check if not null
    while (token != NULL)
    {
        // import to token array
        token = strtok(NULL, " ");
        // incremement
        argv[++count] = token;
    }

}