#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>


const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

// the loop function runs over and over again forever
void loop() {
  if(irrecv.decode(&results)){
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
 
}
