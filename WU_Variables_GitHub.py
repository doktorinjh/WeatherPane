import sys

sys.path.insert(0, '/usr/lib/python2.7/bridge/')

from bridgeclient import BridgeClient as bridgeclient

value = bridgeclient()

value.put("location",'Anywhere, US')
value.put("time",'Last Updated on June 2, 5:05 PM MDT')
value.put("station",'KUSAA1234')

value.put("current_temp",'66.6')
value.put("current_weather",'Mostly Cloudy')
value.put("current_precip",'0')

value.put("today_high",'72')
value.put("today_low",'43')
value.put("today_weather",'Partly Cloudy')
value.put("today_precip",'0')
value.put("today_snow",'0.0')

value.put("tonight_high",'72')
value.put("tonight_low",'43')
value.put("tonight_weather",'Partly Cloudy')
value.put("tonight_precip",'0')
value.put("tonight_snow",'0.0')

value.put("tomorrow_high",'74')
value.put("tomorrow_low",'44')
value.put("tomorrow_weather",'Partly Cloudy')
value.put("tomorrow_precip",'0')
value.put("tomorrow_snow",'0.0')