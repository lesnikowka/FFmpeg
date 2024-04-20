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

std::vector<DeviceInfo> sort_device_information(const std::vector<DeviceInfo>& info);

bool is_part(const std::wstring& part, const std::wstring& full);
