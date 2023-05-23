#include <stdio.h>

struct Student {
	char name[210];
	int eng;
	int math;
	float mean;
};

int main() {
	FILE *fp1, *fp2, *fp3;
	
	fp1 = fopen("db1.txt", "r");
	if(fp1 == NULL) {
		puts("open db1.txt failed.");
		return -1;
	}
	fp2 = fopen("db2.txt", "r");
	if(fp2 == NULL) {
		puts("open db2.txt failed.");
		return -1;
	}
	fp3 = fopen("db3.txt", "w");
	if(fp3 == NULL) {
		puts("open db3.txt failed.");
		return -1;
	}
	
	struct Student stu1[55] = {}, stu2[55] = {}, stu3[55] = {};
	int n1, n2, n3;
	n1 = n2 = n3 = 0;
	
	char str[210];
	int score;
	while(fscanf(fp1, "%s%d", str, &score) == 2) {
		memcpy(stu1[n1].name, str, sizeof str);
		stu1[n1 ++].eng = score;
	}
	while(fscanf(fp2, "%s%d", str, &score) == 2) {
		memcpy(stu2[n2].name, str, sizeof str);
		stu2[n2 ++].math = score;
	}
	for(int i = 0; i < n1; i ++)
		for(int j = 0; j < n2; j ++) {
			if(strcmp(stu1[i].name, stu2[j].name) == 0) {
				int eng = stu1[i].eng, math = stu2[j].math;
				memcpy(stu3[n3].name, stu1[i].name, sizeof stu1[i].name);
				stu3[n3].eng = eng, stu3[n3].math = math;
				stu3[n3 ++].mean = (eng+math)/2.0;
			}
		}
	
	for(int i = 0; i < n3; i ++) {
		fprintf(fp3, "%s %d %d %.1f\n", stu3[i].name, stu3[i].eng, stu3[i].math, stu3[i].mean);
	}
	
	fclose(fp1), fclose(fp2), fclose(fp3);
	
	return 0;
}