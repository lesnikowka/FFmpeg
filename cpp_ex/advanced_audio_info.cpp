#include "advanced_audio_info.hpp"

#pragma comment(lib, "Winmm.lib")

namespace
{
bool is_part(const std::wstring& part, const std::wstring& full)
{
    if (part.size() > full.size())
    {
        return false;
    }

    for (int i = 0; i < part.size(); i++)
    {
        if (part[i] != full[i])
        {
            return false;
        }
    }

    return true;
}

std::vector<DeviceInfo> sort_device_information(const std::vector<DeviceInfo>& info)
{
    std::vector<DeviceInfo> sorted;

    int devices_count = waveInGetNumDevs();

    WAVEINCAPSW wave = {};

    for (int i = 0; i < devices_count; i++)
    {
        int num = i;
        waveInGetDevCapsW(num, &wave, sizeof(WAVEINCAPSW));
        std::wstring device_name(wave.szPname);

        for (const DeviceInfo& dev_info : info)
        {
            if (is_part(device_name, dev_info.name))
            {
                sorted.push_back(dev_info);
                break;
            }
        }
    }

    return sorted;
}
}

std::vector<DeviceInfo>  log_advanced_device_information()
{
    CoInitialize(NULL);

    std::vector<DeviceInfo> device_info;

    IMMDeviceEnumerator* devEnum;
    IMMDeviceCollection* collection = NULL;
    HRESULT h;
    IMMDevice* device = NULL;
    IPropertyStore* store = NULL;
    IAudioClient* client = NULL;
    PROPVARIANT friendly_name;
    WAVEFORMATEX* wave = NULL;
    PropVariantInit(&friendly_name);

    const CLSID CLSID_MMDeviceEnumerator = _uuidof(MMDeviceEnumerator);
    const IID IID_IMMDeviceEnumerator = _uuidof(IMMDeviceEnumerator);

    h = CoCreateInstance(
         CLSID_MMDeviceEnumerator, NULL,
         CLSCTX_ALL, IID_IMMDeviceEnumerator,
         (void**)&devEnum);
    if (h != S_OK)
    {
        return error_v;
    }

    h = devEnum->EnumAudioEndpoints(eCapture, DEVICE_STATE_ACTIVE, &collection);
    if (h != S_OK)
    {
        return error_v;
    }
    UINT count;
    h = collection->GetCount(&count);
    if (h != S_OK)
    {
        return error_v;
    }

    for (int i = 0; i < count; i++)
    {
        store = NULL;
        h = collection->Item(i, &device);
        if (h != S_OK)
        {
            return error_v;
        }
        h = device->OpenPropertyStore(STGM_READ, &store);
        if (h != S_OK)
        {
            return error_v;
        }
        h = store->GetValue(PKEY_Device_FriendlyName, &friendly_name);
        if (h != S_OK)
        {
            return error_v;
        }
        if (store)
        {
            store->Release();
        }

        std::wstring big_friendly_name_w = friendly_name.pwszVal;
        
        h = device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&client);
        if (h != S_OK)
        {
            return error_v;
        }
        h = client->GetMixFormat(&wave);
        if (h != S_OK)
        {
            return error_v;
        }

        device_info.push_back(DeviceInfo{big_friendly_name_w, wave->nChannels, wave->nAvgBytesPerSec});
    }

    device_info = sort_device_information(device_info);

    return device_info;
}
