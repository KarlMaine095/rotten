/**
 * Author: Charlemagne L. Javinal
 * Nickname: 'Charles'
 * Program Name: rotten
 * Version: v1.0
 * Email: KarlMaine095@gmail.com
 * Date Begin: Feb. 15, 2017
 * Date End: Feb. 15, 2017
 * Purpose/Description:
 * 		To cypher and decypher a simple text file to a simple rot1 to rot13
 * 		cypher.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <stdexcept>

void help();
char toRotten(char ch, short rot);

int main(int argc, char* argv[]) {
	if (argc < 3 ) { help(); return 1;}
	short rot;	// defines the number of rotations 
						//needed for cyphering the text
	try {
		rot = std::stoi(std::string(argv[2])); // converts string to int
		if (!(13 > rot && rot > 0 )) // ensure that 13 > rot > 0
			throw std::invalid_argument("argument 2 must be integer more "
										"than 0 and less than or equal 13 ");
	}
	catch (std::invalid_argument& e){
		std::cerr << "caught invalid_argument error " << e.what()<< '\n';
		help();
		return 2;
	}

	std::cout << "rotting textfile using rot" << rot << '\n';
	std::ifstream file(std::string(argv[1]), std::ios_base::in);
		// open file for reading ONLY.
	std::string rottenChars;
	try {
		if (!file.is_open())
			throw std::runtime_error("Error while opening file."
									 "Either the file doesn't exists or "
									 "You don't have the right permission");
		while(!file.eof()){
			char cleanChar = file.get(); // Gets one character.
			rottenChars += toRotten(cleanChar, rot);
		}
	}
	catch (std::runtime_error& e) {
		std::cerr << "Caught runtime_error : " << e.what() << '\n';
		return 3;
	}
	catch (std::exception& e) {
		std::cerr << "Caught an error : " << e.what() << '\n';
		return 4;
	}
	file.close();

	std::ofstream ofile("out.txt", std::ios_base::out);
	ofile << rottenChars;
	ofile.close();

	return 0;
}

char toRotten(char ch, short rot) {
	if (! std::isalpha(ch)) return ch; 
	char rottenCh;
	if('Z' >= ch && ch >= 'A'){
		rottenCh = ch + rot;
		return (rottenCh > 'Z') ? (char)64 + (rottenCh - 'Z') : rottenCh;
	} 
	else if('z' >= ch && ch >= 'a'){
		if (ch <= 'r'){
			rottenCh = ch + rot;
			return (rottenCh > 'z') ? (char)96 + (rottenCh - 'z') : rottenCh;
		}
		else {
			rot -= (122 - static_cast<int>(ch));
			if (rot > 0) return static_cast<char>(96) + rot;
			else return static_cast<char>(122) + rot;
		}
	}
}

void help() {
	std::cout << "Usage: rotten <file> <number-of-rotations>" << '\n'
		<< "Example: '$ rotten ExampleFile.txt 13' will cypher \n" 
		<< "\tExampleFile.txt using rot13 cypher.\n";
}
