#include <iostream>
#include <cmath>

using namespace std;

void comb(int , int , int , int);

int main() {

comb(0, 3, 9, 0);

	return 0;
}

void comb(int prev, int n, int max, int p){
	if (n == 0)
		cout << prev << endl;
	else {
		for (int ii = 1; ii <= max; ii++) {
			comb(prev + ii * (int) pow(10, p), n-1, ii, p+1);
		}
	}
}
