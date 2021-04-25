#include <NewPing.h>
#include <QTRSensors.h>
#define TRIGGER_PIN  6
#define ECHO_PIN     7
#define MAX_DISTANCE 1500


#define leftmotor_dir 45
#define leftmotor_spd 44
#define rightmotor_dir 47
#define rightmotor_spd 46
QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
int spd = 100;
int line = qtr.calibrationOn.minimum[4];
int sV[SensorCount];
int k;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);




void setup() {
  Serial.begin(9600);
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]) {
    A0, A1, A2, A3, A4, A5, A6, A7
  }, SensorCount);
  qtr.setEmitterPin(2);
  pinMode(leftmotor_dir, OUTPUT);
  pinMode(leftmotor_spd, OUTPUT);
  pinMode(rightmotor_dir, OUTPUT);
  pinMode(rightmotor_spd, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

/*delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(leftmotor_dir, HIGH);
      analogWrite(leftmotor_spd, spd);
      digitalWrite(rightmotor_dir, HIGH);
      analogWrite(rightmotor_spd, spd);
      for (uint16_t i = 0; i < 15; i++)
  {
    qtr.calibrate();
  }digitalWrite(leftmotor_dir, LOW);
      analogWrite(leftmotor_spd, spd);
      digitalWrite(rightmotor_dir, LOW);
      analogWrite(rightmotor_spd, spd);
   for (uint16_t i = 0; i < 30; i++)
  {  
    qtr.calibrate();
  }digitalWrite(leftmotor_dir, HIGH);
      analogWrite(leftmotor_spd, spd);//
      digitalWrite(rightmotor_dir, HIGH);
      analogWrite(rightmotor_spd, spd);
    
    for (uint16_t i = 0; i < 15; i++)
  {
qtr.calibrate();
  }
  analogWrite(leftmotor_spd, spd-spd);
   analogWrite(rightmotor_spd, spd-spd);
   delay(200);
*/

}

void moving (bool Left, bool Right, int spd_L, int spd_R){
  Left = not Left;
  digitalWrite(leftmotor_dir, Left);
  analogWrite(leftmotor_spd, spd_L);
  digitalWrite(rightmotor_dir, Right);
  analogWrite(rightmotor_spd, spd_R);
}






void loop() {
 ///////////////////////////////////
 //LeftMotor LOW - вперёд
 //RightMotor HIGH - вперед
   digitalWrite(LED_BUILTIN, LOW);
  qtr.read(sensorValues);
  for (int i = 0; i < SensorCount; i++)
  {
    sV[i] = sensorValues[i];
    sV[i]-=570;
    if((i==0)||(i==7)){
      sV[i]-=30;
    }
    if(sV[i]<10){
      sV[i]=0;
    }
    else{
      sV[i]=1;
    }
    Serial.print(sV[i]);
    Serial.print('\t');
  }

if((sV[3]==1)||(sV[4]==1)){
  moving(1,1,spd,spd);
}
if((sV[1]==0)&&(sV[1]==0)&&(sV[2]==0)&&(sV[3]==0)&&(sV[4]==0)&&(sV[5]==0)&&(sV[6]==0)&&(sV[7]==0)){
  moving(1,1,0,0);
}
if((sV[1]==1)||(sV[2]==1)){
 moving(1,1,spd/2,spd);
}
if((sV[5]==1)||(sV[6]==1)){
 moving(1,1,spd,spd/2);
}
if(sV[0]==1){
 moving(0,1,spd/5,spd+10);
}
if(sV[7]==1){
 moving(1,0,spd+10,spd/5);
}
  Serial.println(); 
  }
