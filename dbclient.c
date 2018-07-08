#define _XOPEN_SOURCE 500
#include <ftw.h>
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>

int fd;
char ip_addr[50];	
static int display_info(const char *fpath, const struct stat *sb,int tflag, struct FTW *ftwbuf)
{	
	
	char buffer[10000];
	
	printf("the file descriptor is = %d\n", fd);
	
	if(tflag == FTW_F)
	{
		
	    printf("%s\n",fpath);
	  
	    strcpy(buffer,fpath);
	    int n = strlen(buffer);
	    buffer[n] = '\n';
	    printf("%s and size of buffer is = %d",buffer, n+1);
	    printf("%ld\n",write(fd,buffer,n+1));
	    write(fd,ip_addr,strlen(ip_addr));
	}
	
	

    return 0;         
}

int main(int argc, char *argv[])
{

		
	
	fd=creat("files.txt",0777);
	printf("create fd %d\n", fd);
	if(fd > 0)
	{
		perror("create : ");
	}
	
    	int flags = 0;
 	if(argc > 2 && strchr(argv[2], 'd') != NULL)
       		 flags |= FTW_DEPTH;
   	 if (argc > 2 && strchr(argv[2], 'p') != NULL)
        	flags |= FTW_PHYS;

   	if (nftw((argc < 2) ? "." : argv[1], display_info, 20, flags) == -1)
	{
       		 perror("nftw");
       		exit(EXIT_FAILURE);
   	 }
		
	/*this program is for the transfer of database */
	int tcp_sock;
	struct sockaddr_in serAdd;
	socklen_t addrlen;
	//char a[100],port[20],ip_addr[100];
	//int name_bytes,ip_bytes,port_bytes;
	long int nbytes;
	char buffer[1000000];

	if((tcp_sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("socket:");
		exit(-1);
	}

	serAdd.sin_family=AF_INET;
  	serAdd.sin_port=htons(10667);
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

	int fp = open("files.txt", 0);
	
	//while(nbytes > 0)
	//{
	
		nbytes = read(fp, buffer, 10000);
	
		printf("no of bytes read = %ld\n", nbytes);

		nbytes = strlen(buffer) + 1;
		//printf("value of nbytes = %d\n", nbytes);

		long chk = send(tcp_sock, buffer, nbytes, 0);
		printf("no of bytes sent = %ld ", chk);

	//}
	

	return 0;
}
