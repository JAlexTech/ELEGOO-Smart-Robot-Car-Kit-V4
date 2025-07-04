/*  Test TB6612 – ELEGOO Smart Robot Car V4.0
    Autor: José Alexander (basado en firmware original ELEGOO)
    Fecha: 2025-06-30
    Descripción: Control de motores simultaneos
*/

int PWMA =5;      // Velocidad motores derecha
int PWMB =6;     // Velocidad motores izquierda
int AIN1 =7;     // Dirección motores derecha
int BIN1 =8;      // Dirección motores izquierda
int STBY =3;      // Stand-by del puente
int VELOCIDAD =180;   // Velocidad de ensayo (0-255)

void setup() {
  Serial.begin(9600);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);          // Activa el TB6612
  Serial.println(F("===== Test de motores iniciado ====="));
}

void loop() 
{
   //Todos los motores
  Serial.println("Todos los motores adelante");
  adelante(VELOCIDAD );
    delay(1000);
  detenerTodo();
    delay(3000);
  Serial.println("Todos los motores atras");
  atras(VELOCIDAD );
    delay(1000);
  detenerTodo();
    delay(3000);
  Serial.println("Vehiculo izquierda");
  izquierda(VELOCIDAD );
    delay(1000);
  detenerTodo();
    delay(3000);
  Serial.println("Vehiculo derecha");
  derecha(VELOCIDAD );
    delay(1000);
  detenerTodo();
    delay(3000);
}
// Función  de control Adelante motores simulataneos
void adelante(int VELOCIDAD)   
{
  adelanteMD(VELOCIDAD );
  adelanteMI(VELOCIDAD );
}
// Función  de control Atras motores simulataneos
void atras(int VELOCIDAD)   
{
  atrasMD(VELOCIDAD );
  atrasMI(VELOCIDAD );
}
// Función  de control Derecha motores simulataneos
void derecha(int VELOCIDAD)   
{
    adelanteMI(VELOCIDAD );
    atrasMD(VELOCIDAD );
}
// Función  de control Izquierda motores simulataneos
void izquierda(int VELOCIDAD)   
{
    adelanteMD(VELOCIDAD );
    atrasMI(VELOCIDAD );
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

void detenerTodo() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  digitalWrite(STBY, LOW);      // Desactiva brevemente el puente
  delay(10);
  digitalWrite(STBY, HIGH);
  Serial.println("Motores detenidos");
}
