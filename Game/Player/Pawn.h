#include "Engine/structs.h"
#include "Engine/other.h"

enum class EFortCustomPartType : uint8_t
{
	Head = 0,
	Body = 1,
	Hat = 2,
	Backpack = 3,
	Charm = 4,
	Face = 5,
	NumTypes = 6,
	EFortCustomPartType_MAX = 7
};

class FortnitePlayerPawn : public FortnitePlayerPawn
{
    void ServerChoosePart(EFortCustomBodyType Part, UObject* CharacterPart);
};