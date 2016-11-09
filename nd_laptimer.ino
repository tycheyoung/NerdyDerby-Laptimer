long time_initial = 0;
long time_final_1 = 10000000;  
long time_final_2 = 10000000;
long time_final_3 = 10000000;
long time_temp1 = 10000000;
long time_temp2 = 10000000;
long time_temp3 = 10000000;

int sw = 6;       // 스위치(SW) 핀 설정

int flag=0;
float calibration_v1;
float calibration_v2;
float calibration_v3;

int reading;          // SW 상태
int previous = LOW;   // SW 이전 상태

long time = 0;        // LED가 ON/OFF 토글된 마지막 시간
const long debounce = 100;  // Debounce 타임 설정 

void setup()
{
  Serial.begin(9600);
  
  pinMode(sw, INPUT_PULLUP); // SW 를 설정, 아두이노 풀업저항 사용

}

void loop() 
{
  if(flag==0)
  {
     int sensorValue_v1 = 0;
     int sensorValue_v2 = 0;
     int sensorValue_v3 = 0;
     
     for (int x = 0 ; x < 6 ; x++)
     {
        sensorValue_v1 = sensorValue_v1 + analogRead(A0);
        sensorValue_v2 = sensorValue_v2 + analogRead(A2);
        sensorValue_v3 = sensorValue_v3 + analogRead(A4);
     }
     sensorValue_v1 = sensorValue_v1 / 6;
     sensorValue_v2 = sensorValue_v2 / 6;
     sensorValue_v3 = sensorValue_v3 / 6;
     calibration_v1 = 65*pow((sensorValue_v1 * 0.0048820125), -1.087);   //This equation can vary from sensor to sensor
     calibration_v2 = 65*pow((sensorValue_v2 * 0.0048820125), -1.087);   //This equation can vary from sensor to sensor
     calibration_v3 = 65*pow((sensorValue_v3 * 0.0048820125), -1.087);   //This equation can vary from sensor to sensor 
     
     flag=flag+1;
  }
  
  reading = digitalRead(sw);  // SW 상태 읽음
  if(reading == LOW && previous == HIGH && millis() - time > debounce)  
  {
    Serial.print("A:");
    Serial.print(time_temp1);
    Serial.println("/");
    delay(10);
    Serial.print("B:");
    Serial.print(time_temp2);
    Serial.println("/");
    delay(10);
    Serial.print("C:");
    Serial.print(time_temp3);
    Serial.println("/");
    delay(10);
    time_final_1 = 10000000;  
    time_final_2 = 10000000;
    time_final_3 = 10000000;
    time_temp1 = 10000000;
    time_temp2 = 10000000;
    time_temp3 = 10000000;

    time = 0;
    time_initial = millis();
  }
  
  previous = reading;
  if(reading == HIGH && previous == HIGH)
  {
      //time for A
      if(time_final_1 == 10000000)
      {
        int sensorValue_0 = 0;
        for (int x = 0 ; x < 6 ; x++)
        {
          sensorValue_0 = sensorValue_0 + analogRead(A0);
        }
        sensorValue_0 = sensorValue_0 / 6;
        float isDistance_0 = 65*pow((sensorValue_0 * 0.0048820125), -1.087);   //This equation can vary from sensor to sensor

         if (isDistance_0 < calibration_v1 - 5)
         {  
             time_final_1 = millis(); 
             time_temp1 = time_final_1 - time_initial;
         }
      }
      //time for B
      if(time_final_2 == 10000000)
      {
        int sensorValue_1 = 0;
        for (int x = 0 ; x < 6 ; x++)
        {
          sensorValue_1 = sensorValue_1 + analogRead(A2);
        }
        sensorValue_1 = sensorValue_1 / 6;
        float isDistance_1 = 65*pow((sensorValue_1 * 0.0048820125), -1.087);   //This equation can vary from sensor to sensor
        
         if (isDistance_1 < calibration_v2 -5)
         {  
             time_final_2 = millis(); 
             time_temp2 = time_final_2 - time_initial;
         }
        }
          //time for B
      if(time_final_3 == 10000000)
      {
        int sensorValue_2 = 0;
        for (int x = 0 ; x < 6 ; x++)
        {
          sensorValue_2 = sensorValue_2 + analogRead(A4);
        }
        sensorValue_2 = sensorValue_2 / 6;
        float isDistance_2 = 65*pow((sensorValue_2 * 0.0048820125), -1.087);   //This equation can vary from sensor to sensor
       
        if (isDistance_2 < calibration_v3 - 5)
         {  
             time_final_3 = millis(); 
             time_temp3 = time_final_3 - time_initial;
         }
      }
  }
  delay (50);
}
