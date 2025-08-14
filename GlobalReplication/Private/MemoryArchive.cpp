#include "GlobalReplication/Public/MemoryArchive.h"
#include "GlobalReplication/Public/DataTypes.h"
#include <cstring> // For memcpy
#include <iostream>
#include <string>

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

// --- FString Serialization ---

// This is the out-of-line implementation for FString's Serialize method.
void FString::Serialize(FArchive& Ar)
{
    if (Ar.IsSaving())
    {
        int32_t Size = ToString().length();
        Ar << Size;
        if (Size > 0)
        {
            Ar.Serialize((void*)ToString().c_str(), Size);
        }
    }
    else
    {
        int32_t Size = 0;
        Ar << Size;
        // Resize the internal string and serialize directly into its buffer.
        // This is safe in C++17 and later.
        Data.resize(Size);
        if (Size > 0)
        {
            Ar.Serialize(Data.data(), Size);
        }
    }
}


// --- TArray Serialization ---

template<typename T>
void TArray<T>::Serialize(FArchive& Ar)
{
    if (Ar.IsSaving())
    {
        int32_t Size = size();
        Ar << Size;
        for (T& Element : *this)
        {
            Ar << Element;
        }
    }
    else
    {
        int32_t Size = 0;
        Ar << Size;
        clear();
        resize(Size);
        for (int32_t i = 0; i < Size; ++i)
        {
            Ar << (*this)[i];
        }
    }
}

// --- Explicit Template Instantiations ---
// This is necessary because the definition is in a .cpp file.
template void TArray<int>::Serialize(FArchive& Ar);
template void TArray<float>::Serialize(FArchive& Ar);
template void TArray<FString>::Serialize(FArchive& Ar);
