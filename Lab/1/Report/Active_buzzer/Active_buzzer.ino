/*
 * Author: Elecrow Engle
 * Date:7/12/2017
 * IDE V1.8.2 
 * Email:engle@elecrow.com
 * Function:
 */
const int buzzer=5; 
void setup(){
  pinMode(buzzer,OUTPUT);
}
void loop(){
  digitalWrite(buzzer, HIGH); // produce sound
}

