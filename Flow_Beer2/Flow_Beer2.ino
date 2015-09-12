

// reading liquid flow rate using Seeeduino and Water Flow Sensor from Seeedstudio.com
// Code adapted by Charles Gantt from PC Fan RPM code written by Crenn @thebestcasescenario.com
// http:/themakersworkbench.com http://thebestcasescenario.com http://seeedstudio.com
 

int NbTopsFan = 0; //measuring the rising edges of the signal
int Calc;                               
int hallsensor = 2;    //The pin location of the sensor
long t_start = 0L;
long t_total = 0L;
long curTime = 0L;
bool isChugging = false;

// The setup() method runs once, when the sketch starts
void setup() //
{ 
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  Serial.begin(9600); //This is the setup function where the serial port is initialised,
  Serial.write(System.deviceID());
} 
// the loop() method runs over and over again,
// as long as the Arduino has power
void loop ()    
{
    // while (NbTopsFan == 0) {
    //     NbTopsFan = digitalRead(hallsensor);
    // }
    NbTopsFan = digitalRead(hallsensor);
    curTime = millis();
    
    Serial.write(NbTopsFan);
    Serial.write(millis());
    
    if (NbTopsFan > 0 && isChugging != false) {
        isChugging = true;
        // Send a request to api.co/start
        // with payload { timestamp: curTime, id: System.deviceID() }
    }
    
    if (NbTopsFan == 0 && isChugging == true) {
        isChugging = false;
        // Send a request to api.co/end
        // with payload { timestamp: curTime, id: System.deviceID() }
    }
    // while (NbTopsFan == 1) {
    //     NbTopsFan = digitalRead(hallsensor);
    // }
}



// reading liquid flow rate using Seeeduino and Water Flow Sensor from Seeedstudio.com
// Code adapted by Charles Gantt from PC Fan RPM code written by Crenn @thebestcasescenario.com
// http:/themakersworkbench.com http://thebestcasescenario.com http://seeedstudio.com
 

int NbTopsFan = 0; //measuring the rising edges of the signal
int Calc;                               
int hallsensor = 2;    //The pin location of the sensor
long t_start = 0L;
long t_total = 0L;
long curTime = 0L;
bool isChugging = false;

// The setup() method runs once, when the sketch starts
void setup() //
{ 
  pinMode(hallsensor, INPUT); //initializes digital pin 2 as an input
  Serial.begin(9600); //This is the setup function where the serial port is initialised,
  Serial.write(System.deviceID());
} 
// the loop() method runs over and over again,
// as long as the Arduino has power
void loop ()    
{
    // while (NbTopsFan == 0) {
    //     NbTopsFan = digitalRead(hallsensor);
    // }
    NbTopsFan = digitalRead(hallsensor);
    curTime = millis();
    
    Serial.write(NbTopsFan);
    Serial.write(millis());
    
    if (NbTopsFan > 0 && isChugging != false) {
        isChugging = true;
        // Send a request to api.co/start
        // with payload { timestamp: curTime, id: System.deviceID() }
    }
    
    if (NbTopsFan == 0 && isChugging == true) {
        isChugging = false;
        // Send a request to api.co/end
        // with payload { timestamp: curTime, id: System.deviceID() }
    }
    // while (NbTopsFan == 1) {
    //     NbTopsFan = digitalRead(hallsensor);
    // }
}


