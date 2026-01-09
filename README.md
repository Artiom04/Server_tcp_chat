# Socket Chat Server in C

Questo progetto implementa un **server TCP in C** che permette la comunicazione tra **due client** tramite socket.  
Il server accetta due connessioni e inoltra i messaggi ricevuti da un client all’altro (chat bidirezionale).

Il processo di comunicazione viene gestito tramite **fork()**, consentendo al server di creare un processo figlio dedicato alla gestione dei client.

---

## 📌 Funzionalità

- Server TCP basato su socket BSD
- Accetta **due client contemporaneamente**
- Comunicazione bidirezionale tra i client
- Utilizzo di `fork()` per la gestione concorrente
- Terminazione della comunicazione con il comando `QUIT`

---

## 🛠️ Requisiti

- Sistema operativo Unix/Linux
- Compilatore GCC
- Librerie standard:
  - `<sys/socket.h>`
  - `<netinet/in.h>`
  - `<unistd.h>`

---

## ⚙️ Compilazione

Usa il seguente comando per compilare il server:

```bash
gcc server_tcp_simple.c -o server_tcp_simple








