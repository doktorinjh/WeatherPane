# WeatherPane
Files to create your own WeatherPane
WeatherPane Display for Arduino Yun and Adafruit NeoPixels
Created: October, 2015

Thanks to the Arduino.cc and /r/Arduino Forum Users for helping
answer my questions while creating this. 

This sketch uses two python scripts to access real time weather
updates from Weather Underground's Weather API and display the
information as weather icons and numbers on a 10x10 Neopixel
display. 
  
If you make any improvements, I'd like to see what you've done!
doktorinjh@gmail.com
  
p.s. This was my very first Arduino project and it was inspired by
the ubiquitous Word Clock. There are probably improvements that 
can be made!
  
This sketch is not licensed for commercial use and may not be
replicated or sold without written permission.
 
Change Log (For my own sanity):
 * 4/1/17 - Uploaded to GitHub
 * 10/30/16 - Added additional weather conditions for Light/Heavy
 * 5/29/16 - Moved scripts to Arduino instead of SD card
 * 5/4/16 - Fixed Current Precip issue
 * 5/3/16 - Added station identification

# To Install:
Copy WU_Bridge_GitHub to the Arduino Yun's main directory (or anywhere else you'd like to run the files, like from an SD card). The WU_Variables_GitHub file is an example of what the Arduino should produce, if everything is connected and working well. The Variables file is what the sketch reads and how it updates the display. 

You will need a WeatherUnderground API Key and enter it in Line 5 of the Bridge file. The Bridge file is setup to get your location from your IP address. If you want a specific weather station, you can enter that on Line 5. More information about that can be found here: https://www.wunderground.com/weather/api/d/docs

For this code to work with your LED setup, you will need to have your 0 LED position starting in the upper left corner of your display. If it is in any other corner, then you will have to redo all of the icons, etc.

# Face Plate
If you'd like to buy a face plate file directly from Ponoko, you can do that here: https://www.ponoko.com/showroom/WeatherPane Otherwise, examples are also provided. 

# 3D Files
There are 4 .stl files that will allow you to print the partitions needed to keep the lights from polluting the other icons. They were made for a Wanhao i3 v1 (or a MonoPrice MakerSelect) that has a bed size of 200mm x 200mm. You'll have to glue the partitions together after they've been printed.
