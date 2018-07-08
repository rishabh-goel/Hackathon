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



//takes buff as a parameter and adds ip_addr at the end of each line
void ip_add(char buff[], char ip_add[]){
	printf("inside function 1\n");
//	char buff[10000];
	char ans[10000];
	//open the file for writing and save it in a buffer//



	//file open and saved in buffer buff//

	int i = 0;		//for keeping track of index on the buffer
	int j = 0;		//for keeping track of index on answer arr
	
	int n = strlen(buff);

	printf("inside function 2\n");

	while(buff[i] != '\0'){
		printf("inside function 3\n");
		printf("current char = %c\n", buff[i]);
	
		while(buff[i] !='\n' && buff[i] != '\0'){
			printf("current char = %c\n", buff[i]);
			ans[j] = buff[i];
			i++;
			j++;
		}
	
		ans[j] = ' ';
		j++;
		ans[j] = ' ';
		j++;
		
		int k = 0;
		
		while(ip_add[k] != '\0'){
			ans[j] = ip_add[k];
			j++;
			k++;
		}

		ans[j] = '\n';
		i++;
		j++;

	}

	ans[j] = '\0';

	//do the writing part in the file
	int fd2=creat("databese.txt",0777);
	write(fd2,ans,strlen(ans));
	printf("the string is \n%s", ans);
}


int main()
{
	
  	int name_bytes,tcp_sock,n;
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
  	serAdd.sin_port=htons(10667);
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
	

	char buff[10000];

	//receiving the file

	if((name_bytes=recv(new_sock, buff,sizeof(buff),0))==-1)
			{
				perror("recv:");
					exit(-1);
			}
			

	int size_sock = sizeof(src_addr);
	

	char ip_addr[size_sock];
	int nt=printf("%s\n",inet_ntoa(src_addr.sin_addr));
	
	strcpy(ip_addr, inet_ntoa(src_addr.sin_addr));

	//memcpy(ip_addr,&(src_addr.sin_addr
	printf("%d\n",nt);
//	ip_add=(char)src_addr.sin_addr.s_addr;

	printf("%s", ip_addr);

	ip_add(buff, ip_addr);

	
	



	
	return 0;
}
    		
