#include <stdio.h>

int main() {
	FILE *fp1;
	
	fp1 = fopen("test.c", "r");
	if(fp1 == NULL) {
		puts("open test.c failed.");
		return -1;
	}
	
	int top = 0;
	char stk[1010] = {};
	int ok = 1;
	
	char ch;
	while((ch = fgetc(fp1)) != EOF) {
//		printf("%c", ch);
		if(ch == '(' || ch == '{') stk[++ top] = ch;
		else if(ch == ')') {
			if(!top || stk[top --] != '(' ) {
				ok = 0;	
			}
		}
		else if(ch == '}') {
			if(!top || stk[top --] != '{' ) {
				ok = 0;
			}
		}
		
		if(!ok) break;
	}
	if(top) 
		ok = 0;
	
	puts(ok == 1 ? "match!" : "fail!");
	
	fclose(fp1);
	
	return 0;
}