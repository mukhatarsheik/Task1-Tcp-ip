#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#define SERVER_PORT 5000
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

void error_handling(const char *message) 
{
	perror(message);
	exit(1);
}

int main() 
{
	int sock;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];
	int msg_len;

	// Create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) 
		error_handling("socket() error");

	// Configure server address
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	server_addr.sin_port = htons(SERVER_PORT);

	// Connect to server
	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
	{
		close(sock);
		error_handling("connect() error");
	}

	printf("Connected to server\n");

	// Communicate with server
	 
	
		//sending message to server
		printf("Enter message from client to server: ");
		__fpurge(stdin);
		scanf("%[^\n]s",buffer);
		msg_len=write(sock,buffer,strlen(buffer));
		printf("msg length after write is %d\n",msg_len);
                if (msg_len < 0) 
		{

			close(sock);
			error_handling("write() error");
		}
                

		// reading the echo message from server
		msg_len = read(sock, buffer, BUFFER_SIZE - 1);
		printf("msg length after read is %d\n",msg_len);
		if (msg_len < 0) 
		{

			close(sock);
			error_handling("read() error");
		}
		//adding null character at the last byte of buffer
		buffer[msg_len] = '\0';

		printf("echo Message received from server: %s\n", buffer);
	
	
	close(sock);
	return 0;
}

