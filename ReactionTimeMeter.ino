
//setup constants and global values
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // display width
#define SCREEN_HEIGHT 64 // display height
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const int LED_PIN = 2;
const int BUTTON_PIN = 4;
int buttonState;
int waitTime;
int reactionTime;
long startTime;
long endTime;

void setup() {

  //set up console for error message
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);         //set text size   
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner

  //set up led and button
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  //print start screen until initiated
  display.clearDisplay();
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("Press to\nstart test"));
  display.display();

  reactionTime = 0;
  buttonState = LOW;
  buttonState = digitalRead(BUTTON_PIN);
  if(buttonState == HIGH){
    //print ready message
    display.clearDisplay();
    display.setCursor(0,0);             // Start at top-left corner
    display.print(F("Get\nready..."));
    display.display();
    //generate LED wait time
    randomSeed(millis());
    waitTime = random(3, 8);
    delay(waitTime*1000);
    //indicate to the user that they can press the button now
    display.clearDisplay();
    display.setCursor(0,0);             // Start at top-left corner
    display.print(F("Go!"));
    display.display();
    digitalWrite(LED_PIN, HIGH);
    startTime = millis();
    buttonState = LOW;
    //wait until user presses button
    while(buttonState == LOW){
      buttonState = digitalRead(BUTTON_PIN);
    }
    //display reaction time
    endTime = millis();
    digitalWrite(LED_PIN, LOW);
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("You took:\n");
    display.print(endTime-startTime);
    display.print(F(" ms"));
    display.display();
    delay(8000);



  }


}

