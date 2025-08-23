#include <FastLED.h>
#define NUM_LEDS     1
#define DATA_PIN     4
#define BUTTON_PIN   2
#define BRIGHTNESS   128
#define DEBOUNCE_MS  60
CRGB leds[NUM_LEDS];

// Estados: 0 = Rojo, 1 = Naranja, 2 = Verde
int estado = 0;
bool iniciado = false;           // ¿ya se oprimió al menos una vez?
// Variables para lectura y antirrebote
int valorPulsador = HIGH;        // lectura cruda actual
int valorAnterior = HIGH;        // última lectura cruda
unsigned long tCambio = 0;       // tiempo de último cambio crudo
bool presionadoEstable = false;  // lectura estable actual (true = presionado)
bool presionadoPrev = false;     // lectura estable anterior

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // botón a GND (pulsado = LOW)
  // Estado inicial: no se ha oprimido → azul
  leds[0] = CRGB::DeepSkyBlue;
  FastLED.show();
  Serial.println("esperando accion");
}

void loop() {
  // -------- Lectura con antirrebote (debounce) --------
  int lectura = digitalRead(BUTTON_PIN);

  if (lectura != valorAnterior) {          // cambio "bruto"
    tCambio = millis();
    valorAnterior = lectura;
  }

  if ((millis() - tCambio) > DEBOUNCE_MS) {
    // Fijar lectura estable (con INPUT_PULLUP, LOW = presionado)
    if (lectura == LOW) {
      presionadoEstable = true;
    } else {
      presionadoEstable = false;
    }

    // -------- Logs estilo solicitado con if (valorPulsador == HIGH) / else --------
    // (Imprime solo cuando cambia el estado estable para no saturar el puerto serie)
    if (presionadoEstable != presionadoPrev) {
      valorPulsador = lectura;            // reflejar lectura cruda
      if (valorPulsador == HIGH) {
        Serial.println(" esperando accion");
      } else {
        Serial.println(" pulsado");
      }
    }

    // -------- Detección de flanco (avanza solo una vez por pulsación) --------
    if (presionadoEstable == true && presionadoPrev == false) {
      if (iniciado == false) {
        iniciado = true;      // primera pulsación: entra al estado 0 (rojo)
        estado = 0;
      } else {
        estado = (estado + 1) % 3;   // 0→1→2→0...
      }
    }

    presionadoPrev = presionadoEstable;
  }

  // -------- Salida final de color usando SOLO if/else --------
  if (iniciado == false) {
    // Aún no se ha oprimido: azul
    leds[0] = CRGB::DeepSkyBlue;
  } else {
    if (estado == 0) {
      leds[0] = CRGB::Red;        // Estado 1: rojo
      // colocar aqui cualquier accion que dese realizar en la opicón 1.
      //Lo ideal es unicamente crear una función para no saturar de codigo esta parte.

    } else {
      if (estado == 1) {
        leds[0] = CRGB::Orange;   // Estado 2: naranja
          // colocar aqui cualquier accion que dese realizar en la opicón 2.
          //Lo ideal es unicamente crear una función para no saturar de codigo esta parte.
      } else {
        leds[0] = CRGB::Green;    // Estado 3: verde
          // colocar aqui cualquier accion que dese realizar en la opicón 3.
          //Lo ideal es unicamente crear una función para no saturar de codigo esta parte.
      }
    }
  }

  FastLED.show();
}
