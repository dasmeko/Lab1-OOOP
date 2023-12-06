#pragma once

#include <vector>
#include <cmath>

using namespace std;

struct Line {
	double a;
	double b;
	double c;

	Line(double _a, double _b, double _c) {
		a = _a;
		b = _b;
		c = _c;
	}

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

	vector<pair<double, double>> intersect(Circle circle) {
		double A = a * a + b * b;
		double B = 2 * b * (circle.x * a + c) - 2 * a * a * circle.y;
		double C = a * a * circle.y * circle.y - a * a * circle.r * circle.r;
		double D = B * B - 4 * A * C;
		if (D < 0) {
			return vector<pair<double, double>>();
		} else if (D < 10e-8) {
			double Y = -B / (2 * C);
			double X = -(b * Y + c) / a;
			return vector<pair<double, double>>{pair<double, double>(X, Y)};
		} else {
			double Y1 = (-B + sqrt(D)) / (2 * C), Y2 = (-B - sqrt(D)) / (2 * C);
			double X1 = -(b * Y1 + c) / a, X2 = -(b * 2 + c) / a;
			return vector<pair<double, double>>{pair<double, double>(X1, Y1), pair<double, double>(X2, Y2)};
		}
	}

	double angle(Line other) {
		if (intersect(other).size() == 0) {
			return 0;
		}

		return acos((a * other.a + b * other.b) / sqrt((a * a + b * b) * (other.a * other.a + other.b * other.b)));
	}

	Line reflect(Line other) {
		vector<pair<double, double>> points = intersect(other);
		if (points.size() == 0) {
			return Line(other.a, other.b, 2 * c - other.c);
		}
		pair<double, double> point = points[0];

		double d = (other.a * a + other.b * b) / sqrt(other.a * other.a + other.b * other.b);
		double D = 4 * a * b - 4 * (a * a - d * d);
		double b1 = (-a * b + sqrt(a * a * b * b - a * a - d * d)) / (b * b - d * d);
		double b2 = (-a * b - sqrt(a * a * b * b - a * a - d * d)) / (b * b - d * d);
		double c1 = -point.first - b1 * point.second, c2 = -point.first - b2 * point.second;
		if (abs(other.b / a - b1) < 10e-8 && abs(other.c / a - c1) < 10e-8) {
			return Line(1, b1, c1);
		} else {
			return Line(1, b2, c2);
		}
	}

	Circle reflect(Circle circle) {
		double d = a * a + b * b;
		double x = (circle.x * b * b - circle.x * a * a - 2 * circle.y * a * b - 2 * a * c) / d;
		double y = (circle.y * a * a - circle.y * b * b - 2 * circle.x * a * b - 2 * b * c) / d;
		return Circle(x, y, circle.r);
	}
};

struct Circle {
	double x;
	double y;
	double r;

	Circle(double _x, double _y, double _r) {
		x = _x;
		y = _y;
		r = _r;
	}

	vector<pair<double, double>> intersect(Line line) {
		return line.intersect(Circle(x, y, r));
	}

	vector<pair<double, double>> intersect(Circle other) {
		double d = sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
		if (d > r + other.r || d == 0) {
			return vector<pair<double, double>>();
		}

		double ux = (x - other.x) / d, uy = (y - other.y) / d;
		if (d == r + other.r) {
			return vector<pair<double, double>>{pair<double, double>(ux, uy)};
		}

		double vx = x + (d * d - other.r * other.r + r * r) / (2 * d) * ux;
		double vy = y + (d * d - other.r * other.r + r * r) / (2 * d) * uy;
		double uPerpx = uy, uPerpy = -ux;
		double a = sqrt((-d + other.r - r) * (-d - other.r + r) * (-d + other.r + r) * (d + other.r + r)) / d;
		double x1 = ux + a / 2 * uPerpx, y1 = uy + a / 2 * uPerpy, x2 = ux - a / 2 * uPerpx, y2 = uy - a / 2 * uPerpy;
		return vector<pair<double, double>>{pair<double, double>(x1, y1), pair<double, double>(x2, y2)};
	}
};