/*
Arduino code for PID. Tested with a initial error (sensorRead in setup()) + noise. Then it tries to stablize.
*/

const int SIGNAL_INPUT_PIN = A0;

// PID params
float SETPOINT = 0.0;
float KP = 0.1;
float KI = 0.1;
float KD = 0.0002;
float integ = 0;
float dt = 0.001; 			// loop time (in seconds)
float errorPrev = 0;

int n = 100; 				// Steps
float sensorRead;
int sensorI = 0;

void setup()
{
  Serial.begin(9600);
  randomSeed(10);
  pinMode(SIGNAL_INPUT_PIN, INPUT);
  sensorRead = 2;
}

void loop()
{  
  while( sensorI + 1 == n ) { }			// TESTING: Stops after going through all points
  
  sensorI = (sensorI + 1) % n;			// looping over dummy signals
  // Serial.println(sensorRead);
  
  float error = SETPOINT - sensorRead;
  integ = integ + error * dt;
  float deriv = (error - errorPrev) / dt;
  
  // float out = KD * deriv;			// TESTING
  float out = KP * error + KI * integ + KD * deriv;
  
  float noise = random(-10,10)/100.0;
  
  sensorRead = sensorRead + out + noise; 		// feedbacking
  //Serial.print(noise);
  //Serial.print(error);
  //Serial.print(sensorRead);
  Serial.print(out);
  Serial.print(", ");
  
  // assignments for next loop
  errorPrev = error;
}