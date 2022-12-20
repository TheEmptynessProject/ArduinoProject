//Import libraries needed
#include <SPI.h>

#include <MFRC522.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <Servo.h>

#include <Vector.h>


//Initiate [idfk know]
Servo servo;
MFRC522 mfrc522(10, 5);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//UIDS that have permission
String array[20] = {
  "B9 35 B4 D4",
  "87 A2 92 60"
};

//setup function
void setup() {
  pinMode(7, OUTPUT);
  servo.attach(3);
  pinMode(5, OUTPUT); //red led
  pinMode(6, OUTPUT); //green led
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  SPI.begin();
  mfrc522.PCD_Init();
  Wire.begin();
  lcd.begin();
}

//loop function
void loop() {
  String xxx;
  int abc = 2;
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  Serial.flush()
  Serial.print("ADMIN\n");
  Serial.print("1. Add to access\n");
  Serial.print("2. Remove access\n");
  Serial.print("3. Print list\n");
  Serial.print("4. Test\n");
  while (Serial.available() == 0) {}
  int choice = Serial.parseInt();

  switch (choice) {
  case 1:
    xxx = readCard();
    array[abc] = xxx;
    abc++;
    break;
  case 2:
    xxx = readCard();
    for (int i = 0; i < abc; i++) { //(sizeof(array) / sizeof(String))
      if (xxx == array[i]) {
        array[i] = "";
      }
    }
    abc--;
    break;
  case 3:
    for (int i = 0; i < 20; i++) {
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
    if (a == abc) {
      denied();
      break;
    }
    break;
  }

}
//String get_uid(byte * buffer, byte bufferSize, String bruh) {
//  for (byte i = 0; i < bufferSize; i++) {
//    bruh.concat(String(buffer[i] < 0x10 ? " 0" : " "));
//    bruh.concat(String(buffer[i], HEX));
//  }
//  return bruh;
//}
String readCard() {
  String bruh;
  while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {}
  Serial.println("Card UID:");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    bruh.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    bruh.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  bruh.toUpperCase().trim();
  Serial.println(bruh);
  return bruh;
}
void access() {
  lcd.clear();
  lcd.print("Access");
  lcd.setCursor(0, 1);
  lcd.print("Granted");
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

void denied() {
  lcd.clear();
  lcd.print("Access");
  lcd.setCursor(0, 1);
  lcd.print("Denied");
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

void snake() {
  int len = 0;
  int gameBoard[16][2] = {}; //0=nothing, 1= snake, 2=food
  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < 2; j++) {
      gameBoard[i][j] = 0;
    }
  }
  struct pos {
    unsigned int X; // x position
    unsigned int Y; //y position
  };
  pos snake[32]; //snake[0] == head, snek[i] == body
  snake[0].X = 0;
  snake[0].Y = 0;
  gameBoard[snake[0].X][snake[0].Y] = 1;
  pos fruit;
  fruit.X = random(0, 16);
  fruit.Y = random(0, 2);
  gameBoard[fruit.X][fruit.Y] = 2;
  lcd.clear();
  while (true) {
    //to add: check collsion with body
    if ((snake[0].X < 0) || (snake[0].Y < 0) || (snake[0].X >= 16) || (snake[0].Y >= 2)) { //check walls collision
      lcd.clear();
      lcd.print("Game Over");
      break;
    }

    if (snake[0].X == fruit.X && snake[0].Y == fruit.Y) {
      len++;
      for (int a = len; a >= 1; a--) {
      snake[a] = snake[a - 1]; //move body 
      }
      while (true) {
        int randx = random(0, 16);
        int randy = random(0, 2);
        if (gameBoard[randx][randy] == 0) {
          fruit.X = randx;
          fruit.Y = randy;
          gameBoard[fruit.X][fruit.Y] = 2;
          break;
        }
      }
    }

    if (len == 32) {
      lcd.clear();
      lcd.print("You won!");
      break;
    }
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 2; j++) {
        if (gameBoard[i][j] == 1) {
          for (int a = len; a >= 1; a--) {
            lcd.setCursor(snake[a].X, snake[a].Y);
            lcd.print("=");
          }
          lcd.setCursor(snake[0].X, snake[0].Y);
          lcd.print("D");
        } else if (gameBoard[i][j] == 2) {
          lcd.setCursor(fruit.X, fruit.Y);
          lcd.print("X");
        }
      }
    }
    Serial.print("SNAKE\n");
    Serial.print("1. W\n");
    Serial.print("2. A\n");
    Serial.print("3. S\n");
    Serial.print("4. D\n");
    String lastDir = dir;
    while (Serial.available() == 0) {}
    String dir = Serial.parseString();
    if ((dir == "1" || dir.toLowerCase() == "w") && (lastDir != "s" || lastDir != "3")) {
      snake[0].Y--;
    } else if ((dir == "2" || dir.toLowerCase() == "a") && (lastDir != "d" || lastDir != "4")) {
      snake[0].X--;
    } else if ((dir == "3" || dir.toLowerCase() == "s") && (lastDir != "w" || lastDir != "1")) {
      snake[0].Y++;
    } else if ((dir == "4" || dir.toLowerCase() == "d") && (lastDir != "a" || lastDir != "2")) {
      snake[0].X++;
    }
    Serial.flush()
    lcd.clear();
  }
}