#include <avr/interrupt.h>
#include <stdlib.h>
#include <Timer.h>

#include <XBOXRECV.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXRECV Xbox(&Usb);

String x1="",y1="",angleleft="",angleright="";int angle=0;String angle1="";
int x=0,y=0;


int en1 = 3;
int m1f = 30;
int m1b = 31;

int en2 = 5;
int m2f = 32;
int m2b = 33;

int en3 = 11;
int m3f = 34;
int m3b = 35;

int f=0;
int g=0;

int p_en1=42;
int p_en2=43;
int p_a1=48;
int p_a2=49;
int p_b1=50;
int p_b2=51;

int rpm_giv_prev1=0;
int rpm_giv_prev2=0;
int rpm_giv_prev3=0;

float Kp=0.0008;
float Kd=0.08;
int rpm1 = 0;
int rpm2 = 0;
int rpm3 = 0;
int count1 = 0;
int count2 = 0;
int count3 = 0;

int sign_x=1;
int sign_y=1;
int sign_angle=1;

int count11 = 0;
int count22 = 0;
int count33 = 0;

int error1=0;
int error2=0;
int error3=0;
int prev_error1=0;
int prev_error2=0;
int prev_error3=0;

float pwm_prev1=0;
float pwm_prev2=0;
float pwm_prev3=0;
float rpm_giv1=0;
float rpm_giv2=0;
float rpm_giv3=0;
float pwm1 =0;
float pwm2 =0;
float pwm3 =0;
int t1=0,t2=0,t3=0;
int x0=0,y0=0,angle0=0;
Timer t;

void setup()
{
Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXbox Wireless Receiver Library Started"));
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);

  pinMode(42,OUTPUT);
  pinMode(43,OUTPUT);
  pinMode(48,OUTPUT);
  pinMode(49,OUTPUT);
  pinMode(50,OUTPUT);
  pinMode(51,OUTPUT);
  
  pinMode(18, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
 int tick=t.every(100,reading);
  attachInterrupt(digitalPinToInterrupt(18),runn1, RISING);
  attachInterrupt(digitalPinToInterrupt(21),runn2,RISING);
  attachInterrupt(digitalPinToInterrupt(20),runn3,RISING);
}

 

void reading()
{
  rpm1=count1/0.5;
  count1=0;
  rpm2=count2/0.5;
  count2=0;
  rpm3=count3/0.5;
  count3=0;
  
  }
void runn1()
{
  count1++;
  if(f==1 || g==1)
  count11++; 
//Serial.print("count= ");Serial.println(count);
}
void runn2()
{
  count2++;
  if(f==1 || g==1)
  count22++;
//Serial.print("count= ");Serial.println(count);
}
void runn3()
{
  count3++;
  if(f==1 || g==1)
  count33++;
//Serial.print("count= ");Serial.println(count);
}

void loop()
{
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    for (uint8_t i = 0; i < 4; i++) {
      if (Xbox.Xbox360Connected[i]) {
        if (Xbox.getButtonPress(L2, i) || Xbox.getButtonPress(R2, i)) {
        }
        else
        angle=0;
        if (Xbox.getButtonClick(B, i) && g==0)
          {
            f=1;
            angle=-150;
            Serial.println("B");
          }
          if (Xbox.getButtonClick(X, i) && f==0)
          {
            g=1;
            angle=150;
            Serial.println("X");
          }
          if (Xbox.getButtonClick(Y, i))
          {
            digitalWrite(p_en1,HIGH);
            digitalWrite(p_en2,LOW);
            digitalWrite(p_a1,HIGH);
            digitalWrite(p_a2,LOW);
            digitalWrite(p_b1,LOW);
            digitalWrite(p_b2,LOW);
          }
          if (Xbox.getButtonClick(A, i))
          {
            digitalWrite(p_en2,HIGH);
            digitalWrite(p_en1,LOW);
            digitalWrite(p_b2,HIGH);
            digitalWrite(p_b1,LOW);
            digitalWrite(p_a1,LOW);
            digitalWrite(p_a2,LOW);
          }
        if (f==1 ||g==1 ||Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500 || Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500 || Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500 || Xbox.getAnalogHat(RightHatY, i) > 7500 || Xbox.getAnalogHat(RightHatY, i) < -7500 ||  f==1)
        {
          
          if (Xbox.getAnalogHat(LeftHatX, i) > 7500 || Xbox.getAnalogHat(LeftHatX, i) < -7500) {
            
            x1=(Xbox.getAnalogHat(LeftHatX, i));
            x=x1.toInt();
            if(x>0)
            x=map(x,7500,32767,0,700);
            else
            x=map(x,-7500,-32768,-1,-700);
           // Serial.println(x);
          }
          else
          {
            x=0;
          }
          if(f==1 && (count11<173 || count22<173 || count33<173))
          {
            Serial.print(count11);Serial.print("     ");
            Serial.print(count22);Serial.print("     ");
            Serial.print(count33);Serial.print("     ");
            
            
            angle=-400;
            x=0;
            y=0;
          }
          if(g==1 && (count11<173 || count22<173 || count33<173))
          {
            Serial.print(count11);Serial.print("     ");
            Serial.print(count22);Serial.print("     ");
            Serial.print(count33);Serial.print("     ");
            
            
            angle=400;
            x=0;
            y=0;
          }
          if(count11>173 && count22>173 && count33>173)
          {
            angle=0;
            x=0;
            y=0;
            count11=0;
            count22=0;
            count33=0;
            f=0;
            g=0;
          }
          
          if (Xbox.getAnalogHat(LeftHatY, i) > 7500 || Xbox.getAnalogHat(LeftHatY, i) < -7500) {
            Serial.print(F("LeftHatY: "));
            Serial.print("\t");
            y1=(Xbox.getAnalogHat(LeftHatY, i));
            y=y1.toInt();
            if(y>0)
            y=map(y,7500,32767,0,700);
            else
            y=map(y,-7500,-32768,-1,-700);
           // Serial.println(y);
          }
          else
          {
            y=0;
          }

          if (Xbox.getAnalogHat(RightHatX, i) > 7500 || Xbox.getAnalogHat(RightHatX, i) < -7500) {
            angle1=(Xbox.getAnalogHat(RightHatX, i));
            angle=angle1.toInt();
            if(angle>0)
            angle=map(angle,7500,32767,-1,-700);
            else
            angle=map(angle,-7500,-32768,0,700);
           // Serial.println(angle);
          }
          else if(f==0 && g==0)
          {
            angle=0;
          }
         }
          else
          {
            if (abs(x)>10)
            {
              sign_x=(x/abs(x));
              x=abs(x)-10;
              x=x*sign_x;
            }
            else
            x=0;

            if (abs(y)>10)
            {
              sign_y=(y/abs(y));
              y=abs(y)-10;
              y=y*sign_y;
            }
            else
            y=0;

           if (abs(angle)>10)
            {
              sign_angle=(angle/abs(angle));
              angle=abs(angle)-10;
              angle=angle*sign_angle;
            }
            else
            angle=0;
          }
          Serial.println();
         //if(x!=x0 || y!=y0 || angle!=angle0){
         rpm_giv1= (-0.667*x)+(0 * y)+(0.333*angle);
         rpm_giv2= (0.333*x)+(-0.577 * y)+(0.333*angle);
         rpm_giv3= (0.333*x)+(0.577 * y)+(0.333*angle);
         
         if((abs(abs(rpm_giv_prev1)-abs(rpm_giv1)))>10)
          {
            pwm1=map(rpm_giv1,-700,700,150,-150);
            pwm1=(0.5*pwm1);
          if(rpm_giv1!=0)
         {
          if(pwm1>0.0)
          {
          digitalWrite(m1f,1);
          digitalWrite(m1b,0);
          }
        else
          {
          digitalWrite(m1f,0);
          digitalWrite(m1b,1);
          }
         }
         else
         {
          digitalWrite(m1f,0);
          digitalWrite(m1b,0);
          
         }
          
            pwm1=abs(pwm1);
            Serial.println("*********************");
          }
          
          if(rpm_giv1==0)
          {
            digitalWrite(m1f,0);
          digitalWrite(m1b,0);
          }

           if((abs(abs(rpm_giv_prev2)-abs(rpm_giv2)))>10)
          {
            pwm2=map(rpm_giv2,-870.1,870.1,150,-150);
            pwm2=(0.5*pwm2);
          if(rpm_giv2!=0)
         {
          if(pwm2>0.0)
          {
          digitalWrite(m2f,1);
          digitalWrite(m2b,0);
          }
        else
          {
          digitalWrite(m2f,0);
          digitalWrite(m2b,1);
          }
         }
         else
         {
          digitalWrite(m2f,0);
          digitalWrite(m2b,0);
          
         }
          
            pwm2=abs(pwm2);
            Serial.println("*********************");
          }
          
          if(rpm_giv2==0)
          {
            digitalWrite(m2f,0);
          digitalWrite(m2b,0);
          }
          if((abs(abs(rpm_giv_prev3)-abs(rpm_giv3)))>10)
          {
            pwm3=map(rpm_giv3,-870.1,870.1,150,-150);
            pwm3=0.5*pwm3;
          if(rpm_giv3!=0)
         {
          if(pwm3>0.0)
          {
          digitalWrite(m3f,1);
          digitalWrite(m3b,0);
          }
        else
          {
          digitalWrite(m3f,0);
          digitalWrite(m3b,1);
          }
         }
         else
         {
          digitalWrite(m3f,0);
          digitalWrite(m3b,0);
          
         }
          
            pwm3=abs(pwm3);
            Serial.println("*********************");
          }
          
          if(rpm_giv3==0)
          {
            digitalWrite(m3f,0);
          digitalWrite(m3b,0);
          }

                  
        t1=millis();
        rpm_giv1=abs(rpm_giv1);
        rpm_giv2=abs(rpm_giv2);
        rpm_giv3=abs(rpm_giv3);
        error1=rpm_giv1-rpm1;
        error2=rpm_giv2-rpm2;
        error3=rpm_giv3-rpm3;
        Serial.print(error1);Serial.print("      ");
        Serial.print(error2);Serial.print("      ");
        Serial.print(error3);Serial.print("      ");
        pwm1=pwm1 + (Kp*error1)+(Kd*((error1-prev_error1)/(t1-t2)));
        pwm2=pwm2 + (Kp*error2)+(Kd*((error2-prev_error2)/(t1-t2)));
        pwm3=pwm3 + (Kp*error3)+(Kd*((error3-prev_error3)/(t1-t2)));
        //Serial.print("PWM_PREV: ");Serial.println(pwm_prev);
        analogWrite(en1,pwm1);
        analogWrite(en2,pwm2);
        analogWrite(en3,pwm3);
        
        prev_error1=error1;
         prev_error2=error2;
         prev_error3=error3;
        t.update();
        rpm_giv_prev1=rpm_giv1;
        
        rpm_giv_prev2=rpm_giv2;
        
        rpm_giv_prev3=rpm_giv3;

        




        
        x0=x;
        y0=y;
        angle0=angle;  
        t2=t1;
      }
}

  }
  else
  {
    analogWrite(en1,0);
        analogWrite(en2,0);
        analogWrite(en3,0);
  }
  }

            
