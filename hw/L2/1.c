#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	FILE *fp1;
	
	char str[1024] = {};
	
	fp1 = fopen("test.c", "r");
	if(fp1 == NULL) {
		puts("open test.c failed.");
		return -1;
	}
	int lineId = 0;
	int hide = 0;
	while(fgets(str, 1024, fp1) != NULL) {
		int n = strlen(str);
		int p = -1, has = 0;
		printf("%d : ", ++ lineId);
		for(int i = 1; i < n; i ++) {
			if(str[i-1] == '/' && str[i] == '/') {
				if(hide) continue;
				str[i-1] = '\0';
				break;
			}
			else if(str[i-1] == '/' && str[i] == '*') {
				if(hide) {
					has = 1;
					continue;
				}
				str[i-1] = '\0';
				p = i-1;
				hide = 1;
			}
			else if(str[i-1] == '*' && str[i] == '/') {
//				printf("%d %d", hide, p);
				if(hide) {
					if(p == -1) p = 0;
					for(int j = i+1; j < n; j ++) {
						str[p+j-i-1] = str[j];
					}
					str[p+n-1-i] = '\0';
					hide = 0, p = -1;
					i = p;
				}
				else if(p != -1) {
					for(int j = p; j <= i && i+j-p+1 < n; j ++) 
						str[j] = str[i+j-p+1];
					str[n-(i-p+1)] = '\0';
					i = p;
				}
			}
		}
		if(hide && p == -1) str[0] = '\0';
		printf("%s\n", str);
	}
	
	
	
	fclose(fp1);
	return 0;
}