#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
 
#define SERV_IP "127.1.1.1"
#define SERV_PORT 12358

int atoi(char *s) {
	int res = 0, len = strlen(s);
	for(int i = 0; i < len; i ++)
		res = res*10+s[i]-'0';
	return res;
}
int SendMsg(char *msg);
void RecvMsg(char *recv);

int main(int argc, char **argv) {
	int clitfd;
	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	
	if(argc != 3) {
		printf("Input error! Usage should be: %s  xxx.xxx.xxx.xxx(ip)  1234(port)\n", argv[0]);
		return 0;
	}
	if((clitfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Creat socket failed: %s\n", strerror(errno));
		return 0;
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	puts("Try to connect...");
	
	if(connect(clitfd, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) == -1) {
		printf("Connet failed: %s\n", strerror(errno));
		return 0;
	}
	puts("Connect success!");
	
	char send_buf[1024], recv_buf[1024];
	int send_len, recv_len, i = 0;
	
	recv_len = read(clitfd, &recv_buf, sizeof(recv_buf));
	if(recv_len) {
		recv_buf[recv_len] = '\0';
		puts("(Server): ");
		printf("          %s\n", recv_buf);
	}
	
	while(1) {
		puts("(Client): ");
		printf("          ");
		i = 0;
		while((send_buf[i] = getchar()) != '\n') i ++;
		if(i == 0) continue;
		send_len = write(clitfd, send_buf, i);
		recv_len = read(clitfd, &recv_buf, sizeof(recv_buf));
		if(recv_len) {
			recv_buf[recv_len] = '\0';
			puts("(Server): ");
			printf("          %s\n", recv_buf);
		}
		else {
			puts("Server closed!");
			puts("Client will close...");
			break;
		}
	}
	
	close(clitfd);
	return 0;
}