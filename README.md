# Progetto Reti 2025
Repository che contiene il progetto di Reti Informatiche (Unipi, Ingegneria Informatica [IFO-L]) dell'anno accademico 2025/2026

# Progetto in breve
Il progetto rappresenta un'applicazione distribuita ibrida (C/S, P2P) per la gestione di un Kanban. I due principali attori sono:
- La lavagna: contiene i dati relativi alla kanban, ed effettua le operazioni per assegnare e confermare i task;
- Gli utenti: rappresentano la parte attiva del progett, sono quelli che effettuano direttamente operazioni sulla lavagna;

Tutti gli altri dettagli implementativi sono disponibili nella documentazione, allegata sia in formato .tex che .pdf.

# Test
Per utilizzare il progetto è necessario per prima cosa scaricarlo:
```bash
git clone https://github.com/Lucaseraaa/progetto_reti_2025
```
Successivamente va aperto e vanno compilati tutti moduli del codice, per semplificare il tutto viene utilizzato un makefile, è sufficiente il comando
```bash
make
```
Per avviare la lavagna il comando è:
```bash
./lavagna
```
e per avviare un utente
```bash
./utente <porta>
```
Con il valore di porta superiore a 5678.
