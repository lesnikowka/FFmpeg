#include <Windows.h>
#include <Audioclient.h>
#include <mmsystem.h>
#include <mmdeviceapi.h>
#include <Functiondiscoverykeys_devpkey.h>
#include <comdef.h>
#include <vector>
#include <string>
#include <iostream>

#define error_v std::vector<DeviceInfo>();

struct DeviceInfo
{
    std::wstring name;
    UINT number_of_channels;
    UINT avg_byte_per_second;
};

std::vector<DeviceInfo> log_advanced_device_information();
