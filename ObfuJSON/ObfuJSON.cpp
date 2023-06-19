#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include <iomanip>
#include <map>

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
		obfuscatedJSON = normalToObfuscatedJSON(normalJSON);

		writeOutput(obfuscatedJSON);
	}

	void generateReplacementMap(const string replacementMapPath) {
		ofstream outputFile(replacementMapPath);
		if (!outputIsCreated(outputFile)) return;

		writeReplacement(outputFile);

		outputFile.close();
	}

private:
		map<string, string> replacementMap;
		string jsonInputPath;
		string jsonOutputPath;

		void readInput(string& normalJSON) {
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

		void writeReplacement(ofstream& outputFile){
			for (const auto& i : replacementMap) {
				outputFile << i.first << " -> " << i.second << endl;
			}
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

		string stringToUnicodeEscape(const string normalJSON){
			stringstream unicodeEscape;
			
			for (const char& i : normalJSON) {
				unicodeEscape << "\\u" << hex << setw(4) << setfill('0') << (int)i;
			}

			return unicodeEscape.str();
		}

		string normalToObfuscatedJSON(const string &normalJSON) {
			string line, obfuscatedJSON;
			replacementMap.clear();
			string originalString, obfuscatedString;

			size_t possition = 0, start=0, end=0;

			while (possition < normalJSON.size()) {
				start = normalJSON.find_first_of("\"", possition+1);

				if (start != string::npos) {
					end = normalJSON.find_first_of("\"", start + 1);

					if (end != string::npos) {

						originalString = normalJSON.substr(start + 1, end - start - 1);
						obfuscatedString = stringToUnicodeEscape(originalString);
						
						obfuscatedJSON += normalJSON.substr(possition, start - possition + 1)
							+ obfuscatedString;
						replacementMap[originalString] = obfuscatedString;

						possition = end;
						continue;
					}
				}
				obfuscatedJSON += normalJSON.substr(possition);
				break;
			}
			return obfuscatedJSON;
		}
};

int main()
{
	string jsonInputPath, jsonOutputPath= "output.json";

	cout << "Enter JSON file name: ";
	cin >> jsonInputPath;

	JSONObfuscator obfuscator(jsonInputPath, jsonOutputPath);

	obfuscator.obfuscate();
	obfuscator.generateReplacementMap("replacementMap.txt");

	return 0;
}