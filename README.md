# ObfuJSON

This is a C++ program that obfuscates strings in a JSON file by replacing them with their respective Unicode escape sequences. It also generates a replacement map file that contains the original strings and their corresponding obfuscated values.

## Enviornment

The program was made using VisualStudio Comunity 2022 and compiled with Visual C++ v14

## Usage

1. Compile and run the program
2. Enter the name of the json file you want obfuscated(include the '.json' at the end). Make sure the json file is in the same file as the program
3. The program will obfuscate your json file and create a "output.json" file in which you fill find your obfuscated json
4. A file named "replacementMap.txt" will also appear that should help you decipher your obfuscated json file

## Code Overview

The code is structured using a class called JSONObfuscator, which encapsulates the obfuscation functionality. It provides the following public methods:

⌂ obfuscate(): Reads the input JSON file, obfuscates the strings, and writes the obfuscated JSON to an output file.
⌂ generateReplacementMap(): Generates a replacement map file that contains the original strings and their obfuscated values.

And the following private methods:

⌂ readInput(): Reads the JSON file
⌂ writeOutput(): Writes the obfuscated JSON file
⌂ writeReplacement(): Writes the replacement map
⌂ inputIsOpen(): Checks if the json file was opened successfuly and outputs an error to the command line otherwise
⌂ outputIsCreated(): Checks if the output file was created successfuly and outputs an error to the command line otherwise
⌂ stringToUnicodeEscape(): Converts inputted string to it's unicode escape sequence
⌂ normalToObfuscatedJSON(): Obfuscates the inputed json file and maps out the string to unicode replacements

The main() function prompts the user to enter the name of the JSON file to obfuscate. It creates an instance of the JSONObfuscator class and calls the obfuscate() and generateReplacementMap() methods.
