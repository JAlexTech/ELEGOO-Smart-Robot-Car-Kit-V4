/*  Test TB6612 – ELEGOO Smart Robot Car V4.0
    Autor: José Alexander (basado en firmware original ELEGOO)
    Fecha: 2025-06-30
    Descripción: Solo motores izquierdo.
*/
int PWMB =6;     // Velocidad motores izquierda
int BIN1 =8;      // Dirección motores izquierda
int STBY =3;      // Stand-by del puente
int VELOCIDAD =180;   // Velocidad de ensayo (0-255)

void setup() {
   Serial.begin(9600);
   pinMode(PWMB, OUTPUT);
   pinMode(BIN1, OUTPUT);
   pinMode(STBY, OUTPUT);
   digitalWrite(STBY, HIGH);          // Activa el TB6612
   Serial.println("===== Test de motores iniciado =====");

}

void loop() {
   // 1. Motores izquierdo adelante 
  Serial.println("Motores adelante");
  adelanteMI(VELOCIDAD);
   delay(1000);
  detener();
   delay(3000);
  atrasMI(VELOCIDAD);
   delay(1000);
  detener();
   delay(3000);
   }
// Función de control Adelante motores del lado izquierdo
void adelanteMI(int VELOCIDAD)   
{
 analogWrite(PWMB, VELOCIDAD);
 digitalWrite(BIN1, HIGH); 
}
// Función de control Atras motores del lado izquierdo
void atrasMI(int VELOCIDAD)   
{
 analogWrite(PWMB, VELOCIDAD);
 digitalWrite(BIN1, LOW); 
}

void detener() {
  analogWrite(PWMB, 0);
  digitalWrite(STBY, LOW);      // Desactiva brevemente el puente
  delay(10);
  digitalWrite(STBY, HIGH);
  Serial.println(F("Motores detenidos"));
}
