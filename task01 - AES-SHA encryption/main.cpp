//This project doesn't work yet and is not compileable!

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

//encryption/decryption
#include "lib/aes.h"
#include "lib/sha1.h"

//AES key generation
#include "lib/entropy.h"
#include "lib/ctr_drbg.h"

/**
 * @brief encryptFile 	Function encrypt file
 * @param filename		Name of file you want to encrypt
 * @return				0 in case of succes, 1 otherwise
 */
int encryptFile(const std::string& filename);

int encryptFile(const std::string& filename) {
	//mbed TLS code
		//AES key generator variables - source: https://tls.mbed.org/kb/how-to/generate-an-aes-key
		mbedtls_ctr_drbg_context ctr_drbg;
		mbedtls_entropy_context entropy;
		unsigned char key[16]; //AES key

		char *pers = "aes generate key";
		int ret;

		//generating of AES key - source: https://tls.mbed.org/kb/how-to/generate-an-aes-key
		mbedtls_entropy_init( &entropy );
		if( ( ret = mbedtls_ctr_drbg_init( &ctr_drbg, mbedtls_entropy_func, &entropy, (unsigned char *) pers, strlen(pers) ) ) != 0 ){
			printf( " failed\n ! mbedtls_ctr_drbg_init returned -0x%04x\n", -ret );
			return 1; //goto exit;
		}

		if( ( ret = mbedtls_ctr_drbg_random( &ctr_drbg, key, 16 ) ) != 0 ) {
			printf( " failed\n ! mbedtls_ctr_drbg_random returned -0x%04x\n", -ret );
			return 1; //goto exit;
		}

		//AES algorithm variables - source: https://tls.mbed.org/kb/how-to/encrypt-with-aes-cbc
		mbedtls_aes_context aes;

		unsigned char iv[16];  //Initialization Vector - vector of really random numbers

		unsigned char input[128] = {0}; //input with 40 bytes of input data and zeroized the rest of input
		unsigned char output[128] = {0};

		size_t input_len = 40;
		size_t output_len = 0;
	//end of mbed TLS code


	char buffer[128] = {0}; //used from conversion char <-> unsigned char

	//begin of encryption
	std::ifstream inputfile(filename); //calling RAII constructor - add control of failure of opening file
	std::ofstream outputfile("encrypted_" + filename);

	mbedtls_aes_setkey_enc( &aes, key, 256 ); //Initialization of aes context - i dont understand

	while(!inputfile.eof()){
		inputfile.read(buffer, input_len);
		for(int i = 0; i < input_len; i++) //copying from array of chars to array of unsigned chars
			input[i] = buffer[i];
		mbedtls_aes_crypt_cbc( &aes, MBEDTLS_AES_ENCRYPT, 24, iv, input, output );
		for(int i = 0; i < input_len; i++) //copying from array of chars to array of unsigned chars
			buffer[i] = output[i];
		outputfile.write(buffer, output_len);
	}

	return 0;
}

void hash(){
	//TODO: Question, what should do this function?
}

int handler(){
	std::cout << "+------------------------------------------------+"
			     "|  Welcome in my super ultra encryption program  |"
			     "+------------------------------------------------+"
				 ""
				 "=================================================="
				 ""
				 "Type '1' in case of encryption\n"
				 "Type '0' in case of decryption\n\n> ";

	unsigned cryptomode;
	std::cin >> cryptomode;

	if(cryptomode) { //encryption
		std::cout << "\nType name of file which you want to encrypt\n\n> " << std::endl;
		std::string filename;
		std::cin >> filename;
		return encryptFile(filename);
	}
	return 0;
}

int main() {
	return handler();
}