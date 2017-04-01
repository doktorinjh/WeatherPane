/*  WeatherPane Display for Arduino Yun and Adafruit NeoPixels
 *  Created: October, 2015
 *  
 *  Thanks to the Arduino.cc and /r/Arduino Forum Users for helping
 *  answer my questions while creating this. 
 *
 *  This sketch uses two python scripts to access real time weather
 *  updates from Weather Underground's Weather API and display the
 *  information as weather icons and numbers on a 10x10 Neopixel
 *  display. 
 *  
 *  If you make any improvements, I'd like to see what you've done!
 *  doktorinjh@gmail.com
 *  
 *  p.s. This was my very first Arduino project and it was inspired by
 *  the ubiquitous Word Clock. There are probably improvements that 
 *  can be made!
 *  
 *  This sketch is not licensed for commercial use and may not be
 *  replicated or sold without written permission.
 *  
 *  Change Log (For my own sanity):
 *  10/30/16 - Added additional weather conditions for Light/Heavy
 *  5/29/16 - Moved scripts to Arduino instead of SD card
 *  5/4/16 - Fixed Current Precip issue
 *  5/3/16 - Added station identification
 */


//Include Libraries
#include <Process.h>
#include <Bridge.h>
#include <Adafruit_NeoPixel.h>

//Pin for Data Connection
#define PIN 6 

//Setup 100 LED Neopixel on Pin 9
Adafruit_NeoPixel strip = Adafruit_NeoPixel (100, PIN, NEO_GRB + NEO_KHZ800);

//Variables for Location and Update Time
char location[25];
char update_time[50];
char station[10];

//Variables for Current Conditions
char current_temp[6];
char current_weather[25];
char current_precip[6];

//Variables for Today's Forecast
char today_high[6];
char today_low[6];
char today_weather[25];
char today_precip[6];
char today_snow[6];

//Variables for Tonight's Forecast
char tonight_high[6];
char tonight_low[6];
char tonight_weather[25];
char tonight_precip[6];
char tonight_snow[6];

//Variables for Tomorrow's Forecast
char tomorrow_high[6];
char tomorrow_low[6];
char tomorrow_weather[25];
char tomorrow_precip[6];
char tomorrow_snow[6];

//Delay between Weather Underground updates
unsigned long interval=1800000;              // Wait 30 Minutes to update from WeatherUnderground
unsigned long previousMillis=0;

void setup() {
  
  //Start the Bridge and Serial
  Bridge.begin();
  delay(7000);
  Console.begin();
  delay(7000);

  //Turn all LEDs off, if they weren't before
  strip.begin();
  strip.show();

  //Get initial Values from the Bridge
  Process bridge;
  bridge.runShellCommand("python /WU_Bridge.py");
  delay(7000);
  
  //Get the weather data from the Python script
  Process variables;
  variables.runShellCommand("python /WU_Variables.py");
}


void loop() {

  //Run the Python script to get new weather values from WU every 30 minutes
  if ((unsigned long) (millis() - previousMillis) >= interval){
  previousMillis = millis();
  Process bridge;
  bridge.runShellCommand("python /WU_Bridge.py");
  }

  //Get the weather data from the Python script
  Process variables;
  variables.runShellCommand("python /WU_Variables.py");

  //Get Variables from the Bridge and Convert to integers (except for weather conditions)
  Bridge.get("current_temp", current_temp, 6);
  Bridge.get("current_weather", current_weather, 25);
  Bridge.get("current_precip", current_precip, 6);
  Bridge.get("today_high", today_high, 6);
  Bridge.get("today_low", today_low, 6);
  Bridge.get("today_weather", today_weather, 25);
  Bridge.get("today_precip", today_precip, 6);
  Bridge.get("today_snow", today_snow, 6);
  Bridge.get("tonight_high", tonight_high, 6);
  Bridge.get("tonight_low", tonight_low, 6);
  Bridge.get("tonight_weather", tonight_weather, 25);
  Bridge.get("tonight_precip", tonight_precip, 6);
  Bridge.get("tonight_snow", tonight_snow, 6);
  Bridge.get("tomorrow_high", tomorrow_high, 6);
  Bridge.get("tomorrow_low", tomorrow_low, 6);
  Bridge.get("tomorrow_weather", tomorrow_weather, 25);
  Bridge.get("tomorrow_precip", tomorrow_precip, 6);
  Bridge.get("tomorrow_snow", tomorrow_snow, 6);
  Bridge.get("location", location, 25);
  Bridge.get("time", update_time, 50);
  Bridge.get("station", station, 10);
  
  //Convert values to integers
  int current_temp_int = atoi(current_temp);
  int current_precip_int = atoi(current_precip);
  int today_high_int = atoi(today_high);
  int today_low_int = atoi(today_low);
  int today_precip_int = atoi(today_precip);
  int today_snow_int = atoi(today_snow);
  int tonight_high_int = atoi(today_high);
  int tonight_low_int = atoi(today_low);
  int tonight_precip_int = atoi(today_precip);
  int tonight_snow_int = atoi(today_snow);
  int tomorrow_high_int = atoi(tomorrow_high);
  int tomorrow_low_int = atoi(tomorrow_low);
  int tomorrow_precip_int = atoi(tomorrow_precip);
  int tomorrow_snow_int = atoi(tomorrow_snow);

  //Print Weather to Serial Monitor to check the incoming data (optional)
  Console.print("In ");
  Console.print(location);
  Console.print(", it is currently ");
  Console.print(current_temp_int);
  Console.print(" degrees out and ");
  Console.print(current_weather);
  Console.println(".");
  Console.print("There is a ");
  Console.print(current_precip_int);
  Console.println("% chance of precip right now.");

  if (today_snow_int > 0) {           //Only print if snow is expected
  Console.print(today_snow_int);
  Console.println(" inches of snow are expected.");
  Console.println("");}

  Console.print("Today's high is ");
  Console.print(today_high_int);
  Console.println(".");
  Console.println("");

  Console.print("Tonight will be ");
  Console.print(tonight_weather);
  Console.print(" with a low of ");
  Console.print(tonight_low_int);
  Console.println(".");
  Console.println("");

  Console.print("Tomorrow will be ");
  Console.print(tomorrow_weather);
  Console.print(" with a high of ");
  Console.print(tomorrow_high_int);
  Console.print(" and a low of ");
  Console.print(tomorrow_low_int);
  Console.println(".");
  Console.print("There is a ");
  Console.print(tomorrow_precip_int);
  Console.println("% chance of precip tomorrow.");
  Console.println("");

  if (tomorrow_snow_int > 0) {           //Only print if snow is expected
  Console.print(tomorrow_snow_int);
  Console.println(" inches of snow are expected.");
  Console.println("");}
  
  //Print Update Time
  Console.println(update_time);
  Console.println("Station ID: ");
  Console.println(station);
  Console.println("");
  Console.println("*************************************************************");
  Console.println("");



  //Start the Weather Display!
  ClearDisplay ();                        // Clear the board between updates


  //CURRENT Conditions
  Now ();                                 // Display NOW
  Temperature (current_temp_int);         // Display Current Temp
  Precipitation (current_precip_int);     // Display Current Precipitation Chance
  Condition (current_weather);            // Display Current Weather Icon
    strip.show();                         // Send display to Board
      delay(15000);                       // Display Current Conditions for 15 seconds


  //TODAY's Forecast
  ClearDisplay ();                        // Clear the display 
  Today ();                               // Display TODAY
  High ();                                // Display HIGH
  Temperature (today_high_int);           // Get Today's High Temp
  Precipitation (today_precip_int);       // Display Today's Chance of Precipitation
  Condition (today_weather);              // Get Today's Forecast Icon
  Snow (today_snow_int);                  // Display Today's Snow Forecast
    strip.show();                         // Send display to Board
      delay(15000);                       // Display Today's Forecast for 15 seconds


  //TONIGHT's Forecast
  ClearDisplay ();                        // Clear the display
  Tonight ();                             // Display TONIGHT
  Low ();                                 // Display LOW
  Temperature (tonight_low_int);          // Display Tonight's Low Temp
  Precipitation (tonight_precip_int);     // Display Tonight's Chance of Precipitation
  Condition (tonight_weather);            // Get Tonight's Forecast Icon
  Snow (tonight_snow_int);                // Display Tonight's Snow Forecast
    strip.show();                         // Send display to Board
      delay(15000);                       // Display Tonight's Forecast for 15 seconds


  //Display TOMORROW's High and Conditions
  ClearDisplay ();                        // Clear the Display  
  Tomorrow ();                            // Display TOMORROW
  High ();                                // Display HIGH
  Temperature (tomorrow_high_int);        // Display Tomorrow's High Temp
  Precipitation (tomorrow_precip_int);    // Display Tomorrow's Chance of Precipitation
  Condition (tomorrow_weather);           // Get Tomorrow's Forecast Icon
  Snow (tomorrow_snow_int);               // Display Tomorrow's Snow Forecast
    strip.show();                         // Send display to Board
      delay(7500);                        // Wait 7.5 seconds and update


  //Display TOMORROW's Low and Conditions
  ClearDisplay ();                        // Clear the Display  
  Tomorrow ();                            // Display TOMORROW
  Low ();                                 // Display LOW
  Temperature (tomorrow_low_int);         // Display Tomorrow's Low Temp
  Condition (tomorrow_weather);           // Get Tomorrow's Forecast Icon
  Snow (tomorrow_snow_int);               // Display Tomorrow's Snow Forecast
  Precipitation (tomorrow_precip_int);    // Display Tomorrow's Chance of Precipitation
    strip.show();                         // Send display to Board
      delay(3500);                        // Wait 3.5 seconds. Less time because of script delay
}


//Temperature Function
void Temperature (int t) {
  if (t < -22)                                         // -25 or less Degrees
    {strip.setPixelColor(0, 60, 180, 255);}
  if (t >= -22 && t < -18)                             // -20 Degrees
    {strip.setPixelColor(45, 0, 130, 255);}
  if ((t >= -18) && (t < -13))                         // -15 Degrees
    {strip.setPixelColor(32, 100, 255, 255);}
  if ((t >= -13) && (t < -8))                          // -10 Degrees
    {strip.setPixelColor(6, 0, 204, 204);}
  if ((t >= -8) && (t < -3))                           // -5 Degrees
    {strip.setPixelColor(87, 0, 150, 150);}
  if ((t >= -3) && (t < 3))                            // 0 Degrees
    {strip.setPixelColor(93, 0, 0, 255);}
  if ((t >= 3) && (t < 8))                             // 5 Degrees
    {strip.setPixelColor(44, 150, 250, 255);}
  if ((t >= 8) && (t < 13))                            // 10 Degrees
    {strip.setPixelColor(72, 150, 250, 255);}
  if ((t >= 13) && (t < 18))                           // 15 Degrees
    {strip.setPixelColor(46, 50, 255, 150);}
  if ((t >= 18) && (t < 23))                           // 20 Degrees
    {strip.setPixelColor(24, 50, 255, 50);}
  if ((t >= 23) && (t < 28))                           // 25 Degrees
    {strip.setPixelColor(58, 108, 170, 62);}
  if ((t >= 28) && (t < 33))                           // 30 Degrees
    {strip.setPixelColor(27, 102, 204, 0);}
  if ((t >= 33) && (t < 38))                           // 35 Degrees
    {strip.setPixelColor(97, 153, 51, 255);}
  if ((t >= 38) && (t < 43))                           // 40 Degrees
    {strip.setPixelColor(64, 153, 255, 51);}
  if ((t >= 43) && (t < 48))                           // 45 Degrees
    {strip.setPixelColor(13, 128, 255, 0);}
  if ((t >= 48) && (t < 53))                           // 50 Degrees
    {strip.setPixelColor(59, 153, 0, 153);}
  if ((t >= 53) && (t < 58))                           // 55 Degrees
    {strip.setPixelColor(84, 255, 255, 51);}
  if ((t >= 58) && (t < 63))                           // 60 Degrees
    {strip.setPixelColor(9, 255, 255, 0);}
  if ((t >= 63) && (t < 68))                           // 65 Degrees
    {strip.setPixelColor(53, 0, 200, 76);}
  if ((t >= 68) && (t < 73))                           // 70 Degrees
    {strip.setPixelColor(90, 255, 100, 31);}
  if ((t >= 73) && (t < 78))                           // 75 Degrees
    {strip.setPixelColor(18, 255, 128, 0);}
  if ((t >= 78) && (t < 83))                           // 80 Degrees
    {strip.setPixelColor(52, 255, 102, 102);}
  if ((t >= 83) && (t < 88))                           // 85 Degrees
    {strip.setPixelColor(35, 255, 51, 51);}
  if (t >= 88 && (t < 110))                            // 90+ Degrees
    {strip.setPixelColor(12, 255, 0, 0);}
}


//Precipitation Function
void Precipitation (int p) {  
  if ((p >= 0) && (p < 5)) {                           // 0% Chance
     strip.setPixelColor(96, 255, 255, 0);}
  if ((p >= 5) && (p < 16)) {                          // 10% Chance
     strip.setPixelColor(14, 0, 0, 255);
     strip.setPixelColor(15, 0, 0, 255);}
  if ((p >= 16) && (p < 26)) {                         // 20% Chance
      strip.setPixelColor(50, 128, 0, 255);
      strip.setPixelColor(51, 128, 0, 255);}
  if ((p >= 26) && (p < 36)) {                         // 30% Chance
      strip.setPixelColor(20, 0, 255, 255);
      strip.setPixelColor(21, 0, 255, 255);}
  if ((p >= 36) && (p < 46)) {                         // 40% Chance
      strip.setPixelColor(40, 0, 255, 128);
      strip.setPixelColor(41, 0, 255, 128);}
  if ((p >= 46) && (p < 56)) {                         // 50% Chance
      strip.setPixelColor(91, 0, 255, 0);
      strip.setPixelColor(92, 0, 255, 0);}
  if ((p >= 56) && (p < 66)) {                         // 60% Chance
      strip.setPixelColor(60, 128, 255, 0);
      strip.setPixelColor(61, 128, 255, 0);}
  if ((p >= 66) && (p < 76)) {                         // 70% Chance
      strip.setPixelColor(82, 204, 102, 0);
      strip.setPixelColor(83, 204, 102, 0);}
  if ((p >= 76) && (p < 86)) {                         // 80% Chance
      strip.setPixelColor(54, 155, 51, 51);
      strip.setPixelColor(55, 155, 51, 51);}
  if ((p >= 86) && (p < 96)) {                         // 90% Chance
      strip.setPixelColor(7, 204, 0, 102);
      strip.setPixelColor(8, 204, 0, 102);}
  if ((p >= 96)) {                                     // 100% Chance
      strip.setPixelColor(36, 255, 0, 0);
      strip.setPixelColor(37, 255, 0, 0);}
}


//Snow Function
void Snow (int s) {
  if ((s > 0) && (s < 2)) {                             // Trace Snow (0"-1")
     strip.setPixelColor(94, 204, 229, 225);
     strip.setPixelColor(95, 204, 229, 225);}
  if ((s >= 2) && (s <= 3))                             // 2-3" of Snow
    {strip.setPixelColor(19, 0, 153, 153);}
  if ((s >= 4) && (s <= 6))                             // 4-6" of Snow
    {strip.setPixelColor(79, 0, 255, 255);}
  if (s > 6)                                            // 6+" of Snow
    {strip.setPixelColor(47, 255, 102, 102);}
}


void Now () {
  strip.setPixelColor(38, 58, 182, 255);                // Turns on NOW
  strip.setPixelColor(39, 58, 182, 255);
}


void Today () {
  strip.setPixelColor(65, 153, 51, 255);                // Turns on TODAY
  strip.setPixelColor(66, 153, 51, 255);
  strip.setPixelColor(67, 153, 51, 255);
}


void Tonight () {
  strip.setPixelColor(75, 153, 76, 0);                  // Turns on TONIGHT
  strip.setPixelColor(76, 153, 76, 0);
  strip.setPixelColor(77, 153, 76, 0);
  strip.setPixelColor(78, 153, 76, 0);
}  


void Tomorrow () {
  strip.setPixelColor(1, 0, 153, 76);                   // Turns on TOMORROW
  strip.setPixelColor(2, 0, 153, 76);
  strip.setPixelColor(3, 0, 153, 76);
  strip.setPixelColor(4, 0, 153, 76);
  strip.setPixelColor(5, 0, 153, 76);
}


void High () {
  strip.setPixelColor(42, 255, 51, 51);                 // Turns on HIGH
  strip.setPixelColor(43, 255, 51, 51);
}


void Low () {
  strip.setPixelColor(88, 51, 255, 255);                // Turns on LOW
  strip.setPixelColor(89, 51, 255, 255);
}


void ClearDisplay () {                                  // Turns all LEDs off
    for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);}
  strip.show();
}


// Weather Icon Functions, 25 in Total
void Condition (char icon[]) {
  if (strcmp(icon, "Clear") == 0) {                     // Clear
    strip.setPixelColor(10, 255, 255, 0);
    strip.setPixelColor(11, 255, 255, 0);
    strip.setPixelColor(28, 255, 255, 0);
    strip.setPixelColor(29, 255, 255, 0);}

  if (strcmp(icon, "Cloudy") == 0) {                    // Cloudy
    strip.setPixelColor(56, 0, 0, 204);
    strip.setPixelColor(57, 0, 0, 204);
    strip.setPixelColor(62, 0, 0, 204);
    strip.setPixelColor(63, 0, 0, 204);}

  if (strcmp(icon, "Partly Cloudy") == 0) {             // Partly Cloudy
    strip.setPixelColor(25, 0, 204, 0);
    strip.setPixelColor(26, 0, 204, 0);
    strip.setPixelColor(33, 0, 204, 0);
    strip.setPixelColor(34, 0, 204, 0);}
  
  if (strcmp(icon, "Mostly Cloudy") == 0) {             // Mostly Cloudy
    strip.setPixelColor(56, 102, 178, 255);
    strip.setPixelColor(57, 102, 178, 255);
    strip.setPixelColor(62, 102, 178, 255);
    strip.setPixelColor(63, 102, 178, 255);}

  if (strcmp(icon, "Rain") == 0) {                      // Rain
    strip.setPixelColor(73, 204, 204, 0);
    strip.setPixelColor(74, 204, 204, 0);
    strip.setPixelColor(85, 204, 204, 0);
    strip.setPixelColor(86, 204, 204, 0);}

  if (strcmp(icon, "Snow") == 0) {                      // Snow
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}

  if (strcmp(icon, "Light Snow") == 0) {                // Light Snow
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}
  
  if (strcmp(icon, "Heavy Snow") == 0) {                // Heavy Snow
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}
    
  if (strcmp(icon, "Snow Showers") == 0) {              // Snow Showers
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}

  if (strcmp(icon, "Thunderstorm") == 0) {              // Thunderstorm
    strip.setPixelColor(30, 0, 51, 102);
    strip.setPixelColor(31, 0, 51, 102);
    strip.setPixelColor(48, 0, 51, 102);
    strip.setPixelColor(49, 0, 51, 102);}

  if (strcmp(icon, "Overcast") == 0) {                  // Overcast
    strip.setPixelColor(56, 102, 178, 255);
    strip.setPixelColor(57, 102, 178, 255);
    strip.setPixelColor(62, 102, 178, 255);
    strip.setPixelColor(63, 102, 178, 255);}

  if (strcmp(icon, "Chance of Rain") == 0) {            // Chance of Rain
    strip.setPixelColor(68, 255, 0, 255);
    strip.setPixelColor(69, 255, 0, 255);
    strip.setPixelColor(70, 255, 0, 255);
    strip.setPixelColor(71, 255, 0, 255);}

  if (strcmp(icon, "Chance of Thunderstorms") == 0) {   // Chance of Thunderstorms
    strip.setPixelColor(80, 153, 0, 153);
    strip.setPixelColor(81, 153, 0, 153);
    strip.setPixelColor(98, 153, 0, 153);
    strip.setPixelColor(99, 153, 0, 153);}
  
  if (strcmp(icon, "Chance of a Thunderstorm") == 0) {  // Chance of a Thunderstorm
    strip.setPixelColor(80, 153, 0, 153);
    strip.setPixelColor(81, 153, 0, 153);
    strip.setPixelColor(98, 153, 0, 153);
    strip.setPixelColor(99, 153, 0, 153);}

  if (strcmp(icon, "Chance of Flurries") == 0) {        // Chance of Flurries
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}
  
  if (strcmp(icon, "Chance Rain") == 0) {               // Chance Rain
    strip.setPixelColor(68, 255, 0, 255);
    strip.setPixelColor(69, 255, 0, 255);
    strip.setPixelColor(70, 255, 0, 255);
    strip.setPixelColor(71, 255, 0, 255);}

  if (strcmp(icon, "Chance of Freezing Rain") == 0) {   // Chance of Freezing Rain
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}
  
  if (strcmp(icon, "Chance of Sleet") == 0) {           // Chance of Sleet
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}

  if (strcmp(icon, "Flurries") == 0) {                  // Flurries (not furries)
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}

  if (strcmp(icon, "Fog") == 0) {                       // Fog
    strip.setPixelColor(56, 102, 178, 255);
    strip.setPixelColor(57, 102, 178, 255);
    strip.setPixelColor(62, 102, 178, 255);
    strip.setPixelColor(63, 102, 178, 255);}

  if (strcmp(icon, "Haze") == 0) {                      // Haze
    strip.setPixelColor(25, 255, 128, 0);
    strip.setPixelColor(26, 255, 128, 0);
    strip.setPixelColor(33, 255, 128, 0);
    strip.setPixelColor(34, 255, 128, 0);}

  if (strcmp(icon, "Mostly Sunny") == 0) {              // Mostly Sunny
    strip.setPixelColor(25, 0, 204, 0);
    strip.setPixelColor(26, 0, 204, 0);
    strip.setPixelColor(33, 0, 204, 0);
    strip.setPixelColor(34, 0, 204, 0);}

  if (strcmp(icon, "Partly Sunny") == 0) {              // Partly Sunny
    strip.setPixelColor(25, 0, 204, 0);
    strip.setPixelColor(26, 0, 204, 0);
    strip.setPixelColor(33, 0, 204, 0);
    strip.setPixelColor(34, 0, 204, 0);}

  if (strcmp(icon, "Freezing Rain") == 0) {             // Freezing Rain
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}

  if (strcmp(icon, "Sleet") == 0) {                     // Sleet
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}

  if (strcmp(icon, "Thunderstorms") == 0) {             // Thunderstorms
    strip.setPixelColor(30, 0, 51, 102);
    strip.setPixelColor(31, 0, 51, 102);
    strip.setPixelColor(48, 0, 51, 102);
    strip.setPixelColor(49, 0, 51, 102);}

  if (strcmp(icon, "Unknown") == 0) {                   // Unknown
    strip.setPixelColor(80, 153, 0, 153);
    strip.setPixelColor(81, 153, 0, 153);
    strip.setPixelColor(98, 153, 0, 153);
    strip.setPixelColor(99, 153, 0, 153);}

  if (strcmp(icon, "Scattered Clouds") == 0) {          // Scattered Clouds
    strip.setPixelColor(25, 0, 204, 0);
    strip.setPixelColor(26, 0, 204, 0);
    strip.setPixelColor(33, 0, 204, 0);
    strip.setPixelColor(34, 0, 204, 0);}

  if (strcmp(icon, "Ice Pellets") == 0) {               // Ice Pellets
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}

  if (strcmp(icon, "Chance of Snow") == 0) {            // Chance of Snow
    strip.setPixelColor(16, 160, 160, 160);
    strip.setPixelColor(17, 160, 160, 160);
    strip.setPixelColor(22, 160, 160, 160);
    strip.setPixelColor(23, 160, 160, 160);}  

  if (strcmp(icon, "Light Rain") == 0) {                // Light Rain
    strip.setPixelColor(68, 255, 0, 255);
    strip.setPixelColor(69, 255, 0, 255);
    strip.setPixelColor(70, 255, 0, 255);
    strip.setPixelColor(71, 255, 0, 255);}
    
  if (strcmp(icon, "Heavy Rain") == 0) {                // Heavy Rain
    strip.setPixelColor(68, 255, 0, 255);
    strip.setPixelColor(69, 255, 0, 255);
    strip.setPixelColor(70, 255, 0, 255);
    strip.setPixelColor(71, 255, 0, 255);}  
}
