#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	FILE *fp1;
	
	fp1 = fopen("eng.txt", "r");
	if(fp1 == NULL) {
		puts("open test.c failed.");
		return -1;
	}
	
	char str[1024] = {}, t[1024] = {}, tt[1024] = {};
	fgets(str, 1024, fp1);
//	scanf("%s", str);
	int n = strlen(str);
	int cnt[26] = {};
	for(int i = 0; i < n; i ++) {
		if('a' <= str[i] && str[i] <= 'z') cnt[str[i]-'a'] ++;
	}
	for(int i = 0; i < 26; i ++) {
		printf("%c : %d\n", 'a'+i, cnt[i]);
	}
	
	scanf("%s %s", t, tt);
	int m = strlen(t), mm = strlen(tt), p = 0;
	for(int i = 0; i+m-1 < n; i ++) {
		int ok = 1;
		for(int j = 0; j < m; j ++) {
			if(str[i+j] != t[j]) {
				ok = 0;
				break;
			}
		}
		if(ok) {
			for(int j = p; j < i; j ++) {
				printf("%c", str[j]);
			}
			for(int j = 0; j < mm; j ++) {
				printf("%c", tt[j]);
			}
			p = i+m;
			i = i+m-1;
		}
	}
	for(int j = p; j < n; j ++) {
		printf("%c", str[j]);
	}
	fclose(fp1);
	return 0;
}
/*
aa u
*/