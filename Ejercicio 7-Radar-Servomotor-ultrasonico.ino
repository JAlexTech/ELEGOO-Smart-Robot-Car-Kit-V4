/*  Test TB6612 – ELEGOO Smart Robot Car V4.0
    Autor: José Alexander (basado en firmware original ELEGOO)
    Fecha: 2025-06-30
    Descripción: Radar con Ultrasonico y servomotor
#include <Servo.h>
Servo miServoA; 
/* --- Configuración básica de pines --- */
int TRIG_PIN = 13;     // Pin que envía el pulso
int ECHO_PIN = 12;     // Pin que recibe el eco
long TIMEOUT_US = 30000UL; // 30 ms → ~5 m
long tPrev;// marca de tiempo
int pos=5; // posición de inicio para el servo
int dir=1; // dirección +1 para avanzar y -1 para retroceder.

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);          // Asegura nivel bajo inicial
  miServoA.attach(11); // Pin 10 o Pin 11.
  miServoA.write(pos);
  tPrev = millis(); // tiempo actual en milisegundo
}


void loop() {
escanearAngulo();
}

void escanearAngulo(){
     if(millis() - tPrev >= 20){    // condición  para saber si ha pasado el tiempo indicado
    pos += dir; // asignación de dirección 
    miServoA.write(pos); // indicar al servo el ángulo de movimiento
        int d = medirDistanciaCm(TRIG_PIN, ECHO_PIN); // Función para medir distacia
    Serial.print(pos);
     Serial.print(",");
     Serial.print(d);
     Serial.print(".");

    if(pos >= 175 || pos <= 5) dir = -dir;// limite del rango de movimiento
    tPrev = millis();// ajuste del tiempo
  }

}
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
