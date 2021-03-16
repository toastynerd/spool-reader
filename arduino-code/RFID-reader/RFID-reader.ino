/* RFID-reader.ino
   arduino code for spool-tracker to read RFID tags
   and send the UID of the tag out over the serial
   port. Based on the example code for the MRC522 chip.
   So far has been tested on a Teensy 4.0 but any arduino
   board should be able to handle it.
*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 rfid(SS_PIN, RST_PIN);

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial); //do nothing if no port opened
  SPI.begin();
  rfid.PCD_Init();
  delay(4); //needed for some boards
  rfid.PCD_DumpVersionToSerial();
} 

void loop() {
  if (! rfid.PICC_IsNewCardPresent()) {
    return;
  }
  Serial.write("new card present");
  if (! rfid.PICC_ReadCardSerial()) {
    return;
  }
  printHex(rfid.uid.uidByte, rfid.uid.size);
  delay(1000); //prevent a bunch of reads from a single tap, might end up doing this on the node side
}
