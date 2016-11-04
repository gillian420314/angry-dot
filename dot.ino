//include library
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//Define Variables
#define OLED_MOSI 11 //D1
#define OLED_CLK 12 //D0
#define OLED_DC 9 //DC
#define OLED_CS 8 //CS
#define OLED_RESET 10 //RES
#define Light_PIN A0
#define Button 2
int buttonState = 0;
int x = 140;
int x2 = 140;
int y = 22;
int r;
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
static const unsigned char PROGMEM DOT[] = {
  0x3f,0x3f,
  0x7f,0xff,
  0xff,0xff,
  0x7f,0xff,
  0x3f,0x3f,
};
static const unsigned char PROGMEM SQUARE[] = {
  0xff,0xff,
  0xff,0xff,
  0xff,0xff,
  0xff,0xff,
  0xff,0xff,
};
void square(){
  display.drawBitmap(x, 22, SQUARE, 10, 5,WHITE);
  display.display();
  r = random(1, 8);
  //delay(15);
  //display.clearDisplay();
}
void dot(){
  display.drawBitmap(25, y, DOT, 10, 5,WHITE);
  display.display();
  delay(15);
  display.clearDisplay();
  square();//call square
  x-=r;
}
void jump(){
   while(y>2){ 
    dot();
    y-=2;
    Serial.println(x);
   }
   if(y<=2) y=2;
   while(y<22){ 
    dot(); 
        y+=2; 
        Serial.println(x); 
      }
}
void gameover(){
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(20,15);
  display.print("GAMEOVER");
  display.display();
}
void haha(){
  gameover();
  while(1);
  
  }
void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  pinMode(Button, INPUT);
  randomSeed(analogRead(0)); 
}

void loop() {
  if(x==y) haha();
  buttonState = digitalRead(Button);
  if ( buttonState == HIGH ){ jump(); }
  dot(); Serial.println(x); 
  
  if(x<=0) x=140;
  
   //while(x=140){quare();}
   //if (x2<=r) {x2=140;}
   //if() gameover();
}
