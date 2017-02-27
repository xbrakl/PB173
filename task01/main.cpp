//This project doesn't work yet and is not compileable!

#include <iostream>
#include <fstream>
#include <string>

#include "mbedtls/include/mbedtls/aes.h"

std::string encrypt(std::ifstream& inputfile) {
	mbedtls_aes_context aes;

	unsigned char key[32]; //AES key
	unsigned char iv[16];  //Initialization Vector - vector of really random numbers

	unsigned char input[128]; //input with 40 bytes of input data and zeroized the rest of input
	unsigned char output[128];

	size_t input_len = 40;
	size_t output_len = 0;

	std::string outputbuffer;

	//TO DO: encryption algorithm by blocks of input datas

	return outputbuffer;
}

void hash(){
	//TODO: Question, what should do this function?
}

int main() {
	std::cout << "Welcome in my super ultra encryption program" << std::endl;
	std::cout << "Type '1' in case of encryption\n"
			     "Type '0' in case of decryption" << std::endl;
	unsigned cryptomode;
	std::cin >> cryptomode;

	if(cryptomode) { //encryption
		std::cout << "Type name of file you want to encrypt\n> " << std::endl;
		std::string filename;
		getline(std::cin, filename);
		std::ifstream inputfile(filename);

		std::string encrypted_output = encrypt(inputfile);

		std::string filename2;
		filename2 = "encrypted_" + filename;
		std::ofstream outputfile(filename);
		outputfile << encrypted_output;
		outputfile.close();
		inputfile.close();
	}
	else { //decryption
		//TODO
	}

	return 0;
}