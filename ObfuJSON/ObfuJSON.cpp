#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class JSONObfuscator
{
public:
	JSONObfuscator(const string jsonInputPath, const string jsonOutputPath)
	{
		this->jsonInputPath = jsonInputPath;
		this->jsonOutputPath = jsonOutputPath;
	}

private:
	string jsonInputPath;
	string jsonOutputPath;

	void readInput() {
		ifstream inputFile(jsonInputPath);
		if (!inputIsOpen(inputFile)) return;

		string line;
		while (!inputFile.eof()) {
			getline(inputFile, line);
		}
	}

	void writeOutput(const string obfuscatedJSON) {
		ofstream outputFile(jsonOutputPath);
		if (!outputIsCreated(outputFile)) return;

		outputFile << obfuscatedJSON;
		outputFile.close();

		cout << "Output file created successfully." << endl;
	}

	bool inputIsOpen(ifstream& inputFile) {
		if (!inputFile.is_open()) {
			cerr << "Error opening input file." << endl;
			return false;
		}
	}

	bool outputIsCreated(ofstream& outputFile) {
		if (!outputFile) {
			cerr << "Error creating output file." << endl;
			return false;
		}
	}
};

int main()
{
	string jsonInputPath, jsonOutputPath = "output.json";

	cout << "Enter JSON file name: ";
	cin >> jsonInputPath;

	JSONObfuscator obfuscator(jsonInputPath, jsonOutputPath);

	return 0;
}