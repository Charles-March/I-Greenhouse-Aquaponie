from network import LoRa
import struct
import socket
lora=LoRa(mode=LoRa.LORA,frequency=868000000, sf=7)
s = socket.socket(socket.AF_LORA, socket.SOCK_RAW) #create a LoRa socket
i=0
while 1:
    if i==0:
        t=s.recv(4)
        rx_data= struct.unpack('f', t)
        temperature = rx_data
    elif i==1:
        t=s.recv(4)
        rx_data= struct.unpack('f', t)
        humidite = rx_data
    elif i==2:
        t=s.recv(4)
        rx_data= struct.unpack('f', t)
        numero=rx_data
        print("Releve, temperature : ")
        print(temperature)
        print(", humidite : ")
        print(humidite)
        print("numero : ")
        print(numero)
    elif i==3:
        t=s.recv(4)
    i = (i+1)%4