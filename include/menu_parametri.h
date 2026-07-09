// menu.h

#ifndef MENU_PARAMETRI_H
#define MENU_PARAMETRI_H

#include "partita.h"
#include "scrittura.h"

// menu principali del gioco e inserimento parametri


/* mostra il menù per la creazione di una nuova partita
e permette la creazione di una nuova partita */
void MenuNuova(Partita **partita);

/* mostra il menù per caricare una nuova partita e ne 
permette il recupero se esiste */
void MenuContinua(Partita **partita);

/* permette all'utente di inserire i parametri della partita*/
void InputParametri(Partita **partita);

/* verifica che le dimensioni inserite dall'utente siano delle
dimensioni accettate*/
bool VerificaDimensioni(Partita *partita);

/* verifica che la difficolta inserita dall'utente sia una
difficolta accettata*/
bool VerificaDifficolta(Partita *partita);

#endif // MENU_PARAMETRI_H