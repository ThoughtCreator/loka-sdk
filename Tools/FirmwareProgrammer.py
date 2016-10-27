import sys, getopt
import serial
import time

file_name = sys.argv[1:][0]
ser = serial.Serial(sys.argv[1:][1], 115200)

print("** Please turn on board");

serial_line = ser.readline()
    
if b"Creator Bootloader" in serial_line:
    print("** Detected Loka Board")
    
    while 1:    
        ser.write('\x03'.encode('utf-16be'))
       
        serial_line = ser.read(1)
        

        if (serial_line == b'>'):
            time.sleep(1);
            ser.write(b"console update\r\n");
            print("** Erasing memory!!")
            break


while 1:   
    
    if ser.inWaiting() == 0:
        sys.stdout.write('.')
        sys.stdout.flush()
        time.sleep(1);
        continue
    
    serial_line = ser.readline()
    
    if b"Memory erased" in serial_line:
    
        print("")
        print("** Memory Erased!");
        print("** Programming!!")
        
        file_object = open(file_name, 'r')
        for line in file_object:
            line = line.replace(" ","");
            ser.write(str.encode(line))
            sys.stdout.write('.')
            sys.stdout.flush()
            time.sleep(0.01);
            
            if "q" in line: 
                break;
            
            if ser.inWaiting() > 0:
                print("Acontece")
                serial_line = ser.read(ser.inWaiting())
                print(serial_line)
                break
        break


print("")

while 1:   
    serial_line = ser.readline()
    
    
    if b"Terminal updated" in serial_line:
        print("** Done!!")
        break
    
    

            
ser.close() # Only executes once the loop exits