// Práctica 1 - Lectura LM35 con salida JSON y control de 3 LEDs por temperatura
const int LM35_PIN = A0;
const int led1 = 2; // LED Rojo
const int led2 = 3; // LED Amarillo
const int led3 = 4; // LED Verde

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(LM35_PIN);
  float temp = (sensorValue * 5.0 / 1024.0) * 100.0;

  // Formato JSON para integración futura
  Serial.print("{\"temperature\":");
  Serial.print(temp);
  Serial.println("}");

  delay(1000);

  // Reset de LEDs
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  // Lógica de activación por rangos
  if (temp <= 27.0) {
    digitalWrite(led1, HIGH);
  } else if (temp > 27.0 && temp <= 28.0) {
    digitalWrite(led2, HIGH);
  } else if (temp > 28.0 && temp <= 32.0) {
    digitalWrite(led3, HIGH);
  } else if (temp > 32.0) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }

  delay(1000);
}