#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctype.h>
using namespace std;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
/*
void decoder(string input) {
	vector<char> unfilteredbytes(input.begin(), input.end()), bytes;
	unfilteredbytes.push_back('\0');
	//char *character = &bytes[0];
	
	for(auto i : unfilteredbytes) {
		if(isxdigit(i)) {
			bytes.push_back(i);
		}
	}

	long int length = 0;
	vector<string> ascis;

	for(int i
	/*
	for(int i = 0; i < bytes.size(); i += 2) {
		if(i == 0) {
			string ascilength;
			bytelength.push_back(bytes[i]);
			bytelength.push_back(bytes[i+1]);
			length = (char) (int)strtol(byte.c_str(), NULL, 16);
		}
		else {
			string byte;
			byte.push_back(bytes[i]);
			byte.push_back(bytes[i+1]);
			ascis.push_back( strtol(byte.c_str(), NULL, 16));
		}
	}

	for(auto i : ascis)
		cout << i;	

	return;
} 
*/
void decode(string input) {
	// Remove whitespace (note: can repeat this for different delimiters e.g commas)
	vector<string> hexadecimalsprior = split(input, ' ');

	// Parse hexadecimals char pairs into a vector
	vector<string> hexadecimals;
	for(auto i : hexadecimalsprior) {
		for(int iterator = 0; iterator < i.size() - 1; iterator += 2) {
			hexadecimals.push_back(i.substr(iterator, 2));
		}
	}


	// Only need to display relevant strings (based on protocol given)
	vector<vector<string>> finalvalues;
	int outer = 0;

	while(hexadecimals.size() > 0) {
		int length = (int) strtol(hexadecimals[0].c_str(), NULL, 16);
		bool lengthnotzero = false;
		vector<string> temp;

		// If length of ASCII string is greater than zero
		if(length != 0) {
			hexadecimals.erase(hexadecimals.begin());
			if(length <= hexadecimals.size()) {
				for(int i = 0; i < length; i++) {
					//cout << "hex[i]: " << hexadecimals[i] << " ";
					temp.push_back(hexadecimals[i]);
				}
				if(length > hexadecimals.size())
					hexadecimals.erase(hexadecimals.begin(), hexadecimals.end());
				else
					hexadecimals.erase(hexadecimals.begin(), hexadecimals.begin() + length);
			}
		}
		// If length is zero, keep inputting values until another zero or end of vector
		else if(length == 0) {
			//cout << "else hex length: " << hexadecimals.size() << " ";
			hexadecimals.erase(hexadecimals.begin());
			lengthnotzero = true;
			int iter = 0;
			while(length < hexadecimals.size()) {
				if(hexadecimals[0] == "00")
					continue;
				else
					length++;
			}
			//cout << "length (==0): " << length;
			while(lengthnotzero && iter < length) {
				//cout << "iter: " << iter << endl;
				if(hexadecimals[0] == "00") {
					lengthnotzero = false;
					hexadecimals.erase(hexadecimals.begin());
				}
				else {
					iter++;
					temp.push_back(hexadecimals[0]);
					hexadecimals.erase(hexadecimals.begin());
				}
			}
			// cout << "iter: " << iter << " ";
		}
		//cout << "here";
			//hexadecimals.erase(hexadecimals.begin());
		//for(auto i : temp)
		//	cout << i;
		if(temp.size() > 0)
			finalvalues.push_back(temp);
		outer++;
	}

	// Display values
	for(auto i : finalvalues) {
		for(auto j : i) {
			if(isprint((char) (int)strtol(j.c_str(), NULL, 16)))
				cout << (char) (int)strtol(j.c_str(), NULL, 16);
			else
				cout << "\\x";
		}
		cout << endl;
	}

	cout << endl;
	return;
}

int main() {

	/*std::string teststring = "Testing this baby out! Yeah!";

	std::vector<std::string> output = split(teststring, ' ');
	for(auto i : output) 
		std::cout << i << std::endl;

	std::cout << std::endl << teststring << std::endl;
	*/

	string output2 = "01 49 02 61 6D 04 48 65 72";
	string output3 = "2C54686520717569636B2062726F776E20666F78206A756D706564206F76657220746865206C617A7920646F67";
	string output4 = "06 48 65 6C 6C 6F 20 00 57 6F 72 6C 64 00";
	string output5 = "00 11 22 44 88 CC 00";
	string output6 = "08 48 69 20 54 68 65 72 65";
	
	decode(output2);
	decode(output3);
	decode(output4);
	decode(output5);
	decode(output6);
	return 0;
}
