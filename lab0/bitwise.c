#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BIT(n) (1<<(n))

char *byte2bin(uint8_t n, char *binstr) 
{
    // one element per bit (0/1)
    uint8_t binary[8];

    int i = 0;
    for(i = 0; i < 8; i++) {
        binary[i] = n % 2;
        n = n / 2;
    }

    // printing binary array in reverse order
    for (int j = 7, k= 0; j >= 0; j--, k++) {
        sprintf(binstr + k, "%d", binary[j]);
    }
	return binstr;
}

void print_usage(char *name) {
	printf("Usage: %s <action> <byte> <bit no>\n", name);
	printf("\tWhere: <action> one of 'h'|'l'|'r'|'s'|'t'\n"
		"\t\t <byte> 8-bit integer in hexadecimal\n"
		"\t\t <bit no> of bit to operate on\n");
}

int main(int argc, char *argv[])
{
	char a;	// action: 'h', 'l', 'r', 's', 't'
	unsigned long n; // value to convert must be smaller than 256
	int bit; // bit to operate on: must be between 0 and 7
    char binary[9]; // array for binary representation of n,
	//  remember that in C strings are terminated with a 0
    // Validate command line arguments
    if (argc != 4) {
        //printf("1st\n");
        print_usage("bitwise");
        return 1;
    } else if (strcmp(argv[1],"h\0")!=0&&strcmp(argv[1],"l\0")!=0&&strcmp(argv[1],"r\0")!=0&&strcmp(argv[1],"s\0")!=0&&strcmp(argv[1],"t\0")!=0) {
        //printf("%s\n", argv[1]);
        //printf("2nd\n");
        print_usage("bitwise");
        return 1;
    } else if (strtol(argv[2], NULL, 0) >= 256) {
        //printf("3rd\n");
        print_usage("bitwise");
        return 1;
    } else if (atoi(argv[3]) < 0 || atoi(argv[3]) > 7) {
        //printf("4th\n");
        print_usage("bitwise");
        return 1;
    }

    a = *argv[1];
    n = atol(argv[2]);
    bit = atoi(argv[3]);
    binary[8] = 0;

	// Print to stdout the binary representation of n

    printf("Your option: %c\n", a);
    printf("Your original number in binary: %s\n", byte2bin(n, binary));
    printf("Your selected bit: %i\n", bit);

	// Do what the user asked and print the result

    if (a == 104 || a == 108) {
        n >>= bit;
        if (n % 2 != 0) printf("The bit %i of your number is high.\n", bit);
        else printf("The bit %i if your number is low.\n", bit);
        return 0;
    } else if (a == 115) {
        uint8_t mask = BIT(bit);
        n |= mask;
        printf("Your modified number is: %s\n", byte2bin(n, binary));
        return 0;
    } else if (a == 114) {
        uint8_t mask = BIT(bit);
        mask = ~mask;
        n &= mask;
        printf("Your modified number is: %s\n", byte2bin(n, binary));
        return 0;
    } else if (a == 116) {
        uint8_t mask = BIT(bit);
        n ^= mask;
        printf("Your modified number is: %s\n", byte2bin(n, binary));
        return 0;
    }
	
    return 0;
}
