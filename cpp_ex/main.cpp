#include "advanced_audio_info.hpp"


int main(int argc, char** argv)
{
    bool isLogNameRequired = argc != 2 || std::stoi(argv[1]) != 1;

    std::vector<DeviceInfo> info = log_advanced_device_information();

    // cout for handling with pipe channel
    for (const DeviceInfo& dev_info : info)
    {
        if (isLogNameRequired)
        {
            std::wcout << dev_info.name << std::endl;
        }
        std::cout << dev_info.number_of_channels << std::endl;
        std::cout << dev_info.avg_byte_per_second << std::endl;
    }
}