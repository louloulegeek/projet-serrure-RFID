#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
MFRC522 module_rfid(SS_PIN, RST_PIN);

int led_rouge = 14;
int led_verte = 15;


void setup() {
  pinMode(led_rouge, OUTPUT);
  pinMode(led_verte, OUTPUT);
  pinMode(buzzer, OUTPUT);
  SPI.begin();
  module_rfid.PCD_Init();
}

void loop() {
  if ( ! module_rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }

  if ( ! module_rfid.PICC_ReadCardSerial()) 
  {
    return;
  }

  String UID = "";

  for (byte i = 0; i < module_rfid.uid.size; i++) {
    UID.concat(String(module_rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    UID.concat(String(module_rfid.uid.uidByte[i], HEX));
  }

  UID.toUpperCase();

  if (UID.substring(1) == "********") 
  {
    digitalWrite(led_verte, HIGH);
    delay(2000);
    digitalWrite(led_verte, LOW);
  }

  else {
    digitalWrite(led_rouge, HIGH);
    delay(2000);
    digitalWrite(led_rouge, LOW);
  }
}
