# water_sensors

## Frame format:  ##

Frame len: 16 bytes

Byte num | Bytes count | Description  
-------- | ---------- | -----------
0 | 1 byte | Method  
1 | 1 byte | Device number  
2 | 1 byte | Device type  
3-9 | 7 bytes | Reserved  
10-13 | 4 bytes | Value  
14-15 | 2 bytes | Magic bytes  


#### Method(byte 0):  ####
Value | Description
----- | -----------
1 | GET
2 | SET (not implemented)  


#### Device number(byte 1):  ####
Depends pin number: 

Value | Description
----- | -----------
1 | PC0
2 | PC1
3 | PC2
4 | PC4
5 | PC5
6 | PB0(D2)  
7 | PB1(D1)  
8 | PB2(D0)  

#### Devicetype: NOT IMPLEMENTED, 1 always ####
Value | Description
----- | -----------
1 | WATER
2 | SMOKE
3 | TEMPERATURE

#### Bytes 3 - 9 reserved, 0 always ####

#### Value(bytes 10-13):  ####
Value from microcontroller.  
So when PC0-PC4 is 1, value is 0, and vice versa.  

Default value from PB0-PB2 depends on PD5-PD7. Value on PD5 and PD7 depends from JP6-JP8. When JP6-JP8 changes JP3-JP5 should change too according JP6-JP8.

#### Magic bytes ####
Byte 14 = 0x00  
Byte 15 = 0xFF  














