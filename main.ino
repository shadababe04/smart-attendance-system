#include "wifi_connect.h"
#include "rfid_reader.h"
#include "camera_capture.h"
#include "face_recognition.h"
#include "attendance_recorder.h"
#include "lcd_display.h"

void setup() {
  Serial.begin(115200);
  lcd_init();
  lcd_display("Initializing...");
  
  wifi_connect();
  rfid_init();
  camera_init();
  
  lcd_display("System Ready");
  delay(2000);
  lcd_display("Scan Your Card");
}

void loop() {
  String tagID = rfid_read();
  if (tagID != "") {
    lcd_display("ID: " + tagID);
    lcd_display("Capturing Face...", 1);
    
    camera_fb_t* fb = camera_capture();
    if (fb) {
      bool faceMatched = face_recognition(fb->buf, fb->len, tagID);
      if (faceMatched) {
        lcd_display("Face Matched");
        lcd_display("Recording...", 1);
        record_attendance(tagID);
      } else {
        lcd_display("Face Not Matched");
      }
      esp_camera_fb_return(fb);
    } else {
      lcd_display("Capture Failed");
    }
    delay(2000);
    lcd_display("Scan Your Card");
  }
}