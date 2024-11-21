/*Descrizione degli Stati della FSM
La seguente macchina a stati finiti (FSM) descrive i diversi stati operativi del
sistema di smaltimento intelligente dei rifiuti liquidi pericolosi.
• AVAILABLE: Stato iniziale, il contenitore `e vuoto e disponibile per l’uso.
– Uscita: LED verde acceso, LCD visualizza ”PRESS OPEN TO EN-
TER WASTE”.
– Transizioni :
∗ Se viene rilevato un utente (PIR attivo), passa a USER DETECTED.
∗ Se viene premuto il pulsante OPEN, passa a WAITING FOR WASTE.
• USER DETECTED: Utente rilevato davanti al contenitore.
– Uscita: LCD mostra ”PRESS OPEN TO ENTER WASTE”.
– Transizioni :
∗ Se viene premuto OPEN, passa a WAITING FOR WASTE.
∗ Se l’utente si allontana (PIR inattivo per pi`u di Tsleep), torna a
AVAILABLE.
• WAITING FOR WASTE: Porta aperta per l’inserimento dei rifiuti.
– Uscita: La porta si apre (motore servo a 90°), LCD mostra ”PRESS
CLOSE WHEN DONE”.
– Transizioni :
∗ Se viene premuto CLOSE o se scade il timeout T1, passa a
WASTE RECEIVED.
∗ Se il contenitore diventa pieno (distanza misurata dal sonar ¡
D1), chiude la porta e passa a FULL.
• WASTE RECEIVED: Rifiuto inserito, porta chiusa.
– Uscita: La porta si chiude (motore a 0°), LCD mostra ”WASTE
RECEIVED” per T2 secondi.
1
– Transizioni :
∗ Dopo T2 secondi, torna a AVAILABLE (se non pieno).
∗ Se il contenitore `e pieno, passa a FULL.
• FULL: Il contenitore `e pieno e non pu`o pi`u accettare rifiuti.
– Uscita: LED rosso acceso, LCD mostra ”CONTAINER FULL”.
– Transizioni :
∗ Quando l’operatore svuota il contenitore tramite il dashboard,
passa a EMPTYING.
• EMPTYING: Fase di svuotamento del contenitore.
– Uscita: La porta si apre sul lato opposto (servo a -90°) per T3 secondi,
poi si richiude.
– Transizioni :
∗ Dopo T3 secondi, ritorna a AVAILABLE.
• ALARM: Problema rilevato, ad esempio per temperatura troppo alta.
– Uscita: LED rosso acceso, LCD mostra ”PROBLEM DETECTED”,
porta chiusa.
– Transizioni :
∗ Quando l’operatore preme RESTORE dal dashboard, ritorna a
AVAILABLE.
*/

#include "game_state.h"
#include <avr/sleep.h>
#include "Arduino.h"

#include "config.h"
#include "lcd.h"
#include "button.h"
#include "led.h"

void set_game_state(int state)
{
    change_state_time = millis();
    trash_state = state;
    switch (state)
    {
    case AVAILABLE:

        break;
    case USER_DETECTED:

        break;
    case WAITING FOR WASTE:

        break;
    case WASTE RECEIVED:

        break;
    case FULL:

        break;
    case EMPTYING:

        break;
    case ALARM:

        break;
    }
}