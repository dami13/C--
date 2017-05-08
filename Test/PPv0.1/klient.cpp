/*
Klient.cpp v0.1 
Klient(Nawiązywanie połączenia)
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

using namespace std;

int main(int argc, char* argv[])
{
	char msg[40];
	int len;
	int my_socket, new_socket;
	socklen_t sin_size;
	struct sockaddr_in my_addr, their_addr;

	if((my_socket = socket(AF_INET, SOCK_STREAM, 0)) == - 1) 
	{
        perror("socket");
        exit(1);
	}

	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(0);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_addr.sin_zero), '\0', 8);
	
	if(bind(my_socket, (struct sockaddr *) &my_addr, sizeof(struct sockaddr)) == -1) 
	{
        perror("bind");
        exit(1);
	}

	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(3490);
	their_addr.sin_addr.s_addr = inet_addr("192.168.1.16");
	memset(&(my_addr.sin_zero), '\0', 8);
	
	if(connect(my_socket, (struct sockaddr *) &their_addr, sizeof(struct sockaddr)) != -1)
	{
		cout << "Nawiązano połączenie z: " << inet_ntoa(their_addr.sin_addr) << ":" << 				their_addr.sin_port << endl;
	}
	else
	{
		perror("connect");
		exit(1);
	}
	
	cout << (recv(my_socket, msg, len, 0)) << endl;
	
	printf("%s\n", msg);
	
	return 0;
}




















































