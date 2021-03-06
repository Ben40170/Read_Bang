// Vue sur github


int capteur, led, result, maxValue;

//
// Paramètres
//
int seuil = 100; // seuil de déclenchement
int refreshDelay = 1; // Delais de raffraichissement de la boucle
int pinNumberLed = 13; // numéro de la pin où est connecté la LED
int analogPinCaptor = A0;
int note = 0x5A; // Note envoyée à chaque depassement de seuil
int velocity = 0x7F; // Velocité de la note envoyée à chaque depassement de seuil
int noteLength = 100; // Delay entre deux notes

// Définir la fonction du pgm
bool isTestMode = false;

int serialBaudsScreen = 9600; // Pour afficher à l'écran
int serialBaudsMidi = 31250; // Pour le port midi


void setup()
{
  // Configuration des paramètres et initialisation
  if (isTestMode) {
    // Configuration Affichage
    Serial.begin(serialBaudsScreen);
  } else {
    // Configarion Midi
    Serial.begin(serialBaudsMidi);
  }

  capteur = analogPinCaptor;
  led = pinNumberLed;
  result = 0;
  maxValue = 0;
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}


void loop()
{
  // Lire le capteur
  result = analogRead(capteur);

  // Déterminer valuer maximum reçue
  if (result > maxValue) {
    maxValue = result;
  }

  // En fonction du Mode
  if (isTestMode) {
    // en Mode TEST Afficher les valeurs
    printResult(result, maxValue);

    // Allumer
    ledIsOn(true);

    // Attendre
    delay(noteLength);

    // Eteindre
    ledIsOn(false);
  } else {
    // Mode pas test -> Mode Midi
    // Verifier seuil
    if (result >= seuil) {
      // Si le resultat est sup à la valeur de seuil
      // Envoyer note midi et allumer la lumière
      noteOn(0x90, note, velocity); // Note On
      ledIsOn(true);

      delay(noteLength);

      // Envoyer le note off et eteindre la lumiere
      noteOn(0x90, note, 0x00); // Note Off
      ledIsOn(false);
    }
  }


  delay(refreshDelay);
}


void ledIsOn (bool isOn)
{
  // Allumer la led en fonction du de isOn
  if (isOn)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
}


void printResult(int v, int m)
{
  // Afficher les Résultats
  Serial.print("Valeur: ");
  Serial.print(v);
  Serial.print(" Max: ");
  Serial.println(m);
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

