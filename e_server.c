#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
  
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024   
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	char message[BUF_SIZE];
	int str_len, i;
	
	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	socklen_t clnt_adr_sz;
	
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);   
	if(serv_sock==-1)
		error_handling("socket() error");
	
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	
	if(listen(serv_sock, 5)==-1)
        //연결요청 대기 큐: 큐의 크기가 5size다.
		error_handling("listen() error");
	
	clnt_adr_sz=sizeof(clnt_adr);

	for(i=0; i<5; i++) //client가 5개 일 경우.
	{
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		if(clnt_sock==-1)
			error_handling("accept() error");
		else
			printf("Connected client %d \n", i+1);
	
		while((str_len=read(clnt_sock, message, BUF_SIZE))!=0)
            //한번만 read해서는 다 안읽힐 수도 있다. TCP는 임의적
            //으로 묶기 때문에. 
			write(clnt_sock, message, str_len);

		close(clnt_sock); //일 해결할때 마다 client는 보낸다.
	}

	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
