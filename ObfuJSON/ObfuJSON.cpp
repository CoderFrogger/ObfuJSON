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

	void obfuscate() {
		string obfuscatedJSON, normalJSON;
		readInput(normalJSON);
		writeOutput(obfuscatedJSON);
	}

private:
		string jsonInputPath;
		string jsonOutputPath;

		void readInput(string &normalJSON) {
			ifstream inputFile(jsonInputPath);
			if (!inputIsOpen(inputFile)) return;

			string line;
			while (getline(inputFile, line)) {
				normalJSON += line + "\n";
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
			return true;
		}

		bool outputIsCreated(ofstream& outputFile) {
			if (!outputFile) {
				cerr << "Error creating output file." << endl;
				return false;
			}
			return true;
		}
};

int main()
{
	string jsonInputPath, jsonOutputPath= "output.json";

	cout << "Enter JSON file name: ";
	cin >> jsonInputPath;

	JSONObfuscator obfuscator(jsonInputPath, jsonOutputPath);

	obfuscator.obfuscate();

	return 0;
}