#include <stdio.h>
#include "calculator.h"

int main() {
	double x = 20, y = 5;
	printf("%f + %f = %f\n", x, y, add(x, y));
	printf("%f - %f = %f\n", x, y, sub(x, y));
	printf("%f * %f = %f\n", x, y, multiply(x, y));
	printf("%f / %f = %f\n", x, y, divide(x, y));
	return 0;
}

