#include <ESP8266WiFi.h> //Test neuer Verbindungsmethode
#include <PubSubClient.h>
#include <ArduinoOTA.h>

// Konstanten für Konfiguration
#define WIFI_SSID "LAB"
#define WIFI_PASSWORD "labwifi1"
#define MQTT_SERVER "192.168.20.174"
#define MQTT_PORT 1883
#define MQTT_USER ""         
#define MQTT_PASSWORD ""
#define ESP_HOSTNAME "ESP8266_MQTT_Test_gelb" 
#define OUT_TOPIC "esp8266gelb/outtopic" 
#define IN_TOPIC "esp8266gelb/intopic"

// Pin-Definitionen für ESP8266
#define LED_PIN D1     // GPIO5 (D1 auf esp8266)
#define BUTTON_PIN D2  // GPIO4 (D2 auf esp8266)

// Konstanten für Timing
const unsigned long BUTTON_DEBOUNCE_DELAY = 50;  // Entprellverzögerung in Millisekunden
const unsigned long MQTT_RECONNECT_DELAY = 5000; // Verzögerung zwischen Reconnect-Versuchen

// Globale Variablen
WiFiClient espClient;  
PubSubClient mqttClient(espClient);
String clientId = "ESP8266-gelb-" + String(random(0xffff), HEX);
int buttonState = HIGH;  // Geändert zu HIGH wegen INPUT_PULLUP
int lastButtonState = HIGH;  // Geändert zu HIGH wegen INPUT_PULLUP
unsigned long lastDebounceTime = 0;

void setup() {  
  Serial.begin(115200); //evtl zu viel Standart:9600 //prüfen
  setup_wifi();
  setup_ota();
  setup_mqtt();
  
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Aktiviert den internen Pull-up-Widerstand
}  
   
void loop() {  
  ArduinoOTA.handle();
  
  if (!mqttClient.connected()) {  
    reconnect_mqtt();  
  }
  mqttClient.loop();
  
  handle_button();
}   
   
void setup_wifi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}  

void setup_ota() {
  ArduinoOTA.setHostname(ESP_HOSTNAME);
  // ArduinoOTA.setPassword("admin");  // Uncomment and set password if needed
  ArduinoOTA.begin();
  Serial.println("OTA setup completed");
}

void setup_mqtt() {
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqtt_callback);
  Serial.println("MQTT setup completed");
}

void mqtt_callback(char* topic, byte* message, unsigned int length) {
  Serial.println("Message arrived on topic: " + String(topic));
  
  String messageTemp;
  for (unsigned int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  
  Serial.println("Message: " + messageTemp);
  
  if (String(topic) == IN_TOPIC) {
    if (messageTemp == "ON") {
      set_led(HIGH);
    } else if (messageTemp == "OFF") {
      set_led(LOW);
    }
  }
}

void set_led(bool state) {
  digitalWrite(LED_PIN, state);
  Serial.println("Changing LED to " + String(state ? "ON" : "OFF"));
  mqttClient.publish(OUT_TOPIC, state ? "ON" : "OFF");
}
      
void reconnect_mqtt() {
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");
      mqttClient.publish(OUT_TOPIC, ESP_HOSTNAME);
      mqttClient.subscribe(IN_TOPIC);
    } else {
      Serial.println(" failed, rc=" + String(mqttClient.state()) + " retrying in 5 seconds");
      delay(MQTT_RECONNECT_DELAY);
    }
  }
}

void handle_button() {
  int reading = digitalRead(BUTTON_PIN);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > BUTTON_DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == LOW) {  // Button is pressed (LOW because of INPUT_PULLUP)
        toggle_led();
      }
    }
  }
  
  lastButtonState = reading;
}

void toggle_led() {
  bool newState = !digitalRead(LED_PIN);
  set_led(newState);
  mqttClient.publish("esp8266gruen/intopic", newState ? "ON" : "OFF");
}
