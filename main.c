// main.c

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "partita.h"
#include "menu_parametri.h"
#include "sudoku.h"
#include "scrittura.h"


int main(void){
    srand(time(NULL));

    char scelta[10];    // la dimensione della stringa è arbitraria e viene impostata a 10 per sicurezza ed evitare overflow

    bool uscita;

    int i;
    int inputY; // variabile per la posizione Y dell'input

    Partita *partita;

    partita = NULL;
    uscita = false;

    while (!uscita)
    {
        system("cls");
        if (partita != NULL) {
            LiberaMemoriaPartita(partita);
            partita = NULL;
        }

        do {
            system("cls");
            CentraSchermo("se si vuole tornare alla schermata precedente scrivere");
            putchar('\n');
            CentraSchermo((char[]){INDIETRO, '\0'});
            putchar('\n');
            putchar('\n');
            CentraSchermo("SUDOKU");
            putchar('\n');
            putchar('\n');
            CentraSchermo("NUOVA PARTITA");
            putchar('\n');
            CentraSchermo("CONTINUA PARTITA");
            putchar('\n');

            inputY = OttieniPosizioneCursore().Y;
            InputCentratoRigaFissa("N/C: ", scelta, 1, inputY);
        } while (scelta[0] != 'N' && scelta[0] != 'C' && scelta[0] != INDIETRO);

        if (scelta[0] == INDIETRO) {
            // Conferma l'uscita dal programma
            do{
                system("cls");
                CentraSchermo("Sei sicuro di voler uscire? (S/N)");
                inputY = OttieniPosizioneCursore().Y;
                InputCentratoRigaFissa("S/N: ", scelta, 1, inputY);
            } while (scelta[0] != 'S' && scelta[0] != 'N');

            if (scelta[0] == 'S') {
                // Conferma l'uscita dal programma
                uscita = true;
                LiberaMemoriaPartita(partita);
                partita = NULL;
            } else {
                // Annulla l'uscita e torna al menu principale
                uscita = false;
                scelta[0] = '\0'; // Resetta la scelta per il ciclo principale
            }
        }else{
            while (scelta[0] != INDIETRO)
            {
                if (scelta[0] == 'N') {
                    system("cls");
                    MenuNuova(&partita);
                } else if (scelta[0] == 'C') {
                    system("cls");
                    MenuContinua(&partita);
                } else {
                    uscita = true;
                }

                if (partita == NULL){
                    scelta[0] = INDIETRO;
                } else {
                    while (!uscita)
                    {
                        Giocare(partita);
                        if (!GrigliaPiena(partita)) {
                            system("cls");
                            CentraSchermo("Vuoi salvare la partita? (S/N)");
                            InputCentrato("S/N: ", scelta, 1);

                            while (scelta[0] != 'S' && scelta[0] != 'N')
                            {
                                system("cls");
                                CentraSchermo("puoi inserire solo S (Si) o N (No)");
                                putchar('\n');
                                inputY = OttieniPosizioneCursore().Y;
                                InputCentratoRigaFissa("S/N: ", scelta, 1, inputY);
                            }

                            if (scelta[0] == 'S') {
                                system("cls");
                                Salvataggio(partita);
                                LiberaMemoriaPartita(partita);
                                partita = NULL;
                            } else {
                                system("cls");
                                LiberaMemoriaPartita(partita);
                                partita = NULL;
                            }


                        }else {
                            system("cls");
                            CentraSchermo("Hai completato il Sudoku!");
                            putchar('\n');
                            system("pause");
                        }

                        scelta[0] = INDIETRO; // Resetta la scelta per il ciclo principale
                        uscita = true;
                    }
                }
            }
            uscita = false; // Esce dal ciclo principale
        }

    }

    system("cls");
    CentraSchermo("Grazie per aver giocato!");
    putchar('\n');
    system("pause");
    return 0;
}
