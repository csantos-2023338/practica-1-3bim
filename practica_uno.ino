#include <Adafruit_NeoPixel.h>
 
#define TRIGGER_PIN 10
#define ECHO_PIN 11
#define NUM_PIXELS 7
#define NEOPIXEL_PIN 9  
#define NEOPIXEL_COLOR_ON_rojo 0xFF0000
#define NEOPIXEL_COLOR_ON_verde 0x1FFF00  
 
int segmentos[] = {2, 3, 4, 5, 6, 7, 8};
int numeros[11][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1},  // 9
  {0, 0, 0, 0, 0, 0, 1}   // G
};
 
int contador = 0;
bool objeto_detectado = false;
 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
 
void setup() {
  Serial.begin(9600);
 
  pixels.begin();
 
  encenderNeoPixel_verde();
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 
  for (int i = 0; i < 7; i++) {
    pinMode(segmentos[i], OUTPUT);
    digitalWrite(segmentos[i], LOW);
  }
}
 
void loop() {
  long duration, distance_cm;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
 
  distance_cm = duration * 0.034 / 2;
 
  Serial.print("Distancia: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
 
  if (distance_cm >= 6 && distance_cm <= 10) {
    if (!objeto_detectado) {
      objeto_detectado = true;
 
      contador++;
     
      if (contador > 9) {
        contador = 9;
        mostrarCaracter('G');
        encenderNeoPixel_rojo();
      } else {
        mostrarNumero(contador);
      }
    }
  } else {
    objeto_detectado = false;
  }
 
  delay(100);
}
 
void mostrarNumero(int num) {
  for (int segmento = 0; segmento < 7; segmento++) {
    digitalWrite(segmentos[segmento], numeros[num][segmento]);
  }
}
 
void mostrarCaracter(char caracter) {
  switch (caracter) {
    case 'G':
      for (int segmento = 0; segmento < 7; segmento++) {
        digitalWrite(segmentos[segmento], numeros[10][segmento]);
      }
      break;
    default:
      for (int segmento = 0; segmento < 7; segmento++) {
        digitalWrite(segmentos[segmento], LOW);
      }
      break;
  }
}
 
void encenderNeoPixel_rojo() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, NEOPIXEL_COLOR_ON_rojo);
  }
  pixels.show();  
}
 
void encenderNeoPixel_verde() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    pixels.setPixelColor(i, NEOPIXEL_COLOR_ON_verde);
  }
  pixels.show();  
}
 
 