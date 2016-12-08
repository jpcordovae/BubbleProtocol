#ifndef BUBBLE_PROTOCOL
#define BUBBLE_PROTOCOL

// BP = Bubble Protocol
#define BP_VERSION_MAX       0
#define BP_VERSION_MIN       1
#define BP_END_LINE          '\n'
#define BP_SPLIT_LINES       '|'
#define BP_PAYLOAD_SIZE      1024 // 1Kb payload
#define BP_MAX_DEVICES       0xFF
#define BP_MAX_STRING_LENGTH 0xFF
#define BP_MAX_IO            0xFF

// bubble line type (BLT)
#define BLT_PROTOCOL 0x00 // routing stuffs
#define BLT_UPDATE   0x02 // update data
#define BLT_COMMAND  0x04 // command other devices

// IO types (physcal connections)
enum enIOTypes { ANALOG, DIGITAL };

#include <stdio.h>
#include <stdint.h>

typedef struct stBubble {
  uint16_t u16_size;
  uint16_t u16_BLT;
  uint16_t u16_pyload[BP_PAYLOAD_SIZE]; // end line included
}stBubble;

typedef struct stIO{
char name[BP_MAX_STRING_LENGTH];
enum enIOTypes type;
union value { float fValue; };
} stIO;

//read functions
//void (*PROTOCOL_FUNCTION)(const uint8_t *_buffer, size_t _buffersize);
//void (*UPDATE_FUNCTION)(const uint8_t *buffer, size_t _buffersize);
//void (*COMMAND_FUNCTION)(const uint8_t *buffer, size_t _buffersize);

// write function to the parent device 
//void (*WRITE_PARENT_FUNCTION)(struct stDevice _parent, const uint8_t *buffer, size_t _buffersize);
//void (*READ_PARENT_FUNCTION)(struct stDevice _parent, const uint8_t *buffer, size_t _buffersize);

typedef struct stDevice {
  char name[UINT8_MAX];
  uint16_t u16_max_payload_size;
  struct stDevice *stDeviceParent;
  struct stDevice *stDevices[BP_MAX_DEVICES];
  struct stIO     *stIOs[BP_MAX_IO];
  // data structures
  struct stBubble stBSend, stBReceive; // buffers to send and receive must be initialized
  void (*write)(const uint8_t *buffer, size_t _buffersize);
  void (*read)(const uint8_t *buffer, size_t _buffersize);
} stDevice;

#endif
