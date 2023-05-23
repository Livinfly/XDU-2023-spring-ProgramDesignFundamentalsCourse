#include <stdio.h>

int main() {
	FILE *fp1, *fp2;
	char str1[1024] = {}, str2[1024] = {};
	
	fp1 = fopen("01.txt", "r");
	if(fp1 == NULL) {
		puts("open 01.txt failed.");
		return -1;
	}
	fp2 = fopen("02.txt", "r");
	if(fp2 == NULL) {
		puts("open 02.txt failed.");
		return -1;
	}
	int same = 1;
	int lineId = 1;
	while(1) {	
		char *f1 = fgets(str1, 1024, fp1);
		char *f2 = fgets(str2, 1024, fp2);
//		printf("%d %d\n", strlen(str1), strlen(str2));
		if(f1 == NULL && f2 != NULL || f1 != NULL && f2 == NULL) {
			printf("Line %d is different!\n", lineId);
			printf("File 1 : %s\nFile 2 : %s\n\n", (f1 == NULL) ? "" : str1, (f2 == NULL) ? "" : str2);
			printf("Before Line %d they're same, but then file %d has ended.\n", lineId, (f1 == NULL) ? 1 : 2);
			same = 0;
			break;
		}
		else if(f1 == NULL && f2 == NULL) break;
		
		if(strcmp(str1, str2) != 0) {
			printf("Line %d is different!\n", lineId);
			printf("File 1 : %s\n\nFile 2 : %s\n\n", str1, str2);
			same = 0;
			break;
		}
		lineId ++;
	}
	
	if(same) 
	 	puts("Two files are same!");
	
	fclose(fp1), fclose(fp2);
	
	return 0;
}