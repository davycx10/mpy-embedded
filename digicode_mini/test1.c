#include <Keypad.h>  // Inclut la bibliothèque Keypad

// Définir les connexions du clavier matriciel
const byte ROW_NUM    = 4;    // Nombre de lignes
const byte COLUMN_NUM = 4;    // Nombre de colonnes

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Pins auxquels le clavier est connecté
byte pin_rows[ROW_NUM] = {2, 3, 4, 5};  // Connexion des lignes
byte pin_column[COLUMN_NUM] = {6, 7, 8, 9};  // Connexion des colonnes

// Définir la broche du buzzer
const int buzzerPin = 27;  // Broche à laquelle le buzzer est connecté

// Créer un objet Keypad
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup() {
  // Serial.begin(9600);  // Initialiser la communication série
  pinMode(buzzerPin, OUTPUT);  // Définir la broche du buzzer en mode sortie
}

void loop() {
  char key = keypad.getKey();  // Obtenir la touche pressée
  if (key) {  // Si une touche est pressée
    // Serial.println(key);  // Afficher la touche dans le moniteur série

    // Faire sonner le buzzer
    tone(buzzerPin, 1000);  // Émettre un son de 1000 Hz
    delay(200);  // Sonner pendant 200 ms
    noTone(buzzerPin);  // Arrêter le son
  }
}
