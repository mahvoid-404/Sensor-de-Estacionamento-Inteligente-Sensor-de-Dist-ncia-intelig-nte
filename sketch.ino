#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 13
#define MAX_DISTANCE 400

#define RED_PIN 14
#define GREEN_PIN 15
#define BLUE_PIN 16

unsigned long previousMillis = 0;
const long interval = 2000;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.println("Sistema Iniciado");
}

void loop() {
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    uint16_t distance = sonar.ping_cm();
    
    if (distance == 0) {
      lcd.setCursor(0, 0);
      lcd.print("Erro na leitura!");
      Serial.println("Erro na leitura do sensor");
      delay(2000);
      lcd.clear();
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Distancia: ");
      lcd.print(distance);
      lcd.print(" cm");
      Serial.print("Distancia: ");
      Serial.print(distance);
      Serial.println(" cm");
      
      if (distance < 20) {
        analogWrite(RED_PIN, 255);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 0);
        Serial.println("LED: Vermelho");
      } else if (distance <= 50) {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 255);
        analogWrite(BLUE_PIN, 0);
        Serial.println("LED: Verde");
      } else {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 255);
        Serial.println("LED: Azul");
      }
    }
  }
}
