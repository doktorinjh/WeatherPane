import urllib2
import json

#Get json data from Weather Underground by using IP address
f = urllib2.urlopen('http://api.wunderground.com/api/***KEY***/conditions/forecast/hourly/q/autoip.json')
json_string = f.read()
parsed_json = json.loads(json_string)

#Current Location and Observation Time
location = parsed_json['current_observation']['display_location']['full']
time = parsed_json['current_observation']['observation_time']
station = parsed_json['current_observation']['station_id']

#Current Conditions
current_temp = parsed_json['current_observation']['temp_f']
current_weather = parsed_json['current_observation']['weather']
current_precip = parsed_json['hourly_forecast'][0]['pop']

#Today's Forecast
today_high = parsed_json['forecast']['simpleforecast']['forecastday'][0]['high']['fahrenheit']
today_low = parsed_json['forecast']['simpleforecast']['forecastday'][0]['low']['fahrenheit']
today_weather = parsed_json['forecast']['simpleforecast']['forecastday'][0]['conditions']
today_precip = parsed_json['forecast']['txt_forecast']['forecastday'][0]['pop']
today_snow = parsed_json['forecast']['simpleforecast']['forecastday'][0]['snow_allday']['in']

#Tonight's Forecast
tonight_high = parsed_json['forecast']['simpleforecast']['forecastday'][0]['high']['fahrenheit']
tonight_low = parsed_json['forecast']['simpleforecast']['forecastday'][0]['low']['fahrenheit']
tonight_weather = parsed_json['forecast']['simpleforecast']['forecastday'][0]['conditions']
tonight_precip = parsed_json['forecast']['txt_forecast']['forecastday'][1]['pop']
tonight_snow = parsed_json['forecast']['simpleforecast']['forecastday'][0]['snow_night']['in']

#Tomorrow's Forecast
tomorrow_high = parsed_json['forecast']['simpleforecast']['forecastday'][1]['high']['fahrenheit']
tomorrow_low = parsed_json['forecast']['simpleforecast']['forecastday'][1]['low']['fahrenheit']
tomorrow_weather = parsed_json['forecast']['simpleforecast']['forecastday'][1]['conditions']
tomorrow_precip = parsed_json['forecast']['simpleforecast']['forecastday'][1]['pop']
tomorrow_snow = parsed_json['forecast']['simpleforecast']['forecastday'][1]['snow_allday']['in']


#Write output to python text file
#f = open( 'C:\Users\User\Desktop\WU_Test.txt', 'w' ) #For testing purposes
f = open( '/WU_Variables.py', 'w' ) #Change if directory is different
f.write("import sys" + '\n' )
f.write(""'\n')
f.write("sys.path.insert(0, '/usr/lib/python2.7/bridge/')" + '\n' )
f.write(""'\n')
f.write("from bridgeclient import BridgeClient as bridgeclient" + '\n' )
f.write(""'\n')
f.write("value = bridgeclient()" + '\n' )
f.write(""'\n')
f.write("value.put(\"location\",'{}')".format((location)) + '\n')
f.write("value.put(\"time\",'{}')".format((time)) + '\n')
f.write("value.put(\"station\",'{}')".format((station)) + '\n')
f.write(""'\n')
f.write("value.put(\"current_temp\",'{}')".format((current_temp)) + '\n') 
f.write("value.put(\"current_weather\",'{}')".format((current_weather)) + '\n')
f.write("value.put(\"current_precip\",'{}')".format((current_precip)) + '\n')
f.write(""'\n')
f.write("value.put(\"today_high\",'{}')".format((today_high)) + '\n')
f.write("value.put(\"today_low\",'{}')".format((today_low)) + '\n')
f.write("value.put(\"today_weather\",'{}')".format((today_weather)) + '\n')
f.write("value.put(\"today_precip\",'{}')".format((today_precip)) + '\n')
f.write("value.put(\"today_snow\",'{}')".format((today_snow)) + '\n')
f.write(""'\n')
f.write("value.put(\"tonight_high\",'{}')".format((tonight_high)) + '\n')
f.write("value.put(\"tonight_low\",'{}')".format((tonight_low)) + '\n')
f.write("value.put(\"tonight_weather\",'{}')".format((tonight_weather)) + '\n')
f.write("value.put(\"tonight_precip\",'{}')".format((tonight_precip)) + '\n')
f.write("value.put(\"tonight_snow\",'{}')".format((tonight_snow)) + '\n')
f.write(""'\n')
f.write("value.put(\"tomorrow_high\",'{}')".format((tomorrow_high)) + '\n')
f.write("value.put(\"tomorrow_low\",'{}')".format((tomorrow_low)) + '\n')
f.write("value.put(\"tomorrow_weather\",'{}')".format((tomorrow_weather)) + '\n')
f.write("value.put(\"tomorrow_precip\",'{}')".format((tomorrow_precip)) + '\n')
f.write("value.put(\"tomorrow_snow\",'{}')".format((tomorrow_snow)) + '\n')
f.close()