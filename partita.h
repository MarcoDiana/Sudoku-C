// partita.h

#ifndef partita_h
#define partita_h

#include "costanti.h"


// Strutture dati
typedef struct {
    int dimensione;
    int ValoriGriglia[DIM_MASSIMA][DIM_MASSIMA];
} Griglia;

typedef struct {
    int dimensione;
    int difficolta;
} Impostazioni;

typedef struct {
    Impostazioni ImpostazioniPartita;
    Griglia GrigliaPartita;
    char NomePartita[LUNGHEZZA_NOME_PARTITA + LUNGHEZZA_ESTENSIONE_FILE];
} Partita;



// Prototipi funzioni di accesso e gestione partita
int LeggereDimensioneGriglia(Partita *partita);
void ScrivereDimensioneGriglia(Partita *partita, int dimensione);
int LeggereValoreGriglia(Partita *partita, int r, int c);
void ScrivereValoreGriglia(Partita *partita, int r, int c, int valore);



char LeggereCarattereNome(Partita *partita, int posizione);



int LeggereDifficolta(Partita *partita);
void ScrivereDifficolta(Partita *partita, int difficolta);
int LeggereDimensioneImpostazioni(Partita *partita);
void ScrivereDimensioneImpostazioni(Partita *partita, int dimensione);

void LiberaMemoriaPartita(Partita *partita);
void Salvataggio(Partita *partita);
Partita *Caricamento(char nome[]);

#endif // PARTITA_H