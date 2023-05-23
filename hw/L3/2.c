#include <stdio.h>

struct Complex{
    double x, y;
};
struct Complex add (struct Complex a, struct Complex b) {
	struct Complex t;
	t.x = a.x+b.x, t.y = a.y+b.y;
    return t;
}
struct Complex sub (struct Complex a, struct Complex b) {
	struct Complex t;
	t.x = a.x-b.x, t.y = a.y-b.y;
    return t;
}
struct Complex mul (struct Complex a, struct Complex b) {
	struct Complex t;
	t.x = a.x*b.x-a.y*b.y, t.y = a.x*b.y+a.y*b.x;
    return t;
}

int main() {
	double a, b;
	scanf("%lf %lf", &a, &b);
	struct Complex c;
	c.x = a, c.y = b;
	
	scanf("%lf %lf", &a, &b);
	struct Complex d;
	d.x = a, d.y = b;
	
	struct Complex t;
	t = add(c, d);
	printf("%lf %lf\n", t.x, t.y);
	t = sub(c, d);
	printf("%lf %lf\n", t.x, t.y);
	t = mul(c, d);
	printf("%lf %lf\n", t.x, t.y);
	return 0;
}