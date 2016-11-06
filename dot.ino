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
int x1 = 128;
int y1 = 22;
int x2 = 26;
int y2 = 22;
int i = 0;
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

void gameover(){
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(18,10);
  display.print("GAMEOVER");
  display.display();
}

void youlose(){
  delay(500);
  gameover();
  //haha();
  while(1);
}
void score(){
  //display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(60,0);
  display.print("score:");
  display.display();
}
void change(){
  //display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(100,0);
  display.print(i);
  display.display(); 
}
void square(){
  display.drawBitmap(x1, y1, SQUARE, 10, 5,WHITE); 
  display.display();
  //delay(15);
  //display.clearDisplay();
}
 
void dot(){
  display.drawBitmap(x2, y2, DOT, 10, 5,WHITE);
  display.display();
  delay(15);
  display.clearDisplay();
  score();//call score
  change();
  square();//call square
  x1-=r;
}
void jump(){
   while(y2>2){ 
    dot();
    y2-=2;
    Serial.println(x1);
   }
   if(y2<=2) y2=2;
   while(y2<22){ 
    dot(); 
        y2+=2; 
        Serial.println(x1);
      }

}

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  pinMode(Button, INPUT);
  randomSeed(analogRead(0)); 
}

void loop() {
  //change();
  buttonState = digitalRead(Button);
  if ( buttonState == HIGH ){ jump(); }
  dot();  Serial.println(x1); 
  r = random(1, 10);
  if(x1<=0) {i++;change();x1=128;}
  
  if ( (x1>24 && x1<32) && y2>18) youlose();
  //if(y2+5>y1+5 && (x1-10) < x2+10 && (x1+10) >x2-10) youlose();
  //if ( (x1>24 && x1<32) ) youlose();
  //if ( x1>26 && x1<30 ) youlose();
  if ( y2>18 && y2<22 ) youlose(); 
}
