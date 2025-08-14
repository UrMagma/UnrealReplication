#include "GlobalReplication/Public/RPC.h"
#include "GlobalReplication/Public/GlobalReplication.h"

void FRPCData::Serialize(FArchive& Ar)
{
    Ar << NetID;

    if (Ar.IsSaving())
    {
        int32_t NameLen = FunctionName.size();
        Ar << NameLen;
        Ar.Serialize((void*)FunctionName.data(), NameLen);

        int32_t ParamLen = Parameters.size();
        Ar << ParamLen;
        Ar.Serialize(Parameters.data(), ParamLen);
    }
    else
    {
        int32_t NameLen = 0;
        Ar << NameLen;
        FunctionName.resize(NameLen);
        Ar.Serialize((void*)FunctionName.data(), NameLen);

        int32_t ParamLen = 0;
        Ar << ParamLen;
        Parameters.resize(ParamLen);
        Ar.Serialize(Parameters.data(), ParamLen);
    }
}
