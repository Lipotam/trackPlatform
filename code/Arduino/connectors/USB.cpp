#include "USB.h"

USB::USB() : ConnectingDevice(&Serial)
{
	//TODO: start serial on speed Constants::usb_serial_speed in `setup` loop
}
