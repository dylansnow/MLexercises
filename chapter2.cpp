#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

inline void keep_window_open() { char ch; cin >> ch; }

int main() {
	cout << "Please enter your name and age:\n";
	string first_name;
	int age;
	cin >> first_name;
	cin >> age;
	cout << "Hello, " << first_name << " (age: " << age << ")\n";
	return 0;
}
