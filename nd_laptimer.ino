const int TriggerPin_1 = 8; //Trig pin #1
const int EchoPin_1 = 9; //Echo pin #1
const int TriggerPin_2 = 12; // Trig pin #2
const int EchoPin_2 = 11; //Echo pin #1
long Duration_1 = 0;
long Duration_2 = 0;

unsigned long time;
long time_initial = 0;
long time_final = 0;  

void setup() {
  pinMode(TriggerPin_1, OUTPUT); // Trigger is an output pin
  pinMode(EchoPin_2, INPUT); // Echo is an input pin
  pinMode(TriggerPin_2, OUTPUT);
  pinMode(EchoPin_2, INPUT);
  Serial.begin(19200); // Serial Output
}

void loop() {
  if(time_initial == 0)
  {
    digitalWrite(TriggerPin_1, LOW);
    delayMicroseconds(2);
    digitalWrite(TriggerPin_1, HIGH); // Trigger pin to HIGH
    delayMicroseconds(10); // 10us high
    digitalWrite(TriggerPin_1, LOW); // Trigger pin to HIGH
    
    Duration_1 = pulseIn(EchoPin_1, HIGH); // Waits for the echo pin to get high
    // returns the Duration in microseconds
   
    long Distance_1 = Distance(Duration_1);
    
    if(Distance_1 < 80)
    {
      time_initial = millis();
      Serial.print("time_initial =");
      Serial.println(time_initial);
    }
  }

  if(time_final == 0)
  {
    digitalWrite(TriggerPin_2, LOW);
    delayMicroseconds(2);
    digitalWrite(TriggerPin_2, HIGH);
    delayMicroseconds(10);
    digitalWrite(TriggerPin_2, LOW);
    
    Duration_2 = pulseIn(EchoPin_2, HIGH);
    long Distance_2 = Distance(Duration_2);

    if(Distance_2 < 80)
    {
      time_final = millis();
      Serial.print("time_final =");
      Serial.println(time_final);
    }
  }

  
  
  if(time_final-time_initial != 0)
  {
    Serial.println(time_final-time_initial);  
  }
  
  delay(50); // Wait to do next measurement
}

long Distance(long time)
{
  // Calculates the Distance in mm
  // ((time)*(Speed of sound))/ toward and backward of object) * 10

  long DistanceCalc; // Calculation variable
  DistanceCalc = ((time / 2.9) / 2); // Actual calculation in mm
  //DistanceCalc = time / 74 / 2; // Actual calculation in inches
  return DistanceCalc; // return calculated value
}

long Distance_2(long time)
{
  // Calculates the Distance in mm
  // ((time)*(Speed of sound))/ toward and backward of object) * 10

  long DistanceCalc_2; // Calculation variable
  DistanceCalc_2 = ((time / 2.9) / 2); // Actual calculation in mm
  //DistanceCalc_2 = time / 74 / 2; // Actual calculation in inches
  return DistanceCalc_2; // return calculated value
}
