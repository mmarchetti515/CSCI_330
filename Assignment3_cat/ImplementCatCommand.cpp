//***************************************************************************
//
//  Implement Cat Command
//  CSCI 330 Assignment 3 
//
//  Michael Marchetti z1860574
//
//***************************************************************************
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    char buffer[512]; //512 is the number of bytes for each chunk
    int fd;

    if(argc > 1)
    {
        // files will be opened in read only mode, or created as such if they do not exist
        fd = open(argv[1], O_RDONLY | O_CREAT, 0644); 
        if(fd == -1) // error if statement if improper value is given
        {
            perror("open");
            return 2;
        } 
        cout << fd << endl;

        // loop for iterating the buffer read for large files
        for(int j=0; j<1000; ++j)
        {
        ssize_t nr; 
        nr = read(fd, buffer, 512); // defines chunk size as 512 bytes
        if(nr == -1)
        {
            perror("read");
            return 3;
        }

        // displays the number of bytes read to the terminal, and the subsequent 
        // information pulled from the file(s)
        buffer[nr] = 0;
        cout << "read " << nr << " bytes: \"";
        cout.flush();

        // size for chunks of file
        ssize_t nw;
        nw = write(1, buffer, nr);

        cout << "\"" << endl;
        }
    }
    // if statement to execute when a file(s) is not given
    int input;
    if(argc = 0)
    {
        cin >> input;
        cout << "Enter 0 to end write";

        return 0;
    }
    // else statement when an invalid input is given
    else
    {
        cerr << "You didn't tell me what to do!" << endl;
    }
    // closes the file descriptor
    close(fd);

    return 0;
}

