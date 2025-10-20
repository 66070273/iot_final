# iot_final
# Rassberry PI
ติดตั้งคำสั่ง: 

sudo apt update

sudo apt install -y mosquitto mosquitto-clients

sudo systemctl enable mosquitto

sudo systemctl start mosquitto


จากนั้นทำใน Virtual Environment :

sudo apt install -y python3 python3-pip python3-venv

python3 -m venv ~/iotvenv

source ~/iotvenv/bin/activate

พอเข้ามาใน venv ติดตั้ง pip

pip install RPLCD paho-mqtt smbus2


# ***** อย่าลืม ******
เปิดใช้งาน I²C Interface โดยใช้คำสั่ง : 

sudo raspi-config

ไปที่ Interface Options → I2C → Enable
sudo reboot

วิธีเช็คว่าเจออุปกรณ์ LCD แล้ว

sudo apt install -y i2c-tools

sudo i2cdetect -y 1

ถ้าเจอขึ้นแบบภาพข้างล่าง

<img width="427" height="165" alt="Screenshot 2568-10-20 at 17 42 47" src="https://github.com/user-attachments/assets/6982e213-0e27-498b-ae99-501a1c3e810b" />
