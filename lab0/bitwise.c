#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

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
    for (int j = 7, k= 0; j >= 0; j--, k++)
        sprintf(binstr + k, "%d", binary[j]); // <- duvida: como funciona o k?
        
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
	int bit; // bit to operate on: must be between 0 an 7
    char binary[9]; // array for binary representation of n,
					//  remember that in C strings are terminated with a 0
    char final[9];

	if (argc != 4){
        printf("\nInvalid number of arguments provided.\nThe function receives 3 args, but %d were received.\n", argc-1);
    }
            switch (*argv[1]){
                
            case 'h':

                //test if bit is 1
                printf(byte2bin(atoi(argv[2]), &binary)); // <- representaçao binario - n percebo pq q aqui se puser *argv[2] dá mal, mas so começou a dar bem dps de trocar 
                
                if (byte2bin(atoi(argv[2]), &binary)[ 7 - atoi(argv[3])] == '1')
                    printf("\ntrue\n");
                else
                    printf("\nfalse\n");

                break;

            case 'l':
    
                //test if bit is 0
                printf(byte2bin(atoi(argv[2]), &binary)); // <- representaçao binario - n percebo pq q aqui se puser *argv[2] dá mal, mas so começou a dar bem dps de trocar 
                
                if (byte2bin(atoi(argv[2]), &binary)[ 7 - atoi(argv[3])] == '0')
                    printf("\ntrue\n");
                else
                    printf("\nfalse\n");
            
                break;

            case 's':

                //switch bit to 1
                printf("Initial state: %s.\n", byte2bin(atoi(argv[2]), &binary)); 
                
                for (int i = 0; i < 8; i ++){

                    if (i == 7 - atoi(argv[3]))
                        final[i] = '1';
                    else 
                        final[i] = byte2bin(atoi(argv[2]), &binary)[i];
                }

                printf("Final state: %s.\n", final); 

                break;

            case 'r':

                //switch bit to 0
                                printf("Initial state: %s.\n", byte2bin(atoi(argv[2]), &binary)); 
                
                for (int i = 0; i < 8; i ++){

                    if (i == 7 - atoi(argv[3]))
                        final[i] = '0';
                    else 
                        final[i] = byte2bin(atoi(argv[2]), &binary)[i];
                }

                printf("Final state: %s.\n", final); 

                break;

            case 't':

                //negates bit

                break;        

            default:

                printf("\nInvalid input.\n");

                break;
        }
        
	
	// Print to stdout the binary representation of n
	
	// Do what the user asked and print the result
	

    return 0;
}


