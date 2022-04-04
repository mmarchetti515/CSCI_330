//***************************************************************
//
//  tcp-z1860574.cc
//  CSCI 330 Assignment 10
//
//  Michael Marchetti z1860574
//
//***************************************************************

#include <cstring>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/stat.h>
#include <string>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

/**
 * @brief remove trailing \r and \n 
 * 
 * @param s string s 
 */
void chomp(char *s)
{
    for(char *p = s + strlen(s) - 1; // start at the end of string
        *p == '\r' || *p == '\n';  // while there is a trailing /r or /n
        p--)  // check next character from back
        *p = '\0';  // change \r or \n to \0
}

int main(int argc, char *argv[])
{
    
    // declare needed variables
	struct sockaddr_in echoserver;
	struct sockaddr_in echoclient;
	struct stat s;
    char buffer[257]; // allow one more spot for nullptr
    char path[256];
	int sock, newSock;
    socklen_t serverlen, clientlen;
	ssize_t received;
    clientlen = sizeof(echoclient);
	newSock = accept(sock, (struct sockaddr *)&echoclient, &clientlen);
	struct stat path_s;
    string st(path);
        char *pathname = strcat(argv[2], st.substr(st.find("/")).c_str());

    
    // Create the TCP socket 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Construct the server sockaddr_in structure
    memset(&echoserver, 0, sizeof(echoserver));      /* Clear struct */
    echoserver.sin_family = AF_INET;                 /* Internet/IP */
    echoserver.sin_addr.s_addr = inet_addr(argv[1]); /* IP address */
    echoserver.sin_port = htons(atoi(argv[2]));      /* server port */

    /**
     * @brief bind the socket 
     */
    if (bind(sock, (struct sockaddr *) &echoserver, serverlen) < 0) 
    {
        perror("Failed to bind server socket");
        exit(EXIT_FAILURE);
    }

    /**
     * @brief make socket passive, set length of queue 
     */
    if (listen(sock, 256) == -1)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

	// fork to make a child process, where it handles communication with
    // the newly-connected client
	int pid = fork();
	if (pid == 0)
	{
		cout << "Client connected: " << inet_ntoa(echoclient.sin_addr) << endl;
		char path[256];
		if ((received = read(newSock, path, sizeof(path))) < 0)
		{
			perror("Failed to reveive message");
			exit(EXIT_FAILURE);
		}

		// check if the path is valid
		if (stat(pathname, &path_s) != -1)
		{
			// check if the path leads to a directory
			if (S_ISDIR(path_s.st_mode))
			{
				// check if index.html is contained in the directory
				struct stat indexcheck;
				char buf[256];
				strcpy(buf, pathname);
				strcat(buf, "/index.html");
				if (stat(buf, &indexcheck) != -1)
				{
					// Print index.html byte for byte
					int fd;
					if ((fd = open(buf, O_RDONLY, 0644)) == -1)
					{
						perror("open");
						exit(EXIT_FAILURE);
					}
					close(fd);
				}

                // if index.html is not contained
				else
				{
					// open directory
					DIR *dirp = opendir(argv[1]);
					if (dirp == 0)
					{
						perror(argv[1]);
						exit(EXIT_FAILURE);
					}

					// fetch all entries in directory
					struct dirent *dirEntry;
					while ((dirEntry = readdir(dirp)) != NULL)
					{
                        // make sure file names do not start with .
						if (dirEntry->d_name[0] != '.')
						{
							cout << dirEntry->d_name << endl;

							if (write(newSock, buffer, strlen(buffer)) < 0)
							{
								perror("error in write: ");
								exit(EXIT_FAILURE);
							}
						}
					}

					closedir(dirp);
					close(newSock);
					exit(0);
				}
			}

            /**
             * @brief if the path leads to a file 
             */
			else if (S_ISREG(path_s.st_mode))
			{
                // print the contents of the file
				int fd, read_num;
				while ((read_num = read(fd, buffer, 256)) != 0)
				{
					if (read_num == -1)
					{
						perror("read");
						exit(EXIT_FAILURE);
					}

					if (write(newSock, buffer, read_num) == -1)
					{
						perror("write");
						exit(EXIT_FAILURE);
					}
				}
				close(fd);
			}
		}

        // if the pathname is not valid
		else
		{
			perror("invalid path");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		// parent process
		close(newSock);
	}
	// release the connection
	close(sock);
}

// could not resolve this issue:
// terminate called after throwing an instance of 'std::out_of_range'
// what():  basic_string::substr: __pos (which is 18446744073709551615) > this->size() (which is 0)
// Aborted