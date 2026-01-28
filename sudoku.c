// sudoku.c

#include "sudoku.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// Funzioni per la gestione della partita

void Giocare(Partita *partita) {
  MostraSudoku(partita);
  bool continua; // indica se la partita deve continuare o è finita
  continua = true;
  while (continua == true) {
    if (GrigliaPiena(partita))
      continua = false;
    else
      continua = ChiediValore(partita);
  }
  return; /* indica che la partita è terminata o il giocatore non vuole salvare
  (true) o se la partita non è terminata e deve essere salvata (false) */
}

int ChiediValore(Partita *partita) {
  bool
      indietro; // indica quando il giocatore vuole tornare indietro e il perché
  int riga;
  int colonna;
  int valore;
  char scelta[10];
  // valore scelto dal giocatore, dimensione arbitraria per sicurezza ed evitare
  // overflow
  indietro = false;

  system("cls");
  MostraSudoku(partita);

  COORD inputPos = OttieniPosizioneCursore();
  int inputY = inputPos.Y;

  do {
    InputCentratoRigaFissa("Riga: ", scelta, 2, inputY);
    if (scelta[0] == INDIETRO) {
      indietro = true;
    } else {
      riga = atoi(scelta) - 1;
    }
  } while ((riga > LeggereDimensioneGriglia(partita) || riga < 0) &&
           scelta[0] != INDIETRO);

  if (indietro == 0) {
    do {
      InputCentratoRigaFissa("Colonna: ", scelta, 2, inputY);
      if (scelta[0] == INDIETRO) {
        indietro = true;
      } else {
        colonna = atoi(scelta) - 1;
      }
    } while ((colonna > LeggereDimensioneGriglia(partita) || colonna < 0) &&
             scelta[0] != INDIETRO);
  }

  if (indietro == 0) {
    do {
      InputCentratoRigaFissa("Valore: ", scelta, 2, inputY);
      if (scelta[0] == INDIETRO) {
        indietro = true;
      } else {
        valore = atoi(scelta);
      }
    } while ((valore > LeggereDimensioneGriglia(partita) || valore < 1) &&
             scelta[0] != INDIETRO);
  }

  if (!indietro && NumeroCorretto(partita, riga, colonna, valore)) {
    ScrivereValoreGriglia(partita, riga, colonna, valore);
  }

  return !indietro;
}

void InizializzazioneGriglia(Partita *partita) {
  int piene; // indica il numero di caselle da riempire
  int numero;
  int colonna;
  int riga;

  ScrivereDimensioneImpostazioni(partita, LeggereDimensioneGriglia(partita));

  if (LeggereDifficolta(partita) == DIFFICOLTA_MINIMA) {
    piene = FACILE * (pow(LeggereDimensioneGriglia(partita), 2));
  } else {
    if (LeggereDifficolta(partita) == DIFFICOLTA_MASSIMA) {
      piene = DIFFICILE * (pow(LeggereDimensioneGriglia(partita), 2));
    } else {
      piene = MEDIA * (pow(LeggereDimensioneGriglia(partita), 2));
    }
  }

  // inizializza la griglia a 0
  riga = 0;
  while (riga < LeggereDimensioneGriglia(partita)) {
    colonna = 0;
    while (colonna < LeggereDimensioneGriglia(partita)) {
      ScrivereValoreGriglia(partita, riga, colonna, 0);
      colonna++;
    }
    riga++;
  }

  // riempie con numeri casuali
  while (piene > 0) {
    colonna = (rand() % LeggereDimensioneGriglia(partita));
    riga = (rand() % LeggereDimensioneGriglia(partita));

    // Controllo se la cella è vuota prima di provare a riempirla
    if (LeggereValoreGriglia(partita, riga, colonna) == 0) {
      numero = 1 + (rand() % LeggereDimensioneGriglia(partita));
      if (NumeroCorretto(partita, riga, colonna, numero)) {
        ScrivereValoreGriglia(partita, riga, colonna, numero);
        piene--;
      }
    }
  }
  return;
}

bool NumeroCorretto(Partita *partita, int r, int c, int n) {
  // verifica che il numero non è ripetuto nella riga, colonna, eventuale
  // diagonale e regione
  return !(ControllaRiga(partita, r, n) || ControllaColonna(partita, c, n) ||
           ControllaDiagonale(partita, r, c, n) ||
           ControllaRegione(partita, r, c, n));
  // se anche uno restituiesce true tutta la funzione restituisce false
  // altrimenti restituisce true
}

bool ControllaRegione(Partita *partita, int r, int c, int n) {
  int i;
  int k;
  bool controllo;
  int Lregione; // indica il lato della regione
  controllo = false;

  Lregione = sqrt(LeggereDimensioneGriglia(partita));

  // Trova l'angolo in alto a sinistra della regione
  r -= r % Lregione;
  c -= c % Lregione;

  i = 0;
  while (i < Lregione && controllo == false) {
    k = 0;
    while (k < Lregione && controllo == false) {
      /* CORREZIONE: Aggiunto +i e +k agli indici per scorrere
         tutte le celle della regione, non solo la prima */
      if (LeggereValoreGriglia(partita, r + i, c + k) == n) {
        controllo = true;
      }
      k++;
    }
    i++;
  }

  return controllo;
}

bool ControllaDiagonale(Partita *partita, int r, int c, int n) {
  bool controllo;
  int i, j;
  controllo = false;

  // Controllo Diagonale Principale
  if (r == c) {
    i = 0;
    while (i < LeggereDimensioneGriglia(partita) && controllo == false) {
      if (LeggereValoreGriglia(partita, i, i) == n) {
        controllo = true;
      }
      i++;
    }
  }

  // Controllo Anti-Diagonale (indipendente, per gestire la cella centrale
  // correttamente)
  if (r + c == LeggereDimensioneGriglia(partita) - 1) {
    i = 0;
    j = LeggereDimensioneGriglia(partita) - 1;
    while (i < LeggereDimensioneGriglia(partita) && controllo == false) {
      if (LeggereValoreGriglia(partita, i, j) == n) {
        controllo = true;
      }
      i++;
      j--;
    }
  }
  return controllo;
}

bool ControllaColonna(Partita *partita, int c, int n) {
  bool controllo;
  int i;

  controllo = false;

  i = 0;
  while (i < LeggereDimensioneGriglia(partita) && controllo == false) {
    if (LeggereValoreGriglia(partita, i, c) == n) {
      controllo = true;
    }
    i++;
  }
  return controllo;
}

bool ControllaRiga(Partita *partita, int r, int n) {
  bool controllo;
  int i;
  i = 0;
  controllo = false;
  while (i < LeggereDimensioneGriglia(partita) && controllo == false) {
    if (LeggereValoreGriglia(partita, r, i) == n) {
      controllo = true;
    }
    i++;
  }
  return controllo;
}

bool GrigliaPiena(Partita *partita) {
  int riga;
  int colonna;
  bool verifica;

  verifica = true;
  riga = 0;
  while (riga < LeggereDimensioneGriglia(partita) && verifica == true) {
    colonna = 0;
    while (colonna < LeggereDimensioneGriglia(partita) && verifica == true) {
      if (LeggereValoreGriglia(partita, riga, colonna) == 0)
        verifica = false;
      colonna++;
    }
    riga++;
  }
  return verifica;
}
