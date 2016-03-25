#include "Energia.h"
#include "pin_definitions.h"
#include "NEC_IR.h"
#include "pin_definitions.h"
#include "ultrasonic.h"
#define LEDR RED_LED
#define LEDB BLUE_LED
#define LEDG GREEN_LED
int dist;

void setup()
{
  ultrasonic_init(TRIG, ECHO);
  pinMode(LEFT_MOTOR_PWM,OUTPUT);                
  pinMode(RIGHT_MOTOR_PWM,OUTPUT);
  pinMode(LEFT_MOTOR_DIR,OUTPUT);                           
  pinMode(RIGHT_MOTOR_DIR,OUTPUT);
  pinMode(LEDR, OUTPUT); 
  pinMode(LEDB, OUTPUT); 
  pinMode(LEDG, OUTPUT); 
  pinMode(BEEP, OUTPUT);
  ir_init();
  Serial.begin(9600);
  tone(BEEP, 2400, 400);
}
void loop()
{
  char inp_char;
  dist = us_meassure();
  if (ir_data_get){
    ir_data_get = 0;
    Serial.print(ir_data.address_high, HEX);
    Serial.print(" ");
    Serial.print(ir_data.address_low, HEX);
    Serial.print(" ");
    Serial.println(ir_data.command, HEX);
    inp_char = ir_data.command; 
  }
  if (dist<=30){
    analogWrite (LEFT_MOTOR_PWM, 0);
    analogWrite (RIGHT_MOTOR_PWM, 0);
    delay (200);
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDB, LOW);
  digitalWrite(LEDG, LOW);
  tone(BEEP, 2400, 400);
  }   
  else if(inp_char==0xD)
  {
    digitalWrite(LEFT_MOTOR_DIR,HIGH);
  digitalWrite(RIGHT_MOTOR_DIR,HIGH);
  analogWrite(RIGHT_MOTOR_PWM,90);
  analogWrite(LEFT_MOTOR_PWM,90);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDR, HIGH);
  }
  else if(inp_char==0x10)
  {
    digitalWrite(LEFT_MOTOR_DIR,HIGH);
  digitalWrite(RIGHT_MOTOR_DIR,HIGH);
  analogWrite(RIGHT_MOTOR_PWM,40);
  analogWrite(LEFT_MOTOR_PWM,0);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDR, LOW);
  }
  else if(inp_char==0x12)
  {
    digitalWrite(LEFT_MOTOR_DIR,HIGH);
  digitalWrite(RIGHT_MOTOR_DIR,HIGH);
  analogWrite(RIGHT_MOTOR_PWM,0);
  analogWrite(LEFT_MOTOR_PWM,40);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, LOW);
  digitalWrite(LEDR, LOW);
  }
  else if(inp_char==0x11)
  {
    digitalWrite(LEFT_MOTOR_DIR,HIGH);
  digitalWrite(RIGHT_MOTOR_DIR,HIGH);
  analogWrite(RIGHT_MOTOR_PWM,0);
  analogWrite(LEFT_MOTOR_PWM,0);
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
  }
  inp_char = 0;
}



