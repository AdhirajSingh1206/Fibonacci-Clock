#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);

RTC_DS1307 rtc;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned long lastTime ;                           // MAIN CLOCK WORKS 

int lastButtonState2 ;                             // HOURS UPDATE BUTTON 
int buttonState2 ;  

int lastButtonState3 ;                             // MINUTES UPDATE BUTTON
int buttonState3 ;  

int lastButtonState4 ;                             // ACTIVATION UPDATE BUTTON
int buttonState4 ;  
int reading ;
int activationState ;
unsigned long lastDebounceTime ; 

int lastButtonState5 ;                             // PALLETE UPDATE BUTTON  
int buttonState5 ; 
int palleteChoice ;   

//////////////////////////////////////PALLETE/CHOICES///////////////////////////////////////////////////////// 

uint32_t colors[10][3] =
{
  {
    // #1 RGB
    pixels.Color(255, 10, 10), // hours
    pixels.Color(10, 255, 10), // minutes
    pixels.Color(10, 10, 255) // both;
  },
  {
    // #2 Mondrian
    pixels.Color(255, 10, 10), // hours
    pixels.Color(248, 222, 0), // minutes
    pixels.Color(10, 10, 255) // both;
  },
  {
    // #3 Basbrun
    pixels.Color(80, 40, 0), // hours
    pixels.Color(20, 200, 20), // minutes
    pixels.Color(255, 100, 10) // both;
  },
  {
    // #4 80's
    pixels.Color(245, 100, 201), // hours
    pixels.Color(114, 247, 54), // minutes
    pixels.Color(113, 235, 219) // both;
  }
  ,
  {
    // #5 Pastel
    pixels.Color(255, 123, 123), // hours
    pixels.Color(143, 255, 112), // minutes
    pixels.Color(120, 120, 255) // both;
  }
  ,
  {
    // #6 Modern
    pixels.Color(212, 49, 45), // hours
    pixels.Color(145, 210, 49), // minutes
    pixels.Color(141, 95, 224) // both;
  }
  ,
  {
    // #7 Cold
    pixels.Color(209, 62, 200), // hours
    pixels.Color(69, 232, 224), // minutes
    pixels.Color(80, 70, 202) // both;
  }
  ,
  {
    // #8 Warm
    pixels.Color(237, 20, 20), // hours
    pixels.Color(246, 243, 54), // minutes
    pixels.Color(255, 126, 21) // both;
  }
  ,
  {
    //#9 Earth
    pixels.Color(70, 35, 0), // hours
    pixels.Color(70, 122, 10), // minutes
    pixels.Color(200, 182, 0) // both;
  }
  ,
  {
    // #10 Dark
    pixels.Color(211, 34, 34), // hours
    pixels.Color(80, 151, 78), // minutes
    pixels.Color(16, 24, 149) // both;
  }
};

//////////////////////////////////////BASIC/SETUP////////////////////////////////////////////////////////////

void setup() {

  pinMode(2, INPUT);                                // SETTING UP INPUTS
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  Serial.begin(57600);                              // SERIAL FOR DEBUGGING
  Serial.println("Starting");                      
  
  Serial.begin(57600);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  pixels.begin();
  pixels.show();                                    // INITIALIZING ALL PIXELS TO 'OFF'

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));   // UPDATES TIME ACCORDING TO COMPUTERS TIME 
 
 }

////////////////////////////////////////MAIN/CLOCK/WORKS///////////////////////////////////////////////////////////////
String Set(int digit, int type) {

  String ret ;

  if (digit == 1) {
    switch (random(1, 3)) {
      case 1 :
        ret =  "B----" ;
        break ;
      case 2:
        ret = "-B---" ;
        break ;
    }
  }

  if (digit == 2) {
    switch (random(1, 3)) {
      case 1 :
        ret =  "BB---" ;
        break ;
      case 2:
        ret = "--B--" ;
        break ;
    }
  }

  if (digit == 3) {
    switch (random(1, 4)) {
      case 1 :
        ret =  "B-B--" ;
        break ;
      case 2:
        ret = "-BB--" ;
        break ;
      case 3:
        ret = "---B-" ;
        break ;
    }
  }

  if (digit == 4) {
    switch (random(1, 4)) {
      case 1 :
        ret =  "BBB--" ;
        break ;
      case 2:
        ret = "B--B-" ;
        break ;
      case 3:
        ret = "-B-B-" ;
        break ;
    }
  }

  if (digit == 5) {
    switch (random(1, 4)) {
      case 1 :
        ret =  "--BB-" ;
        break ;
      case 2:
        ret = "----B" ;
        break ;
      case 3:
        ret = "BB-B-" ;
        break ;
    }
  }

  if (digit == 6) {
    switch (random(1, 5)) {
      case 1 :
        ret =  "B---B" ;
        break ;
      case 2:
        ret = "-B--B" ;
        break ;
      case 3:
        ret = "B-BB-" ;
        break ;
      case 4:
        ret = "-BBB-" ;
        break ;
    }
  }

  if (digit == 7) {
    switch (random(1, 4)) {
      case 1 :
        ret =  "--B-B" ;
        break ;
      case 2:
        ret = "BB--B" ;
        break ;
      case 3:
        ret = "BBBB-" ;
        break ;
    }
  }

  if (digit == 8) {
    switch (random(1, 4)) {
      case 1 :
        ret =  "---BB" ;
        break ;
      case 2:
        ret = "B-B-B" ;
        break ;
      case 3:
        ret = "-BB-B" ;
        break ;
    }
  }

  if (digit == 9) {
    switch (random(1, 4)) {
      case 1 :
        ret =  "B--BB" ;
        break ;
      case 2:
        ret = "-B-BB" ;
        break ;
      case 3:
        ret = "BBB-B" ;
        break ;
    }
  }

  if (digit == 10) {
    switch (random(1, 3)) {
      case 1 :
        ret =  "--BBB" ;
        break ;
      case 2:
        ret = "BB-BB" ;
        break ;
    }
  }

  if (digit == 11) {
    switch (random(1, 3)) {
      case 1 :
        ret =  "B-BBB" ;
        break ;
      case 2:
        ret = "-BBBB" ;
        break ;
    }
  }

  if (digit == 12) {
    ret =  "BBBBB" ;
  }

  if ( type == 1 ) {
    return ret ;
  } else {
    ret.replace('B', 'R');
    return ret ;
  }
}


String Merge(String  M , String H ) {
  String mer = M ;
  for ( int i  = 0 ; i < 5 ; i++ ) {
    if (( M.charAt(i) == 'B' ) && (H.charAt(i) == 'R'))  {       // IF BOTH RED AND BLUE ARE ON
      mer.setCharAt(i, 'G') ;
    } else {
      if (( M.charAt(i) == '-' ) && (H.charAt(i) == 'R'))  {
        mer.setCharAt(i, 'R')    ;
      }
    }
  }
  return mer ;
}


void colourPut(String conv , int p  ) {       
  for ( int j  = 0 ; j < 5 ; j++ ) {
    if ( conv.charAt(j) == 'B' ) {
      pixels.setPixelColor(j, colors[p][1]);
    } else if ( conv.charAt(j) == 'R' ) {
      pixels.setPixelColor(j, colors[p][2]);
    } else if ( conv.charAt(j) == 'G' ) {
      pixels.setPixelColor(j, colors[p][3]);
    } else if ( conv.charAt(j) == '-' ) {
      pixels.setPixelColor(j, pixels.Color(0, 0, 0));
    }
    pixels.show();
  }
}


int RoundingOff (int dig ) {                                     // ROUNDS OFF MINUTES TO 0s AND 5s  
                                                                 // ACCURACY IS 5 MINUTES
  int  tens = dig / 10 ;
  int ones = dig - (tens * 10) ;

  if ( ones < 5 ) {
    ones = 0 ;
  } else  {
    ones = 5   ;
  }

  dig = (tens * 10) + ones ;
  dig /= 5 ;                                                     // MULTIPLY BY 5 TO GET MINUTES 
  return dig ;
}


void loop() {
  
  //////////////////////////////////////PALLETE/UPDATE/BUTTON///////////////////////////////////////////////////////
       
  buttonState5 = digitalRead(5);

  if (buttonState5 != lastButtonState5) {
    if (buttonState5 == HIGH && activationState == HIGH ) {      // ONLY WHEN UPDATE BUTTON IS ACTIVE 
      palleteChoice++ ;
    }
  }

  if( palleteChoice >= 10 ) palleteChoice = 0 ;                  // ONLY TEN PALLETES ARE AVAILABLE

  //////////////////////////////////////ACTIVATION/UPDATE/BUTTON///////////////////////////////////////////////////////
                                        
  reading = digitalRead(4);
  if (reading != lastButtonState4) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > 50) {                      // DOUNCE DELAY IS 50 
    if (reading != buttonState4) {
      buttonState4 = reading;

      if (buttonState4 == HIGH) {
        activationState = !activationState;
      }
    }
  }
  
  //////////////////////////////////////HOURS/UPDATE/BUTTON///////////////////////////////////////////////////////
                                        
  buttonState2 = digitalRead(2);

  if (buttonState2 != lastButtonState2) {
    if (buttonState2 == HIGH && activationState == HIGH ) {      // ONLY WHEN UPDATE BUTTON IS ACTIVE 
      DateTime newTime = DateTime(rtc.now().unixtime() + 3600);
      rtc.adjust( newTime );
    
      goto q ;                                                   // UPDATES TIMES AGAIN
    }
  }

  //////////////////////////////////////MINUTES/UPDATE/BUTTON//////////////////////////////////////////////////////
                                        
  buttonState3 = digitalRead(3);

  if (buttonState3 != lastButtonState3) {
    if (buttonState3 == HIGH && activationState == HIGH) {       // ONLY WHEN UPDATE BUTTON IS ACTIVE 
      DateTime fixTime = rtc.now();
      DateTime newTime = DateTime(
       fixTime.year(),
       fixTime.month(),
       fixTime.day(),
       fixTime.hour(),
       ((fixTime.minute() - fixTime.minute() % 5) + 5) % 60, 0);
      rtc.adjust( newTime );
      
      goto q ;                                                   // UPDATES TIMES AGAIN
    }

  }

  ///////////////////////////////////////MAIN/CLOCK/CONTROL////////////////////////////////////////////////////
                                                                                  
  if ((millis() - lastTime) > 300000) {

    q :
    
    DateTime now = rtc.now();
    int h = now.hour() ;
    int m = RoundingOff(now.minute());

    if ( h > 12 ) {
      h -= 12 ;
    }

    Serial.println(h) ;
    Serial.println(m) ;
    Serial.println(activationState);                             // EDIT BUTTON TOGGLE  

    String mi = Set(m , 1 ) ;
    String ho = Set(h , 2 ) ;

    String colour = Merge(mi, ho) ;
    colourPut(colour, palleteChoice ) ;
    Serial.println(colour) ;
   
    lastTime = millis() ;
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  lastButtonState2 = buttonState2;                               // RESETTING BUTTON STATES
  lastButtonState3 = buttonState3;
  lastButtonState4 = reading;
  lastButtonState5 = buttonState5;

}
