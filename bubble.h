#ifndef BUBBLE_PROTOCOL
#define BUBBLE_PROTOCOL

// BP = Bubble Protocol
#define BP_VERSION_MAX       0
#define BP_VERSION_MIN       1
#define BP_END_LINE          '\n'
#define BP_SPLIT_LINES       "|"
#define BP_PAYLOAD_SIZE      1024 // 1Kb payload
#define BP_MAX_DEVICES       0xFF
#define BP_MAX_STRING_LENGTH 0xFF
#define BP_MAX_IO            0xFF

// bubble line type (BLT)
#define BLT_PROTOCOL 0x00 // routing stuffs
#define BLT_UPDATE   0x02 // update data
#define BLT_COMMAND  0x04 // command other devices

// IO types (physcal connections)
enum enIOType { NON_TYPE_INIT = 0, ANALOG_INPUT, ANALOG_OUTPUT, DIGITAL_INPUT, DIGITAL_OUTPUT };
enum enIOStatus { NON_STATUS_INIT = 0, ENABLED, DISABLED, SUSPENDED, DISCONNECTED };

#include <stdio.h>
#include <stdint.h>
#include <memory>

typedef struct stIO {
	char name[UINT8_MAX];
	enIOType type;
	enIOStatus status;
	float value;
	stIO *next;
} stIO;

enum session_handshake { NONE, WELCOME, VERSION_CHECK, ACCEPTED, REJECTED };

typedef struct stDevice {
	char name[UINT8_MAX];
	stDevice *dev_list;
	stDevice *next;
	stIO *stIOs;
	// data structures
	char bufferIN[UINT8_MAX];
	char bufferOUT[UINT8_MAX];
}stDevice;

extern stDevice *this_device;

stDevice *GetNewStDevice(char *_name);
int AddDevice(stDevice *_device, stDevice *_new_device);
int DeleteDeviceByName(stDevice *_device, char *c_device_name);
stDevice *GetDeviceByName(char _dev_name[]);
int DeleteDeviceByPtr(stDevice *_parent_device, stDevice *_device_to_delete);
void UpdateDevice(stDevice *_device, char _msg[]);
void ReceiveFromChild(char *_msg);

stIO *GetIOByName(stDevice *_device, char *_io_name);

#endif
