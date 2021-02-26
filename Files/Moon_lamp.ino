
/************************ Adafruit IO Configuration *******************************/

#define IO_USERNAME    "....."
#define IO_KEY         "....."

/******************************* WIFI Configuration **************************************/

#define WIFI_SSID       "...."
#define WIFI_PASS       "...."

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/************************ Main Program Starts Here *******************************/
#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>

#define LED_PIN 0

int current = 0;
int last = 0;

AdafruitIO_Feed *command = io.feed("light-the-moon");

void setup() {
  
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);

  Serial.print("Connecting to Adafruit IO");
  io.connect();
  
  command->onMessage(handleMessage);

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  io.run();
}

void handleMessage(AdafruitIO_Data *data) {

  int command = data->toInt();

  if (command == 1){
    Serial.print("received <- ");
    Serial.println(command);
     digitalWrite(LED_PIN, HIGH);     
  } else {
    Serial.print("received <- ");
    Serial.println(command);
    digitalWrite(LED_PIN, LOW);
  }
}
