#include <stdio.h>

int cmp(const int *a, const int *b) {
   return *a - *b;
}

int main() {
	FILE *fp1, *fp2, *fp3;
	
	fp1 = fopen("num1.txt", "r");
	if(fp1 == NULL) {
		puts("open num1.txt failed.");
		return -1;
	}
	fp2 = fopen("num2.txt", "r");
	if(fp2 == NULL) {
		puts("open num2.txt failed.");
		return -1;
	}
	fp3 = fopen("num3.txt", "w");
	if(fp3 == NULL) {
		puts("open num3.txt failed.");
		return -1;
	}
	
	int n = 0;
	int num[1010] = {};
	
	int x;
	while(fscanf(fp1, "%d", &x) == 1) {
		num[n ++] = x;
	}
	while(fscanf(fp2, "%d", &x) == 1) {
		num[n ++] = x;
	}
	
	qsort(num, n, sizeof(int), cmp);
	for(int i = 0; i < n; i ++)
		fprintf(fp3, "%d ", num[i]);
	puts("");
	
	fclose(fp1), fclose(fp2), fclose(fp3);
	
	return 0;
}