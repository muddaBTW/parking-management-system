# ParkNGo

> **Abstract** : This project presents an automated parking management system using OpenCV and a machine learning model to detect available parking slots and recognize vehicle license plates. OpenCV processes real-time camera feeds to identify occupied and vacant spaces, while the machine learning model enhances accuracy. This system improves efficiency, reduces manual effort, and enables real-time monitoring, making it ideal for smart parking solutions

### Project Members
1. SHAIKH MUDDASSIR IMTIYAZ  [ Team Leader ] 
2. GUPTA VIKAS BECHU 
3. FATEH MOHAMEDALI MUSTAQALI 
4. ANSARI MOHAMMED JAISH ANEES AHMED 

### Project Guides
1. PROF. MOHD ASHFAQUE SHAIKH  [ Primary Guide ] 

### Deployment Steps
Please follow the below steps to run this project.
🔧 Hardware Setup
IR Sensors:
SENSOR1 → GPIO 32
SENSOR2 → GPIO 33
SENSOR3 → GPIO 25
SENSOR4 → GPIO 26
LEDs:
LED1 → GPIO 2
LED2 → GPIO 4
LED3 → GPIO 5
LED4 → GPIO 18
LCD (16x2 via I2C):
SDA → GPIO 21
SCL → GPIO 22
Address: 0x27

📦 Install Libraries in Arduino IDE
Blynk
LiquidCrystal_I2C
WiFi and Wire (default with ESP32 board package)

⚙️ Configure Blynk
Create a Blynk Template
Add 4 LED Widgets for parking status:
V0 → Spot 1
V1 → Spot 2
V2 → Spot 3
V3 → Spot 4
Add a Value Display Widget on V4 for total available spots
Enable Events for notifications:
spot1_vacant, spot2_vacant, etc.

🛠️ Update Code
Replace BLYNK_AUTH_TOKEN with your actual token
Set your Wi-Fi ssid and pass

🚀 Upload Code
Select your ESP32 board (e.g., DOIT ESP32 DevKit v1)
Select the correct COM port
Upload the code using Arduino IDE

🔌 Power ESP32
Use USB or 18650 Battery

✅ Test the System
Block/unblock sensors to simulate vehicle movement
LEDs blink when spots are empty
LCD shows real-time slot status
Blynk updates the app and sends notifications

### Subject Details
- Class : SE (COMP) Div A - 2024-2025
- Subject : Mini Project 1-B (MP-1(P)(2019))
- Project Type : Mini Project

### Platform, Libraries and Frameworks used
1. ESP32: https://www.espressif.com/en/products/socs/esp32
2.Arduino IDE: https://www.arduino.cc/en/software
3.Blynk IoT Platform: https://blynk.io/
4.LiquidCrystal_I2C by Frank de Brabander: https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
5.WiFi and Wire Libraries (ESP32 Default): https://www.arduino.cc/reference/en/language/functions/communication/wire/

### References
- Youtube video:(https://youtu.be/4LVirWqHk6w?si=7II0qf6IcJIKgpvA)
