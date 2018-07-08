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


int search(char buffer[], char pat[], int n, int m){
	printf("inside search\n");
	int index = 0;
	
	int i=0, j, k;

	while(i != n-m){
		if(buffer[i] == '\n'){
			index = i;
		}

		j = 0;

		if(buffer[i] == pat[0]){
			while(buffer[i++] == pat[j++] && j != m+1){
				printf("current character = %c\n", buffer[i-1]);
			}
		}

		if(j == m+1){
			return index;
		}
		
		i++;
	}
	
	return -1;			
}



int main()
{

	
	
	//connection
	char name[100];
	int name_bytes,tcp_sock,n,accepted_sock;
  	//int b;
	///char a[4000000];
  	struct sockaddr_in serAdd,clientAddr,ip_check, src_addr;
  	socklen_t asize,addrlen;
//	struct sockaddr src_addr;
 	
	if((tcp_sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket:");
		exit(-1);
	}
  	
	serAdd.sin_family=AF_INET;
  	serAdd.sin_port=htons(10851);
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
	
	if((name_bytes=recv(new_sock,name,sizeof(name),0))==-1)
	{
		perror("recv:");
		exit(-1);
	}
			
	printf("file request successfully recieved\n");
	
		
	

	//file search ka main program:


	int fd,i;
	char * fmt = "%[^\n]%*c";

	if((fd=open("databese.txt",0))==-1)
	{
		perror("open:");
		exit(-1);
	}
	
	
	
	char buffer[10000];
	int read_bytes;

	if((read_bytes=read(fd,buffer,10000))==-1)
	{
		perror("read:");
		exit(-1);
	}	
	
	printf("the no of bytes read from the file = %d", read_bytes);

	//printf("enter the name of the file\n");
	//scanf(fmt, name);

	printf("the file entered is %s", name);
	
	int position = search(buffer, name, read_bytes, strlen(name));
	char path[100];
	int j =0;
	if(position >=0){
		int i = position+1;
		while(buffer[i]!=' '){
			path[j] = buffer[i];
			i++;
			j++;
		}
		path[j] = '\0';

		printf("the full path name is = %s", path);
	}

	int t=position+j+3;
	char ip[20];

	int k = 0;

	for(i=t;buffer[i]!='\n'; i++){
		ip[k++] = buffer[i];	
	}	

	ip[k] = '\0';
	printf("ip address is %s", ip);		

 	if(position>=0)
  	printf("\nfile_name was found at position %d\n",position);
 	else
  	printf("\nfilenot found\n");

	int send_to_client=send(new_sock,ip,strlen(ip),0);
	
	printf("ip address sent!!");


}

