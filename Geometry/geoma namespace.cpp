#include <bits/stdc++.h>
#define pt Geoma::Point
#define li Geoma::Line
#define pb push_back
using namespace std;

namespace Geoma {

	const double EPS = 1e-9;

	struct Point {
		double x, y;
		Point(double a, double b) {x = a; y = b;}
	};

	struct Line {
		double A, B, C;
		Line(double a, double b, double c) {A = a; B = b; C = c; normalize();}
		void normalize() {
			double Z = sqrt(A * A + B * B);
			A /= Z; B /= Z; C /= Z;
			if (A < -EPS or (fabs(A) < EPS and B < -EPS)) {A *= -1; B *= -1; C *= -1;}
		}
	};

	double det(double a, double b, double c, double d) {return a * d - b * c;}

	Line get_line(Point a, Point b) {
		double A = a.y - b.y;
		double B = b.x - a.x;
		double C = -A * a.x - B * a.y;
		return Line(A, B, C);
	}

	bool intersect(Line l1, Line l2) {
		if (fabs(det(l1.A, l1.B, l2.A, l2.B)) < EPS) return false;
		else return true;
	}

	bool equivalent(Line l1, Line l2) {
		return fabs(det(l1.A, l1.B, l2.A, l2.B)) < EPS 
		and fabs(det(l1.A, l1.C, l2.A, l2.C)) < EPS 
		and fabs(det(l1.B, l1.C, l2.B, l2.C)) < EPS;
	}

	Point intersection(Line l1, Line l2) {
		double denom = det(l1.A, l1.B, l2.A, l2.B);
		double x = -det(l1.C, l1.B, l2.C, l2.B) / denom;
		double y = -det(l1.A, l1.C, l2.A, l2.C) / denom;
		return Point(x, y);
	}

	double signed_triangle_area(Point a, Point b, Point c) {return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y) / 2.0;}

	double triangle_area(Point a, Point b, Point c) {return fabs(signed_triangle_area(a, b, c));}

	bool clockwise(Point a, Point b, Point c) {return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y) < -EPS;}

	bool counter_clockwise(Point a, Point b, Point c) {return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y) > EPS;}

	double polygon_area(vector<Point> points) {
		double area = 0.0;
		int sz = int(points.size());
		for (int i = 0; i < sz; i++) {
			int j = (i + 1) % sz;
			area += signed_triangle_area(points[0], points[i], points[j]);
		}
		return area;
	}
}

void solve() {
	double x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	double x3, y3; cin >> x3 >> y3;
	pt p = pt(x1, y1);
	pt q = pt(x2, y2);
	pt r = pt(x3, y3);
	li l1 = Geoma::get_line(p, q);
	li l2 = Geoma::get_line(p, r);
	Geoma::Point isect = Geoma::intersection(l1, l2);
	cout << isect.x << " " << isect.y << endl;
	cout << Geoma::counter_clockwise(p, q, r) << endl;
	vector<pt> v;
	v.push_back(pt(0, 0));
	v.push_back(pt(1, 0));
	v.push_back(pt(1, 1));
	v.push_back(pt(0, 1));
	cout << Geoma::polygon_area(v) << endl;
}

int main() {
	solve();
	return 0;
}