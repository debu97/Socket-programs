#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>  // Library for close() 

#define BUFFERSIZE 1024
#define PORT 5000

int main()
{
	int req_sock, conn_sock, bytes_recv, bytes_sent, bind_status;
	struct sockaddr_in s_server, s_client;
	int s_len = sizeof(s_server);
	char send_buf[BUFFERSIZE], recv_buf[BUFFERSIZE];

	// Creating a socket which requests
	req_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(req_sock<0)
	{
		printf("Socket creation failed\n");
		return 1;
	}
	else
	{
		printf("Request socket creation successful with descriptor %d \n", req_sock);
	}

	// Bind the socket
	s_server.sin_family = AF_INET;
	s_server.sin_port = htons(PORT);
	s_server.sin_addr.s_addr = htonl(INADDR_ANY);

	bind_status = bind(req_sock, (struct sockaddr*)&s_server, sizeof(s_server));
	if(bind_status < 0)
	{
		printf("Socket Binding failed.\n");
		return 1;
	}
	else
	{
		printf("Socket Binding successful\n");
	}

	// Enable request socket to accept connection requests
	listen(req_sock, 5);// enable to listen can handle 5 req at same time

    
	// Enable Requesting socket to accept connections
	printf("Waiting for connection Requests\n");
	conn_sock = accept(req_sock, (struct sockaddr*)&s_client, &s_len);
	if(conn_sock == -1)
	{
		printf("Connection Request Rejected\n");
		close(req_sock);
		return 1;
	}
	else
	{
		printf("Connection request accepted with socket %d\n", conn_sock);
	}
    int count = 0;
    while(1)
    {
	bytes_recv = recv(conn_sock, recv_buf, sizeof(recv_buf), 0);
	recv_buf[bytes_recv] = '\0';
    if (bytes_recv != 0)
    {
	printf("%d Bytes Received : %s \n",bytes_recv, recv_buf);
    count++;
	//strcpy(send_buf, recv_buf);
	//bytes_sent = send(conn_sock, send_buf, strlen(send_buf), 0);
	//printf("%d bytes sent : %s\n", bytes_sent, send_buf);

    printf("%d recv() system calls \n", count);
    }
    }
	close(req_sock);
    
	close(conn_sock);
    
	return 0;	
}	
