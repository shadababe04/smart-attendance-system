#ifndef RFID_READER_H
#define RFID_READER_H

#include <MFRC522.h>
#include <SPI.h>

#define SS_PIN 21
#define RST_PIN 22
MFRC522 rfid(SS_PIN, RST_PIN);

void rfid_init() {
  SPI.begin();
  rfid.PCD_Init();
}

String rfid_read() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return "";
  }
  String tagID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    tagID += String(rfid.uid.uidByte[i], HEX);
  }
  rfid.PICC_HaltA();
  return tagID;
}

#endif