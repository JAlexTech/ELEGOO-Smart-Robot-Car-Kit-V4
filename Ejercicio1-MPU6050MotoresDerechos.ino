/*  Test TB6612 – ELEGOO Smart Robot Car V4.0
    Autor: José Alexander (basado en firmware original ELEGOO)
    Fecha: 2025-06-30
    Descripción: Solo motores derecho.
*/
int PWMA =5;      // Velocidad motores derecha
int AIN1 =7;     // Dirección motores derecha
int STBY =3;      // Stand-by del puente
int VELOCIDAD =180;   // Velocidad de ensayo (0-255)

void setup() {
   Serial.begin(9600);
   pinMode(PWMA, OUTPUT);
   pinMode(AIN1, OUTPUT);
   pinMode(STBY, OUTPUT);
   digitalWrite(STBY, HIGH);          // Activa el TB6612
   Serial.println("===== Test de motores iniciado =====");

}

void loop() {
   // 1. Motores derechos adelante 
  Serial.println("Motor 1 adelante");
  adelanteMD(VELOCIDAD);
   delay(1000);
  detener();
   delay(3000);
  atrasMD(VELOCIDAD);
   delay(1000);
  detener();
   delay(3000);
}
// Función  de control Adelante motores del lado derecho
void adelanteMD(int VELOCIDAD)   
{
 analogWrite(PWMA, VELOCIDAD);
 digitalWrite(AIN1, HIGH); 
}
// Función de control  Atras motores del lado derecho
void atrasMD(int VELOCIDAD)   
{
 analogWrite(PWMA, VELOCIDAD);
 digitalWrite(AIN1, LOW); 
}

void detener() {
  analogWrite(PWMA, 0);
  digitalWrite(STBY, LOW);      // Desactiva brevemente el puente
  delay(10);
  digitalWrite(STBY, HIGH);
  Serial.println(F("Motores detenidos"));
}
