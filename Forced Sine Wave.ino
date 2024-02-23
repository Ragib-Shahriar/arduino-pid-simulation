/*
Arduino code for PID. Tested with a forced sine wave.
*/

const int SIGNAL_INPUT_PIN = A0;

// PID params
float SETPOINT = 0.0;
float KP = 0.5;
float KI = 1;
float KD = 0.001;
float integ = 0;
float dt = 0.001; 			// loop time (in seconds)
float errorPrev = 0;

// TESTING with a Sine wave
float sensorValues[] = {0.0,0.21,0.42,0.61,0.76,0.88,0.96,1.0,0.99,0.93,0.83,0.69,0.52,0.32,0.11,-0.11,-0.32,-0.52,-0.69,-0.83,-0.93,-0.99,-1.0,-0.96,-0.88,-0.76,-0.61,-0.42,-0.21};
size_t n = sizeof(sensorValues) / sizeof(float);
int sensorI = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(SIGNAL_INPUT_PIN, INPUT);
}

void loop()
{
  float sensorRead = sensorValues[sensorI];
  // float sensorRead = analogRead(SIGNAL_PIN);
  
  while( sensorI + 1 == n ) { }			// TESTING: Stops after going through all points
  
  sensorI = (sensorI + 1) % n;			// looping over dummy signals
  // Serial.println(sensorRead);
  
  float error = SETPOINT - sensorRead;
  Serial.println(error);
  integ = integ + error * dt;
  float deriv = (error - errorPrev) / dt;
  
  // float out = KD * deriv;			// TESTING
  float out = KP * error + KI * integ + KD * deriv;
  
  Serial.print(out);
  Serial.print(", ");
  
  // assignments for next loop
  errorPrev = error;
}