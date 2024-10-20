# ControlRGBLEDWithComputerVisionAndArduino
### See this <a href="https://www.youtube.com/shorts/f3V4fJ6UyYo" target="_blank">code in action on my YouTube Channel</a>

A simple code for Arduino and Python to control LED RGB with computer vision on index-thumb distance in pixels

Thanks to a simple computer vision program in python, we can control the RGB LED light color moving our index and thumb.

The RGB LED color will change based on the distance between index and thumb that I set up on the code as fixed values.
You can adjust these for your applications.

The python code will send ARRAYS via serial communication to Arduino.

[0,0,0] To switch off the RGB LEDs
[1,0,0] To set the RGB LEDs to RED
[0,1,0] To set the RGB LEDs to GREEN
[0,0,1] To set the RGB LEDs to BLUE

You can also customize my code to get yellow, cyan and magenta. 

This is a really simple customization, in fact you can send:
[1,1,0] for yellow
[1,0,1] for magenta
[0,1,1] for cyan

Now, to make the entire code work follow these steps and rules...

# First, in Python you have to install
- MediaPipe with -> pip install mediapipe
- OpenCV with -> pip install opencv-python
- CVZone with -> pip install cvzone

Then use the code I provided for Python.

# Second on ARDUINO, install the CVZone package.
You will find the CVZone package inside a zip file inside this repository inside the "packages" folder.
You must install this package via your ARDUINO IDE.

1) Download the CVZone ZIP inside "packages" folder
2) On your ARDUINO IDE go to "Sketch > #include library > Add library from .ZIP file"
3) Then, select the CVZone ZIP you've downloaded
4) Now you can use the module CVZone with "#include <cvzone.h>" and receive serial inputs from the python code
5) Copy the .ino file in this repo and load in into your ARDUINO

# Third, start everything
1) Compile and load the ARDUINO code on your arduino board
2) Start the python code with F5 or CTRL+F5

You have to follow these steps in the exact order I've told you.

If you start Python first and you load the arduino code after, you'll get an error in the Arduino IDE because python will lock
the port you set up for the serial communication between arduino and your pc.

If you've followed the exact steps (first load arduino code, then start python code) you should see a window on your computer screen with the
hand tracking feature fully functional.

If you are moving your index and thumb but lights of the RGB LEDs are not changing, push the reset button on your arduino board, then try again.
