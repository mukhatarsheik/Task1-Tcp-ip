#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 5000

void error_handling(const char *message) 
{
	perror(message);
	exit(1);
}

int main() 
{
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	unsigned int client_addr_size;
	char buffer[1024];
	int msg_len;

	// Create server socket
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock == -1) 
		error_handling("socket() error");

	// Configure server address
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	// Bind the socket to the address
	if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr))<0) 
	{
		close(server_sock);
		error_handling("bind() error");
	}

	// Listen for incoming connections with a backlog of 5
	if (listen(server_sock, 5) < 0) 
	{
		close(server_sock);
		error_handling("listen() error");
	}

	printf("Server is running and listening on port %d...\n", SERVER_PORT);

	
	
		// Accept a client connection
		client_addr_size = sizeof(client_addr);
		client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
		if (client_sock < 0) 
		{
			close(server_sock);
			error_handling("accept() error");
		}

		printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                printf("waiting for the client to send the message\n");
		// Communicate with client
	        msg_len = read(client_sock, buffer, sizeof(buffer) - 1); 
		
			buffer[msg_len] = '\0';
			printf("Received message from client: %s\n", buffer);

			// Echo back to client
			if (write(client_sock, buffer, msg_len) == -1) 
			{
				close(client_sock);
				close(server_sock);
				error_handling("write() error");
			}
		

		if (msg_len == -1) 
		{
			close(client_sock);
			close(server_sock);
			error_handling("read() error");
		}

		// Close client socket
		close(client_sock);
	

	// Close server socket
	close(server_sock);
		printf("Client disconnected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	return 0;
}

