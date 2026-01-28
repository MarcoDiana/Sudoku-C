// sudoku.h

#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>

#include "partita.h"
#include "scrittura.h"

// Funzioni per la gestione della partita

/* permette al giocatore di iniziare la partita e giocare*/
void Giocare(Partita *partita);

/* chiede i valori al giocatore da inserire nella griglia */
int ChiediValore(Partita *partita);

/* si occupa di inizializzare una griglia appena creata con in 
numero un certo numero di valori in base a dimensione griglia e 
difficoltà partita */
void InizializzazioneGriglia(Partita *partita);



// Controllo delle regole del sudoku

/*verifica che il numero inserito in una casella rispetti le regole
del sudoku */
bool NumeroCorretto(Partita *partita, int r, int c, int n);

/* verifica che il numero inserito non sia presente nella regiorne
in cui è presente la casella in cui l'utente vuole scrivere */
bool ControllaRegione(Partita *partita, int r, int c, int n);

/* verifica che il numero inserito non sia presente nella diagonale
in cui è presente la casella in cui l'utente vuole scrivere*/
bool ControllaDiagonale(Partita *partita, int r, int c, int n);

/* verifica che il numero inserito non sia presente nella colonna
in cui è presente la casella in cui l'utente vuole scrivere*/
bool ControllaColonna(Partita *partita, int c, int n);

/* verifica che il numero inserito non sia presente nella riga
in cui è presente la casella in cui l'utente vuole scrivere*/
bool ControllaRiga(Partita *partita, int r, int n);

/* controlla che la griglia sia piena */
bool GrigliaPiena(Partita *partita);



#endif // SUDOKU_H