#include "bubble.h"
#include "tcp_client.hpp"
#include "tcp_service.hpp"

/*switch(m_handshake)
{
  case NONE:
    std::cerr << "should not be here " << __LINE__ << " " << __FILE__ << std::endl; 
    break;
  case WELCOME:
    //TODO: trim sData
    if(sData.compare(std::string("V1.0\n"))!=0)
      {
	std::cout << "CLIENT VERSION NOT COMPATIBLE.\n";
	do_write(std::string("CONNECTION REJECTED BY PROTOCOL VERSION\n"));
      }else{
      do_write(std::string("CONNECTION ACCEPTED\n"));
      m_handshake = REJECTED;
    }
    m_handshake = ACCEPTED;
    break;
  case VERSION_CHECK:
    break;
  case ACCEPTED:
    break;
  case REJECTED:
    break;
};*/

stDevice *this_device = (stDevice*) malloc(sizeof(stDevice));

stDevice *GetNewStDevice(char *_name)
{
	if (GetDeviceByName(_name) != NULL) {
		//LOG this
		return NULL;
	}
	assert(strlen(_name) != 0);
	stDevice *new_device_ptr = (stDevice*)malloc(sizeof(stDevice));
	memset(new_device_ptr->name, 0x00, sizeof(new_device_ptr->name));
	memset(new_device_ptr->bufferIN, 0x00, sizeof(new_device_ptr->bufferIN));
	memset(new_device_ptr->bufferOUT, 0x00, sizeof(new_device_ptr->bufferOUT));
	new_device_ptr->dev_list = NULL;
	new_device_ptr->next = NULL;
	new_device_ptr->stIOs = NULL;
	return new_device_ptr;
}

//NOTE: name device supose to be checked already
int AddDevice(stDevice *_parent_device, stDevice *_new_device)
{
	if (_new_device == NULL) 
	{
		return RET_ERROR_DEVICE_IS_NULL;
	}
	if (_parent_device == NULL)
	{
		_parent_device = _new_device;
		return RET_OK;
	}
	while (_parent_device->next != NULL) {
		_parent_device = _parent_device->next;
	}
	_parent_device->next = _new_device;
	return RET_OK;
}

//NOTE: only child devices can be deleted
int DeleteDeviceByName(stDevice *_base_device, char *c_device_name)
{
	stDevice *tmp = GetDeviceByName(c_device_name);
	return DeleteDeviceByPtr(tmp);
}

stDevice *GetDeviceByName(stDevice *_parent, char *_child_dev_name)
{
	stDevice *tmp = _parent->dev_list;
	while (tmp != NULL) 
	{
		if (strcmp(tmp->name,_child_dev_name) == 0) return tmp;
		else tmp = tmp->next;
	}
	return NULL;
}

int DeleteDeviceByPtr(stDevice *_parent_device, stDevice *_device_to_delete)
{
	stDevice *tmp = _parent_device->dev_list;
	while (tmp != NULL) 
	{
		if (tmp == _device_to_delete) 
		{
			stDevice *tmp2 = tmp;
			tmp = tmp->next;
			delete(tmp2);
			return RET_OK;
		}
	}
	return RET_ERROR_DEVICE_NOT_FOUND;
}

int AddIO(stDevice *_device, char *_name, enIOType _type, enIOStatus _status, float _initial_value)
{
	if (GetIOByName(_device, _name) != NULL) return RET_ERROR_IO_ALREADY_EXIST;
	stIO *tmp = GetNewStIO();
	strcpy(tmp->name, _name);

}

stIO *GetNewStIO()
{
	stIO *tmp = (stIO*)malloc(sizeof(stIO));
	memset(tmp->name,0x00,UINT8_MAX);
	tmp->status = NON_STATUS_INIT;
	tmp->type = NON_TYPE_INIT;
	tmp->next = NULL;
	return tmp;
}

stIO *GetIOByName(stDevice *_device, char *_io_name) 
{
	stIO *tmp = _device->stIOs;
	while (tmp != NULL) 
	{
		if (strcmp(tmp->name, _io_name)) 
		{
			return tmp;
		}
		tmp = tmp->next;
	}
	return NULL;
}

int DeleteStIO(stDevice *_parent, stIO *_io_target) 
{
	stIO *tmp = _parent->stIOs;
	while (tmp != NULL){
		if (tmp == _io_target) {
			stIO *tmp2 = tmp;
			tmp = tmp->next;
			delete tmp2;
			return RET_OK;
		}
		tmp = tmp->next;
	}
	return RET_ERROR_IO_NOT_FOUND;
}

int DeleteStIOByName(stDevice *_parent, char *_io_name)
{
	stIO *tmp_io = GetIOByName(_parent,_io_name);
	if (tmp_io == NULL) return RET_ERROR_IO_NOT_FOUND;
	return DeleteStIO(_parent, tmp_io);
}

//U|main_dev|child_dev|child2_dev|IO|1.02
void UpdateIO(char *_device_str, char *_io_name, float value)
{
	char splitter[] = { "|" };
	char *dev_tmp = strtok(_device_str,splitter);
	char *dev_tmp_ant = NULL;
	while (dev_tmp != NULL)
	{
		dev_tmp_ant = dev_tmp;
		if (strcmp(dev_tmp, "IO") == 0)
		{

		}
		dev_tmp = strtok(NULL, splitter);
	}
}

void UpdateDevice(stDevice *_device, char _msg[])
{
	//
}

void ReceiveFromChild(char *_msg)
{

}

