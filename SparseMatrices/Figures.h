#pragma once

#include <vector>

using namespace std;

class Line {
	double a;
	double b;
	double c;

public:
	vector<pair<double, double>> intersect(Line other) {
		double den = other.b * a - other.a * b;
		if (den == 0) {
			return vector<pair<double, double>>();
		}
		else {
			double num = other.a * c - other.c * a;
			return vector<pair<double, double>>{pair<double, double>(-(c * den + b * num) / (a * den), num / den)};
		}
	}
};

class Circle {
	double x;
	double y;
	double r;
};