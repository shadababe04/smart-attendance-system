#ifndef FACE_RECOGNITION_H
#define FACE_RECOGNITION_H

#include <HTTPClient.h>

const char* faceRecognitionURL = "YOUR_FACE_RECOGNITION_SERVER_URL";

// Function to perform face recognition
bool face_recognition(uint8_t* image, size_t imageLen, String tagID) {
  HTTPClient http;
  http.begin(faceRecognitionURL);
  http.addHeader("Content-Type", "image/jpeg");
  http.addHeader("X-RFID", tagID);
  int httpCode = http.POST(image, imageLen);
  if (httpCode > 0) {
    String response = http.getString();
    http.end();
    return response.equals("Match");
  }
  http.end();
  return false;
}

#endif