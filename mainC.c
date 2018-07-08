#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{

	int tcp_sock,new_sock,accept_sock;
	struct sockaddr_in serAdd,newCon;
	socklen_t addrlen,newlen;
	char a[100],port[20],ip_addr[100];
	int name_bytes,ip_bytes,port_bytes;
	long int nbytes=1;
	char buffer[1000000];

	if((tcp_sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket:");
		exit(-1);
	}

	serAdd.sin_family=AF_INET;
  	serAdd.sin_port=htons(10851);
  	serAdd.sin_addr.s_addr=inet_addr("127.0.0.1");	

	memset(serAdd.sin_zero,'\0',sizeof(serAdd.sin_zero));	

	addrlen=sizeof(serAdd);


	printf("connecting to server....\n");

	if(connect(tcp_sock,(struct sockaddr*)&serAdd,addrlen)==-1)
	{
		perror("connect:");
		exit(-1);
	}

	printf("connection established\n");

	printf("enter the movie or song you want to request for\n");
	scanf("%s",a);
	
	if((name_bytes=send(tcp_sock,a,strlen(a),0))==-1)
	{
		perror("send:");
		exit(-1);
	}

	
	if((port_bytes=recv(tcp_sock,ip_addr,sizeof(ip_addr),0))==-1)
	{
		perror("recv:");
		exit(-1);
	}
	printf("%s\n",ip_addr);
	printf("recieved the ip address and port no successfully\n");
     	close(tcp_sock);
	// we now make a new socket for this client which establishes a connection with the client that has the requested file whose ip address and port no. have been sent by the server.

	if((new_sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket:");
		exit(-1);
	}

	struct in_addr ip_ad;
	inet_aton(ip_addr, &ip_ad);
	newCon.sin_family=AF_INET;
  	newCon.sin_port=htons(10788); //atoi converts a string and returns an integer value
  	newCon.sin_addr.s_addr=ip_ad.s_addr;

	newlen=sizeof(newCon);
	
	printf("connecting to server....\n");

	if(connect(new_sock,(struct sockaddr*)&newCon,newlen)==-1)
	{
		perror("connect:");
		exit(-1);
	}

	printf("connection established\n");

	
	int fp = creat("abc.mp3",0777);

	printf("waiting for message :\n");
		
	while(nbytes > 0)
	{

		nbytes = recv(new_sock, buffer, 1000000, 0);
		
		printf("bytes received = %ld\n", nbytes);	
		

		long bytes_return = write(fp, buffer, nbytes);
		
		printf("bytes written = %ld\n", bytes_return);
	}
	


	return 0;
}



	
	

