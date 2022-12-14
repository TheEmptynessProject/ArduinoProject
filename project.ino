#include <SPI.h>

#include <MFRC522.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

<<<<<<< HEAD
#include <Servo.h>
String array[20] = {
  "B9 35 B4 D4",
  "87 A2 92 60"
};
Servo servo;
MFRC522 mfrc522(10, 5);
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  pinMode(7,OUTPUT);
  servo.attach(3);
  pinMode(5, OUTPUT); //red
  pinMode(6, OUTPUT); //green
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  SPI.begin();
  mfrc522.PCD_Init();
  Wire.begin();
  lcd.begin();
}

void loop() {
  String xxx;
  int abc = 2;
  digitalWrite(5, LOW);
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
    for (int i = 0; i < (sizeof(array) / sizeof(String)); i++) {
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
    for (int i = 0; i < (sizeof(array) / sizeof(String)); i++) {
      if (xxx == array[i]) {
        access();
        break;
      } else {
        a++;
      }
    }
    if (a == (sizeof(array) / sizeof(String))) {
      denied();
      break;
    }
    break;
  }

}
String get_uid(byte * buffer, byte bufferSize, String bruh) {
  for (byte i = 0; i < bufferSize; i++) {
    bruh.concat(String(buffer[i] < 0x10 ? " 0" : " "));
    bruh.concat(String(buffer[i], HEX));
  }
  return bruh;
}
String readCard() {
  String bruh;
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.print(F("Card UID:"));
  bruh = get_uid(mfrc522.uid.uidByte, mfrc522.uid.size, bruh);
  bruh.toUpperCase();
  bruh.trim();
  Serial.println();
  Serial.print(bruh);
  Serial.println();
  return bruh;
}
void access() {
  lcd.clear();
  lcd.print("Access");
  lcd.setCursor(0, 1);
  lcd.print("Granted");
  digitalWrite(6, HIGH);  
  tone(7,10000);
  delay(50);
  noTone(7);
  servo.write(0);
  delay(2500);
  servo.write(90);
  digitalWrite(6, LOW);
  tone(7,10000); 
  delay(50);
  noTone(7);
}

void denied() {
  lcd.clear();
  lcd.print("Access");
  lcd.setCursor(0, 1);
  lcd.print("Denied");
digitalWrite(5, HIGH);  
  tone(7,500);
  delay(100);
  digitalWrite(5, LOW);  
  noTone(7);
  delay(100);
  digitalWrite(5, HIGH); 
  tone(7,500);
  delay(100);
  digitalWrite(5, LOW);  
  noTone(7);
  delay(100);
  digitalWrite(5, HIGH); 
  tone(7,500);
  delay(100);
  digitalWrite(5, LOW);  
  noTone(7);
}

void snake() {
    int len = 1;
    int gameBoard[16][2] = {}; //0=nothing, 1= snake, 2=food, 3=had fruit
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 2; j++) {
        gameBoard[i][j] = 0;
      }
    }
    struct pos {
      unsigned int X; // x position
      unsigned int Y; //y position
    };
    pos snake[32];
    snake[0].X=0;
    snake[0].Y=0;
    gameBoard[snake[0].X][snake[0].Y] = 1;
    pos fruit;
    fruit.X=random(0,16);
    fruit.Y=random(0,2);
    gameBoard[fruit.X][fruit.Y] = 2;
    lcd.clear();
    while (true) {
      if ((snake[0].X < 0) || (snake[0].Y < 0) || (snake[0].X >= 16) || (snake[0].Y >= 2)) {
        lcd.clear();
        lcd.print("Game Over2");
        break;
      }

      if (snake[0].X == fruit.X && snake[0].Y == fruit.Y) {
        len++;
        while (true){
          int randx = random(0,16);
          int randy = random(0,2);
            if (gameBoard[randx][randy] == 0){
                fruit.X = randx;
                fruit.Y = randy;
              break;
            }
        }
        gameBoard[fruit.X][fruit.Y] = 2;
      }

      if (len == 32) {
        lcd.clear();
        lcd.print("You won!");
        break;
      }
      for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 2; j++) {
          if (gameBoard[i][j] == 1) {
            for(int a=len; a>=1; a--){ 
lcd.setCursor(snake[a].X, snake[a].Y);
lcd.print("D");
snake[a] = snake[a-1];
}
            }
            else if (gameBoard[i][j] == 2) {
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
        while (Serial.available() == 0) {}
        int dir = Serial.parseInt();
        if (dir == 1) {
          snake[0].Y--;
        } else if (dir == 2) {
          snake[0].X--;
        } else if (dir == 3) {
          snake[0].Y++;
        } else if (dir == 4) {
          snake[0].X++;
        }
        lcd.clear();
      }
    }
=======
String array[] = { "B9 35 B4 D4",
	"87 A2 92 60" };

MFRC522 mfrc522(10, 8);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	pinMode(5, OUTPUT);	// red led
	pinMode(6, OUTPUT);	//green led
	Serial.begin(9600);
	while (!Serial);
	SPI.begin();
	mfrc522.PCD_Init();
	Wire.begin();
	lcd.begin();
}

void loop()
{
	String xxx;
	Serial.print("ADMIN\n");
	Serial.print("1. Add to access\n");
	Serial.print("2. Remove access\n");
	Serial.print("3. Print list\n");
	Serial.print("4. Test\n");
	while (Serial.available() == 0) {}

	int choice = Serial.parseInt();
	if (!mfrc522.PICC_IsNewCardPresent())
	{
		return;
	}

	if (!mfrc522.PICC_ReadCardSerial())
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

	switch (choice)
	{
		case 1:
			array[(sizeof(array) / sizeof(String)) + 1] = xxx;
			break;
		case 2:
			for (int i = 0; i < (sizeof(array) / sizeof(String)); i++)
			{
				if (xxx == array[i])
				{
					array[i] = "";
				}
			}

			break;
		case 3:
			for (int i = 0; i < (sizeof(array) / sizeof(String)); i++)
			{
				Serial.print(array[i]);
				Serial.println();
			}

			break;
		case 4:

			int a = 0;
			for (int i = 0; i < (sizeof(array) / sizeof(String)); i++)
			{
				if (xxx == array[i])
				{
					access();
				}
				else
				{
					a++;
				}
			}

			if (a == (sizeof(array) / sizeof(String)))
			{
				denied();
			}

			break;
	}
}

String get_uid(byte *buffer, byte bufferSize, String bruh)
{
	for (byte i = 0; i < bufferSize; i++)
	{
		bruh.concat(String(buffer[i] < 0x10 ? " 0" : " "));
		bruh.concat(String(buffer[i], HEX));
	}

	return bruh;
}

void access()
{
	lcd.clear();
	lcd.print("Access");
	lcd.setCursor(0, 1);
	lcd.print("Granted");
	digitalWrite(6, HIGH);
	delay(1500);
	digitalWrite(6, LOW);
}

void denied()
{
	lcd.clear();
	lcd.print("Access");
	lcd.setCursor(0, 1);
	lcd.print("Denied");
	digitalWrite(5, HIGH);
	delay(1500);
	digitalWrite(5, LOW);
}
>>>>>>> a5c2e330da27f67ce8f3a473f79984a1e7410cf9
