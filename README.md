# Sudoku in C

Un gioco del Sudoku da riga di comando implementato in linguaggio C.
Permette all'utente di creare nuove partite, generare schemi giocabili e interagire tramite console in lingua italiana.

## Struttura del Progetto

Il progetto utilizza un'organizzazione standard per i file sorgente e header:
- `src/`: Contiene i file sorgente `.c` (es. main.c, sudoku.c).
- `include/`: Contiene i file header `.h`.

## Prerequisiti

Per compilare il progetto avrai bisogno di:
- Un compilatore C (es. GCC o Clang).
- [CMake](https://cmake.org/) (versione 3.10 o superiore).

## Compilazione

Il progetto utilizza CMake per una compilazione multipiattaforma. Segui questi passaggi per compilarlo:

1. Crea la cartella di build e configura il progetto:
   ```bash
   cmake -S . -B build
   ```
2. Compila i file sorgente:
   ```bash
   cmake --build build
   ```

## Esecuzione

Dopo aver compilato correttamente, l'eseguibile si troverà nella cartella `build/`. 
Avvia il gioco con:

```bash
./build/sudoku
```
*(Su Windows potrebbe essere `./build/Debug/sudoku.exe` a seconda del generatore CMake).*

## Licenza

Questo progetto è distribuito sotto la licenza MIT. Vedi il file `LICENSE` per maggiori dettagli.
