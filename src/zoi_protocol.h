#ifndef ZOI_PROTOCOL_H
#define ZOI_PROTOCOL_H
#include <string.h>

#define ZOI_FRAME_SIZE 16

#define ZOI_METHOD_GET 1
#define ZOI_METHOD_SET 2

#define ZOI_DEV_TYPE_WATER 1
#define ZOI_DEV_TYPE_SMOKE 2
#define ZOI_DEV_TYPE_TEMPERATURE 3


#define ZOI_MAGIC_END1 0x00
#define ZOI_MAGIC_END2 0xFF


void FillGetBuffer(unsigned char dev_type, unsigned char dev_num, unsigned char value, unsigned char * buffer) {
  memset(buffer, 0, ZOI_FRAME_SIZE);
  buffer[0] = ZOI_METHOD_GET;
  buffer[1] = dev_num;
  buffer[2] = dev_type;
  buffer[ZOI_FRAME_SIZE-2-4] = value;
  buffer[ZOI_FRAME_SIZE-2] = ZOI_MAGIC_END1;
  buffer[ZOI_FRAME_SIZE-1] = ZOI_MAGIC_END2;
}



#endif
