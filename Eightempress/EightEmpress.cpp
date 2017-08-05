#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	int space[8][8] = {0};
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			cout << " " << space[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}

