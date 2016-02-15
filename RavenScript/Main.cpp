#include <iostream>
#include "TestTiger\TestTiger.h"
using namespace std;

int main() {
	cout << "Raven Script" << endl;
	raven::TestTiger::RunAndDisposeTests();
	system("pause");
	return 0;
}