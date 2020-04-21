#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

int datafromUser = 0;
int data;
int i = 0;
int arr[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
/*initialise the pins to be used here

*/
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.begin(9600);

}

void loop() {
  if (Serial.available() > 0) {
    data = Serial.read();
    if (data != 13) {
      arr[i] = data;
      i++;

      radio.write(&arr[i], sizeof(arr[i]));
    }
  }
}
