#include <fstream>
#include <iostream>
using namespace std;

void read_crs_file() {
	string buffer;
	fstream filestr;
	filestr.open("car-s-91.crs");
	if (filestr.is_open()) {
		cout << "SUCCESS" << endl;
		while (getline(filestr, buffer)) {
			cout << buffer << endl;
		}
		filestr.close();
	} else {
		cerr << "ERROR" << endl;
	}
}
