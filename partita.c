// partita.c

#include "partita.h"
#include <stdio.h>
#include <stdlib.h>
#include "scrittura.h"

int LeggereDimensioneGriglia(Partita *partita) {
  return partita->GrigliaPartita.dimensione;
}

void ScrivereDimensioneGriglia(Partita *partita, int dimensione) {
  partita->GrigliaPartita.dimensione = dimensione;
  return;
}

int LeggereValoreGriglia(Partita *partita, int r, int c) {
  return partita->GrigliaPartita.ValoriGriglia[r][c];
}

void ScrivereValoreGriglia(Partita *partita, int r, int c, int valore) {
  partita->GrigliaPartita.ValoriGriglia[r][c] = valore;
  return;
}

// Funzioni di accesso al campo NomePartita contenuto in Partita
char LeggereCarattereNome(Partita *partita, int posizione) {
  return partita->NomePartita[posizione];
}

// Funzioni di accesso al dato al tipo di dato Impostazioni contenuto in Partita
int LeggereDifficolta(Partita *partita) {
  return partita->ImpostazioniPartita.difficolta;
}

void ScrivereDifficolta(Partita *partita, int difficolta) {
  partita->ImpostazioniPartita.difficolta = difficolta;
  return;
}

int LeggereDimensioneImpostazioni(Partita *partita) {
  return partita->ImpostazioniPartita.dimensione;
}

void ScrivereDimensioneImpostazioni(Partita *partita, int dimensione) {
  partita->ImpostazioniPartita.dimensione = dimensione;
  return;
}

void LiberaMemoriaPartita(Partita *partita) {
  if (partita != NULL) {
    free(partita);
  }
}

void Salvataggio(Partita *partita) {
  FILE *file;
  char nomeFile[LUNGHEZZA_NOME_PARTITA + LUNGHEZZA_ESTENSIONE_FILE];

  snprintf(nomeFile, sizeof(nomeFile), "%s.bin", partita->NomePartita);
  file = fopen(nomeFile, "wb");
  if (file == NULL || fwrite(partita, sizeof(Partita), 1, file) != 1) {
    CentraSchermo("Salvataggio non riuscito");
  }
  fclose(file);
  return;
}

Partita *Caricamento(char nome[]) {
  Partita *partita;
  FILE *file;
  char nomeFile[LUNGHEZZA_NOME_PARTITA + LUNGHEZZA_ESTENSIONE_FILE];

  partita = (Partita *)malloc(sizeof(Partita));
  snprintf(nomeFile, sizeof(nomeFile), "%s.bin", nome);

  file = fopen(nomeFile, "rb");
  if (file == NULL || fread(partita, sizeof(Partita), 1, file) != 1) {
    free(partita);
    partita = NULL;
  }
  fclose(file);
  return partita;
}
