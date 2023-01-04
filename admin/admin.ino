#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servo;
MFRC522 mfrc522(10, 9);
LiquidCrystal_I2C lcd(0x27, 16, 2);

String array[20] = {
  "B9 35 B4 D4"
};
int abc = 1;
void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  servo.attach(4);
  pinMode(5, OUTPUT); //red led
  pinMode(6, OUTPUT); //green led
  delay(100);
  SPI.begin();
  mfrc522.PCD_Init();
  Wire.begin();
  lcd.begin();
  
}

void loop() {
  String xxx;
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(500);
  Serial.print("ADMIN\n");
  Serial.print("1. Add to access\n");
  Serial.print("2. Remove access\n");
  Serial.print("3. Print list\n");
  Serial.print("4. Test\n");
  lcd.clear();
  lcd.print("Waiting for");
  lcd.setCursor(0, 1);
  lcd.print("Keycard");
  while (Serial.available() == 0) {}
  int choice = Serial.parseInt();

  switch (choice) {
  case 1:
    xxx = readCard();
    array[abc] = xxx;
    abc++;
    lcd.clear();
    lcd.print("Added to");
    lcd.setCursor(0, 1);
    lcd.print("Access");
    delay(3000);
    break;
  case 2:
    xxx = readCard();
    for (int i = 0; i < (sizeof(array) / sizeof(String)); i++) { //
      if (xxx == array[i]) {
        array[i] = "";
      }
    }
    abc--;
    lcd.clear();
    lcd.print("Removed from");
    lcd.setCursor(0, 1);
    lcd.print("Access");
    delay(3000);
    break;
  case 3:
    for (int i = 0; i < abc; i++) {
      Serial.println(array[i]);
    }
    break;
  case 4:
    xxx = readCard();
    int a = 0;
    for (int i = 0; i < abc; i++) {
      if (xxx == array[i]) {
        access();
        break;
      } else {
        a++;
      }
    }
    Serial.println(a);
    if (a == abc) {
      denied();
      break;
    }
    break;
  }

}
String readCard() {
  String bruh;
  while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
  }
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    bruh.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    bruh.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  bruh.toUpperCase();
  bruh.trim();
  return bruh;
}
void access() {
  lcd.clear();
  lcd.print("Access");
  lcd.setCursor(0, 1);
  lcd.print("Granted");
  for (int i = 0; i < 1; i++)
	{
		digitalWrite(6, HIGH);
		tone(7, 10000, 250);
		delay(150);
		digitalWrite(5, LOW);
	}
	servo.write(0);
	delay(2500);
	servo.write(90);
}

void denied() {
  lcd.clear();
  lcd.print("Access");
  lcd.setCursor(0, 1);
  lcd.print("Denied");
  for (int i = 0; i < 5; i++)
	{
		digitalWrite(5, HIGH);
		tone(7, 500, 100);
		delay(200);
		digitalWrite(5, LOW);
	}
}