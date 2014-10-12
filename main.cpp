/**
 * Christos Gogos (2014)
 *
 *
 */
#include <fstream>
#include <iostream>
using namespace std;

void read_crs_file();

int main(int argc, char **argv) {
	int choice;
	do {
		cout << "1. Read a .crs file" << endl;
		cout << "2. Option" << endl;
		cout << "3. Option" << endl;
		cout << "4. Option" << endl;
		cout << "5. Exit" << endl;
		cout << "Choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			read_crs_file();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		default:
			cout << "Invalid choice. Try again!" << endl;
		}
	} while (choice != 5);

}


