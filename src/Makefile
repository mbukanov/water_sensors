all:
	avr-gcc -mmcu=atmega8 -Os *.c -o main.o -D F_CPU=1000000
	
	avr-objcopy -j .text -j .data -O ihex main.o sensors_for_home.hex
	avrdude -c usbasp -p m8 -P usb -U flash:w:sensors_for_home.hex

clean:
	rm sensors_for_home.hex *.o
