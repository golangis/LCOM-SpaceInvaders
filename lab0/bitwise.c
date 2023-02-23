#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BIT(n) (1<<(n));
#define BIT1(n) (0<<(n));


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

int main(int argc, char *argv[]){
  char action;
  unsigned long num;
  int bit;
  char binary[9];
  uint8_t aux;

  //this section is to detect if the input given is valid
  if (argc != 4){
    printf("\nInvalid number of arguments. The function receives 3 arguments but %d were given.\n", argc-1);
    return 1;
  }

  if (!((*argv[1] == 'h') || (*argv[1] == 'l') || (*argv[1] == 's') || (*argv[1] == 'r') || (*argv[1] == 't'))){
    printf ("\n Invalid argument, expected either h, l, s, r, t but %d was given \n", *argv[1]);      return 1;
  }

  if(strtol(argv[2], NULL, 16) >= 256){
    printf("\nThe hexadecimal number given is too long\n");
    return 1;
  }

  if((atoi(argv[3]) < 0) || (atoi(argv[3]) > 7)){
    printf("\nThere is no bit of order %d \n", *argv[3]);
    return 1;
  }
    
  printf("\n The action you chose was %c \n", *argv[1]);
  printf("\n The number you gave is %s \n", byte2bin(atol(argv[2]), binary));
  printf("\nThe bit you selected is %i \n", atoi(argv[3]));

  action = *argv[1];
  num = atol(argv[2]);
  bit = atoi(argv[3]);

  switch(action){
    case 'h':
      if(binary[7 - bit] % 2 == 1){
        printf("\n The bit of the number you gave is high\n");
      }
      else{
        printf("\n The bit of the number you gave is low \n");
      }
      return 0;
    case 'l':
      num >>= bit;
      if(num % 2 == 1){
        printf("\n The bit of the number you gave is high\n");
      } 
      else{
        printf("\n The bit of the number you gave is low\n");
      }
      return 0;
    case 's':
      aux = BIT(bit);
      num = num | aux;
      printf("\n The number is now: %s \n", byte2bin(num, binary));
      return 0;

    case 'r':
      aux = BIT(bit);
      aux = ~aux;  
      num = num & aux;
      printf("\n The number is now: %s \n", byte2bin(num, binary));
      return 0;

    case 't':
      aux = BIT(bit);
      num = num ^ aux;
      printf("\n The number is now: %s \n", byte2bin(num, binary));
      return 0;
  }
  return 0;
}