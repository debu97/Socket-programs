#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>  //Library for close

#define BUFFERSIZE 1024
#define SERVERPORT 5000
#define SERVERADDR "127.0.0.1"

int main()
{
	int sock, bytes_sent, bytes_recv, conn_status;
	struct sockaddr_in s_server;
	char send_buf[BUFFERSIZE], recv_buf[BUFFERSIZE];
    int i;
    
	// Creating Socket
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock<0)
	{
		printf("Socket creation failed. \n");
		return 1;
	}
	else
	{
		printf("Socket creation successful with descriptor %d\n", sock);
	}

	s_server.sin_family = AF_INET;
	s_server.sin_port = htons(SERVERPORT);
	inet_aton(SERVERADDR, &s_server.sin_addr);

	conn_status = connect(sock, (struct sockaddr*)&s_server, sizeof(s_server));
	if(conn_status == -1)
	{
		printf("Connection to server failed.\n");
		close(sock);
		return 1;
	}
	else
	{
		printf("Connected to Server.\n");
	}
    
	// Reading message from keyboard and send
	printf("Enter the message: \n");
	scanf("%s", send_buf);

    for (i = 0; i<10; i++)
    {
	bytes_sent = send(sock, send_buf, strlen(send_buf), 0);
	printf("%d bytes sent : %s \n", bytes_sent, send_buf);
    //sleep(1);
	

    }
	close(sock);

	return 0;
}
