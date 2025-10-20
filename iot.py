#!/usr/bin/env python3
import json
from paho.mqtt import client as mqtt
from RPLCD.i2c import CharLCD

# --- MQTT Configuration ---
BROKER = "0.0.0.0"  # Broker อยู่ในเครื่องนี้เอง
PORT = 1883
TOPIC = "kmitl/iot/66070273/sensor"  # ต้องตรงกับ Arduino

# --- LCD Configuration ---
LCD_I2C_ADDR = 0x27   # จาก i2cdetect
lcd = CharLCD('PCF8574', LCD_I2C_ADDR, cols=16, rows=2)

def on_connect(client, userdata, flags, rc):
    print(f"Connected to MQTT broker (rc={rc})")
    client.subscribe(TOPIC)

def on_message(client, userdata, msg):
    payload = msg.payload.decode()
    print(f"{msg.topic}: {payload}")
    try:
        data = json.loads(payload)
        t = float(data.get("temp", 0))
        h = float(data.get("humidity", 0))
        lcd.clear()
        lcd.write_string(f"Temp: {t:5.1f}C")
        lcd.crlf()
        lcd.write_string(f"Hum : {h:5.1f}%")
    except Exception as e:
        lcd.clear()
        lcd.write_string("Invalid Data")

def main():
    lcd.clear()
    lcd.write_string("Waiting MQTT...")
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(BROKER, PORT, 60)
    client.loop_forever()

if __name__ == "__main__":
    main()
