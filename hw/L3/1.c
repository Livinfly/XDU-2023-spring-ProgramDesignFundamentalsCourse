#include <stdio.h>

int main() {
	char str[1024] = {};
	scanf("%s", str);
	int n = strlen(str);
	long long x = 0;
	for(int i = 0; i < n; i ++) {
		x = x*2 + str[i]-'0';
	}
	printf("%lld\n", x);
	return 0;
}