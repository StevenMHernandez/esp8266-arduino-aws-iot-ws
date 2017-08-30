/*
 * Copyright (C) 2017 Tomas Nilsson (joekickass)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 *    http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Dummy main file - to be deleted
 */
#include <Arduino.h>
#include <WiFiManager.h>

#include "config/ConnectionParams.h"
#include "mqtt/MqttClient.h"
#include "aws/AwsIotSigv4.h"
#include "aws/ESP8266DateTimeProvider.h"

WiFiManager wifiManager;

ESP8266DateTimeProvider dtp;
AwsIotSigv4 sigv4(&dtp);
ConnectionParams cp(sigv4);
WebSocketClientAdapter adapter(cp);
MqttClient client(adapter, cp);

void setup() {
  // Set up and wait for serial port to connect
  Serial.begin (115200);
  while (!Serial || !Serial.available());

  // Set up wifi
  wifiManager.autoConnect("mywemos");
  Serial.println("wifi connected... yeey :)");

  // Connect Mqtt Client
  int res = client.connect();
  Serial.printf("mqtt connect=%d\n", res);

  // Subscribe to 5 topics
  if (res == 0) {
    client.subscribe("t1", 1,
      [](const char* topic, const char* msg)
      { Serial.printf("Got msg '%s' on topic %s\n", msg, topic); }
    );

    client.subscribe("t2", 0,
      [](const char* topic, const char* msg)
      { Serial.printf("Got msg '%s' on topic %s\n", msg, topic); }
    );

    client.subscribe("t3", 1,
      [](const char* topic, const char* msg)
      { Serial.printf("Got msg '%s' on topic %s\n", msg, topic); }
    );

    client.subscribe("t4", 1,
      [](const char* topic, const char* msg)
      { Serial.printf("Got msg '%s' on topic %s\n", msg, topic); }
    );

    client.subscribe("t5", 0,
      [](const char* topic, const char* msg)
      { Serial.printf("Got msg '%s' on topic %s\n", msg, topic); }
    );
  }
}

void loop() {
  if (client.isConnected()) {

    client.publish("t1", "hello t1", 0, false);
    client.yield();

    client.publish("t2", "hello t2", 0, false);
    client.yield();

    client.publish("t3", "hello t3", 0, false);
    client.yield();

    client.publish("t4", "hello t4", 0, false);
    client.yield();

    client.publish("t5", "hello t5", 0, false);
    client.yield();

  } else {
    Serial.println("Not connected...");
    delay(2000);
  }
}
