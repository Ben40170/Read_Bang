int capteur, led, result, maxValue;

//
// Paramètres
//
int seuil = 450; // seuil de déclenchement
int ledTime = 1000; // temps d'allumage de la LED en ms
int refreshDelay = 10; // Delais de raffraichissement de l'affichage
int pinNumberLed = 13; // numéro de la pin où est connecté la LED
int analogPinCaptor = A0;


void setup()
{
  // Configuration des paramètres et initialisation
  Serial.begin(9600);
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

  // Affichage
  printResult(result, maxValue);

  // Allumer la led en fonction du resultat et du seuil
  led(result, seuil, ledTime);

  delay(refreshDelay);
}


void led (int r, int s, int d) 
{
  // Allumer la led en fonction du resultat et du seuil
  if (r >= s)
  {
    digitalWrite(led, HIGH);
    delay(d);
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


