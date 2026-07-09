// menu_parametri.c

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "menu_parametri.h"
#include "partita.h"
#include "sudoku.h"

void MenuNuova(Partita **partita) {
  char scelta;
  char scelta_str[10]; // la dimensione della stringa è arbitraria e viene
                       // impostata a 10 per sicurezza ed evitare overflow
  int i;
  int inputY; // variabile per la posizione Y dell'input

  *partita = (Partita *)malloc(sizeof(Partita));
  while (*partita == NULL) {
    *partita = (Partita *)malloc(sizeof(Partita));
  }

  scelta_str[0] = '\0';
  scelta = '\0';

  i = 0;
  while (scelta_str[0] != 'S' && scelta_str[0] != 'N' &&
         scelta_str[0] != INDIETRO) {
    CentraSchermo("Sai gia' come giocare? (S/N)");
    inputY = OttieniPosizioneCursore().Y;
    InputCentratoRigaFissa("S/N: ", scelta_str, 1, inputY);
  }
  scelta = scelta_str[0];

  if (scelta == INDIETRO) {
    LiberaMemoriaPartita(*partita);
    *partita = NULL;
  } else {
    if (scelta == 'N') {
      system("cls");
      CentraSchermo(
          "Durante la partita ti ritroverai con una griglia con il lato della "
          "dimensione che selezionerai con un certo numero di caselle "
          "(asseconda della difficolta') con dei valori preinseriti. \nIl tuo "
          "obbiettivo e' di rimpire la griglia con numeri da 1 alla dimensione "
          "che sceglierai stando attento che ogni riga, colonna, diagonale "
          "principale e regione (aree della dimensione 2x2 o 3x3 o 4x4 "
          "all'interno del sudoku) non abbia ripetizioni. \n Per selezionare "
          "la cella bastera' inserire la riga e la colonna a cui vuoi "
          "assegnare il valore e poi scrivere il numero che ci vuoi inseirire "
          "e, se corretto, verra' inserito.");
      putchar('\n');
      system("pause");
    }

    system("cls");
    CentraSchermo("solo nella selezione del nome puoi tornare indietro "
                  "premendo INVIO senza inserire nulla");
    putchar('\n');
    CentraSchermo("NOME PARTITA max caratteri");
    putchar('\n');
    i = 0;
    while (i < (CARATTERI_MAX / 2)) {
      putchar(' ');
      i++;
    }
    printf("%d", LUNGHEZZA_NOME_PARTITA - 1);
    putchar('\n');
    putchar('\n');
    inputY = OttieniPosizioneCursore().Y;
    putchar('\n');
    putchar('\n');
    putchar('\n');
    CentraSchermo("Gli spazi prima del nome non saranno considerati");
    putchar('\n');
    CentraSchermo("Se inserisci solo spazzi e poi invio tornerai indietro");
    InputCentratoRigaFissa("Nome della partita: ", (*partita)->NomePartita,
                           LUNGHEZZA_NOME_PARTITA, inputY);

    RimuoviSpaziIniziali((*partita)->NomePartita);
    RimuoviSpaziFinali((*partita)->NomePartita);

    if (LeggereCarattereNome((*partita), 0) == PRECEDENTE) {
      /* Se il nome è vuoto, libera la memoria e torna indietro.
      Questo evita anche problemi con il nome vuoto al momento della creazione
      del file di salvataggio */
      LiberaMemoriaPartita(*partita);
      *partita = NULL;
    } else {

      // Inserimento parametri
      InputParametri(partita);

      if (*partita != NULL)
        InizializzazioneGriglia(*partita);
      else {
        LiberaMemoriaPartita(*partita);
        *partita = NULL;
      }
    }
  }
  return;
}

void MenuContinua(Partita **partita) {
  char nome[LUNGHEZZA_NOME_PARTITA];
  bool trovato; // indica se la partita cercata è stata trovata

  nome[0] = '\0'; // inizializza la stringa nome
  trovato = false;
  *partita = NULL;

  while (trovato == false && nome[0] != PRECEDENTE) {
    system("cls");
    CentraSchermo(
        "NOME PARTITA max 50 caratteri \n (non inserire come primo carattere ");
    CentraSchermo((char[]){PRECEDENTE, '\0'});
    CentraSchermo("o tornerai indietro): ");
    printf("\n\n\n");
    CentraSchermo("nome della partita che si vuole continuare: ");
    fgets(nome, sizeof(nome), stdin);

    RimuoviSpaziIniziali(nome);
    RimuoviSpaziFinali(nome);

    if (nome[0] == PRECEDENTE) {
      CentraSchermo("nome non valido");
    } else {
      nome[strcspn(nome, "\n")] = '\0'; // rimuove il carattere di nuova linea
      *partita = Caricamento(nome);
    }

    if (*partita != NULL) {
      trovato = true;
    } else {
      CentraSchermo("partita non trovata, ritentare");
    }
  }
  if (nome[0] == PRECEDENTE) {
    if (*partita != NULL) {
      LiberaMemoriaPartita(*partita);
      *partita = NULL;
    }
  }
  return;
}

void InputParametri(Partita **partita) {
  char scelta_str[10]; // la dimensione della stringa è arbitraria e viene
                       // impostata a 10 per sicurezza ed evitare overflow
  int inputY;

  system("cls");

  inputY = OttieniPosizioneCursore().Y;

  do {
    InputCentratoRigaFissa("Dimensioni (4, 9, 16): ", scelta_str, 2, inputY);
    if (scelta_str[0] == INDIETRO) {
      LiberaMemoriaPartita(*partita);
      *partita = NULL;
    } else {
      ScrivereDimensioneGriglia(*partita, atoi(scelta_str));
    }
  } while (scelta_str[0] != INDIETRO && VerificaDimensioni(*partita) == false);

  if (*partita != NULL && scelta_str[0] != INDIETRO) {
    ScrivereDimensioneImpostazioni(*partita,
                                   LeggereDimensioneGriglia(*partita));

    system("cls");

    inputY = OttieniPosizioneCursore().Y;

    do {
      InputCentratoRigaFissa("Difficolta' (0, 1 , 2): ", scelta_str, 2, inputY);
      if (scelta_str[0] == INDIETRO) {
        LiberaMemoriaPartita(*partita);
        *partita = NULL;
      } else {
        ScrivereDifficolta(*partita, atoi(scelta_str));
      }
    } while (scelta_str[0] != INDIETRO &&
             VerificaDifficolta(*partita) == false);
  }

  return;
}

bool VerificaDimensioni(Partita *partita) {
  bool verifica;

  if (LeggereDimensioneGriglia(partita) == DIM_MINIMA)
    verifica = true;

  else if (LeggereDimensioneGriglia(partita) == DIM_MEDIA)
    verifica = true;

  else if (LeggereDimensioneGriglia(partita) == DIM_MASSIMA)
    verifica = true;

  else
    verifica = false;

  return verifica;
}

bool VerificaDifficolta(Partita *partita) {
  bool verifica;

  if (LeggereDifficolta(partita) <= DIFFICOLTA_MASSIMA &&
      LeggereDifficolta(partita) >= DIFFICOLTA_MINIMA)
    verifica = true;

  else
    verifica = false;

  return verifica;
}
