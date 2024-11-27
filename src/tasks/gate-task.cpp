#include <Arduino.h>


enum Stato {
  DISPONIBILE,
  APERTURA,
  ATTESA_CHIUSURA,
  // ... altri stati come PIENO, ALLARME_TEMPERATURA
};

Stato statoCorrente = DISPONIBILE;

const int PIN_SENSORE_UTENTE =  /* definire il pin */;
const int PIN_SENSORE_RIFIUTI = /* definire il pin */;
const int PIN_SPORTELLO = /* definire il pin */;
const int PIN_LED_VERDE = /* definire il pin */;
const int PIN_LED_ROSSO = /* definire il pin */;
const int PIN_PULSANTE_APERTURA = /* definire il pin */;
const int PIN_PULSANTE_CHIUSURA = /* definire il pin */;

const int TEMPO_SLEEP =  /* definire il tempo in millisecondi */;
const int TEMPO_MAX_APERTURA = /* definire il tempo in millisecondi */;
const int TEMPO_MESSAGGIO_RICEVUTO = /* definire il tempo in millisecondi */;
const int SOGLIA_DISTANZA_PIENO = /* definire la distanza in cm */;

unsigned long tempoUltimoUtente = 0;
bool sportelloAperto = false; 
Funzione setup():
void setup() {
  Serial.begin(9600); 
  pinMode(PIN_SENSORE_UTENTE, INPUT);
  pinMode(PIN_SENSORE_RIFIUTI, INPUT);
  pinMode(PIN_SPORTELLO, OUTPUT);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_ROSSO, OUTPUT);
  pinMode(PIN_PULSANTE_APERTURA, INPUT_PULLUP);
  pinMode(PIN_PULSANTE_CHIUSURA, INPUT_PULLUP);

  digitalWrite(PIN_LED_VERDE, HIGH); // Sistema disponibile all'avvio
  // ... inizializzazione LCD e altri componenti
}
Funzione step() per la gestione della FSM:
void step() {
  switch (statoCorrente) {
    case DISPONIBILE:
      // Controllare la presenza dell'utente
      if (digitalRead(PIN_SENSORE_UTENTE) == HIGH) {
        tempoUltimoUtente = millis(); 
      }
      // Andare in sleep se non c'è utente da TEMPO_SLEEP
      if (millis() - tempoUltimoUtente > TEMPO_SLEEP) {
        // ... logica per la modalità sleep 
      } 
      // Gestire la pressione del pulsante OPEN
      if (digitalRead(PIN_PULSANTE_APERTURA) == LOW) {
        apriSportello();
        statoCorrente = APERTURA;
      }
      break;

    case APERTURA:
      // Controllare se il pulsante CLOSE è premuto o se è scaduto TEMPO_MAX_APERTURA
      if (digitalRead(PIN_PULSANTE_CHIUSURA) == LOW || 
          millis() - tempoApertura > TEMPO_MAX_APERTURA) {
        chiudiSportello();
        statoCorrente = ATTESA_CHIUSURA;
      }
      // Controllare se il container è pieno
      if (leggiDistanzaRifiuti() < SOGLIA_DISTANZA_PIENO) {
        chiudiSportello();
        statoCorrente = PIENO; // Assumendo che PIENO sia uno stato definito
      }
      break;

    case ATTESA_CHIUSURA:
      // Visualizzare il messaggio "WASTE RECEIVED" per TEMPO_MESSAGGIO_RICEVUTO
      delay(TEMPO_MESSAGGIO_RICEVUTO);
      statoCorrente = DISPONIBILE;
      break;

    // ... altri casi per gli altri stati
  }
}
Funzioni di supporto:
void apriSportello() {
  // ... codice per aprire lo sportello (es. azionare un servomotore)
  sportelloAperto = true;
  tempoApertura = millis();
}

void chiudiSportello() {
  // ... codice per chiudere lo sportello
  sportelloAperto = false;
}

int leggiDistanzaRifiuti() {
  // ... codice per leggere la distanza dal sensore di rifiuti
}

// ... altre funzioni di supporto per la gestione del display, LED, ecc.
Chiamata alla funzione step() nel loop principale:
void loop() {
  step();
  // ... altro codice, come la gestione della comunicazione seriale
}