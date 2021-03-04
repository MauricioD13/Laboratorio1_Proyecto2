
import serial
import time

       
        
port = serial.Serial('COM7', 19200, timeout=0)
result = []

flag_init = 0;
while True:
    
    data = port.read()
    
    if(data.decode() == '#'):
        flag_init = 1;
        
    elif(flag_init == 1 and data.decode()!='-' and data.decode()!=''):
        result.append(data.decode());
        
        if(len(result)==3):
            flag_init = 0;
            print(f"VOLTAGE:{result}")
            result = []
            
            
            
    
    

    