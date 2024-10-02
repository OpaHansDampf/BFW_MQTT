#include <PubSubClient.h>
#include <ArduinoOTA.h>

#define wifi_ssid "LAB"
#define wifi_password "labwifi1"
#define mqtt_server "192.168.20.174"
#define mqtt_user ""         
#define mqtt_password ""
#define ESPHostname "ESP8266_MQTT_Test_gelb" 
String clientId = "ESP8266-gelb";      

#define outTopic "esp8266gelb/outtopic" 
#define inTopic "esp8266gelb/intopic"
   
WiFiClient espClient;  
PubSubClient client(espClient);  

const int LEDPin = 5;     // der Output Pin wo das LED angehängt ist
const int buttonPin = 4;  // der Input Pin wo der Taster angehängt ist
int buttonState = 0;
int lastButtonState = 0;
    
void setup() {  
  Serial.begin(9600);
  setup_wifi();
  ArduinoOTA.setHostname(ESPHostname);
  // ArduinoOTA.setPassword("admin");
  ArduinoOTA.begin();
   
  client.setServer(mqtt_server, 1883); 
  client.setCallback(callback);  
  pinMode(LEDPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}  
   
void loop() {  
  if (!client.connected()) {  
    reconnect();  
  }
  client.loop();
  ArduinoOTA.handle();
  
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      client.publish("esp8266gelb/outtopic", "OFF"); 
      Serial.println("Changing Button to OFF");
      client.publish("esp8266gruen/intopic", "OFF");
    } else {
      client.publish("esp8266gelb/outtopic", "ON");
      Serial.println("Changing Button to ON");
      client.publish("esp8266gruen/intopic", "ON");
    }
    // Kurze Pause zum entprellen
    delay(100);
  }
  lastButtonState = buttonState; //fehler
}   
   
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}  

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  if (String(topic) == inTopic) {
    if(messageTemp == "ON"){
      Serial.println("Changing LED to ON");
      digitalWrite(LEDPin, HIGH);   //Invertiertes Signal
      client.publish(outTopic, "ON");
      delay(200);
    }
    else if(messageTemp == "OFF"){
      Serial.println("Changing LED to OFF");
      digitalWrite(LEDPin, LOW);  //Invertiertes Signal
      client.publish(outTopic, "OFF"); 
      delay(200);
    }
  }
}
      
 void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(outTopic, ESPHostname);
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
   }
}
