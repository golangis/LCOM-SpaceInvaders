#ifndef SHIELD_H
#define SHIELD_H

typedef struct {
    int x;
    int y;
    int thickness;
    int lives;
} Shield;

Shield* initShield(int x);
void drawShield(Shield* shield);
void damage(Shield* shield);

#endif
