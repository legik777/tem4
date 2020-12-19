#include <iostream>

#include "student.h"

using namespace std;
using namespace nlohmann;

int main(int n, char* arr[]) {
	if (n != 1) {
		string path = arr[1];
		ifstream input(path);
		if (input) {
			nlohmann::json js;
			input >> js;
			parseJS(js);
		}
		else {
			cout << "unable to open json: " + path << endl;
		}
	}
	else {
		cout << "No arguments found!" << endl;
	}
}