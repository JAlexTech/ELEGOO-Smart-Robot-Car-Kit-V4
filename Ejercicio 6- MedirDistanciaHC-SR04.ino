/*  Test Ulstrasonico HC-SR04 – ELEGOO Smart Robot Car V4.0
    Autor: José Alexander (basado en firmware original ELEGOO)
    Fecha: 2025-06-30
    Descripción: Medir distancia en cm con el HC-SR04
*/
/* --- Configuración básica de pines --- */
int TRIG_PIN = 13;     // Pin que envía el pulso
int ECHO_PIN = 12;     // Pin que recibe el eco
long TIMEOUT_US = 30000UL; // 30 ms → ~5 m

/* ---------- SETUP ---------- */
void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);          // Asegura nivel bajo inicial
  Serial.println("HC-SR04 listo…");
}

/* ---------- LOOP ---------- */
void loop() {
  float d = medirDistanciaCm(TRIG_PIN, ECHO_PIN); // Función para medir distacia
  if (d > 0) {                          // Valor válido
    Serial.print(F("Distancia: "));
    Serial.print(d, 1);                 // Un decimal
    Serial.println(" cm");
  } else {
    Serial.println("Fuera de rango");
    }
      delay(100);                           // 10 lecturas por segundo
}

/* ---------- FUNCIÓN OPTIMIZADA ---------- */
float medirDistanciaCm(int trigPin, int echoPin) {
  /* 1. Pulso de disparo: 10 µs en alto */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  /* 2. Duración del eco con control de tiempo máximo */
  long dur = pulseIn(echoPin, HIGH, TIMEOUT_US);
  if (dur == 0) return -1.0;            // Sin eco → error/rango excedido
  /* 3. Conversión a cm (velocidad del sonido ~343 m/s a 20 °C) */
  float distancia = dur / 58.0;         // 58 µs ≈ 1 cm
  /* 4. Verificación de límites prácticos */
  if (distancia < 2 || distancia > 400) return -1.0;
  return distancia;
}
