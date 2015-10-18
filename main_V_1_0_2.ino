// Thesis Project by Katsikavelas Ioannis ,Larisa ,Greece 
//Academic year   2014-2015

/*

 * @author      Ioannis Katsikavelas <ioankats93@gmail.com>              
 * @copyright   2015 - Ioannis Katsikavelas 
 * @license     {@link http://choosealicense.com/licenses/mit/ | MIT License}
 
 */


//Sonar on Servo 
#include <NewPing.h>
#define trigPin 13
#define echoPin 12
#define max_distance 300
//NewPing sonar(trigPin, echoPin, max_distance);


//Sonar For Emergency
#define trigPine 10
#define echoPine 9
#define max_distancee 100
//NewPing sonaremerg(trigPine, echoPine, max_distancee);


////// ANALOG PINS 
#define ledgreen A0
#define ledred   A1
#define programmingswitchstate A2

/// SERVO 
#include <Servo.h>
Servo myservo;
#define servodelay 170
const int servopin = 11 ;


//H-BRIDGE DECLARATION 
// connect motor controller pins to Arduino digital pins
// motor one
int enA = 3;
int in1 = 4;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;


//VARIABLES//

int obst ;
int emebreak ;

unsigned long time ;   



void setup()
{
  Serial.begin (9600);
  pinMode(ledred,OUTPUT);       
  pinMode(ledgreen,OUTPUT);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPine, OUTPUT);
  pinMode(echoPine, INPUT);
  pinMode(programmingswitchstate,INPUT);

  
  myservo.attach(servopin);

  // H-BRIDGE PART
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  launchscreen();
  launchtestrobot();
}
///////////////////////////////// LAUNCH - TESTING //////////////////////////////////////////// (start)

void launchscreen()
{
  Serial.println("//////////////////////////");
  delay(100);
  Serial.println("Thesis Project");
  delay(100);
  Serial.println("Made by : Katsikavelas Ioannis");
  delay(100);
  Serial.println("Technological Institute Of Larisa");
  delay(100);
  Serial.println("Electrical engineering Department");
  delay(100);
  Serial.println("Academic Year 2014-2015");
  delay(100);
  Serial.println("Surepervisor : Mr. Kalogiannis Grigoris");
  delay(100);
  Serial.println("//////////////////////////");
}

void ledtets(){
  digitalWrite(ledgreen,HIGH);
  delay(300);
  digitalWrite(ledred,HIGH);
  delay(300);
  digitalWrite(ledgreen,LOW);
  delay(300);
  digitalWrite(ledred,LOW);
  delay(300);
  digitalWrite(ledgreen,HIGH);
  digitalWrite(ledred,HIGH);
  delay(300);
  digitalWrite(ledgreen,LOW);
  digitalWrite(ledred,LOW);
  delay(300);
  digitalWrite(ledgreen,HIGH);
  delay(300);
  digitalWrite(ledred,HIGH);
  delay(300);
  digitalWrite(ledgreen,LOW);
  delay(300);
  digitalWrite(ledred,LOW);
  delay(300);
  digitalWrite(ledgreen,HIGH);
  digitalWrite(ledred,HIGH);
  delay(300);
  digitalWrite(ledgreen,LOW);
  digitalWrite(ledred,LOW);
}

void blinking()
{
    digitalWrite(ledred,HIGH);
    delay(300);
    digitalWrite(ledred,LOW);
    delay(300);
    Serial.println("");
    Serial.println("Coding Mode...");
    Serial.println("");
}



void programmingMode()
{  
  for (int i = 0; i < 100; i--)
  { 
    if (digitalRead(programmingswitchstate) == LOW)
    {
      break;
    }
      
      blinking();
      
  } 
}


void motorsTest()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 200);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 200);
  delay(900);
  stopall();
  delay(2000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 200);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 200);
  delay(900);
  stopall();
}



void launchtestrobot()
{
  ledtets();
  delay(2500);

  ///////////////// M O D E S //////////////////////////
  
  // Switch No1  Programming Mode  switch
  programmingMode();

  int pos = 0;    // variable to store the servo position 
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
  myservo.write(90);
  delay(1000);
  motorsTest();
  delay(2000);
}

///////////////////////////////// LAUNCH - TESTING //////////////////////////////////////////// (end)


int proxihead() 
{
  int obst=0;
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin , HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 8) 
  {  // This is where the LED On/Off happens
  digitalWrite(ledred,HIGH); // When the Red condition is met, the Green LED should turn off
  digitalWrite(ledgreen,LOW);
  obst = 1 ;                        // obstacle recognition
  }
  else 
  {
   digitalWrite(ledred,LOW);
   digitalWrite(ledgreen,HIGH);
   obst=0;
  }

  /*
  if (distance >= 200 || distance <= 0)
  {
   Serial.println("Out of range");
  }
  else 
  {
    Serial.print(distance);
    Serial.println(" cm");
  }
  */

  return obst ;

}



int emergencybreak()
{
  int emebreak=0;
  long duration, distance;
   digitalWrite(trigPine, LOW);  
   delayMicroseconds(2); 
   digitalWrite(trigPine, HIGH);
   delayMicroseconds(10); 
   digitalWrite(trigPine, LOW);
   duration = pulseIn(echoPine , HIGH);
   distance = (duration/2) / 29.1;
   if (distance < 20) 
   {  
     emebreak = 1 ;  // obstacle recognision
   }
  else 
  {
    emebreak=0;
  }

  /*
  if (distance >= 200 || distance <= 0)
  {
    Serial.println("Out of range");
  }
  else 
  {
    Serial.print("EMERGENCY_BREAK_VALUES  ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  */

  return emebreak ;
}


void stopall()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0); 
  analogWrite(enB, 0);
   
}

//anagnwrisi empodiou kai stripsimo pros tin antiheti pleura 




int changeDirection1()
{
  int changeDirect = cerebrum();
  int right = 0 ;
    if (changeDirect == 1 )
    {
      stopall();
      delay(500);
      headright90();
      delay(11);
      int obst = updatedistances();
        if (obst== 1)
          {
            right = 1 ;
          }
        else
          {
            right = 0 ;
          }


        
    }
    Serial.print( " Time :  ");
    time = millis()/1000 ;
    //prints time since program started
    Serial.print(time);
    Serial.println(" Sec ");
    delay(100);
    Serial.println(" Found obstacle  35˚ right") ;  
    return right ;

}

int changeDirection2()
{
  int changeDirect = cerebrum();
  int right1 = 0 ;
    if (changeDirect == 1 )
    {
      stopall();
      delay(500);
      headright45();
      delay(11);
      int obst = updatedistances();
        if (obst== 1)
          {
            right1 = 1 ;
          }
        else
          {
            right1 = 0 ;
          }

    }
    Serial.print( " Time :  ");
    time = millis()/1000 ;
    //prints time since program started
    Serial.print(time);
    Serial.println(" Sec ");
    delay(100);
    Serial.println(" Found obstacle  55˚ right") ;  
    return right1 ;
}

int changeDirection3()
{
  int changeDirect = cerebrum();
  int center = 0 ;
    if (changeDirect == 1 )
    {
      stopall();
      delay(500);
      headcenter();
      delay(11);
      int obst = updatedistances();
        if (obst== 1)
          {
            center = 1 ;
          }
        else
          {
            center = 0 ;
          }
        
    }
    Serial.print( " Time :  ");
    time = millis()/1000 ;
    //prints time since program started
    Serial.print(time);
    delay(100);
    Serial.println(" Sec ");
    Serial.println(" Found obstacle  straight ahead ") ;  
    return center ;
}

int changeDirection4()
{
  int changeDirect = cerebrum();
  int left = 0 ;
    if (changeDirect == 1 )
    {
      stopall();
      delay(500);
      headleft45();
      delay(11);
      int obst = updatedistances();
        if (obst== 1)
          {
            left = 1 ;
          }
        else
          {
            left = 0 ;
          }
        
    }
    Serial.print( " Time :  ");
    time = millis()/1000 ;
    //prints time since program started
    Serial.print(time);
    Serial.println(" Sec ");
    delay(100);
    Serial.println(" Found obstacle  145˚ left") ;  
    return left ;
}

int changeDirection5()
{
  int changeDirect = cerebrum();
  int left1 = 0 ;
    if (changeDirect == 1 )
    {
      stopall();
      delay(500);
      headleft90();
      delay(11);
      int obst = updatedistances();
        if (obst== 1)
          {
            left1 = 1 ;
          }
        else
          {
            left1 = 0 ;
          }
        
    }
    Serial.print( " Time :  ");
    time = millis()/1000 ;
    //prints time since program started
    Serial.print(time);
    Serial.println(" Sec ");
    delay(100);
    Serial.println(" Found obstacle  165˚ left") ;  
    return left1 ;
}

///???
void finalDirect()
{
  int right1 = changeDirection1();
  
  int right2 = changeDirection2();

  int center = changeDirection3();

  int left1 = changeDirection4();
 
  int left2 = changeDirection5();





  if ( center == 1 && right1 != 1 && right2 != 1 && left1 != 1 && left2 != 1 )
    {
      stopall();
      turnleft90(); 
      delay(700);  //calibration needed
      stopall();
     
    }
  if ( (right1 == 1 || right2 == 1) && left1 != 1 && left2 != 1 )
    {
      stopall();
      turnleft90(); 
      delay(700); //calibration needed
      stopall();
      ;
    }
    if ( (left1 == 1  || left2 == 1) && right1 != 1 && right2 != 1 ) 
    {
      stopall();
      turnright90();
      delay(700);
      stopall();
     
    }

/*
    
  if (right1 == 1 && left2 == 1 )
    {
      stopall();
      gostraight();
      delay(700);
      stopall();
    }

*/
    

  if ((right1 == 1  || right2 == 1 ) && (left1 == 1 ||  left2 == 1) )
    {
      stopall();
      gobackwards();
      delay(700);
      stopall();
      turnright90();
      delay(300);
     
    }



}


void lookaround()
 {
  updatedistances();
  headright90(); 
  delay(servodelay);
  //cerebrum();  
  int final1 = cerebrum();
  if (final1 == 1 )
    {
      delay(500);
      finalDirect();
    }
    

  updatedistances();
  headright45();
  delay(servodelay);
  //cerebrum();
  int final2 = cerebrum();
  if (final2 == 1 )
    {
      delay(500);
      finalDirect();
    }

  updatedistances();
  headcenter();
  delay(servodelay);
  //cerebrum();
  int final3 = cerebrum();
  if (final3 == 1 )
    {
      delay(500);
      finalDirect();
    }

  updatedistances();
  headleft45();
  delay(servodelay);
  //cerebrum();
  int final4 = cerebrum();
  if (final4 == 1 )
    {
      delay(500);
      finalDirect();
    }

  updatedistances();
  headleft90();
  delay(servodelay);
  //cerebrum();
  int final5 = cerebrum();
  if (final5 == 1 )
    {
      delay(500);
      finalDirect();
    }

  updatedistances();
  headleft45();
  delay(servodelay);
  //cerebrum();
  int final6= cerebrum();
  if (final6 == 1 )
    {
      delay(500);
      finalDirect();
    }

  updatedistances();
  headcenter();
  delay(servodelay);
  //cerebrum();
  int final7 = cerebrum();
  if (final7 == 1 )
    {
      delay(500);
      finalDirect();
    }

  updatedistances();
  headright45();
  delay(servodelay);
  //cerebrum();
  int final8 = cerebrum();
  if (final8 == 1 )
    {
      delay(500);
      finalDirect();
    }
}




int updatedistances()
{ 
  int stopb ;
  obst = proxihead();
  delay(15);
  emebreak = emergencybreak();
   if  (obst == 1  || emebreak == 1)
      { 
        stopb = 1 ;
      }
  else
      {
        stopb = 0 ;
      }
  return stopb ;
}

/////?
 int updateEmeBreak()
 {       
  int stopb ;
  emebreak = emergencybreak();
   if  (obst == 1  || emebreak == 1)
      { 
        stopb = 1 ;
      }
  else
      {
        stopb = 0 ;
      }
  return stopb ;
}


int cerebrum()
{
  int stopb = updatedistances();
  int changeDirection ;
  if (stopb == 1)
      {
        stopall();
        changeDirection = 1;
      }
  else
      {
        gostraight();
        changeDirection = 0;
      }
   return changeDirection ;
}

int cerebrum1() 
{
  int stopb = updatedistances();
  int changeDirection ;
  if (stopb == 1)
      {
        changeDirection = 1;
      }
  else
      {
        changeDirection = 0;
      }
   return changeDirection ;
}



//// SPEED CORRECTIONS
void gostraight()
{
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  //lookaround();
}

//// SPEED CORRECTIONS
void gobackwards()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 255);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 255);

 
}




void turnleft90()
{
  stopall();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 190);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(740);
  stopall();
}




void turnright90()
{
  stopall();
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 190);
  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(740);
  stopall();
}


void headright90() 
{ 
 
  myservo.write(35);
 
}

void headright45()
{
  
  myservo.write(55);
  
}

void headcenter()
{
  
  myservo.write(90);
 
}

void headleft45()
{
  
  myservo.write(145);
  
}

void headleft90()
{
  
  myservo.write(165);
  
}


///////// MAIN ///////

void loop () 
{
  lookaround(); 
}





