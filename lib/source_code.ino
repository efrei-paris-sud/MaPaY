#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


/* Servo */

Servo myservo;        
int pos = 83;         // variable to store the servo position  


/* LCD */

LiquidCrystal_I2C lcd(0x3F,20,4);  


/* LED */

int redLED = 52;
int greenLED = 53;

int pathLED1 = 24; //rouge 1
int pathLED2 = 26; //rouge 2
int pathLED3 = 27; //rouge 3
int pathLED4 = 28; //rouge 4
int pathLED5 = 23; //jaune 1
int pathLED6 = 29; //jaune 2
int pathLED7 = 30; //jaune 3
int pathLED8 = 31; //jaune 4

/* Parking barrier */

int barrierStatus = 0;
int entranceStatus = 0;
int exitStatus = 0;

/* Parking slots */

int parking_slots = 6;
int counter = parking_slots;

/* IR Sensor */

const int IN_A0 = A0; //entrance sensor
const int IN_A1 = A1; //exit sensor

const int IN_A15_s1 = A15; //slot 1
const int IN_A11_s2 = A11; //slot 2
const int IN_A12_s3 = A12; //slot 3
const int IN_A14_s4 = A14; //slot 4
const int IN_A13_s5 = A13; //slot 5
const int IN_A10_s6 = A10; //slot 6



/* Slots variables */

int slot1 = 0;
int slot2 = 0;
int slot3 = 0;
int slot4 = 0;
int slot5 = 0;
int slot6 = 0;

int slot_nb = parking_slots;

int path = 0;




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  
  Serial.begin(9600);
  myservo.attach(45);  
  
  lcd.init();                      
  lcd.backlight();

  displayStartScreen();
  
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(pathLED1, OUTPUT);
  pinMode(pathLED2, OUTPUT);
  pinMode(pathLED3, OUTPUT);
  pinMode(pathLED4, OUTPUT);
  pinMode(pathLED5, OUTPUT);
  pinMode(pathLED6, OUTPUT);
  pinMode(pathLED7, OUTPUT);
  pinMode(pathLED8, OUTPUT);
  
  
  pinMode (IN_A0, INPUT);
  pinMode (IN_A1, INPUT);
  pinMode (IN_A15_s1, INPUT);
  pinMode (IN_A11_s2, INPUT);
  pinMode (IN_A12_s3, INPUT);
  pinMode (IN_A14_s4, INPUT);
  pinMode (IN_A13_s5, INPUT);
  pinMode (IN_A10_s6, INPUT);
  
  
  myservo.write(pos);
}

void loop() {
  
    Entrance();
    Exit();
    barrierClose();
    slot_occupation();
}


/***************************************** FUNCTIONS ************************************************/


void displayStartScreen()    
{
  lcd.clear();
  lcd.setCursor(5,1);
  lcd.print("MaPaY Team");
  lcd.setCursor(4,2);
  lcd.print("welcomes you !");
  delay(5000);
  displayParkingScreen();
}

void displayParkingScreen()
{
  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("Slots remaining :");
  lcd.setCursor(9,2);
  lcd.print(counter);
  if (counter == 0){
  lcd.clear();
  lcd.setCursor(4,1);
  lcd.print("Parking full");  
  }

}

void Entrance(){
  
int sensor_entrance = analogRead(IN_A0);

  if ((sensor_entrance<300) and (counter != 0)){
       digitalWrite(greenLED, HIGH);
       entranceStatus = 1;
       if (exitStatus == 0){
       barrierOpenEntrance();
       }
  }
  
}

void Exit(){
  
int sensor_exit = analogRead(IN_A1);

  if (sensor_exit<300){
       digitalWrite(redLED, HIGH);
       exitStatus = 1;
       if (entranceStatus == 0){
       barrierOpenExit();
       }
    }
}


void barrierOpenEntrance()
{
  if(barrierStatus == 0)
  {
    slot_choice();
    myservo.write(0);
    barrierStatus = 1;
    slots();
  }
}

void barrierOpenExit()
{
  if(barrierStatus == 0)
  {
    myservo.write(0);
    barrierStatus = 1;
    slots();
  }
}



void barrierClose()
{
    if((entranceStatus ==1) and (exitStatus == 1) and (barrierStatus = 1))
    {
      delay(3000);
      myservo.write(pos);
      barrierStatus = 0;
      entranceStatus = 0;
      exitStatus = 0;
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, LOW);
    }  
}

void slots()
{
      if ((entranceStatus == 1) and (exitStatus == 0)){
          --counter; 
          displayParkingScreen();
      }
      if ((exitStatus == 1) and (entranceStatus == 0) and (counter != parking_slots)){
          ++counter; 
          displayParkingScreen();
      }
    
  }

void slot_occupation()
{
   int sensor_slot1 = analogRead(IN_A15_s1);
   int sensor_slot2 = analogRead(IN_A11_s2);
   int sensor_slot3 = analogRead(IN_A12_s3);
   int sensor_slot4 = analogRead(IN_A14_s4);
   int sensor_slot5 = analogRead(IN_A13_s5);
   int sensor_slot6 = analogRead(IN_A10_s6);
   

 {
  if (sensor_slot1<200){
        slot1 = 1;
        if(path == 1){
          digitalWrite(pathLED1, LOW);
          digitalWrite(pathLED2, LOW); 
          path = 0;

        }
   }
   else{
      slot1 = 0;
   }
 }
  
  
  {
   if (sensor_slot2<200){
        slot2 = 1;
        if(path == 2){
          digitalWrite(pathLED1, LOW);
          digitalWrite(pathLED2, LOW); 
          digitalWrite(pathLED3, LOW); 

        }
   }
   else{
      slot2 = 0;
   }
  }
  {
  if (sensor_slot3<200){
        slot3 = 1;
        if(path == 3){
          digitalWrite(pathLED1, LOW);
          digitalWrite(pathLED2, LOW); 
          digitalWrite(pathLED3, LOW);
          digitalWrite(pathLED4, LOW);

        }
   }
   else{
      slot3 = 0;
   }
  }

  { 
    if (sensor_slot4<200){
        slot4 = 1;
        if(path == 4){
          digitalWrite(pathLED5, LOW);
          digitalWrite(pathLED6, LOW);
          
        }
   }
   else{
      slot4 = 0;
   }
  }
  {
   if (sensor_slot5<200){
        slot5 = 1;
        if(path == 5){
          digitalWrite(pathLED5, LOW);
          digitalWrite(pathLED6, LOW);
          digitalWrite(pathLED7, LOW);
          
        }
   }
   else{
      slot5 = 0;
   }
  }
  {
   if (sensor_slot6<200){
        slot6 = 1;
        if(path == 6){
          digitalWrite(pathLED5, LOW);
          digitalWrite(pathLED6, LOW);
          digitalWrite(pathLED7, LOW);
          digitalWrite(pathLED8, LOW);
          
        }
   }
   else{
      slot6 = 0;
   }
  }
}

void slot_choice(){

  int slots[]= {slot1, slot2, slot3, slot4, slot5, slot6};
  for (byte i = 0; i < slot_nb ; i = i + 1) {
      if(slots[i] == 0)
      {
        slot_guidance(i);
        return;
      }
}  
}

void slot_guidance(int n){
    if(n == 0){
        
        digitalWrite(pathLED1, HIGH);
        digitalWrite(pathLED2, HIGH);
        path = 1;

    }

    if(n == 1){
        
        digitalWrite(pathLED1, HIGH);
        digitalWrite(pathLED2, HIGH);
        digitalWrite(pathLED3, HIGH);
        path = 2;
    }

    if(n == 2){
        digitalWrite(pathLED1, HIGH);
        digitalWrite(pathLED2, HIGH);
        digitalWrite(pathLED3, HIGH);
        digitalWrite(pathLED4, HIGH);
        path = 3;
    } 
    
    if(n == 3){
        digitalWrite(pathLED5, HIGH);
        digitalWrite(pathLED6, HIGH);
        path = 4;
    } 

    if(n == 4){
        digitalWrite(pathLED5, HIGH);
        digitalWrite(pathLED6, HIGH);
        digitalWrite(pathLED7, HIGH);
        path = 5;
    } 

    if(n == 5){
        digitalWrite(pathLED5, HIGH);
        digitalWrite(pathLED6, HIGH);
        digitalWrite(pathLED7, HIGH);
        digitalWrite(pathLED8, HIGH);
        path = 6;
    } 
}


    
