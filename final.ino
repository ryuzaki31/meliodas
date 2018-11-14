#include<Wire.h>

const int MPU6050_addr=0x68;
int16_t AccX,AccY,AccZ,Temp,GyroX,GyroY,GyroZ;
int r=8,l=9,u=10,d=11,s=12; 
int rf=4,rb=5,lf=6,lb=7;

  
void setup(){
  
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
   pinMode(l,OUTPUT);
  pinMode(r,OUTPUT);
  pinMode(u,OUTPUT);
  pinMode(d,OUTPUT);
  pinMode(s,OUTPUT);
  pinMode(rf,OUTPUT);
  pinMode(lf,OUTPUT);
  pinMode(rb,OUTPUT);
  pinMode(lb,OUTPUT);
  Serial.begin(9600);
}
void loop(){
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
  
  GyroX=Wire.read()<<8|Wire.read();
  GyroY=Wire.read()<<8|Wire.read();
  GyroZ=Wire.read()<<8|Wire.read();
 
  if(GyroX>=2500){//forword
    Serial.print(" || GyroX = "); Serial.println("x+");
    digitalWrite(r,HIGH); 
    digitalWrite(l,LOW);
    digitalWrite(s,LOW); 
    digitalWrite(u,LOW);
    digitalWrite(d,LOW);
    forw();  
    }
  if(GyroX<=-2500){//back
    Serial.print(" || GyroX = "); Serial.println("x-");
    digitalWrite(l,HIGH);
    digitalWrite(r,LOW);
    digitalWrite(s,LOW);
    digitalWrite(u,LOW);
    digitalWrite(d,LOW);
    back();
    }
    if(GyroX>-2500 && GyroX<2500 && GyroY>-2500 && GyroY<2500 ){
    Serial.print(" || Status =  "); Serial.println("0");
    digitalWrite(s,HIGH);
    digitalWrite(l,LOW);
    digitalWrite(r,LOW);
    digitalWrite(u,LOW);
    digitalWrite(d,LOW);

     digitalWrite(rf,LOW);
    digitalWrite(rb,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(lb,LOW);
    }
    if(GyroY>=5000){//right
    Serial.print(" || GyroY = "); Serial.println("y+");
    digitalWrite(u,HIGH); 
    digitalWrite(d,LOW);
    digitalWrite(s,LOW);
    digitalWrite(l,LOW);
    digitalWrite(r,LOW);

       right();
    }
  if(GyroY<=-5000){//left
    Serial.print(" || GyroY = "); Serial.println("y-");
    digitalWrite(d,HIGH);
    digitalWrite(u,LOW);
    digitalWrite(s,LOW);
    digitalWrite(l,LOW);
    digitalWrite(r,LOW);
    left();
    }
  delay(100);
}
void forw(){
  digitalWrite(rf,HIGH);
  digitalWrite(lf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
}
void back(){
  digitalWrite(rb,HIGH);
  digitalWrite(lb,HIGH);
  digitalWrite(rf,LOW);
  digitalWrite(lf,LOW);
}

void left(){
  digitalWrite(rf,HIGH);
  digitalWrite(lf,LOW);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);  
}
void right(){
  digitalWrite(rf,LOW);
  digitalWrite(lf,HIGH);
  digitalWrite(rb,LOW);
  digitalWrite(lb,LOW);
}
