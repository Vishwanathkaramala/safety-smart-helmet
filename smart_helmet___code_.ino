#include <SPI.h>
#include <MFRC522.h>
#include <math.h>

const int xpin = A3; /* connect x_out of module to A1 of UNO board */
const int ypin = A2; /* connect y_out of module to A2 of UNO board */
const int zpin = A1;
 
#define SS_PIN 10 
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

const int alc = A0;
int alc_value;
const int mtr = 8;
const int buz = 7;
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Show your License");
  Serial.println();
  pinMode(alc, INPUT);
  pinMode(mtr, OUTPUT);
  pinMode(buz, OUTPUT);
}
void loop() 
{
  // Look for new cards
  int x_adc_value, y_adc_value, z_adc_value; 
  double x_g_value, y_g_value, z_g_value;
  double roll, pitch, yaw;
 
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "B2 B2 C8 2D") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Verified Your License");
    Serial.println();
    delay(3000);
    Serial.println("Put on Your Helmet and please blow");
    for(int i = 0; i <= 3000; i++)
    {
      delay(1);
    }
    alc_value = analogRead(alc);
    Serial.print("Alcohol Content:");
    Serial.print(alc_value);
    Serial.println("");
    if(alc_value >= 500)
    {
      Serial.println("Drunk and Drive is not Allowable");
    }
    else
    {
      Serial.println("Have a Safe and Happy Drive");
      digitalWrite(mtr, HIGH);
      delay(2000);
      digitalWrite(mtr, LOW);
      for(int i = 0; i <= 6000; i++)
      {
        delay(1);
      }
  
  int x_value = analogRead(xpin);
  int y_value = analogRead(ypin);
  int z_value = analogRead(zpin);
  
  Serial.print(x_value);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(y_value);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(z_value);
  Serial.print("\t");
  //lcd.setCursor(0,1);
  if((x_value <400  | x_value > 500)|(y_value < 400 | y_value > 500)|(z_value < 500 | z_value > 590))
  {
    Serial.println("Accident Happened");
    digitalWrite(buz, HIGH);
    delay(2000);
    digitalWrite(buz, LOW);
  }
  else
  {
    Serial.println("Enjoy Driving");
  } 
    }
  }
 
 else   {
    Serial.println("Your License is not valid");
    delay(3000);
  }
}
