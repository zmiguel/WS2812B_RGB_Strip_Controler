#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define NUM_LEDS 292 //how many leds
#define DATA_PIN 21 //data min, hint: 21

#define Diff 8;
#define HSVDiff 2;

//Brightness & RGB pins
#define BriPls 2
#define BriMin 3
#define BriRst 4

#define btn11 5
#define btn12 6
#define btn13 7

#define btn21 8
#define btn22 9
#define btn23 10

#define btn31 16
#define btn32 14
#define btn33 15

#define btnDefault 18
#define btnModeBack 19
#define btnModeNext 20

#define FRAMES_PER_SECOND  120

int BriArr[] = {0, 2, 4, 8, 16, 32, 64, 128, 255};
int BriVal = 5;
int RedVal = 255;
int GrnVal = 255;
int BluVal = 255;

int HueVal = 0;
int SatVal = 255;
int ValVal = 255;

int mode = 1;
int nModes = 3; //total number of modes

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

//buttons
long tm = 0;
long debounce = 200;
int reading;
int resp;

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

void updateStripRGB(){
  fill_solid(leds,NUM_LEDS,CRGB(RedVal,GrnVal,BluVal));
}

void updateStripHSV(){
  fill_solid(leds,NUM_LEDS,CHSV(HueVal,SatVal,ValVal));
}

void updateStripBri(){
  FastLED.setBrightness(BriArr[BriVal]);
}

void setPins(){
  pinMode(BriPls, INPUT_PULLUP);
  pinMode(BriMin, INPUT_PULLUP);
  pinMode(BriRst, INPUT_PULLUP);
  pinMode(btn11, INPUT_PULLUP);
  pinMode(btn12, INPUT_PULLUP);
  pinMode(btn13, INPUT_PULLUP);
  pinMode(btn21, INPUT_PULLUP);
  pinMode(btn22, INPUT_PULLUP);
  pinMode(btn23, INPUT_PULLUP);
  pinMode(btn31, INPUT_PULLUP);
  pinMode(btn32, INPUT_PULLUP);
  pinMode(btn33, INPUT_PULLUP);
  pinMode(btnDefault, INPUT_PULLUP);
  pinMode(btnModeBack, INPUT_PULLUP);
  pinMode(btnModeNext, INPUT_PULLUP);
}

void setup() {
  delay(1000);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  updateStripRGB();
  updateStripBri();
  setPins();
}

//Brightness Functions
void incBri(){
  BriVal++;
  if(BriVal > 8){BriVal = 8;}
}
void decBri(){
  BriVal--;
  if(BriVal < 0){BriVal = 0;}
}
void rstBri(){
  BriVal = 5;  
}
//Red Functions
void incRed(){
  RedVal += Diff;
  if(RedVal > 255){RedVal = 255;}
}
void decRed(){
  RedVal -= Diff;
  if(RedVal < 0){RedVal = 0;}
}
void rstRed(){
  RedVal = 255;  
}
//Green Functions
void incGrn(){
  GrnVal += Diff;
  if(GrnVal > 255){GrnVal = 255;}
}
void decGrn(){
  GrnVal -= Diff;
  if(GrnVal < 0){GrnVal = 0;}
}
void rstGrn(){
  GrnVal = 255;  
}
//Blue Functions
void incBlu(){
  BluVal += Diff;
  if(BluVal > 255){BluVal = 255;}
}
void decBlu(){
  BluVal -= Diff;
  if(BluVal < 0){BluVal = 0;}
}
void rstBlu(){
  BluVal = 255;  
}
//Hue Functions
void incHue(){
  HueVal += HSVDiff;
}
void decHue(){
  HueVal -= HSVDiff;
}
void rstHue(){
  HueVal = 0;  
}
//Mode Functions
void modeNext(){
  mode++;
  if(mode>nModes){mode = 1;}
}
void modeBack(){
  mode--;
  if(mode<1){mode = nModes;}
}
void modeRst(){
  mode = 0;
}
//READ PRESSED BUTTON
int getBtn(){
  //Serial.println(digitalRead(BriMin));
  if(digitalRead(BriPls) == LOW && millis() - tm > debounce){
    //Bri+
    tm = millis();
    return 1;
  }else if(digitalRead(BriMin) == LOW && millis() - tm > debounce){
    //Bri-
    tm = millis();
    return 2;
  }else if(digitalRead(BriRst) == LOW && millis() - tm > debounce){
    //Bri Rst
    tm = millis();
    return 3;
  }else if(digitalRead(btn11) == LOW && millis() - tm > debounce){
    //Red+
    tm = millis();
    return 4;
  }else if(digitalRead(btn12) == LOW && millis() - tm > debounce){
    //Red-
    tm = millis();
    return 5;
  }else if(digitalRead(btn13) == LOW && millis() - tm > debounce){
    //Red Rst
    tm = millis();
    return 6;
  }else if(digitalRead(btn21) == LOW && millis() - tm > debounce){
    //Grn+
    tm = millis();
    return 7;
  }else if(digitalRead(btn22) == LOW && millis() - tm > debounce){
    //Grn-
    tm = millis();
    return 8;
  }else if(digitalRead(btn23) == LOW && millis() - tm > debounce){
    //Grn Rst
    tm = millis();
    return 9;
  }else if(digitalRead(btn31) == LOW && millis() - tm > debounce){
    //Blu+
    tm = millis();
    return 10;
  }else if(digitalRead(btn32) == LOW && millis() - tm > debounce){
    //Blu-
    tm = millis();
    return 11;
  }else if(digitalRead(btn33) == LOW && millis() - tm > debounce){
    //Blu Rst
    tm = millis();
    return 12;
  }else if(digitalRead(btnDefault) == LOW && millis() - tm > debounce){
    //Ext 1
    tm = millis();
    return 13;
  }else if(digitalRead(btnModeBack) == LOW && millis() - tm > debounce){
    //Ext 2
    tm = millis();
    return 14;
  }else if(digitalRead(btnModeNext) == LOW && millis() - tm > debounce){
    //Ext 3
    tm = millis();
    return 15;
  }else{
    return 0;
  }
}

void staticRGBMode(int mData){
  switch(mData){
    case 4:
      incRed();
      break;
    case 5:
      decRed();
      break;
    case 6:
      rstRed();
      break;
    case 7:
      incGrn();
      break;
    case 8:
      decGrn();
      break;
    case 9:
      rstGrn();
      break;
    case 10:
      incBlu();
      break;
    case 11:
      decBlu();
      break;
    case 12:
      rstBlu();
      break;
    default:
      break;
  }
  updateStripRGB();
}

void staticHSVMode(int mData){
  switch(mData){
    case 4:
      incHue();
      break;
    case 5:
      decHue();
      break;
    case 6:
      rstHue();
      break;
    default:
      break;
  }
  updateStripHSV();
}

void rainbowMode(int mData){
  fill_rainbow( leds, NUM_LEDS, gHue);
  gHue += 2;
}

void modeAction(int mData){
  switch(mode){
    case 1:
      staticRGBMode(mData);
      break;
    case 2: 
      staticHSVMode(mData);
      break;
    case 3:
      rainbowMode(mData);
      break;
  }
}

void loop() {
  resp = getBtn();
  switch(resp){
    case 1:
      incBri();
      updateStripBri();
      modeAction(0);
      break;
    case 2:
      decBri();
      updateStripBri();
      modeAction(0);
      break;
    case 3:
      rstBri();
      updateStripBri();
      modeAction(0);
      break;
    case 4:
      modeAction(resp);
      break;
    case 5:
      modeAction(resp);
      break;
    case 6:
      modeAction(resp);
      break;
    case 7:
      modeAction(resp);
      break;
    case 8:
      modeAction(resp);
      break;
    case 9:
      modeAction(resp);
      break;
    case 10:
      modeAction(resp);
      break;
    case 11:
      modeAction(resp);
      break;
    case 12:
      modeAction(resp);
      break;
    case 13:
      modeRst();
      modeAction(0);
      break;
    case 14:
      modeBack();
      modeAction(0);
      break;
    case 15:
      modeNext();
      modeAction(0);
      break;
    default:
      modeAction(0);
      break;
  }
  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND); 
}
