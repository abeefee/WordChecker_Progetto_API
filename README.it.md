# 🔍 WordChecker - Lexical Filtering - Progetto API 2021/22

*You can read this also in [English](readme.md)*

> **Nota Accademica:** Questo progetto è stato sviluppato come Prova Finale per il corso di *Algoritmi e Principi dell'Informatica* del Politecnico di Milano (Anno Accademico 2021/22), con voto finale **30/30 e lode**. Il codice è stato valutato tramite un correttore automatico basato su severi vincoli di tempo di esecuzione e di utilizzo della memoria.

### Descrizione del Progetto
WordChecker è un software in linguaggio C (C11) per il controllo, la validazione e il filtraggio di dizionari di parole, con una logica simile a quella del gioco *Wordle*. 

Il sistema riceve un dizionario di base e confronta parole di tentativo con una parola di riferimento. Sulla base dell'esito del confronto, il motore **apprende dinamicamente dei vincoli** (presenza, assenza, posizione esatta o quantità minima/esatta di specifici caratteri) ed è in grado di filtrare e stampare in ordine lessicografico solo le parole del dizionario ancora compatibili con tali vincoli.

### Caratteristiche Tecniche & Sfide Affrontate
Essendo un progetto focalizzato sull'efficienza algoritmica, l'implementazione ha richiesto un'attenta progettazione delle strutture dati per minimizzare i tempi di ricerca e l'occupazione della memoria:

* **Struttura Dati Ibrida:** Implementazione di un Albero Binario di Ricerca (BST) ibridato con una Lista Concatenata. Questo approccio garantisce una ricerca efficiente e permette un'iterazione sequenziale veloce per stampare il dizionario in ordine lessicografico.
* **Smart Filtering (Cancellazione Logica):** Invece di distruggere o ribilanciare l'albero durante i filtraggi, ogni nodo del dizionario è dotato di un flag `inPartita`. Le parole scartate vengono semplicemente disattivate a livello logico. Questo azzera i tempi di deallocazione e ricostruzione dell'albero tra una partita e l'altra.
* **Operazioni su Stringhe Custom:** Creazione di una funzione `faststrcmp` personalizzata per massimizzare le performance di confronto rispetto alla libreria standard, ottimizzando i milioni di attraversamenti dell'albero necessari.
* **Gestione Dinamica dei Vincoli:** Utilizzo di una Lista Concatenata secondaria (`node_v`) per tracciare storicamente i vincoli di gioco appresi, permettendo di valutare e filtrare istantaneamente eventuali nuove parole inserite a partita in corso.

### Tecnologie e Profiling
* **Linguaggio:** C (Standard C11, VLA supportati)
* **Compilatore (consigliato):** GCC
* **Testing & Profiling (Suite Valgrind):** 
  * **Memcheck:** Utilizzato per garantire l'assenza assoluta di memory leaks nella gestione dinamica della memoria.
  * **Callgrind:** Utilizzato per profilare i tempi di esecuzione, identificare i colli di bottiglia e ottimizzare le performance (es. l'attraversamento dell'albero).
  * **Massif:** Utilizzato per profilare e ottimizzare l'occupazione dell'heap memory, rientrando nei severi vincoli spaziali richiesti dal correttore.

### Compilazione ed Esecuzione
Il progetto non necessita di dipendenze esterne. Per compilarlo:

```bash
gcc -Wall -Werror -O2 -g3 src/wordchecker.c -o wordchecker
```

Per eseguire i test:

```bash
./wordchecker < tests/test1.txt > my_output.txt