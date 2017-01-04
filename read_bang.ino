int bangPin, led;

void setup() {
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  bangPin = A1;
  led=8;
}

void loop() {
  analogRead(bangPin);
  Serial.println(bangPin);
  delay(10);

}
