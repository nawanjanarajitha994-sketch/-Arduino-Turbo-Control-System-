# -Arduino-Turbo-Control-System-
 Arduino-based turbo system using RPM and pressure sensor
# -flow-chart-
 Start
 ↓
Read RPM & Pressure
 ↓
Is RPM > 1000?
 ↓ yes
Is Pressure < 1150?
 ↓ yes
Turn Relay ON
 ↓
Else → Relay OFF
 ↓
Repeat
#-CONNECTIONS-
1. HC-020K RPM SENSOR
 VCC → 5V
 GND → GND
 OUT → D2
2. BMP280 PRESSURE SENSOR
 VCC → 3.3V 
 GND → GND
 SDA → A4
 SCL → A5
3. RELAY MODULE (CONTROL SIDE)
 VCC → 5V
 GND → GND
 IN  → D8
4. RELAY → MOTOR (POWER SIDE)
  12V + → COM
  NO     → Motor +
  Motor - → 12V -

Use NO (Normally Open)

5. FLYBACK DIODE
(Motor +) --|>|-- (Motor -)
 6. POWER CONNECTION
Arduino → USB power
Motor → 12V battery

