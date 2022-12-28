#include <SPI.h>
#include <SoftwareSerial.h>
#include <MFRC522.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <Servo.h>


//Initiate [idfk know]
Servo servo;
MFRC522 mfrc522(10, 9); //SS_PIN, RST_PIN
LiquidCrystal_I2C lcd(0x27, 16, 2);

//UIDS that have permission
String array[20] = {
  "B9 35 B4 D4",
  "87 A2 92 60",
  "F1 B8 56 1B"
};

//setup function
void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(0, INPUT);//add
  pinMode(8, INPUT);//remove
  servo.attach(4);
  pinMode(5, OUTPUT); //red led
  pinMode(6, OUTPUT); //green led
  delay(100);
  SPI.begin();
  mfrc522.PCD_Init();
  Wire.begin();
  lcd.begin();
  
}

//loop function
void loop() {
  String xxx;
  int abc = 3; //how many uids in array
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
    xxx = readCard();
    int a = 0;
    for (int i = 0; i < abc; i++) {
      if (xxx == array[i]) {
        access(xxx);
        break;
      } else {
        a++;
      }
    }
    if (a == abc) {
      denied(xxx);
    }

}
String readCard() {
  String bruh;
  while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
  }
  if(digitalRead(0)){
    Serial.println("Removed");
  } else if (digitalRead(8)){
    Serial.println("Added");
  } else {
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    bruh.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    bruh.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  bruh.toUpperCase();
  bruh.trim();
  }
  return bruh;
}
void access(String auga) {
  lcd.clear();
  lcd.print("Access");
  lcd.setCursor(0, 1);
  lcd.print("Granted");

  Serial.print("Access Granted");
  Serial.print(",");
  Serial.print("UID:");
  Serial.print(auga);
  Serial.println();

  digitalWrite(6, HIGH);
  tone(7, 10000);
  delay(50);
  noTone(7);
  servo.write(0);
  delay(2500);
  servo.write(90);
  digitalWrite(6, LOW);
  tone(7, 10000);
  delay(50);
  noTone(7);
}

void denied(String auga) {
  lcd.clear();
  lcd.print("Access");
  lcd.setCursor(0, 1);
  lcd.print("Denied");

Serial.print("Access Denied");
  Serial.print(",");
  Serial.print("UID:");
  Serial.print(auga);
  Serial.println();

  digitalWrite(5, HIGH);
  tone(7, 500);
  delay(100);
  digitalWrite(5, LOW);
  noTone(7);
  delay(100);
  digitalWrite(5, HIGH);
  tone(7, 500);
  delay(100);
  digitalWrite(5, LOW);
  noTone(7);
  delay(100);
  digitalWrite(5, HIGH);
  tone(7, 500);
  delay(100);
  digitalWrite(5, LOW);
  noTone(7);
}