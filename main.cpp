/**
 * Christos Gogos (2014)
 *
 *	30/10/2014: Κώδικας για ανάγνωση δεδομένων
 *
 */

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <list>
using namespace std;

int stu_no; // αριθμός σπουδαστών
int crs_no; // αριθμός μαθημάτων
int per_no; // αριθμός περιόδων εξέτασης (δίνεται στην εκφώνηση)
int* crs_per_stu_n; // πίνακας με αριθμό μαθημάτων ανά σπουδαστή
int** crs_per_stu; // 2Δ πίνακας με τους αριθμούς των μαθημάτων ανά σπουδαστή
int* stu_per_crs_n; // πίνακας με τον αριθμό των σπουδαστών ανά μάθημα
int** stu_per_crs; // 2Δ πίνακας με τους αριθμούς των σπουδαστών ανά μάθημα
int** conflict_matrix; // 2Δ πίνακας συγκρούσεων

void print_conflict_density() {
	int c = 0;
	for (int i = 1; i < crs_no + 1; i++)
		for (int j = 1; j < crs_no + 1; j++)
			if (conflict_matrix[i][j] == 1)
				c++;
	double conflictDensity = (double) c / (crs_no * crs_no);
	cout << "Conflict density is " << conflictDensity << endl;
}

void read_problem_data(string problem) {
	string stu_fn = "";
	if (problem == "CAR91-II") {
		stu_fn = "car-s-91-II.stu";
		stu_no = 16925;
		crs_no = 682;
		per_no = 35;
	} else if (problem == "CAR91") {
		stu_fn = "car-s-91.stu";
		stu_no = 16925;
		crs_no = 682;
		per_no = 35;
	} else if (problem == "KFU93") {
		stu_fn = "kfu-s-93.stu";
		stu_no = 5349;
		crs_no = 461;
		per_no = 20;
	} else if (problem == "LSE91") {
		stu_fn = "lse-f-91.stu";
		stu_no = 2726;
		crs_no = 381;
		per_no = 18;
	} else if (problem == "TRE92") {
		stu_fn = "tre-s-92.stu";
		stu_no = 4360;
		crs_no = 261;
		per_no = 23;
	} else if (problem == "UTE92") {
		stu_fn = "ute-s-92.stu";
		stu_no = 2750;
		crs_no = 184;
		per_no = 10;
	} else {
		cerr << "Not implemented";
		exit(-1);
	}

	crs_per_stu_n = new int[stu_no + 1](); // δημιουργία πίνακα και αρχικοποίηση με 0
	crs_per_stu = new int*[stu_no + 1]();
	stu_per_crs_n = new int[crs_no + 1]();
	stu_per_crs = new int*[crs_no + 1]();
	conflict_matrix = new int*[crs_no + 1]();
	for (int i = 0; i < crs_no + 1; i++) {
		conflict_matrix[i] = new int[crs_no + 1]();
	}

	fstream filestr;
	string buffer;
	filestr.open(stu_fn.c_str());
	int stu_index = 1;
	if (filestr.is_open()) {
		while (getline(filestr, buffer)) {
			string buffer2;
			stringstream ss;
			ss.str(buffer); // αρχικοποίηση stringstream
			int crs = 0; // αριθμός μαθημάτων στα οποία θα εξεταστεί ο σπουδαστής
			while (ss >> buffer2) {
				int crs_index = atoi(buffer2.c_str());
				crs++;
				stu_per_crs_n[crs_index]++;
			}
			crs_per_stu_n[stu_index] = crs;
			crs_per_stu[stu_index] = new int[crs]();

			ss.clear();
			ss.str(buffer);
			int j = 0;
			while (ss >> buffer2) {
				int crs_index = atoi(buffer2.c_str());
				crs_per_stu[stu_index][j] = crs_index;
				j++;
			}
			stu_index++;
		}
		filestr.close();

// δημιουργία πίνακα crs_per_stu
		for (int i = 1; i < crs_no + 1; i++) {
			int students = stu_per_crs_n[i];
			stu_per_crs[i] = new int[students]();
		}
		int temp[crs_no + 1];
		for (int i = 0; i <= crs_no; i++)
			temp[i] = 0;
		for (int i = 1; i < stu_no + 1; i++) {
			for (int j = 0; j < crs_per_stu_n[i]; j++) {
				int k = crs_per_stu[i][j];
				stu_per_crs[k][temp[k]] = i;
				temp[k]++;
			}
		}

// δημιουργία πίνακα conflict_matrix
		for (int exam1 = 1; exam1 < crs_no + 1; exam1++) {
			for (int exam2 = exam1 + 1; exam2 < crs_no + 1; exam2++) {
				bool f = true;
				for (int i = 0; i < stu_per_crs_n[exam1] && f; i++)
					for (int j = 0; j < stu_per_crs_n[exam2] && f; j++)
						if (stu_per_crs[exam1][i] == stu_per_crs[exam2][j]) {
							conflict_matrix[exam1][exam2] = 1;
							conflict_matrix[exam2][exam1] = 1;
							f = false;
						}
			}
		}
	} else {
		cout << "Error opening file: " << stu_fn << endl;
		exit(-1);
	}
}

int main(int argc, char **argv) {
	int choice;
	string prob;
	do {
		cout << "1. Φόρτωση  προβλήματος" << endl;
		cout << "2. Στατιστικά" << endl;
		cout << "3. Γράφος προβλήματος" << endl;
		cout << "4. Φόρτωση λύσης-υπολογισμός κόστους" << endl;
		cout << "5. Έξοδος" << endl;
		cout << "Επιλογή: ";
		cin >> choice;
		switch (choice) {
		case 1:
			cout
					<< "Δώσε όνομα προβλήματος[CAR91-II|CAR91|KFU93|LSE91|TRE92|UTE92]: ";
			cin >> prob;
			read_problem_data(prob);
			print_conflict_density();
			break;
		case 2:
			cout << "Δεν έχει υλοποιηθεί ακόμα" << endl;
			break;
		case 3:
			cout << "Δεν έχει υλοποιηθεί ακόμα" << endl;
			break;
		case 4:
			cout << "Δεν έχει υλοποιηθεί ακόμα" << endl;
			break;
		case 5:
			break;
		default:
			cout << "Λάθος επιλογή. Προσπαθήστε ξανά!" << endl;
		}
	} while (choice != 5);
}

