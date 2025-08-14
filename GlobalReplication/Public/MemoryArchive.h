#pragma once

#include "GlobalReplication.h"
#include <vector>
#include <cstdint>

/**
 * @brief An implementation of FArchive that uses an in-memory buffer.
 */
class FMemoryArchive : public FArchive
{
public:
    FMemoryArchive(std::vector<uint8_t>& InData, bool bInIsSaving);
    virtual ~FMemoryArchive() = default;

    virtual void Serialize(void* Data, int64_t Num) override;

    const std::vector<uint8_t>& GetData() const { return Data; }

private:
    std::vector<uint8_t>& Data;
    size_t Offset = 0;
};
