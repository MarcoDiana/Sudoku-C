// scrittura.h

#ifndef scrittura_h
#define scrittura_h

#include <windows.h>
#include "costanti.h"
#include "partita.h"


// Centratura dei testi e degli input

void CentraSchermo(char testo[]);

void InputCentrato(char *domanda, char *input, int lunghezza_input);

void InputCentratoRigaFissa(char *domanda, char *input, int lunghezza_input, int riga);


// Gestione del cursore

COORD OttieniPosizioneCursore();

void VaiAllaRiga(int riga);


// Correzione Stringhe
void RimuoviSpaziIniziali(char *str);

void RimuoviSpaziFinali(char *str);


/* Stampa la griglia del sudoku */
void MostraSudoku(Partita *partita);


#endif // scrittura_h