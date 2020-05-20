#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] ="00001";

//int datafromUser = 0;
int data;
int i = 0;
int d[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//initialise the pins to be used here
Servo servolf;
Servo servorf;
Servo servolb;
Servo servorb;
int servolfp,servorfp,servolbp,servorbp;
int state=0;
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);
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
  if(motion =="Stop")
  {
    digitalWrite(10,LOW);   
    digitalWrite(11,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
Serial.println("Stop");


  }
  if(motion=="whegsforward"){
     digitalWrite(14,HIGH);   
     digitalWrite(15,LOW); 
  }
    if(motion=="whegsbackward"){
     digitalWrite(15,HIGH);   
     digitalWrite(14,LOW); 
  }
  }

void loop() {
  while(Serial.available() > 0) {
    if(i<15){
    data = Serial.read();
    d[i]=data;
    i++;
    }
    else{
      i=0;
      break;
    }
  }
  //state deciding condition
  if(d[5]==1){
    state=0;
    }
    else if(d[6]==1){
      state=1;
    }
    else if(d[11]==0&&d[7]==1){
      state=2;
    }
     else if(d[11]==0&&d[8]==1){
      state=3;
    }
     else if(d[11]==0&&d[9]==1){
      state=4;
    }
     else if(d[11]==0&&d[10]==1){
      state=5;
    }
    else if(d[11]==1&&d[7]==1){
      state=6;
    }
     else if(d[11]==1&&d[8]==1){
      state=7;
    }
    else if(d[11]==1&&d[9]==1){
      state=8;
    }
    else if(d[11]==1&&d[10]==1){
      state=9;
    }
     else if(d[11]==1){
      state=10;
    }
     else if(d[12]==1){
      state=11;
    }
    else if(d[1]>0){
      state=12;//wheels forward
      }
      else if(d[1]>0&&d[13]==1){
        state=13;//whegs forward
        }
        else if(d[2]>0){
      state=14;//wheels back 
      }
      else if(d[2]>0&&d[13]==1){
        state=15;//whegs back
        }
        else if(d[3]>0){
      state=16;//wheels left
      }
      else if(d[3]>0&&d[13]==1){
        state=17;//whegs left
        }
         else if(d[4]>0){
      state=18;//wheels right
      }
         else if(d[4]>0&&d[13]==1){
        state=19;//whegs right
        }
      radio.write(state, sizeof(state));

      
      //giving commands to servo on the bases of state
      if(state==0)
      {
           int pos=45;
           servolf.write(pos);
           servorf.write(pos);
           servolb.write(pos);
           servorb.write(pos);
           servolfp=pos;servorfp=pos;servolbp=pos;servorbp=pos;
      }
      else if(state==1){
           int pos=135;
           servolf.write(pos);
           servorf.write(pos);
           servolb.write(pos);
           servorb.write(pos);
           servolfp=pos;servorfp=pos;servolbp=pos;servorbp=pos;   
       }
      else if(state==2){
        int i;
        for(i=servolfp;i<175;i++){
        servolf.write(i);
        if(state!=2)
        break;
        }
        servolfp=servolfp+i;      
      }
       else if(state==3){
        int i;
        for(i=servorfp;i<175;i++){
        servorf.write(i);
        if(state!=3)
        break;
        }
        servorfp=servorfp+i;      
      }
       else if(state==4){
        int i;
        for(i=servorbp;i<175;i++){
        servorb.write(i);
        if(state!=4)
        break;
        }
        servorbp=servorbp+i;      
      }
      else if(state==5){
        int i;
        for(i=servolbp;i<175;i++){
        servolb.write(i);
        if(state!=5)
        break;
        }
        servolbp=servolbp+i;      
      }
      else if(state==6){
        int i;
        for(i=servolfp;i>0;i--){
        servolf.write(i);
        if(state!=6)
        break;
        }
        servolfp=servolfp-i;      
      }
      else if(state==7){
        int i;
        for(i=servorfp;i>0;i--){
        servorf.write(i);
        if(state!=7)
        break;
        }
        servorfp=servorfp-i;      
      }
      else if(state==8){
        int i;
        for(i=servorbp;i>0;i--){
        servorb.write(i);
        if(state!=8)
        break;
        }
        servorbp=servorbp-i;      
      }
      else if(state==9){
        int i;
        for(i=servolbp;i>0;i--){
        servolb.write(i);
        if(state!=9)
        break;
        }
        servolbp=servolbp-i;      
      }
      else if(state==10){
        int pos=45;
        servolf.write(pos);
        servorf.write(pos);
        servolb.write(pos);
        servorb.write(pos);
        for(i=pos;i<175;i++){
        servolf.write(i);
        servorf.write(i);
        servolb.write(i);
        servorb.write(i);
        if(state!=10)
        break;
        }
        servolbp=servolbp+i;
        servorbp=servorbp+i;
        servolfp=servolbp+i;
        servorfp=servorbp+i;      
      }
      else if(state==11){
        int pos=135;
        servolf.write(pos);
        servorf.write(pos);
        servolb.write(pos);
        servorb.write(pos);
        for(i=pos;i>0;i--){
        servolf.write(i);
        servorf.write(i);
        servolb.write(i);
        servorb.write(i);
        if(state!=11)
        break;
        }
        servolbp=servolbp-i;
        servorbp=servorbp-i;
        servolfp=servolbp-i;
        servorfp=servorbp-i;      
      }
      //motors 
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
  
