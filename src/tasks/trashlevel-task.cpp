#include "Arduino.h"
#include "LiquidCrystal_I2C.h"

// Definizioni dei pin
const int PIN_SENSORE_RIFIUTI = /* definire il pin */;
const int PIN_LED_VERDE = /* definire il pin */;
const int PIN_LED_ROSSO = /* definire il pin */;

// Soglia di riempimento
const int SOGLIA_DISTANZA_PIENO = /* definire la distanza in cm */;

// Definizione della FSM
enum StatoRifiuti {
  NON_PIENO,
  PIENO
};

StatoRifiuti statoCorrente = NON_PIENO;

// Inizializzazione LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); 

void setup() {
  Serial.begin(9600);
  pinMode(PIN_SENSORE_RIFIUTI, INPUT);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_ROSSO, OUTPUT);
  lcd.init();
  lcd.backlight();
}

void loop() {
  gestisciLivelloRifiuti();
  // ... altre funzioni del sistema
}

void gestisciLivelloRifiuti() {
  int distanza = leggiDistanzaRifiuti();

  switch (statoCorrente) {
    case NON_PIENO:
      if (distanza < SOGLIA_DISTANZA_PIENO) {
        statoCorrente = PIENO;
        digitalWrite(PIN_LED_VERDE, LOW);
        digitalWrite(PIN_LED_ROSSO, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Container Pieno!");
        // Invia messaggio di container pieno al dashboard
      }
      break;
    case PIENO:
      // Controlla lo stato del pulsante EMPTY sul dashboard
      if (/* pulsante EMPTY premuto */) {
        statoCorrente = NON_PIENO;
        digitalWrite(PIN_LED_ROSSO, LOW);
        digitalWrite(PIN_LED_VERDE, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Container Disponibile");
      }
      break;
  }
}

int leggiDistanzaRifiuti() {
  // Implementa la lettura del sensore di distanza
  // ...
}