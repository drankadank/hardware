// This #include statement was automatically added by the Particle IDE.
#include "HttpClient/HttpClient.h"

float lightLevel = 0;
char payload[64];

// reading liquid flow rate using Seeeduino and Water Flow Sensor from Seeedstudio.com
// Code adapted by Charles Gantt from PC Fan RPM code written by Crenn @thebestcasescenario.com
// http:/themakersworkbench.com http://thebestcasescenario.com http://seeedstudio.com
 
volatile int NbTopsFan; //measuring the rising edges of the signal
int Calc;                               
int hallsensor = D2;    //The pin location of the sensor
bool isChugging = false;
int zeroCount = 0;
bool shouldPingStart = true;
bool shouldPingEnd = false;
 
void rpm ()     //This is the function that the interupt calls 
{ 
  NbTopsFan++;  //This function measures the rising and falling edge of the hall effect sensors signal
} 
// The setup() method runs once, when the sketch starts
HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    //  { "Content-Type", "application/json" },
    //  { "Accept" , "application/json" },
    { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;


void setup() //
{ 
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  pinMode(D5, OUTPUT);
  Serial.begin(9600); //This is the setup function where the serial port is initialised,
  attachInterrupt(D2, rpm, RISING); //and the interrupt is attached
} 
// the loop() method runs over and over again,
// as long as the Arduino has power

void pingStart() {
    Serial.println();
    Serial.println("Application>\tStart of Loop.");
    // Request path and body can be set at runtime or at setup.
    request.hostname = "d9fc80a3.ngrok.io";
    request.port = 80;
    char str[80];
    char mil[15];
    sprintf(mil, "%d", millis());
    strcpy(str, "/start");
    strcat(str, "?timestamp=");
    strcat(str, mil);
    strcat(str, "&id=");
    strcat(str, System.deviceID().c_str());
    request.path = str;
    // The library also supports sending a body with your request:
    //sprintf(payload, "{\"timestamp\":%i,\"id\":%s}", millis(), System.deviceID().c_str());
    //request.body = "{\"timestamp\":\"3\",\"id\":\"asdf\"}";

    // Get request
    http.post(request, response, headers);
    Serial.print("Application>\tResponse status: ");
    Serial.println(response.status);

    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);
}

void pingEnd() {
    Serial.println();
    Serial.println("Application>\tStart of Loop.");
    // Request path and body can be set at runtime or at setup.
    request.hostname = "d9fc80a3.ngrok.io";
    request.port = 80;
    char str[80];
    char mil[15];
    sprintf(mil, "%d", millis());
    strcpy(str, "/end");
    strcat(str, "?timestamp=");
    strcat(str, mil);
    strcat(str, "&id=");
    strcat(str, System.deviceID().c_str());
    request.path = str;
    // The library also supports sending a body with your request:
    //sprintf(payload, "{\"timestamp\":%i,\"id\":%s}", millis(), System.deviceID().c_str());
    //request.body = "{\"timestamp\":\"3\",\"id\":\"asdf\"}";

    // Get request
    http.put(request, response, headers);
    Serial.print("Application>\tResponse status: ");
    Serial.println(response.status);

    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);
}

void togglePings() {
    shouldPingStart = !shouldPingStart;
    shouldPingEnd = !shouldPingEnd;
}

void loop ()    
{
    NbTopsFan = 0;   //Set NbTops to 0 ready for calculations
    // sei();      //Enables interrupts
    interrupts();
    //cli();      //Disable interrupts
    noInterrupts();
    Calc = (NbTopsFan * 60 / 7.5); //(Pulse frequency x 60) / 7.5Q, = flow rate in L/hour 
    if (Calc > 0){
        zeroCount = 0;
    }
    if (Calc > 0 && isChugging == false) {
        isChugging = true;
        digitalWrite(D5, HIGH);
        if (shouldPingStart == true) {
            pingStart();
            togglePings();
        }
    }
    if (Calc == 0 && isChugging == true) {
        zeroCount++;
        if (zeroCount > 30) {
            zeroCount = 0;
            isChugging = false;
            if (shouldPingEnd == true) {
                digitalWrite(D5, LOW);
                pingEnd();
                togglePings();
            }
        }
    }
}

