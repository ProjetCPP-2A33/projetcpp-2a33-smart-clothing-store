#include <MFRC522.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// Pins pour le module RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);  // Crée une instance de MFRC522 pour la lecture du RFID

// Pins pour l'écran LCD
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);  // Création de l'objet LCD

// Déclaration du servo-moteur
Servo myServo;

// Variables pour l'ID et le nom
String rfidID = "";  // ID RFID accumulé
String fournisseurNom = "";  // Nom du fournisseur
String messageRecu = "";  // Message reçu de Qt

// Pin de la LED
int ledPin = 1;  // Utilisation de la pin 13 pour la LED

// Variables pour la gestion du délai
unsigned long previousMillis = 0;  // Stocke l'heure du dernier événement
const long interval = 7000;  // Intervalle de 7 secondes

void setup() {
  lcd.begin(16, 2);  // LCD 16x2
  Serial.begin(9600); // Initialiser la communication série
  lcd.print("Welcome Fournisseurs");

  // Initialisation du module RFID
  SPI.begin();
  rfid.PCD_Init();

  // Initialisation du servo
  myServo.attach(8);  // Attacher le servo à la pin 8
  myServo.write(0);   // Initialiser le servo à la position 0 (fermée)

  // Initialiser la LED
  pinMode(ledPin, OUTPUT);  // Définir la pin de la LED comme une sortie
}

void loop() {
  // Vérifier si une nouvelle carte RFID est présente
  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial()) {
      rfidID = "";  // Réinitialiser l'ID RFID accumulé à chaque nouvelle carte

      // Accumuler l'ID RFID complet
      for (byte i = 0; i < rfid.uid.size; i++) {
        rfidID += String(rfid.uid.uidByte[i], HEX);  // Ajouter l'ID en hexadécimal
      }

      rfidID.toUpperCase();  // Convertir en majuscules
      Serial.println(rfidID);  // Afficher l'ID complet sur le port série

      // Vérifier si des données Qt sont disponibles
      if (Serial.available() > 0) {
        fournisseurNom = Serial.readString();  // Lire la chaîne envoyée par Qt
        fournisseurNom.trim();  // Enlever les espaces inutiles

        // Afficher le message sur deux lignes
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Welcome Fournisseurs");  // Ligne 1
        lcd.setCursor(0, 1);
        lcd.print(fournisseurNom);  // Ligne 2 : Nom du fournisseur

        // Activer la LED et faire clignoter
        digitalWrite(ledPin, HIGH);  // Allumer la LED
        delay(500);                   // Attendre 500 ms
        digitalWrite(ledPin, LOW);   // Éteindre la LED
        delay(500);                   // Attendre 500 ms

        // Simuler l'ouverture et fermeture de la porte
        myServo.write(90);  // Ouvrir la porte
        delay(1000);
        myServo.write(0);   // Fermer la porte
      } else {
        // Si aucun fournisseur n'est trouvé
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Welcome Fournisseurs");  // Message par défaut
        lcd.setCursor(0, 1);
        lcd.print("Attente Donnees");
      }

      // Réinitialiser le compteur pour le délai non-bloquant
      previousMillis = millis();
    }
  }

  // Réafficher "Attendez un RFID" après 3 secondes
  if (millis() - previousMillis >= interval) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Attendez un RFID");
    previousMillis = millis();
  }

  // Lire les messages Qt
  if (Serial.available() > 0) {
    messageRecu = Serial.readString();
    messageRecu.trim();

    // Afficher les messages sur deux lignes
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome Fournisseurs");
    lcd.setCursor(0, 1);
    lcd.print(messageRecu.substring(0, 16));  // Ligne 2

    // Activer la LED et faire clignoter
    digitalWrite(ledPin, HIGH);  // Allumer la LED
    delay(500);                   // Attendre 500 ms
    digitalWrite(ledPin, LOW);   // Éteindre la LED
    delay(500);                   // Attendre 500 ms

    // Activer le servo après affichage
    myServo.write(90);  // Ouvrir la porte
    delay(1000);  // Maintenir l'ouverture pendant 1 seconde
    myServo.write(0);  // Fermer la porte

    delay(3000);  // Attente de 3 secondes
  }
}
