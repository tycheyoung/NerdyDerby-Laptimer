//unsigned long time;
long time_initial = 0;
long time_final_1 = 0;  
long time_final_2 = 0;
int sw = 10;       // 스위치(SW) 핀 설정
int led = 6;       // LED 핀 설정
 
int state = LOW;      // LED 상태
int reading;          // SW 상태
int previous = LOW;   // SW 이전 상태
 
long time = 0;        // LED가 ON/OFF 토글된 마지막 시간
long debounce = 100;  // Debounce 타임 설정

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Start test");
  
  pinMode(sw, INPUT_PULLUP); // SW 를 설정, 아두이노 풀업저항 사용
  pinMode(led, OUTPUT);      // LED 설정
}

void loop() {
  
  reading = digitalRead(sw);  // SW 상태 읽음
 
  //SW 가 눌려졌고 스위치 토글 눌림 경과시간이 Debounce 시간보다 크면 실행
  if (reading == HIGH && previous == LOW && millis() - time > debounce) 
  {
    if (state == HIGH)    // LED 가 HIGH 면 LOW 로 바꿔준다.
      state = LOW;
    else                  // LED 가 LOW 면 HIGH 로 바꿔준다.
    {
      state = HIGH;
      time_initial = millis();
    }
    time = millis();
  }

  digitalWrite(led, state);
 
  previous = reading;

  if(state == HIGH)
  {
//    Serial.print("time initial = ");
//    Serial.println(time_initial);
    
        if(time_final_1 == 0)
      {
          // read the input on analog pin 0:
          int sensorValue = 0;
          for (int x = 0 ; x < 6 ; x++)
          {
            sensorValue = sensorValue + analogRead(A0);
          }
          sensorValue = sensorValue / 6;
          float Distance = pow((sensorValue / 1893.9), -1.087);   //This equation can vary from sensor to sensor
      
          if(Distance < 10)
          {
              time_final_1 = millis();
              Serial.print("time_final 1 = ");
              Serial.println(time_final_1);
          } 
          if((time_final_1 & time_initial) != 0)
          {
            Serial.print("time difference ="); 
            Serial.println(time_final_1-time_initial);  
          }
      }
    
      if(time_final_2 == 0)
      {
          // read the input on analog pin 1:
          int sensorValue = 0;
          for (int x = 0 ; x < 6 ; x++)
          {
            sensorValue = sensorValue + analogRead(A1);
          }
          sensorValue = sensorValue / 6;
          float Distance = pow((sensorValue / 1893.9), -1.087);   //This equation can vary from sensor to sensor
      
          if(Distance < 5)
          {
              time_final_2 = millis();
              Serial.print("time_final 2 = ");
              Serial.println(time_final_2);
          } 
          if((time_final_2 & time_initial) != 0)
          {
            Serial.print("time difference ="); 
            Serial.println(time_final_2-time_initial);  
          }
      }
  }

}
