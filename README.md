# water_sensors

## Frame format:  ##

Frame len: 16 bytes

byte num | byts count | Description  
-------- | ---------- | -----------
0 | 1 byte | Method  
1 | 1 byte | Device number  
2 | 1 byte | Device type  
3-11 | 9 bytes | Reserved  
12-15 | 4 bytes | Value  
16-17 | 2 bytes | Magic bytes  


#### Method(byte 0):  ####
0 - GET  
1 - SET (not implemented)  

#### Device number(byte 1):  ####
Depends pin number:  
PC0 - 1  
PC1 - 2  
PC2 - 3  
PC4 - 4  
PC5 - 5  
PB0 - 6(D2)  
PB1 - 7(D1)  
PB2 - 8(D0)  

#### Device type: not implemented, 0 always ####

#### Bytes 3 - 11 reserved, 0 always ####

#### Value(bytes 12-15):  ####
Value from microcontroller.  
So when PC0-PC4 is 1, value is 0, and vice versa.  

Default value from PB0-PB2 depends on PD5-PD7. Value on PD5 and PD7 depends from JP6-JP8. When JP6-JP8 changes JP3-JP5 should change too according JP6-JP8.

#### Magic bytes ####
Byte 16 = 0x00  
Byte 17 = 0xFF  














