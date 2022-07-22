#ifndef STRUCTS_H_
#define STRUCTS_H_
#include <stdbool.h>

typedef struct Celulas_t
{
    bool temBomba;
    bool estaAberta;
    int vizinhos; // vai de 0 a 8
    int campo;
} Celulas;

#endif
