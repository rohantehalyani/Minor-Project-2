#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
int incoming;
int i=0;


/* declare all the pins to be used here
 *  
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
}

void loop() {
  if (radio.available()) {
    int arr[17]={};
    radio.read(&arr[i], sizeof(arr[i]);
    if{
      i=0;
      /* write the mapping of analog pins here for dc motors
       *  
       */
    }
    else if(arr[/*value of index */] && /*other array index value*/){
      /* write the code for servo motors
       *  
       */
    }
    
  }
}
