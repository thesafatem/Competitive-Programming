#include <iostream>
using namespace std;

long long gcd(long long a, long long b, long long &x, long long &y) {
	if (a == 0) {
		x = 0;
		y = 1;
		return b;
	}
	long long x1, y1;
	long long d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

void extended_euclidean() {
	long long a, b; cin >> a >> b;
	long long x, y;
	long long g = gcd(a, b, x, y);
	cout << x * a + y * b << " " << g << endl;
}

int main() {
	extended_euclidean();
}	