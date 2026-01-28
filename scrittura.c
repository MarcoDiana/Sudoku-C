// scrittura.c

#include "scrittura.h"
#include "partita.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// Centratura dei testi e degli input

void CentraSchermo(char testo[]) {
  char *puntatoreTesto;
  char *fineRiga;
  char *puntoTaglio;
  char *limiteLinea;
  char *spazioTaglio;
  char *lettoreCaratteri;
  int lunghezzaRiga;
  int spaziPrima;

  puntatoreTesto = testo;
  while (*puntatoreTesto != '\0') {
    /* Determina dove finisce la riga corrente */
    fineRiga = puntatoreTesto;
    while (*fineRiga != '\0' && *fineRiga != '\n') {
      fineRiga++;
    }

    /* Calcola il punto di taglio iniziale */
    puntoTaglio = fineRiga;
    lunghezzaRiga = puntoTaglio - puntatoreTesto;

    /* Se la riga supera la larghezza, trova l’ultimo spazio entro il limite */
    if (lunghezzaRiga > CARATTERI_MAX) {
      limiteLinea = puntatoreTesto + CARATTERI_MAX;
      spazioTaglio = limiteLinea;
      while (spazioTaglio > puntatoreTesto && *spazioTaglio != ' ') {
        spazioTaglio--;
      }
      puntoTaglio = spazioTaglio;
      lunghezzaRiga = puntoTaglio - puntatoreTesto;
    }

    /* Calcola e stampa il padding di sinistra */
    spaziPrima = (CARATTERI_MAX - lunghezzaRiga) / 2;
    while (spaziPrima > 0) {
      putchar(' ');
      spaziPrima--;
    }

    /* Stampa i caratteri della riga centrata */
    lettoreCaratteri = puntatoreTesto;
    while (lettoreCaratteri < puntoTaglio) {
      putchar(*lettoreCaratteri);
      lettoreCaratteri++;
    }
    putchar('\n');

    /* Avanza oltre il testo stampato e salta spazi o newline */
    puntatoreTesto = puntoTaglio;
    while (*puntatoreTesto == ' ' || *puntatoreTesto == '\n') {
      puntatoreTesto++;
    }
  }
}

void InputCentrato(char *domanda, char *input, int lunghezza_input) {
  int totale;
  int spazi;
  int i;

  printf("\33[2K\r"); // cancella la riga corrente

  totale = strlen(domanda) + lunghezza_input;
  spazi = (CARATTERI_MAX - totale) / 2;
  i = 0;
  while (i < spazi) {
    putchar(' ');
    i++;
  }
  printf("%s", domanda);
  fflush(stdout); // assicura che la domanda sia stampata prima dell'input

  fgets(input, lunghezza_input + 2, stdin);

  return;
}

void InputCentratoRigaFissa(char *domanda, char *input, int lunghezza_input,
                            int riga) {
  VaiAllaRiga(riga);  // Posiziona il cursore sulla riga desiderata
  printf("\33[2K\r"); // Cancella la riga
  InputCentrato(domanda, input,
                lunghezza_input); // Usa la tua funzione invariata
}

// Gestione del cursore

COORD OttieniPosizioneCursore() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  return csbi.dwCursorPosition;
}

void VaiAllaRiga(int riga) {
  COORD coord;
  coord.X = 0;
  coord.Y = riga;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Correzione Stringhe

void RimuoviSpaziIniziali(char *str) {
  int i;
  int j;
  i = 0;
  // Trova il primo carattere non spazio
  while (str[i] == ' ') {
    i++;
  }
  // Sposta la stringa a sinistra
  if (i > 0) {
    j = 0;
    while (str[i]) {
      str[j] = str[i];
      i++;
      j++;
    }
  }
  return;
}

void RimuoviSpaziFinali(char *str) {
  int len = strlen(str);
  while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n')) {
    len--;
  }

  return;
}

// Mostra Sudoku

void MostraSudoku(Partita *partita) {
  int i;
  int j;
  int val; // valore della cella corrente
  int dimensioneGriglia;
  int dimensioneRiga;
  bool regioneSeparata; // indica se la regione è separata da una linea

  /* indica la riga da scrivere a schermo che poi verrà scritta
  con la funzione CentraSchermo così da semplificare il centramento
  della stringa */
  dimensioneRiga = (3 * LeggereDimensioneGriglia(partita)) + 3;
  /* la lunghezza della stringa sarà uguale all'espressione sopra riportata
  perchè davanti a ogni numero andrà uno spazio tranne al primo e per ogni
  numero ci devono essere a disposizione 2 posti per i numeri a doppia cifra. In
  più bisogna considerare che abbiamo bisogno di 4 caratteri iniziali per le
  coordinate delle righe, cioè avremo una composizione del tipo "cc| " c sta per
  cifra */

  dimensioneGriglia = LeggereDimensioneGriglia(partita);

  // stampa nome partita
  CentraSchermo(partita->NomePartita);
  putchar('\n');

  j = 0;
  // Calcola spazi iniziali per centrare la riga
  while (j < 3) { // 3 spazi per centrare la riga perchè sono i caratteri
                  // iniziali "cc |"
    putchar(' ');
    j++;
  }

  // Calcola spazi iniziali per centrare l'intestazione colonne
  j = 0;
  while (j < (CARATTERI_MAX - dimensioneRiga) / 2) {
    putchar(' ');
    j++;
  }

  // Intestazione colonne sottolineata
  putchar(' ');
  j = 0;
  while (j < dimensioneGriglia) {
    printf("\033[4m"); // Inizio del testo sottolineato
    if (j + 1 > 9) {
      putchar('1');
      putchar(((j + 1) % 10) + '0');
    } else {
      putchar(' ');
      putchar((j + 1) + '0');
    }
    printf("\033[0m"); // Fine del testo sottolineato
    if (j == sqrt(LeggereDimensioneGriglia(partita)) - 1 &&
        j != dimensioneGriglia - 1) {
      putchar(' ');
      putchar(' ');

    } else if (j != dimensioneGriglia - 1) {
      putchar(' ');
    }

    j++;
  }
  putchar(' ');
  putchar('\n');

  // Stampa righe della griglia
  i = 0;
  while (i < dimensioneGriglia) {
    // Centra la riga
    j = 0;
    while (j < (CARATTERI_MAX - dimensioneRiga) / 2) {
      putchar(' ');
      j++;
    }

    // Stampa la linea di separazione orizzontale tra le regioni
    if (i > 0 && i % (int)sqrt(LeggereDimensioneGriglia(partita)) == 0 &&
        !regioneSeparata) {
      j = 0;
      while (j < 4) {
        putchar(' ');
        j++;
      }

      j = 0;
      while (j < dimensioneGriglia) {
        printf("\033[4m");
        putchar(' ');
        putchar(' ');
        printf("\033[0m");
        putchar(' ');
        if (j == sqrt(LeggereDimensioneGriglia(partita)) - 1 &&
            j != dimensioneGriglia - 1) {
          putchar(' ');
        }
        j++;
        ; // 3 spazi per ogni cella perché "  |" e vengono sottolineati solo gli
          // spazi
      }

      regioneSeparata = true; // Indica che la regione è separata da una linea
    } else {
      regioneSeparata =
          false; // Indica che la regione non è separata da una linea
      // Numero riga
      if (i + 1 > 9) {
        putchar('1');
        putchar(((i + 1) % 10) + '0');
      } else {
        putchar(' ');
        putchar((i + 1) + '0');
      }
      putchar(' ');

      // Celle della riga
      j = 0;

      putchar('|');
      while (j < dimensioneGriglia) {
        val = LeggereValoreGriglia(partita, i, j);
        printf("\033[4m"); // Inizio del testo sottolineato
        if (val == 0) {
          putchar(' ');
          putchar(' ');
        } else if (val > 9) {
          putchar('1');
          putchar((val % 10) + '0');
        } else {
          putchar(' ');
          putchar(val + '0');
        }
        printf("\033[0m"); // Fine del testo sottolineato
        putchar('|');
        if (j == sqrt(LeggereDimensioneGriglia(partita)) - 1 &&
            j != dimensioneGriglia - 1) {
          putchar('|');
        }
        j++;
      }
      i++;
    }
    putchar('\n');
  }
  putchar('\n');
  putchar('\n');
  return;
}
