void setup() {
  pinMode(12, OUTPUT);
}

void loop() {
  digitalWrite(12, HIGH);
  delay(80);
  digitalWrite(12, LOW);
  delay(25);
  digitalWrite(12, HIGH);
  delay(800);
  digitalWrite(12, LOW);
  delay(25);
  


}
