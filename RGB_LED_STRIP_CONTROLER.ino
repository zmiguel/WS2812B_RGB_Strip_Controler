#include <FastLED.h>

#define NUM_LEDS 292 //how many leds
#define DATA_PIN 21 //data min, hint: 21

#define Diff 8;
#define HSVDiff 4;

//Brightness & RGB pins
#define BriPls 2
#define BriMin 3
#define BriRst 4

#define RedPls 5
#define RedMin 6
#define RedRst 7

#define GrnPls 8
#define GrnMin 9
#define GrnRst 10

#define BluPls 16
#define BluMin 14
#define BluRst 15

#define ExtraOne 18
#define ExtraTwo 19
#define ExtraTre 20

int BriArr[] = {0, 2, 4, 8, 16, 32, 64, 128, 255};
int BriVal = 5;
int RedVal = 255;
int GrnVal = 255;
int BluVal = 255;

int HueVal = 0;
int SatVal = 255;
int ValVal = 255;

int State = 1;
//buttons
long tm = 0;
long debounce = 200;
int reading;
int resp;

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

void updateStripRGB(){
  fill_solid(leds,NUM_LEDS,CRGB(RedVal,GrnVal,BluVal));
  FastLED.show();
}

void updateStripHSV(){
  fill_solid(leds,NUM_LEDS,CHSV(HueVal,SatVal,ValVal));
  FastLED.show();
}

void updateStripBri(){
  FastLED.setBrightness(BriArr[BriVal]);
  FastLED.show();
}

void setPins(){
  pinMode(BriPls, INPUT_PULLUP);
  pinMode(BriMin, INPUT_PULLUP);
  pinMode(BriRst, INPUT_PULLUP);
  pinMode(RedPls, INPUT_PULLUP);
  pinMode(RedMin, INPUT_PULLUP);
  pinMode(RedRst, INPUT_PULLUP);
  pinMode(GrnPls, INPUT_PULLUP);
  pinMode(GrnMin, INPUT_PULLUP);
  pinMode(GrnRst, INPUT_PULLUP);
  pinMode(BluPls, INPUT_PULLUP);
  pinMode(BluMin, INPUT_PULLUP);
  pinMode(BluRst, INPUT_PULLUP);
  pinMode(ExtraOne, INPUT_PULLUP);
  pinMode(ExtraTwo, INPUT_PULLUP);
  pinMode(ExtraTre, INPUT_PULLUP);
}

void setup() {
  Serial.begin(9600);
  delay(500);
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
//READ PRESSED BUTTON
int getBtn(){
  //Serial.println(digitalRead(BriMin));
  if(digitalRead(BriPls) == LOW && millis() - tm > debounce){
    Serial.println("Bri+");
    tm = millis();
    return 1;
  }else if(digitalRead(BriMin) == LOW && millis() - tm > debounce){
    Serial.println("Bri-");
    tm = millis();
    return 2;
  }else if(digitalRead(BriRst) == LOW && millis() - tm > debounce){
    Serial.println("Bri Rst");
    tm = millis();
    return 3;
  }else if(digitalRead(RedPls) == LOW && millis() - tm > debounce){
    Serial.println("Red+");
    tm = millis();
    return 4;
  }else if(digitalRead(RedMin) == LOW && millis() - tm > debounce){
    Serial.println("Red-");
    tm = millis();
    return 5;
  }else if(digitalRead(RedRst) == LOW && millis() - tm > debounce){
    Serial.println("Red Rst");
    tm = millis();
    return 6;
  }else if(digitalRead(GrnPls) == LOW && millis() - tm > debounce){
    Serial.println("Grn+");
    tm = millis();
    return 7;
  }else if(digitalRead(GrnMin) == LOW && millis() - tm > debounce){
    Serial.println("Grn-");
    tm = millis();
    return 8;
  }else if(digitalRead(GrnRst) == LOW && millis() - tm > debounce){
    Serial.println("Grn Rst");
    tm = millis();
    return 9;
  }else if(digitalRead(BluPls) == LOW && millis() - tm > debounce){
    Serial.println("Blu+");
    tm = millis();
    return 10;
  }else if(digitalRead(BluMin) == LOW && millis() - tm > debounce){
    Serial.println("Blu-");
    tm = millis();
    return 11;
  }else if(digitalRead(BluRst) == LOW && millis() - tm > debounce){
    Serial.println("Blu Rst");
    tm = millis();
    return 12;
  }else if(digitalRead(ExtraOne) == LOW && millis() - tm > debounce){
    Serial.println("Ext 1");
    tm = millis();
    return 13;
  }else if(digitalRead(ExtraTwo) == LOW && millis() - tm > debounce){
    Serial.println("Ext 2");
    tm = millis();
    return 14;
  }else if(digitalRead(ExtraTre) == LOW && millis() - tm > debounce){
    Serial.println("Ext 3");
    tm = millis();
    return 15;
  }else{
    return 0;
  }
}


void loop() {
  resp = getBtn();
  switch(resp){
    case 1:
      incBri();
      updateStripBri();
      break;
    case 2:
      decBri();
      updateStripBri();
      break;
    case 3:
      rstBri();
      updateStripBri();
      break;
    case 4:
      incRed();
      updateStripRGB();
      break;
    case 5:
      decRed();
      updateStripRGB();
      break;
    case 6:
      rstRed();
      updateStripRGB();
      break;
    case 7:
      incGrn();
      updateStripRGB();
      break;
    case 8:
      decGrn();
      updateStripRGB();
      break;
    case 9:
      rstGrn();
      updateStripRGB();
      break;
    case 10:
      incBlu();
      updateStripRGB();
      break;
    case 11:
      decBlu();
      updateStripRGB();
      break;
    case 12:
      rstBlu();
      updateStripRGB();
      break;
    case 13:
      incHue();
      updateStripHSV();
      break;
    case 14:
      decHue();
      updateStripHSV();
      break;
    case 15:
      rstHue();
      updateStripHSV();
      break;
    default:
      break;
  }
}
