#pragma once

#include "GlobalReplication/Public/GlobalReplication.h"

// Header for a packet containing replicated properties.
struct FPropertyPacketHeader
{
    uint64_t NetID;
    uint8_t SubObjectIndex; // 0 for the main object, 1+ for components

    void Serialize(FArchive& Ar)
    {
        Ar << NetID;
        Ar << SubObjectIndex;
    }
};
