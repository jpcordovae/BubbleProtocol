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
enum enIOTypes { ANALOG_INPUT, ANALOG_OUTPUT, DIGITAL_INPUT, DIGITAL_OUTPUT };

#include <stdio.h>
#include <stdint.h>

enum session_handshake { NONE, WELCOME, VERSION_CHECK, ACCEPTED, REJECTED };

void AddDevice();
void DeleteDevice();

typedef struct stDevice {
  char name[UINT8_MAX];
  struct stDevice *stDeviceParent;
  struct stDevice *stDevices[BP_MAX_DEVICES];
  struct stIO     *stIOs[BP_MAX_IO];
  // data structures
  char bufferIN[UINT8_MAX];
  char bufferOUT[UINT8_MAX];
  void (*write)(const uint8_t *buffer, size_t _buffersize);
  void (*read)(const uint8_t *buffer, size_t _buffersize);
} stDevice;

#endif
