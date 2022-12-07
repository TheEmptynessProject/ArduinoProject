#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

String array[] = {
"B9 35 B4 D4",
"87 A2 92 60"

};


MFRC522 mfrc522(10,8);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(5, OUTPUT); // red led
  pinMode(6, OUTPUT); //green led
  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init();
Wire.begin();
  lcd.begin();
}

/**
 * Main loop.
 */
void loop() {
String xxx;
      Serial.print("ADMIN\n");
Serial.print("1. Add to access\n");
Serial.print("2. Remove access\n");
Serial.print("3. Print list\n");
Serial.print("4. Test\n");
    while (Serial.available() == 0) {
}
    int choice = Serial.parseInt();
if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
      Serial.print(F("Card UID:"));
      xxx = get_uid(mfrc522.uid.uidByte, mfrc522.uid.size, xxx);
      xxx.toUpperCase();
      xxx.trim();
      Serial.println();
      Serial.print(xxx);
      Serial.println();

    switch (choice){
        case 1:
array[(sizeof(array) / sizeof(String))+1] = xxx;
break;
        case 2:
for(int i = 0; i<(sizeof(array) / sizeof(String)); i++){
  if(xxx==array[i]){
    array[i] = "";
  }
}
break;
        case 3:
for(int i = 0; i<(sizeof(array) / sizeof(String)); i++){
Serial.print(array[i]);
Serial.println();  
}
break;
        case 4:

int a = 0;
  for(int i = 0; i<(sizeof(array) / sizeof(String)); i++){
if (xxx == array[i]){
    access();
  }
  else {
    a++;
  }
  }
  if (a == (sizeof(array) / sizeof(String))){
    denied();
  }
      break;
    }
      
  
}

String get_uid(byte *buffer, byte bufferSize, String bruh) {
  for (byte i = 0; i < bufferSize; i++) {
    bruh.concat(String(buffer[i] < 0x10 ? " 0" : " "));
    bruh.concat(String(buffer[i], HEX));
  }
  return bruh;
}
void access(){
  lcd.clear();
  lcd.print("Access");
  lcd.setCursor(0,1);
  lcd.print("Granted");
  digitalWrite(6, HIGH);
  delay(1500);
  digitalWrite(6,LOW);
}

void denied(){
  lcd.clear();
  lcd.print("Access");
  lcd.setCursor(0,1);
  lcd.print("Denied");
  digitalWrite(5,HIGH);
  delay(1500);
  digitalWrite(5,LOW);
}