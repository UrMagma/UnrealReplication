#include "GlobalReplication/Public/MemoryArchive.h"
#include <cstring> // For memcpy

FMemoryArchive::FMemoryArchive(std::vector<uint8_t>& InData)
    : Data(InData)
{
}

void FMemoryArchive::Serialize(void* InData, int64_t Num)
{
    if (Offset + Num > Data.size())
    {
        Data.resize(Offset + Num);
    }

    std::memcpy(Data.data() + Offset, InData, Num);
    Offset += Num;
}
