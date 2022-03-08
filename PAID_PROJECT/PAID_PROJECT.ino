/* This code works with MLX90614 (GY906) and OLED screen
 * It measures both ambient and object temperature in Fahrenheit and display it on the screen
 * Please visit www.surtrtech.com for more details
 */

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); //Declaring the display name (display)
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
const int trigPin = 11;
const int echoPin = 12;
long duration;
int distance;
void setup() {  
  
  mlx.begin(); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Start the OLED display
  display.clearDisplay();
  display.display();
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    if(distance < 10){
      display.clearDisplay();
  
      display.setTextSize(2);                    
      display.setTextColor(WHITE);              
      display.setCursor(0,0);
      display.println("Your Temp");
     
      display.setCursor(110,0);
      display.setTextSize(1);                    
      display.setTextColor(WHITE);             
      display.setCursor(0,20);                
      display.println("Temp"); 
      
      display.setTextSize(2);
      display.setCursor(50,17);
      display.println(mlx.readObjectTempC(),1);
      
      display.setCursor(110,17);
      display.println("C");
      
      display.display();

      if(mlx.readObjectTempC() < 32 ){
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH);
        delay(2000);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN1,HIGH);
        digitalWrite(IN4,HIGH);
        delay(2000);
        digitalWrite(IN1,LOW);
        digitalWrite(IN4,LOW);
      }
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4 ,LOW);
    }
    
     
}
