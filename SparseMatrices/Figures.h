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
};

vector<pair<double, double>> intersect(Line l1, Line l2) {
	double den = l2.b * l1.a - l2.a * l1.b;
	if (den == 0) {
		return vector<pair<double, double>>();
	}
	else {
		double num = l2.a * l1.c - l2.c * l1.a;
		return vector<pair<double, double>>{pair<double, double>(-(l1.c * den + l1.b * num) / (l1.a * den), num / den)};
	}
}

vector<pair<double, double>> intersect(Line line, Circle circle) {
	double A = line.a * line.a + line.b * line.b;
	double B = 2 * line.b * (circle.x * line.a + line.c) - 2 * line.a * line.a * circle.y;
	double C = line.a * line.a * circle.y * circle.y - line.a * line.a * circle.r * circle.r;
	double D = B * B - 4 * A * C;
	if (D < 0) {
		return vector<pair<double, double>>();
	}
	else if (D < 10e-8) {
		double Y = -B / (2 * C);
		double X = -(line.b * Y + line.c) / line.a;
		return vector<pair<double, double>>{pair<double, double>(X, Y)};
	}
	else {
		double Y1 = (-B + sqrt(D)) / (2 * C), Y2 = (-B - sqrt(D)) / (2 * C);
		double X1 = -(line.b * Y1 + line.c) / line.a, X2 = -(line.b * Y2 + line.c) / line.a;
		return vector<pair<double, double>>{pair<double, double>(X1, Y1), pair<double, double>(X2, Y2)};
	}
}

double angle(Line l1, Line l2) {
	if (intersect(l1, l2).size() == 0) {
		return 0;
	}

	return acos((l1.a * l2.a + l1.b * l2.b) / sqrt((l1.a * l1.a + l1.b * l1.b) * (l2.a * l2.a + l2.b * l2.b)));
}

Line reflect(Line l1, Line l2) {
	vector<pair<double, double>> points = intersect(l1, l2);
	if (points.size() == 0) {
		return Line(l2.a, l2.b, 2 * l1.c - l2.c);
	}
	pair<double, double> point = points[0];

	double d = (l2.a * l1.a + l2.b * l1.b) / sqrt(l2.a * l2.a + l2.b * l2.b);
	double D = 4 * l1.a * l1.b - 4 * (l1.a * l1.a - d * d);
	double b1 = (-l1.a * l1.b + sqrt(l1.a * l1.a * l1.b * l1.b - l1.a * l1.a - d * d)) / (l1.b * l1.b - d * d);
	double b2 = (-l1.a * l1.b - sqrt(l1.a * l1.a * l1.b * l1.b - l1.a * l1.a - d * d)) / (l1.b * l1.b - d * d);
	double c1 = -point.first - b1 * point.second, c2 = -point.first - b2 * point.second;
	if (abs(l2.b / l1.a - b1) < 10e-8 && abs(l2.c / l1.a - c1) < 10e-8) {
		return Line(1, b1, c1);
	}
	else {
		return Line(1, b2, c2);
	}
}

Circle reflect(Line line, Circle circle) {
	double d = line.a * line.a + line.b * line.b;
	double x = (circle.x * line.b * line.b - circle.x * line.a * line.a - 2 * circle.y * line.a * line.b - 2 * line.a * line.c) / d;
	double y = (circle.y * line.a * line.a - circle.y * line.b * line.b - 2 * circle.x * line.a * line.b - 2 * line.b * line.c) / d;
	return Circle(x, y, circle.r);
}

vector<pair<double, double>> intersect(Circle circle, Line line) {
	return intersect(line, circle);
}

vector<pair<double, double>> intersect(Circle c1, Circle c2) {
	double d = sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
	if (d > c1.r + c2.r || d == 0) {
		return vector<pair<double, double>>();
	}

	double ux = (c1.x - c2.x) / d, uy = (c1.y - c2.y) / d;
	if (d == c1.r + c2.r) {
		return vector<pair<double, double>>{pair<double, double>(ux, uy)};
	}

	double vx = c1.x + (d * d - c2.r * c2.r + c1.r * c1.r) / (2 * d) * ux;
	double vy = c1.y + (d * d - c2.r * c2.r + c1.r * c1.r) / (2 * d) * uy;
	double uPerpx = uy, uPerpy = -ux;
	double a = sqrt((-d + c2.r - c1.r) * (-d - c2.r + c1.r) * (-d + c2.r + c1.r) * (d + c2.r + c1.r)) / d;
	double x1 = ux + a / 2 * uPerpx, y1 = uy + a / 2 * uPerpy, x2 = ux - a / 2 * uPerpx, y2 = uy - a / 2 * uPerpy;
	return vector<pair<double, double>>{pair<double, double>(x1, y1), pair<double, double>(x2, y2)};
}