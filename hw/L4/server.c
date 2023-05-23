#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
 
#define SERV_IP "127.1.1.1"
#define SERV_PORT 12358

char *admin = "ljljhjlc";
int is_admin = 0;

struct sockaddr_in serv_addr, clit_addr;
socklen_t clit_size;
int servfd, clitfd;
int recv_len;

int Init();
int atoi(char *s);
void SendMsg(char *msg);
int GetStr(char *s, int type, char *song, char *singer);
int QuerySong(char *send_buf, int type, char *s);
void AdminLogin(char *pwd);
int AddSong(char *song, char *singer);
int DelSong(char *song, char *singer);

int main(int argc, char **argv) {
	if(Init() == 0) {
		return 0;
	}
	char recv_buf[1024];
	while(1) {
		recv_len = read(clitfd, recv_buf, sizeof(recv_buf));
		recv_buf[recv_len] = '\0';
		if(recv_len == 0) {
			puts("Client exit!");
			break;
		}
		
		puts("(Client):");
		printf("          %s\n", recv_buf);
		if(recv_buf[0] == '0' && recv_buf[1] == ' ') {
			AdminLogin(recv_buf+2);
		}
		else if(recv_buf[0] == 'A' && recv_buf[1] == ' ') {
			if(!is_admin) {
				SendMsg("You are not the Admin!");
				continue;
			}
			char song[1024], singer[1024];
			if(GetStr(recv_buf+2, 0, song, singer) == -1) {
				SendMsg("Wrong Command!");
				continue;
			}
			if(AddSong(song, singer) == 1) {
				SendMsg("OK");
			}
			else {
				SendMsg("Failed to work!");
			}
		}
		else if(recv_buf[0] == 'D' && recv_buf[1] == ' ') {
			if(!is_admin) {
				SendMsg("You are not the Admin!");
				continue;
			}
			char song[1024], singer[1024];
			if(GetStr(recv_buf+2, 0, song, singer) == -1) {
				SendMsg("Wrong Command!");
				continue;
			}
			if(DelSong(song, singer) == 1) {
				SendMsg("OK");
			}
			else {
				SendMsg("Failed to work!");
			}
		}
		else if(recv_buf[0] == '1' && recv_buf[1] == ' ') {
			char song[1024], singer[1024], send_buf[1024] = {};
			if(GetStr(recv_buf+2, 1, song, singer) == -1) {
				SendMsg("Wrong Command!");
				continue;
			}
			if(QuerySong(send_buf, 1, song) == 1) {
				SendMsg(strcat(send_buf, "Finished!"));
			}
			else {
				SendMsg("Failed to work!");
			}
		}
		else if(recv_buf[0] == '2' && recv_buf[1] == ' ') {
			char song[1024], singer[1024], send_buf[1024] = {};
			if(GetStr(recv_buf+2, 2, song, singer) == -1) {
				SendMsg("Wrong Command!");
				continue;
			}
			if(QuerySong(send_buf, 2, singer) == 1) {
				SendMsg(strcat(send_buf, "Finished!"));
			}
			else {
				SendMsg("Failed to work!");
			}
		}
		else {
			SendMsg("Wrong command!");
		}
//		write(clitfd, recv_buf, recv_len);
	}
	
	close(servfd);
	close(clitfd);
	return 0;
}

int Init() {
	memset(&serv_addr, 0, sizeof(serv_addr));
	memset(&clit_addr, 0, sizeof(clit_addr));
	
	if((servfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("Creat socket failed : %s\n", strerror(errno));
		return 0;
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
	
	if(bind(servfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
		printf("Bind failed: %s\n", strerror(errno));
		return 0;
	}
	
	if(listen(servfd, 1024) == -1) {
		printf("Listen failed: %s\n", strerror(errno));
		return 0;
	}
	
	puts("Init success!");
	printf("IP: %s  Port: %d\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
	puts("Waiting for connect...");
	
	socklen_t clit_size = 0;
	
	if((clitfd = accept(servfd, (struct sockaddr *)&clit_addr, &clit_size)) == -1) {
		printf("Accept failed: %s\n", strerror(errno));
		return 0;
	}
	
	printf("Client access:\n          IP: %s  Port: %d\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));
	
	SendMsg("Send '0' 'password' to login admin\n\
          Send '1' 'song name' to query songs by its name\n\
          Send '2' 'singer name' to query songs by singer's name\n\
          (in the admin mode)\n\
          Send 'A' 'song name' 'singer name' to add a song\n\
          Send 'D' 'song name' 'singer name' to del a song");
    return 1;
}
int atoi(char *s) {
	int res = 0, len = strlen(s);
	for(int i = 0; i < len; i ++)
		res = res*10+s[i]-'0';
	return res;
}
void SendMsg(char *send_buf) {
	int send_len = strlen(send_buf);
	write(clitfd, send_buf, send_len);
}
int GetStr(char *s, int type, char *song, char *singer) {
	int len = strlen(s), cnt = 0, tlen = 0;
	char tmp[1024] = {};
	if(type == 0) {
		int i;
		for(i = 0; i < len; i ++) {
			if(s[i] == ' ') break;
			tmp[tlen ++] = s[i];
		}
		if(tlen == 0) return -1;
		tmp[tlen] = '\0';
		memcpy(song, tmp, sizeof tmp);
		
		tlen = 0;
		for(i = i+1; i < len; i ++) {
			if(s[i] == ' ') break;
			tmp[tlen ++] = s[i];
		}
		if(tlen == 0) return -1;
		tmp[tlen] = '\0';
		memcpy(singer, tmp, sizeof tmp);
	}
	else {
		int i;
		for(i = 0; i < len; i ++) {
			if(s[i] == ' ') break;
			tmp[tlen ++] = s[i];
		}
		if(tlen == 0) return -1;
		tmp[tlen] = '\0';
		if(type == 1) 
			memcpy(song, tmp, sizeof tmp);
		else 
			memcpy(singer, tmp, sizeof tmp);
	}
	return 1;
}
int QuerySong(char *send_buf, int type, char *s) {
	FILE *db;
	db = fopen("db.txt", "r");
	if(db == NULL) return 0;
	char s1[1024], s2[1024];
	while(fscanf(db, "%s : %s", s1, s2) == 2) {
		if(type == 1 && strcmp(s, s1) == 0 || type == 2 && strcmp(s, s2) == 0) {
			strcat(send_buf, strcat(strcat(s1, " : "), s2));
			strcat(send_buf, "\n          ");
		}
	}
	fclose(db);
	return 1;
}
void AdminLogin(char *pwd) {
	if(is_admin) {
		SendMsg("Admin, you have logged in.");
		return;
	}
	if(strcmp(pwd, admin) == 0) {
		is_admin = 1;
		SendMsg("Admin, Welcome!");
	}
	else {
		SendMsg("Wrong password.");
	}
}
int AddSong(char *song, char *singer) {
	FILE *db;
	db = fopen("db.txt", "a+");
	if(db == NULL) return 0;
	fprintf(db, "%s : %s\n", song, singer);
	fclose(db);
	return 1;
}
int DelSong(char *song, char *singer) {
	FILE *db, *tmp;
	db = fopen("db.txt", "a+");
	if(db == NULL) return 0;
	tmp = fopen("tmp.txt", "w");
	if(tmp == NULL) return 0;
	char s1[1024], s2[1024];
	while(fscanf(db, "%s : %s", s1, s2) == 2) {
		if(strcmp(song, s1) == 0 && strcmp(singer, s2) == 0) {
			continue;
		}
		else {
			fprintf(tmp, "%s : %s\n", s1, s2);
		}
	}
	fclose(db);
	remove("./db.txt");
	rename("./tmp.txt", "db.txt");
	fclose(tmp);
	return 1;
}
