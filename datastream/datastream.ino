#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo servo;
MFRC522 mfrc522(10, 9);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//UIDS that have permission
String array[20] = { 
  "B9 35 B4 D4" };
int abc = 1;
void setup()
{
	Serial.begin(9600);
	pinMode(7, OUTPUT);
	servo.attach(4);
	pinMode(5, OUTPUT);	//red led
	pinMode(6, OUTPUT);	//green led
	delay(100);
	SPI.begin();
	mfrc522.PCD_Init();
	Wire.begin();
	lcd.begin();
}

void loop()
{
	String xxx;
	int a = 0;
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	xxx = readCard();
	for (int i = 0; i < abc; i++)
	{
		if (xxx == array[i])
		{
			access(xxx);
			break;
		}
		else
		{
			a++;
		}
	}

	if (a == abc)
	{
		denied(xxx);
	}
}

String readCard()
{
	String bruh;
  lcd.clear();
  lcd.print("Waiting for");
  lcd.setCursor(0,1);
  lcd.print("Keycard");
	while (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {}

	for (byte i = 0; i < mfrc522.uid.size; i++)
	{
		bruh.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
		bruh.concat(String(mfrc522.uid.uidByte[i], HEX));
	}

	bruh.toUpperCase();
	bruh.trim();
	return bruh;
}

void access(String auga)
{
	lcd.clear();
	lcd.print("Access");
	lcd.setCursor(0, 1);
	lcd.print("Granted");
	Serial.print("Access Granted");
	Serial.print(",");
	Serial.print(auga);
	Serial.println();

	for (int i = 0; i < 1; i++)
	{
		digitalWrite(6, HIGH);
		tone(7, 10000, 250);
		delay(150);
		digitalWrite(6, LOW);
	}
	servo.write(0);
	delay(2500);
	servo.write(90);
}

void denied(String auga)
{
	lcd.clear();
	lcd.print("Access");
	lcd.setCursor(0, 1);
	lcd.print("Denied");
	Serial.print("Access Denied");
	Serial.print(",");
	Serial.print(auga);
	Serial.println();
  for (int i = 0; i < 5; i++)
	{
		digitalWrite(5, HIGH);
		tone(7, 500, 100);
		delay(200);
		digitalWrite(5, LOW);
	}
}