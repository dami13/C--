/*
Listen.cpp v0.1 
Server(obsługujący połączenia)
Damian Pasek
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MYPORT 3490
#define BACKLOG 10

using namespace std;

int main(int argc, char* argv[])
{
	string msg = "Hello";
	int my_socket, new_socket, wys = 0;
	socklen_t sin_size;
	struct sockaddr_in my_addr, their_addr;

	if((my_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
        perror( "socket" );
        exit( 1 );
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(MYPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero), '\0', 8);
	
	if(bind(my_socket, ( struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) 
	{
        perror( "bind" );
        exit( 1 );
	}
	
	if(listen(my_socket, BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}

	while(1)
	{
		sin_size = sizeof(struct sockaddr_in);
		if((new_socket = accept(my_socket, (struct sockaddr *) &their_addr, &sin_size)) == -1)
		{
			perror("accept");
			continue;
		}
		
		cout << "server: Połączenie z: " << inet_ntoa(their_addr.sin_addr) << endl;

		if(wys = send(new_socket, msg.c_str(), msg.length(), 0) == -1)
		{
			perror("send");
			exit(0);
		}
		cout << "Wysłano: " << wys << endl;
		close(new_socket);
		close(my_socket);
	}
	return 0;
}




















































