#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial BTSerial(2, 3); // RX | TX
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD I2C address 0x27
 
int Force_VAL = 0;
int temp = 0;
int btn = 0;
int buzz = 6;
 
void setup() {
  pinMode(A0, INPUT);
  pinMode(4, INPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);
  BTSerial.begin(9600);
  lcd.init();
  lcd.backlight();  
  lcd.setCursor(0, 0);
  lcd.print("Force Sensor");
  digitalWrite(buzz, LOW);
}
 
void loop() {
  Force_VAL = analogRead(A0);
  btn = digitalRead(4);
  Serial.println(btn);
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("Value:");
  lcd.print(Force_VAL);
 
  if (Force_VAL < 50 || Force_VAL > 200) { //Enter Force Value Range according to the item
    temp = 1;
    BTSerial.println("Alert: Force detected!");
  } else {
    BTSerial.println("Status: OK");
  }
 
  if (btn == 1) {
    temp = 0;
  }
 
  if (temp == 1) {
    digitalWrite(buzz, HIGH);
  }
 
  if (temp == 0) {
    digitalWrite(buzz, LOW);
  }

  delay(10);
}