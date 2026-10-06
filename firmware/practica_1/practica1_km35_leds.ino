const int LM35_PIN = A0;
const int led1 = 2; // LED Rojo / Indicador 1
const int led2 = 3; // LED Amarillo / Indicador 2
const int led3 = 4; // LED Verde / Indicador 3


void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}
void loop() {
 // Leer el valor analógico del sensor LM35
 int sensorValue = analogRead(LM35_PIN);
 // Convertir el valor analógico a temperatura en grados Celsius
 float temp = (sensorValue * 5.0 / 1024.0) * 100.0;
 // Imprimir los datos en formato JSON
 Serial.print("{");
 Serial.print("\"temperature\":");
 Serial.print(temp);
 Serial.println("}");
 delay(1000); // Esperar 5 segundos antes de la siguiente lectura
 // Apagar todos los LEDs antes de evaluar la condición
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  // Evaluar reglas de la guía
  if (temp <= 27.0) {
    digitalWrite(led1, HIGH);
  } 
  else if (temp >= 27.0 && temp <= 28.0) {
    digitalWrite(led2, HIGH);
  } 
  else if (temp >= 28.0 && temp <= 32.0) {
    digitalWrite(led3, HIGH);
  } 
  else if (temp >= 32.0) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }

  delay(1000);
}
