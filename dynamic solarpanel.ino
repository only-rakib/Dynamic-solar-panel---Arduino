#include <Servo.h>
//defining Servos
Servo servohori;
int servoh = 0;
int servohLimitHigh = 160;
int servohLimitLow = 20;

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 160;
int servovLimitLow = 20;
//Assigning LDRs
int ldrtopl = A2;
int ldrtopr = A1;
int ldrbotl = A3;
int ldrbotr = A0;

 void setup () 
 {
  Serial.begin(9600);
  servohori.attach(10);
  servohori.write(0);
  servoverti.attach(9);
  servoverti.write(90);
  delay(500);
 }

void loop()
{
  servoh = servohori.read();
  Serial.println(servoh);
  
  servov = servoverti.read();
  Serial.println(servov);
  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // calculating average
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs
  Serial.print("Avg Top:");
  Serial.println(avgtop);
  Serial.print("Avg Bot:");
  Serial.println(avgbot);
  Serial.print("Avg Left:");
  Serial.println(avgleft);
  Serial.print("Avg Right:");
  Serial.println(avgright);
  
  if (avgtop < avgbot)
  {
    Serial.println("Avg Bot:");
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(10);
  }
  else if (avgbot < avgtop)
  {
    Serial.println("Avg Top:");
    servoverti.write(servov -1);
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);
  }
  
 if (avgleft > avgright)
  {
    servohori.write(servoh +1);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servohori.write(servoh -1);
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    delay(10);
  }
  else 
  {
    servohori.write(servoh);
  }
  delay(50);
}
