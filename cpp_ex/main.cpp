#include "advanced_audio_info.hpp"

void writeToStd(HANDLE handle, char* buffer, int size)
{
    WriteFile(
        handle,
        buffer,
        size,
        NULL,
        NULL);
}

int main(int argc, char** argv)
{
    std::vector<DeviceInfo> info = log_advanced_device_information();

    HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    std::string nextLine = "\r\n";

    for (const DeviceInfo& dev_info : info)
    {
        std::string number_of_channels  = std::to_string(dev_info.number_of_channels);
        std::string avg_byte_per_second  = std::to_string(dev_info.avg_byte_per_second);

        writeToStd(outHandle, const_cast<char*>(number_of_channels.data()), number_of_channels.size());
        writeToStd(outHandle, const_cast<char*>(nextLine.data()), nextLine.size());
        writeToStd(outHandle, const_cast<char*>(avg_byte_per_second.data()), avg_byte_per_second.size());
        writeToStd(outHandle, const_cast<char*>(nextLine.data()), nextLine.size());
    }
}