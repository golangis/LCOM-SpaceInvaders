#include "shield.h"

Shield* initShield() {
  Shield* shield = (Shield*) malloc (sizeof(Shield));
  shield->lives = 15;
  shield->thickness = 3;
  return shield;
}

