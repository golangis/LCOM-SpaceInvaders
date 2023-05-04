#ifndef SHIELD_H
#define SHIELD_H

typedef struct {
    int x;
    int y;
    int thickness;
    int lives;
} Shield;

Shield* initShield();
void drawShield(Shield* shield);

#endif
