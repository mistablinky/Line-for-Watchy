# Line for Watchy

Analog Watchface for Watchy E-Paper Watch

Design inspired by Line Watch Face for Google Wear OS by Seahorsepip
https://play.google.com/store/apps/details?id=com.seapip.thomas.line_watchface

![Line for Watchy Light Mode](/images/line-for-watchy_light.png)
![Line for Watchy Dark Mode](/images/line-for-watchy_dark.png)

**Setup**
- Follow the instructions on ![https://github.com/sqfmi/Watchy](https://github.com/sqfmi/Watchy) to setup your Arduino IDE for Watchy
- Make sure the RTClib by Adafruit is installed (tested with version 1.12.4)
- Create a folder "Line-for-Watchy" and copy all files from the repository to it
- Open the ino File with your Arduino IDE and upload to your Watchy
- Enjoy :)

The Watchy time will automatically set to the watchface upload time in case the power has lost. Thats the way I like it. But for sure there is room for improvement, because there seems to be a gap between taking and setting the time (depends on Arduino compilation time, sometimes up to a minute for me).