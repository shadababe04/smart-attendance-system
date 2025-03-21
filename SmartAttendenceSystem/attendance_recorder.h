#ifndef ATTENDANCE_RECORDER_H
#define ATTENDANCE_RECORDER_H

#include <HTTPClient.h>

// Declare and define variables
const char* googleScriptURL = "YOUR_GOOGLE_SCRIPT_URL"; // Replace with your Google Script URL
const char* thingspeakAPIKey = "YOUR_THINGSPEAK_API_KEY"; // Replace with your ThingSpeak API Key

// Function declarations
void send_to_google_sheets(String tagID);
void send_to_thingspeak(String tagID);

// Function to record attendance
void record_attendance(String tagID) {
  send_to_google_sheets(tagID);
  send_to_thingspeak(tagID);
}

// Function to send data to Google Sheets
void send_to_google_sheets(String tagID) {
  HTTPClient http;
  http.begin(googleScriptURL); // Use the declared variable
  http.addHeader("Content-Type", "application/json");
  String payload = "{\"id\":\"" + tagID + "\",\"name\":\"User\"}";
  int httpCode = http.POST(payload);
  if (httpCode > 0) {
    Serial.println("Data sent to Google Sheets");
  }
  http.end();
}

// Function to send data to ThingSpeak
void send_to_thingspeak(String tagID) {
  HTTPClient http;
  String url = "https://api.thingspeak.com/update?api_key=" + String(thingspeakAPIKey) + "&field1=" + tagID; // Use the declared variable
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.println("Data sent to ThingSpeak");
  }
  http.end();
}

#endif