#include <Mouse.h>

//Määritellään sisääntulopinnit
const int leftSensor = A0;
const int rightSensor = A1;
const int upSensor = A2;
const int downSensor = A3;

const int xPin   = A4;   
const int yPin   = A5;

const int activateButton = 8;

int leftAverage = 0;
int rightAverage = 0;
int upAverage = 0;
int downAverage = 0;

//Laita debug 1 jos haluat printtaukset serial monitorille
bool debug = 0;

int x = 0; 
int y = 0;
int z = 0;
float ax = 0.0;
float ay = 0.0;
float az = 0.0;

int yVertical = 0;
int xTiltUp = 0;
int xTiltDown = 0;
  
void setup() {
  pinMode(activateButton, INPUT);
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(upSensor, INPUT);
  pinMode(downSensor, INPUT);
  Serial.begin(19200);
}

void loop() {    
  bool active = digitalRead(activateButton);
  
  //Debug 1 jos haluat printtaukset
  if(debug = 1){
    Serial.println(active);
  }
  
  //if(active == 1)
  //{
    Average(leftSensor, rightSensor, upSensor, downSensor);
    Move(leftAverage, rightAverage, upAverage, downAverage);
  //}
}

//////////////////////////////////////////////////
void Move(int leftAverage, int rightAverage, int upAverage, int downAverage)
{
  int xSpeed = rightAverage - leftAverage;
  int ySpeed = upAverage - downAverage;
  xSpeed = map(xSpeed, 0, 20, 0, 10);
  ySpeed = map(ySpeed, 0, 20, 0, 10);
  
  if(abs(ySpeed) < abs(xSpeed)){
    
    for(int i = 0; i < abs(xSpeed); i++)
  {
    if(xSpeed < 0){
      
      Mouse.move(1, 0, 0);

    }
    else
    
    {
      Mouse.move(-1, 0, 0);
      
    }
if(abs(ySpeed) > i){
  
    if(ySpeed < 0){
      
      Mouse.move(0, -1, 0);
    }
    else
    {
      Mouse.move(0, 1, 0);
    }}}}
    
  if(abs(xSpeed) < abs(ySpeed)){
     
     for(int i = 0; i < abs(ySpeed); i++)
  {
    if(ySpeed < 0){
      
      Mouse.move(0, -1, 0);

    }
    else
    
    {
      Mouse.move(0, 1, 0);
      
    }
    if(abs(xSpeed) > i){
      
    
    if(xSpeed < 0){
      
      Mouse.move(1, 0, 0);
    }
    else
    {
      Mouse.move(-1, 0, 0);
    }
  }}}}
  

void Average(int leftSensor, int rightSensor, int upSensor, int downSensor)
{
  float leftAverages[3];
  float rightAverages[3];
  float upAverages[3];
  float downAverages[3];
  int leftValues[20];
  int rightValues[20];
  int upValues[20];
  int downValues[20];
  
  for(int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      leftValues[j] = analogRead(leftSensor);
      rightValues[j] = analogRead(rightSensor);
      upValues[j] = analogRead(upSensor);
      downValues[j] = analogRead(downSensor);
    }
    leftAverages[i] = MaxMinAverage(leftValues);
    rightAverages[i] = MaxMinAverage(rightValues);
    upAverages[i] = MaxMinAverage(upValues);
    downAverages[i] = MaxMinAverage(downValues);
  }
  
  for (int i = 0; i < 3; ++i) 
  {
    int a = 0; 
    for (int j = i + 1; j < 3; ++j)
    {   
      if (leftAverages[i] > leftAverages[j]) 
      {  
        a =  leftAverages[i];
        leftAverages[i] = leftAverages[j];
        leftAverages[j] = a;
      }  
    }
  }
  for (int i = 0; i < 3; ++i) 
  {
    int a = 0; 
    for (int j = i + 1; j < 3; ++j)
    {   
      if (rightAverages[i] > rightAverages[j]) 
      {   
        a =  rightAverages[i];
        rightAverages[i] = rightAverages[j];
        rightAverages[j] = a;
      }  
    }
  }
  for (int i = 0; i < 3; ++i) 
  {
    int a = 0; 
    for (int j = i + 1; j < 3; ++j)
    {   
      if (downAverages[i] > downAverages[j]) 
      {  
        a =  downAverages[i];
        downAverages[i] = downAverages[j];
        downAverages[j] = a;
      }  
    }
  }
  for (int i = 0; i < 3; ++i) 
  {
    int a = 0; 
    for (int j = i + 1; j < 3; ++j)
    {   
      if (upAverages[i] > upAverages[j]) 
      {   
        a =  upAverages[i];
        upAverages[i] = upAverages[j];
        upAverages[j] = a;
      }  
    }
  }
  leftAverage = leftAverages[1];
  rightAverage = rightAverages[1];
  upAverage = upAverages[1];
  downAverage = downAverages[1];
}
///////////////////////////////////////////////
int MaxMinAverage(int sensorValues[])
{
  int average;
  int maximum = 0;
  int minimum = 1024;
  for(int i = 0; i  < 20; i++)
  {
    if(sensorValues[i] > maximum )
    {
      maximum = sensorValues[i];
    }
    if(sensorValues[i] < minimum )
    {
      minimum = sensorValues[i];
    }
  }
  average = maximum - minimum;
  
  //Debug 1 jos haluat printtaukset
  if(debug == 1)
  {
    Serial.print("Average: ");
    Serial.println(average);
  }
  return average;
}
/////////////////////////////////////////
void TiltControl(){

 y = 1;

 for(int i = 0; i < 20; i++)
 {
  y = y + analogRead(yPin);
 }
  y = y / 20;
  ay = 0.1353 * y - 46.077;

if(ay > 3.5){
  yVertical = 1;
}
if(ay < 1){
  yVertical = 0;
}
 x = 1;

 for(int i = 0; i < 20; i++)
 {
  x = x + analogRead(xPin);
 }
  x = x / 20;
  ax = 0.1463 * x - 50.767;

if(ax > 1){
  xTiltUp = 1;
}
if(ax < 0){
  xTiltUp = 0;
}
if(ax < -1){
  xTiltDown = 1;
}
if(ax > -0.45){
  xTiltDown = 0;
}}
///////////////////////////////////////
