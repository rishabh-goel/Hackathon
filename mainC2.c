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
	
	int tcp_sock,n,accepted_sock;
  	//int b;
	long nbytes=1;
	
  	struct sockaddr_in serAdd,clientAddr,ip_check, src_addr;
  	socklen_t asize,addrlen;
//	struct sockaddr src_addr;
 	
	if((tcp_sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket:");
		exit(-1);
	}
  	
	serAdd.sin_family=AF_INET;
  	serAdd.sin_port=htons(10788);
  	serAdd.sin_addr.s_addr=(INADDR_ANY);
        

	if((bind(tcp_sock,(struct sockaddr *)&serAdd,sizeof(serAdd)))==-1)
	{
		perror("bind:");
		exit(-1);
	}
		  	
	asize=sizeof(src_addr);
	
	if((listen(tcp_sock,10))==-1)
	{
		perror("listen:");
		exit(-1);
	}
	
	printf("before \n");
	int new_sock;

	if((new_sock=accept(tcp_sock,(struct sockaddr *)&src_addr,&asize))==-1)
	{
		perror("accept:");
		exit(-1);
	}

	
	printf("after...\n");

	int fp1 = open("SleepAway.mp3", 0);
	
	while(nbytes > 0)
	{
		char buffer[20000];
		nbytes = read(fp1, buffer, 10000);
	
		printf("no of bytes read = %ld\n", nbytes);
		printf("%s\n", buffer);
		//nbytes = strlen(buff) + 1;
		//printf("value of nbytes = %d\n", nbytes);

		long chk = send(new_sock, buffer, nbytes, 0);
		printf("no of bytes sent = %ld ", chk);

	}
	

	return 0;
}
