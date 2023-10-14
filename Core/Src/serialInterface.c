#include <serialInterface.h>

#include "usbd_cdc_if.h"

void serial_update(){
	uint8_t buffer[] = "Hello, World!\r\n";
	CDC_Transmit_FS(buffer, sizeof(buffer));
}
