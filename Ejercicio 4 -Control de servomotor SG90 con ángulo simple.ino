/*  Test Servonotor SG90 – ELEGOO Smart Robot Car V4.0
    Autor: José Alexander (basado en firmware original ELEGOO)
    Fecha: 2025-06-30
    Descripción: Control de servomotor SG90 con ángulo simple
*/
#include <Servo.h> // encargada de la abstracción de la Modulación por ancho de pulsos.  
Servo miServoA; // Objeto encargado de administrar todas las órdenes a través de él
void setup() {
  miServoA.attach(10); // Pin 10 o Pin 11.

}

void loop() {
  miServoA.write(0);
  delay(1000);
  miServoA.write(90);
  delay(1000);
  miServoA.write(175);
  delay(1000);
}
