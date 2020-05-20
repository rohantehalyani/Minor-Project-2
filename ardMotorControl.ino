#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
int state=0;
int i=0;
int pos=0;
Servo servolf;
Servo servorf;
Servo servolb;
Servo servorb;
int servolfp,servorfp,servolbp,servorbp;

/* declare all the pins to be used here
 *  
 */
/*  STATES
   0-Arms down .All serrvo at 45 degree
   1-All arms up.All servo at 135 degrees
   2-Increment serrvo S1
   3-Increment serrvo S2
   4-Increment serrvo S3
   5-Increment serrvo S4
   6-Decrement servo s1
   7-Decrement servo s2
   8-Decrement servo s3
   9-Decrement servo s4
   10-Increment all servos 
   11-Decrement all servos
   12-Wheels DC motor forward
   13-Whegs DC motor forward
   14-Wheels DC motor back
   15-Whegs DC motor back
   16-Wheels DC motor left
   17-Whegs DC motor left
   18-Wheels DC motor right
   19-Whegs DC motor right
   */
void setup() {
 Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
/* declare the functioning of pins here
 *  
 */
 servolf.attach(2);
  servorf.attach(3);
  servolb.attach(4);
  servorb.attach(5);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  pinMode(15,OUTPUT);
  delay(100);
  int pos=0;
  servolf.write(pos);
  servorf.write(pos);
  servolb.write(pos);
  servorb.write(pos);
  servolfp=pos;servorfp=pos;servolbp=pos;servorbp=pos;
}



void moveWheelsDC(String motion){
  if(motion =="Forward")
  {
    digitalWrite(10,HIGH);   
    digitalWrite(11,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
Serial.println("Forward");

  }
  if(motion =="Back")
  {
    digitalWrite(10,LOW);   
    digitalWrite(11,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
Serial.println("Backward");


  }
  if(motion =="Right")
  {
    digitalWrite(10,LOW);   
    digitalWrite(11,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
Serial.println("Right");


  }
  if(motion =="Left")
  {
    digitalWrite(10,HIGH);   
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
Serial.println("Left");


  }
  if(motion=="whegsforward"){
     digitalWrite(14,HIGH);   
     digitalWrite(15,LOW); 
  }
    if(motion=="whegsbackward"){
     digitalWrite(15,HIGH);   
     digitalWrite(14,LOW); 
    }
  if(motion =="Stop")
  {
    digitalWrite(10,LOW);   
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
Serial.println("Stop");


  }
  }



void loop() {
  if (radio.available()) {
    radio.read(&state, sizeof(state));
    //On the basis of various states control different motors
     if(state==0)
      {
           for(int pos=0;pos<45;pos=pos+2)
           {
           servolf.write(pos);
           servorf.write(pos);
           servolb.write(pos);
           servorb.write(pos);}
           servolfp=pos;servorfp=pos;servolbp=pos;servorbp=pos;
      }
    else if(state==1){
          for(int pos=0;pos<135;pos=pos+2)
           {
           servolf.write(pos);
           servorf.write(pos);
           servolb.write(pos);
           servorb.write(pos);}
          servolfp=pos;servorfp=pos;servolbp=pos;servorbp=pos;
      
      }
      else if(state==2){
        servolfp=servolfp+5;
        servolf.write(servolfp);    
      }

      else if(state==3){
        servorfp=servorfp+5;
        servorf.write(servorfp);    
      }
      else if(state==4){
        servorbp=servorbp+5;
        servorb.write(servorbp);  
      }
      else if(state==5){
        servolbp=servolbp+5;
        servolb.write(servolbp);    
      }
      else if(state==6){
        servolfp=servolfp-5;
        servolf.write(servolfp);   
      }
      else if(state==7){
        servorfp=servorfp-5;
        servorf.write(servorfp);    
      }
      else if(state==8){
        servorbp=servorbp-5;
        servorb.write(servorbp);  
      }
      else if(state==9){
        servolbp=servolbp-5;
        servolb.write(servolbp);    
      }
      else if(state==10)
      {
        servolbp=servolbp+5;
        servorbp=servorbp+5;
        servolfp=servolbp+5;
        servorfp=servorbp+5;
        servolb.write(servolbp);
        servorb.write(servorbp);  
        servolf.write(servolfp); 
        servorf.write(servorfp);       
      }
      else if(state==11)
      {
        servolbp=servolbp-5;
        servorbp=servorbp-5;
        servolfp=servolbp-5;
        servorfp=servorbp-5;
        servolb.write(servolbp);
        servorb.write(servorbp);  
        servolf.write(servolfp); 
        servorf.write(servorfp);       
      }
      else if(state==12){
        moveWheelsDC("Forward");        
      }
      else if(state==13){
        moveWheelsDC("whegsforward");
      }
      else if(state==14){
        moveWheelsDC("Back");        
      }
       else if(state==15){
        moveWheelsDC("whegsbackward");
      }
      else if(state==16){
        moveWheelsDC("Left");        
      }
      else if(state==18){
        moveWheelsDC("Right");        
      }
      else{
        moveWheelsDC("Stop");
      }
      
    
  }
}
