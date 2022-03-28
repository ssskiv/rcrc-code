#include <iarduino_MultiServo.h>

#include <Wire.h>                       // Подключаем библиотеку Wire
//#include <Adafruit_PWMServoDriver.h>    // Подключаем библиотеку Adafruit_PWMServoDriver
#include <SoftwareSerial.h>

//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40); // Установка адреса I2C 0x40
iarduino_MultiServo MSS;
#define SERVOMIN1  60//230                   // Минимальная длительность импульса для сервопривода
#define SERVOMAX1  140//320
#define CENTER1 100//285// Максимальная длина импульса для сервопривода
#define SERVO_1 15                       // Номер порта (0 - 15)
#define SERVO_HAND_1 1                       // Номер порта (0 - 15)
#define SERVO_HAND_2 0
#define SERVO_HAND_3 3
#define SERVO_HAND_4 2
#define SERVO_HAND_5 8
#define SERVO_HAND_6 9
#define SERVO_HAND_7 10
#define SERVO_HAND_8 11
SoftwareSerial mySerial(2, 5);//rx,tx
bool lightstat=true;
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  MSS.servoSet(SERVO_1, SERVO_SG90);
  MSS.servoSet(SERVO_HAND_1, SERVO_MG996R);
  MSS.servoSet(SERVO_HAND_2, SERVO_SG90);
  MSS.servoSet(SERVO_HAND_3, SERVO_MG996R);
  MSS.servoSet(SERVO_HAND_4, SERVO_SG90);
  MSS.servoSet(SERVO_HAND_5, SERVO_MG996R);
  MSS.servoSet(SERVO_HAND_6, SERVO_MG996R);
  MSS.servoSet(SERVO_HAND_7, SERVO_MG996R);
  MSS.servoSet(SERVO_HAND_8, SERVO_MG996R);
  MSS.begin();
  //pwm.begin();  // Инициализация
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13,OUTPUT);
  //pwm.setPWMFreq(60);                   // Частота следования импульсов 60 Гц
  //pwm.setPWM(SERVO_1, 0, CENTER1);
  delay(10); // Пауза
  MSS.servoWrite(15, CENTER1);
}

void loop()
{ while (mySerial.available()) {
    String mes = mySerial.readStringUntil('\n');
    String tag = mes.substring(1, 2);
    delay(1);
    //Serial.println(mes);
    if (tag == "j")  {
      //Serial.println("j");//j  030  020
      /*
         Пары двигателей:

         10,12 пины -
      */
      int xNotMapped = mes.substring(2, 7).toInt();
      int yNotMapped = mes.substring(8).toInt();
      int xMapped = map(xNotMapped, -99, 99, SERVOMIN1, SERVOMAX1);
      int yMapped = map(yNotMapped, 99, -99, -255, 255);
      Serial.println(yMapped);
      if (yMapped == 0) {
        analogWrite(9, yMapped); analogWrite(10, yMapped);
        digitalWrite(11, LOW); digitalWrite(12, LOW);
      }
      if (yMapped > 0)
      {
        analogWrite(9, 255 - yMapped);
        analogWrite(10, 255 - yMapped); digitalWrite(11, HIGH); digitalWrite(12, HIGH);
      }
      if (yMapped < 0)
      { analogWrite(9, 255 - yMapped); analogWrite(10, 255 - yMapped);
        digitalWrite(11, LOW); digitalWrite(12, LOW);
      }
      if (xNotMapped == 0) {
        MSS.servoWrite(SERVO_1, CENTER1);
      }
      else {
        MSS.servoWrite(SERVO_1, xMapped);
      }
      //Serial.println(xNotMapped);
      //pwm.setPWM(SERVO_1, 0, xMapped);



    } else {
      if (tag == "l") {
        digitalWrite(13,lightstat);
        if(lightstat)
        lightstat=false;
        else
        lightstat=true;
        } else {
        int angle = mes.substring(2).toInt();
        switch (tag.toInt()) {
          case 1:
            MSS.servoWrite(SERVO_HAND_1, angle);
            break;
          case 2:
            MSS.servoWrite(SERVO_HAND_2, angle);
            break;
          case 3:
            MSS.servoWrite(SERVO_HAND_3, angle);
            break;
          case 4:
            MSS.servoWrite(SERVO_HAND_4, angle);
            break;
          case 5:
            MSS.servoWrite(SERVO_HAND_5, angle);
            break;
          case 6:
            MSS.servoWrite(SERVO_HAND_6, angle);
            break;
          case 7:
            MSS.servoWrite(SERVO_HAND_7, angle);
            break;
          case 8:
            MSS.servoWrite(SERVO_HAND_8, angle);
            break;
        }
      }
    }
  }

}
