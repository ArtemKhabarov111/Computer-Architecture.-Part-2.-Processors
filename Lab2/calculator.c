#include "calculator.h"

double add(double a, double b) {
	return a + b;
}

double sub(double a, double b) {
	return a - b;
}

double multiply(double a, double b) {
	return a * b;
}

double divide(double a, double b) {
	return b != 0 ? a / b : 0; 
}

