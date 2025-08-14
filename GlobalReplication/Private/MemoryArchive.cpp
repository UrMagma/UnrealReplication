#include "GlobalReplication/Public/MemoryArchive.h"
#include <cstring> // For memcpy
#include <iostream>

FMemoryArchive::FMemoryArchive(std::vector<uint8_t>& InData, bool bInIsSaving)
    : FArchive(bInIsSaving), Data(InData)
{
}

void FMemoryArchive::Serialize(void* InData, int64_t Num)
{
    if (bIsSaving)
    {
        if (Offset + Num > Data.size())
        {
            Data.resize(Offset + Num);
        }
        std::memcpy(Data.data() + Offset, InData, Num);
    }
    else
    {
        if (Offset + Num > Data.size())
        {
            std::cerr << "FMemoryArchive::Serialize: Read out of bounds" << std::endl;
            return;
        }
        std::memcpy(InData, Data.data() + Offset, Num);
    }

    Offset += Num;
}
