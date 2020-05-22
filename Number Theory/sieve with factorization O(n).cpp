#include <iostream>
using namespace std;

const int MAXN = 1e5 + 5;
int lp[MAXN + 1];
int pr[MAXN + 1];
int sz = 0;

void sieve() {
	for (int i = 2; i <= MAXN; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr[sz++] = i;
		}
		for (int j = 0; j < sz and pr[j] <= lp[i] and i * pr[j] <= MAXN; j++) {
			lp[i * pr[j]] = pr[j];
		}
	}
}	

int main() {
	sieve();
	for (int i = 0; i < sz; i++) {
		cout << pr[i] << " ";
	}
	cout << endl;
}	