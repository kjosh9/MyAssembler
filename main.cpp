//////////////////////////////////////////////////////////
//	Joshua Knestaut
//	ECE 2500
//	2/18/2016
//	myAssembler




#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <list>

#include <stdlib.h>

#include "exceptions.h"
#include "lexer.h"
#include "util.h"

using namespace std;

//contains vital information to the instruction
struct instr_package {
	string opCode;
	char type;
	string funct;
	string shamt;
	string immediate;
	string rd;
	string rs;
	string rt;
};

//holds a label and location for the label
struct labelLocate {
	string label;
	int location;
};

//determines the mnemonic and unique info for instruction
void nameWork(string name, instr_package &inst, int count) {

	inst.shamt = "00000";

	if (name == "add") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "100000";
	}
	else if (name == "addi") {
		inst.type = 'i';
		inst.opCode = "001000";
	}
	else if (name == "addiu") {
		inst.type = 'i';
		inst.opCode = "001001";
	}
	else if (name == "addu") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "100001";
	}
	else if(name == "and"){
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "100100";
	}
	else if (name == "andi") {
		inst.type = 'i';
		inst.opCode = "001100";
	}
	else if (name == "beq") {
		inst.type = 'i';
		inst.opCode = "000100";
	}
	else if (name == "bne") {
		inst.type = 'i';
		inst.opCode = "000101";
	}
	else if (name == "jr") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "001000";
	}
	else if (name == "lbu") {
		inst.type = 'i';
		inst.opCode = "100100";
	}
	else if (name == "lhu") {
		inst.type = 'i';
		inst.opCode = "100101";
	}
	else if (name == "ll") {
		inst.type = 'i';
		inst.opCode = "110000";
	}
	else if (name == "lui") {
		inst.type = 'i';
		inst.opCode = "001111";
	}
	else if (name == "lw") {
		inst.type = 'i';
		inst.opCode = "100011";
	}
	else if (name == "nor") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "100111";
	}
	else if (name == "or") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "100101";
	}
	else if (name == "ori") {
		inst.type = 'i';
		inst.opCode = "001101";
	}
	else if (name == "slt") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "101010";
	}
	else if (name == "slti") {
		inst.type = 'i';
		inst.opCode = "001010";
	}
	else if (name == "sltiu") {
		inst.type = 'i';
		inst.opCode = "001011";
	}
	else if (name == "sltu") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "101011";
	}
	else if (name == "sll") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "000000";
	}
	else if (name == "srl") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "000010";
	}
	else if (name == "sb") {
		inst.type = 'i';
		inst.opCode = "101000";
	}
	else if (name == "sc") {
		inst.type = 'i';
		inst.opCode = "111000";
	}
	else if (name == "sh") {
		inst.type = 'i';
		inst.opCode = "101001";
	}
	else if (name == "sw") {
		inst.type = 'i';
		inst.opCode = "101011";
	}
	else if (name == "sub") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "100010";
	}
	else if (name == "subu") {
		inst.type = 'r';
		inst.opCode = "000000";
		inst.funct = "100011";
	}
	else {
		throw_bad_asm(count, "");
	}
}

//determines the number for the provided register string
string findRegValue(string reg, int count) {

	string regValue;

	if (reg == "$zero") { regValue = "00000"; }
	else if (reg == "$at") { regValue = "00001"; }
	else if (reg == "$v0") { regValue = "00010"; }
	else if (reg == "$v1") { regValue = "00011"; }
	else if (reg == "$a0") { regValue = "00100"; }
	else if (reg == "$a1") { regValue = "00101"; }
	else if (reg == "$a2") { regValue = "00110"; }
	else if (reg == "$a3") { regValue = "00111"; }
	else if (reg == "$t0") { regValue = "01000"; }
	else if (reg == "$t1") { regValue = "01001"; }
	else if (reg == "$t2") { regValue = "01010"; }
	else if (reg == "$t3") { regValue = "01011"; }
	else if (reg == "$t4") { regValue = "01100"; }
	else if (reg == "$t5") { regValue = "01101"; }
	else if (reg == "$t6") { regValue = "01110"; }
	else if (reg == "$t7") { regValue = "01111"; }
	else if (reg == "$s0") { regValue = "10000"; }
	else if (reg == "$s1") { regValue = "10001"; }
	else if (reg == "$s2") { regValue = "10010"; }
	else if (reg == "$s3") { regValue = "10011"; }
	else if (reg == "$s4") { regValue = "10100"; }
	else if (reg == "$s5") { regValue = "10101"; }
	else if (reg == "$s6") { regValue = "10110"; }
	else if (reg == "$s7") { regValue = "10111"; }
	else if (reg == "$t8") { regValue = "11000"; }
	else if (reg == "$t9") { regValue = "11001"; }
	else if (reg == "$k0") { regValue = "11010"; }
	else if (reg == "$k1") { regValue = "11011"; }
	else if (reg == "$gp") { regValue = "11100"; }
	else if (reg == "$sp") { regValue = "11101"; }
	else if (reg == "$fp") { regValue = "11110"; }
	else if (reg == "$ra") { regValue = "11111"; }
	else { throw_bad_asm(count, ""); }

	return regValue;
}

//assembled the machine code into binary string
string buildCode(instr_package &inst) {

	string machineCode;

	if (inst.type == 'r') {

		machineCode = inst.opCode;	//start with the opcode
		machineCode.append(inst.rs); //append rs
		machineCode.append(inst.rt); //append rt
		machineCode.append(inst.rd); //append rd
		machineCode.append(inst.shamt); //append shamt
		machineCode.append(inst.funct); //append funct

	}
	else if (inst.type == 'i') {

		machineCode = inst.opCode;	//start with the opcode
		machineCode.append(inst.rs); //append rs
		machineCode.append(inst.rt); //append rt
		machineCode.append(inst.immediate); //append immediate

	}
	//should return a 32bit value
	return machineCode;
}

//converts the string of binary values to a string of hex
string binToHex(string binary) {

	string hex = "00000000";
	int value = 0;

	//cout << "converting binary to hex" << endl;

	for (int i = 0; i < 8; i++) {
		//cout << "---------------------------------" << endl;
		//cout << "byte:" << i << endl;

		for (int j = 0; j <4 ; j++) {
			//cout << "bit: " << j;
			if (binary[(4 * i) + j] == '1') {
				//cout << "= 1" << endl;
				value += pow(2,3-j);
			}
			else {
				//cout << "= 0" << endl;
			}

			//cout << "		value = " << value << endl;
		}
		//simple way of putting the integer in the string as a hex value
		switch (value) {

			case 15:
				hex[i] = 'f';
				break;
			case 14:
				hex[i] = 'e';
				break;
			case 13:
				hex[i] = 'd';
				break;
			case 12:
				hex[i] = 'c';
				break;
			case 11:
				hex[i] = 'b';
				break;
			case 10:
				hex[i] = 'a';
				break;
			case 9:
				hex[i] = '9';
				break;
			case 8:
				hex[i] = '8';
				break;
			case 7:
				hex[i] = '7';
				break;
			case 6:
				hex[i] = '6';
				break;
			case 5:
				hex[i] = '5';
				break;
			case 4:
				hex[i] = '4';
				break;
			case 3:
				hex[i] = '3';
				break;
			case 2:
				hex[i] = '2';
				break;
			case 1:
				hex[i] = '1';
				break;
			case 0:
				hex[i] = '0';
				break;
		}

		//cout << "Byte value: " << value << endl;
		value = 0;
	}
	
	return hex;
}

//function to take decimal immediates and turn 
//them into my binary system
string intToBin(int number) {
	string immediate = "0000000000000000";

	if (number < 0) {

		//cout << "offset =" << number << endl;

		immediate[0] = '1';
		for (int i = 14; i >= 0; i--) {
			if ((number >> i)&1 == 1) {
				immediate[15 - i] = '1';
			}
		}
	}
	else {
		for (int i = 15; i >= 0; i--) {
			if (number >= pow(2, i)) {
				immediate[15 - i] = '1';
				number -= pow(2, i);
			}
		}
	}
	return immediate;
}

//same as function about, but with smaller string
string binShamt(int number) {
	string shamt = "00000";
	for (int i = 4; i >= 0; i--) {
		if (number >= pow(2, i)) {
			shamt[4 - i] = '1';
			number -= pow(2, i);
		}
	}
	return shamt;

}

std::string read_file(const std::string& name) {
  std::ifstream file(name);
  if (!file.is_open()) {
    std::string error = "Could not open file: ";
    error += name;
    throw std::runtime_error(error);
  }
  std::stringstream stream;
  stream << file.rdbuf();
  return std::move(stream.str());
}

int main(int argc, char** argv) {
  // Adjusting -- argv[0] is always filename.
  --argc;
  ++argv;


  // all variable used
  string binMachineCode, machineCode;
  instr_package sample;
  string temp;
  int proCount = 0;
  vector <labelLocate> labelList;
  labelLocate nuLabel;
  string txtName;
	
  if (argc == 0) {
    std::cerr << "Need a file" << std::endl;
    return 1;
  }

  for (int i = 0; i < argc; ++i) {
    std::string asmName(argv[i]);

    if (!util::ends_with_subseq(asmName, std::string(".asm"))) {
      std::cerr << "Need a valid file name (that ends in .asm)" << std::endl;
      std::cerr << "(Bad name: " << asmName << ")" << std::endl;
      return 1;
    }

	//creating the output file name
	txtName = asmName;
	txtName.pop_back();
	txtName.pop_back();
	txtName.pop_back();
	txtName.append("txt");

	//opening up the output file
	ofstream txtFile;
	txtFile.open(txtName); 

    // 4 is len(".asm")
    auto length = asmName.size() - string_length(".asm");
    std::string baseName(asmName.begin(), asmName.begin() + length);
    std::string objName = baseName + ".obj";
    try {
      auto text = read_file(asmName);
      try {
		auto lexed = lexer::analyze(text);		// Parses the entire file and returns a vector of instructions
		
		for (int z = 0; z < 2; z++) {

			proCount = 0;

			for (int i = 0; i < (int)lexed.size(); i++) {

				if (lexed[i].labels.size() > 0) {		// Checking if there is a label in the current instruction
					if (z == 1)
						std::cout << "label = " << lexed[i].labels[0] << "\n";		// Prints the label
					else {
						nuLabel.label = lexed[i].labels[0];
						nuLabel.location = proCount;
						labelList.push_back(nuLabel);
					}
				}
				
				if(z == 1)
					std::cout << "instruction name = " << lexed[i].name << "\n";		// Prints the name of instruction
				
				sample.type = 'k';
				
				nameWork(lexed[i].name, sample, proCount);

				if(z == 1)
					std::cout << "tokens = ";

				std::vector<lexer::token> tokens = lexed[i].args;
				if (z == 1) {
					for (int j = 0; j < (int)tokens.size(); j++) {       // Prints all the tokens of this instruction like $t1, $t2, $t3
						if (tokens[j].type == lexer::token::Integer)
							std::cout << tokens[j].integer() << " ";
						else
							std::cout << tokens[j].string() << " ";
					}
				}
				if (sample.type == 'r') {
					sample.rd = findRegValue(tokens[0].string(), proCount+1);
					sample.rs = findRegValue(tokens[1].string(), proCount+1);

					//check and make sure it is not a shift amount
					if (tokens[2].type == lexer::token::Integer) {
						sample.shamt = binShamt(tokens[2].integer());
						sample.rt = sample.rs;
						sample.rs = "00000";
					}
					else {
						sample.rt = findRegValue(tokens[2].string(),proCount+1);
					}
				}
				else if (sample.type == 'i') {
					sample.rt = findRegValue(tokens[0].string(),proCount+1);

					//check and make sure the next value isnt an offset
					if (tokens[1].type == lexer::token::Integer) {
						sample.immediate = intToBin(tokens[1].integer());
						sample.rs = tokens[2].string();
						sample.rs.erase(0, 1);
						sample.rs.erase(3, 1);
						sample.rs = findRegValue(sample.rs,proCount+1);
						//cout << "source reg: " << sample.rs << endl;
					}
					else {
						sample.rs = findRegValue(tokens[1].string(),proCount+1);
						if (tokens[2].type == lexer::token::Integer) {
							sample.immediate = intToBin(tokens[2].integer());
						}
						//this is for the case of a branch instruction
						else if(z == 1){
							temp = tokens[2].string();
							sample.immediate = "FFFFFFFFFFFFFFFF";

							for (int w = 0; w < labelList.size(); w++) {
								if (labelList[w].label == temp) {
									//cout << "location = " << labelList[w].location << "||PC =" << proCount << endl;
									//cout << "offset = " << labelList[w].location - proCount + 1 << endl;
									sample.immediate = intToBin(labelList[w].location - (proCount + 1));
								} 
							}
							if (sample.immediate == "FFFFFFFFFFFFFFFF") {
								throw_bad_label(proCount+1, temp);								
							}

							temp = sample.rt;
							sample.rt = sample.rs;
							sample.rs = temp;
						}
					}
				}

				//printing out some stuff
				if (z == 1) {
					binMachineCode = buildCode(sample);
					//cout << endl << "Binary Machine Code: " << binMachineCode << endl;
					machineCode = binToHex(binMachineCode);

					///debugging stuffs
					//cout << "rs = " << sample.rs << endl;
					//cout << "rt = " << sample.rt << endl;
					//cout << "rd = " << sample.rd << endl;
					//cout << "shamt = " << sample.shamt << endl;
					//cout << "funct = " << sample.funct << endl; 

					//output to the terminal
					cout << endl << "Machine Code: " << machineCode << endl;

					//output to the txt file
					txtFile << machineCode << endl;

					std::cout << "\n";
				}
				
				proCount++;
			}
		}
	  } catch(const bad_asm& e) {
		std::stringstream error;
		error << "Cannot assemble the assembly code at line " << e.line;
		throw std::runtime_error(error.str());
		} catch(const bad_label& e) {
		 std::stringstream error;
		error << "Undefined label " << e.what() << " at line " << e.line;
		throw std::runtime_error(error.str());
		}
	  
    } catch (const std::runtime_error& err) {
      std::cout << err.what() << std::endl;
      return 1;
    }
  }
  //getchar();
  return 0;
}
