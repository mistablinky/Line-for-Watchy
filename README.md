# Line for Watchy

Analog Watchface for Watchy E-Paper Watch

Design inspired by [Line Watch Face for Google Wear OS by Seahorsepip](https://play.google.com/store/apps/details?id=com.seapip.thomas.line_watchface)

![Line for Watchy Dark Mode](/images/line-for-watchy.png)

![Line for Watchy](/images/23_Line.gif) (Image by [SQFMI](https://watchy.sqfmi.com/))



**Setup**
- Follow the instructions on [https://github.com/sqfmi/Watchy](https://github.com/sqfmi/Watchy) to setup your Arduino IDE for Watchy
- Make sure the ```RTClib.h``` by Adafruit is installed (tested with version 1.12.4)
- Make sure the ```WiFi.h``` and ```time.h``` libraries are installed
- Create a folder ```Line-for-Watchy``` and copy all files from the repository to it
- For ntp time server synchronization add the file ```secrets.h``` to that folder with the following two lines:
```c++
const char* ssid = "yourWiFiNetworkName";
const char* password = "yourWiFiNetworkPassword";
```
- Open the File ```Line-for-Watchy.ino``` with your Arduino IDE and make the following adaptations if necessary
  - The ntp time will be translated to your local time based on the time zone settings in line 35. The default is Europe/Berlin - adapt according to the [posix_tz_db](https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv) if necessary
  - Toggle between light and dark mode in Line 49 - The default is dark mode.
- Upload to your Watchy and Enjoy :)

On reset (after uploading the watch face) Watchy tries automatically to connect to your WiFi and obtain current date and time from ntp time server. If that fails Watchy will be synchronized with the compile date and time.

**Changelog**
- 0.1 (2021-02-13): initial version
- 0.2 (2021-02-21): added ntp time server synchronization

**Free Culture License**
This work is licensed under a Creative Commons *Attribution-ShareAlike 4.0 International License (CC BY-SA 4.0)*.
Adaptations and commercial use are allowed AS LONG AS OTHERS SHARE ALIKE. [License terms](https://creativecommons.org/licenses/by-sa/4.0/)