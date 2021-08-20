

// ###################### SENSORS VARIABLES ######################
#include "DHT.h"
#define DHTPIN 1     // Digital pin connected to the DHT sensor
//#define PHOTOPIN A0     // Digital pin connected to the DHT sensor
#define WINDPIN A0
#define DHTPIN 2

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// ###################### WEBSITE VARIABLES ######################
//#include <WiFi.h>  NOT WORKING
#include <ESP8266WiFi.h> . //WORKING
#include "ThingSpeak.h"

// ############ ATTENZIONE DATI DA NON CARICARE SU GITHUB ###############
WiFiClient client;                                //WiFi connection details
char ssid[] = "SSID";                 //WiFi Name
char pass[] = "PASSWORD";   

unsigned long myChannelNumber = channel_number;          //Thingspeak channel number
const char * myWriteAPIKey = "WRITE_API_KEY"; 


// ###################### MEASUREMENTS VARIABLES ######################
int temp = 0;
int hum = 0;
int percTemp = 0;
int windSpeed = 0;


//##################### TIMER VARIABLES ############################
long lastTime = 0;  
long timerDelay = 30000; //time passed between every website update (30 secs)



bool flag = true;

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n");

  pinMode(WINDPIN, INPUT);
  
  dht.begin();
}

void recTemp(){
  temp = dht.readTemperature();   //reading temperature
}

void recHum(){
  hum = dht.readHumidity();       //reading humidity
}

void recPercTemp(){
  percTemp = dht.computeHeatIndex(temp, hum, false); //computing perceived temperature
}

bool checkDHT11(){
  if (isnan(temp) || isnan(hum) || isnan(percTemp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return false;
  }
  return true;
}

void recWindSpeed(){
  float avg = 0;

  for(int i = 0; i < 10000 ; i++){
    avg+= analogRead(WINDPIN);
    //delay(50);
  }

  windSpeed = avg/10000;
}



void updateThingSpeak ()                                             //Function to post data to Thingspeak
{
  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, hum);
  ThingSpeak.setField(3, percTemp);
  ThingSpeak.setField(4, windSpeed);
  
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200)
  {
    Serial.println("Channel update successful.");
  }
  else
  {
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
}


void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // ############ WIFI OPS ########
    WiFi.begin(ssid, pass);                                            //Connect to WiFi network
    Serial.print("Starting");
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println();
  
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
  
  
    // ############ THINGSPEAK OPS ########
    ThingSpeak.begin(client);                                          //Initialise ThingSpeak
    delay(10000);   //wait 10 secs
  

    recWindSpeed();
    
    recTemp();
    recHum();
    recPercTemp();
  
    //check if sensors are ok
    if(checkDHT11()){
      Serial.println("Sending data...");
      updateThingSpeak();
    
      Serial.println("Sended");
    }else{
      Serial.println("Failed reading sensors.\nWebsite data not updated.");
    }

    lastTime = millis();
  }
}
