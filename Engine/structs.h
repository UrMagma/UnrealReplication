#pragma once
/*
* CREDIT TO MILXNOR!
*/

#include <Windows.h>
#include <string>
#include <locale>
#include <format>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <thread>

#include "Engine/other.h"
#include <regex>

using namespace std::chrono;

#define INL __forceinline

static inline void (*ToStringO)(struct FName*, class FString&);
static inline void* (*ProcessEventO)(void*, void*, void*);

std::string FN_Version = "0.0";
static double FnVerDouble = 0;
int Engine_Version;

static struct FChunkedFixedUObjectArray* ObjObjects;
static struct FFixedUObjectArray* OldObjects;

namespace FMemory
{
	void (*Free)(void* Original);
	void* (*Realloc)(void* Original, SIZE_T Count, uint32_t Alignment /* = DEFAULT_ALIGNMENT */);
}

struct Timer
{
	time_point<std::chrono::steady_clock> start, end;
	duration<float> dura;

	Timer()
	{
		start = high_resolution_clock::now();
	}

	~Timer()
	{
		end = high_resolution_clock::now();
		dura = end - start;

		float ns = dura.count() * 10000.0f;
		std::cout << ("Took ") << ns << ("ns \n");
	}
};

template <class ElementType>
class TArray
{
	friend class FString;
protected:
	ElementType* Data = nullptr;
	int32_t ArrayNum = 0;
	int32_t ArrayMax = 0;
public:
	void Free()
	{
		if (FMemory::Free)
			FMemory::Free(Data);

		Data = nullptr;

		ArrayNum = 0;
		ArrayMax = 0;
	}

	 auto Num() const { return ArrayNum; }

	INL ElementType& operator[](int Index) const { return Data[Index]; }

	INL ElementType& At(int Index) const
	{
		return Data[Index];
	}

	bool IsValid() const
	{
		return Data;
	}

	INL int32_t Slack() const
	{
		return ArrayMax - ArrayNum;
	}

	void Reserve(int Number, int Size = sizeof(ElementType))
	{
		if (!FMemory::Realloc)
		{
			MessageBoxA(0, ("How are you expecting to reserve with no Realloc?"), ("Project Reboot"), MB_ICONERROR);
			return;
		}

		{
			Data = (ElementType*)FMemory::Realloc(Data, (ArrayMax = ArrayNum + Number) * Size, 0);
		}
	}

	int Add(const ElementType& New, int Size = sizeof(ElementType))
	{
		Reserve(1, Size);

		if (Data)
		{
			memcpy_s((ElementType*)(Data + (ArrayNum * Size)), Size, (void*)&New, Size);
			++ArrayNum;
			++ArrayMax;
			return ArrayNum;
		}

		std::cout << ("Invalid Data when adding!\n");

		return -1;
	};


	void RemoveAtSwapImpl(int Index, int Count = 1, bool bAllowShrinking = true)
	{
		if (Count)
		{
			const int NumElementsInHole = Count;
			const int NumElementsAfterHole = ArrayNum - (Index + Count);
			const int NumElementsToMoveIntoHole = std::min(NumElementsInHole, NumElementsAfterHole);
			if (NumElementsToMoveIntoHole)
			{
				memcpy(
					(uint8_t*)Data + (Index) * sizeof(ElementType),
					(uint8_t*)Data + (ArrayNum - NumElementsToMoveIntoHole) * sizeof(ElementType),
					NumElementsToMoveIntoHole * sizeof(ElementType)
				);
			}
			ArrayNum -= Count;

			if (bAllowShrinking)
			{
			}
		}
	}

	inline void RemoveAtSwap(int Index)
	{
		RemoveAtSwapImpl(Index, 1, true);
	}

	inline bool RemoveAt(const int Index)
	{
		if (Index < ArrayNum)
		{
			if (Index != ArrayNum - 1)
			{
				Data[Index] = Data[ArrayNum - 1];
			}

			--ArrayNum;

			return true;
		}

		return false;
	};

	INL auto GetData() const { return Data; }
};

class FString
{
public:
	TArray<TCHAR> Data;

	void Set(const wchar_t* NewStr)
	{
		if (!NewStr || std::wcslen(NewStr) == 0) return;

		Data.ArrayMax = Data.ArrayNum = *NewStr ? (int)std::wcslen(NewStr) + 1 : 0;

		if (Data.ArrayNum)
			Data.Data = const_cast<wchar_t*>(NewStr);
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data.Data);
		std::string str(length, '\0');
		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data.Data, Data.Data + length, '?', &str[0]);

		return str;
	}

	INL void operator=(const std::string& str) { Set(std::wstring(str.begin(), str.end()).c_str()); }

	void FreeString()
	{
		Data.Free();
	}

	FString()
	{
	}

	~FString()
	{
	}
};

#define NAME_NO_NUMBER_INTERNAL 0
#define NAME_None 0

struct FNameEntryId(*FromValidEName)(EName Ename);

struct FNameEntryId
{
	FORCEINLINE static FNameEntryId FromEName(EName Ename)
	{
		return Ename == NAME_None ? FNameEntryId() : FromValidEName(Ename);
	}

	int32_t Value;
};

struct FName
{
	uint32_t ComparisonIndex;
	uint32_t Number = NAME_NO_NUMBER_INTERNAL;

	INL std::string ToString()
	{
		if (!this)
			return "";

		FString temp;

		ToStringO(this, temp);

		auto Str = temp.ToString();

		temp.FreeString();

		return Str;
	}

	INL std::wstring ToSFtring()
	{
		if (!this)
			return L"";

		FString temp;

		ToStringO(this, temp);

		auto Str = std::wstring(temp.Data.GetData());

		temp.FreeString();

		return Str;
	}

	bool operator==(const FName& other)
	{
		return (other.ComparisonIndex == this->ComparisonIndex);
	}

	FORCEINLINE FName(EName Ename) : FName(Ename, NAME_NO_NUMBER_INTERNAL) {}

	FORCEINLINE FName(EName Ename, int32_t InNumber)
		: ComparisonIndex(FNameEntryId::FromEName(Ename).Value)
		, Number(InNumber)
	{
	}

	FName() {}
	FName(int _ComparisonIndex) : ComparisonIndex(_ComparisonIndex) {}
};

template <typename Fn>
inline Fn GetVFunction(const void* instance, std::size_t index)
{
	auto vtable = *reinterpret_cast<const void***>(const_cast<void*>(instance));
	return reinterpret_cast<Fn>(vtable[index]);
}

struct light
{
	int finalSize = 0;
	std::vector<int> Offsets;
	void* addr = nullptr;
	int onOffset = 0;

	template <typename T> void set(const T& t) {
		auto OffsetToUse = onOffset == 0 ? 0 : Offsets.at(onOffset);
		*(T*)( (char*)addr + OffsetToUse) = t;
		onOffset++;
	}

	template <typename First, typename... Rest> void set(const First& first, const Rest&... rest) {
		if (addr)
		{
			auto OffsetToUse = onOffset == 0 ? 0 : Offsets.at(onOffset);
			std::cout << std::format("Setting {} at offset: {}", first, OffsetToUse);
			* (First*)((char*)addr + OffsetToUse) = first;
			onOffset++;
			set(rest...);
		}
	}

	template <typename First, typename... Rest> void execute(const std::string& funcName, const First& first, const Rest&... rest) {
		addr = malloc(finalSize);

		set(first, rest...);

		return;
	}

	~light()
	{
		if (addr)
			free(addr);
	}
};

struct UObject;

struct UObject
{
	void** VFTable;
	int32_t ObjectFlags;
	int32_t InternalIndex;
	UObject* ClassPrivate;
	FName NamePrivate;
	UObject* OuterPrivate;

	INL std::string GetName() { return NamePrivate.ToString(); }
	INL std::wstring GetNFame() { return NamePrivate.ToSFtring(); }

	INL std::string GetFullName()
	{
		std::string temp;

		for (auto outer = OuterPrivate; outer; outer = outer->OuterPrivate)
			temp = std::format("{}.{}", outer->GetName(), temp);

		return std::format("{} {}{}", ClassPrivate->GetName(), temp, this->GetName());
	}

	INL std::string GetFullNameWOCP()
	{
		std::string temp;

		for (auto outer = OuterPrivate; outer; outer = outer->OuterPrivate)
			temp = std::format("{}.{}", outer->GetName(), temp);

		return std::format("{}{}", temp, this->GetName());
	}

	INL std::wstring GetFullNFame()
	{
		std::wstring temp;

		for (auto outer = OuterPrivate; outer; outer = outer->OuterPrivate)
			temp = outer->GetNFame() + L"." + temp;

		return ClassPrivate->GetNFame() + L" " + temp + this->GetNFame();
	}

	INL std::string GetFullNameT()
	{
		std::string temp;

		for (auto outer = OuterPrivate; outer; outer = outer->OuterPrivate)
			temp = std::format("{}.{}", outer->GetName(), temp);

		return temp + this->GetName();
	}

	bool IsA(UObject* cmp) const;

	INL struct UFunction* Function(const std::string& FuncName);

	INL auto ProcessEvent(UObject* Function, void* Params = nullptr)
	{
		return ProcessEventO(this, Function, Params);
	}

	INL void* ProcessEvent(const std::string& FuncName, void* Params = nullptr)
	{
		auto fn = this->Function(FuncName);

		if (!fn)
		{
			std::cout << ("[ERROR] Unable to find ") << FuncName << '\n';
			return nullptr;
		}

		return ProcessEvent((UObject*)fn, Params);
	}

	UObject* CreateDefaultObject()
	{
		static auto Index = 0;

		if (Index == 0)
		{
			if (Engine_Version < 421)
				Index = 101;
			else if (Engine_Version >= 420 && FnVerDouble < 7.40)
				Index = 102;
			else if (FnVerDouble >= 7.40)
				Index = 103;
			else if (Engine_Version == 424)
				Index = 106;
			else if (Engine_Version == 425)
				Index = 114;
			else
				std::cout << ("Unable to determine CreateDefaultObject Index!\n");
		}

		if (Index != 0)
		{
			if (Engine_Version < 424 || Engine_Version == 425)
				return GetVFunction<UObject* (*)(UObject*)>(this, Index)(this);
			else
			{
			}
		}
		else
			std::cout << ("Unable to create default object because Index is 0!\n");
		return nullptr;
	}

	template <typename strType = std::string, typename First, typename... Rest> void Exec(const strType& FunctionName, const First& first, const Rest&... rest) {
		static auto fn = this->Function(FunctionName);

		if (fn)
		{
			auto Params = light();
			Params.finalSize = fn->GetParmsSize();
			Params.Offsets = fn->GetAllParamOffsets();

			Params.execute(FunctionName, first, rest...);

			if (Params.addr)
				this->ProcessEvent(fn, Params.addr);
		}
	}

	template <typename MemberType = UObject*>
	INL MemberType* Member(const std::string& MemberName);

	template <typename MemberType>
	INL MemberType* CachedMember(const std::string& MemberName);

	template <typename MemberType>
	INL MemberType* FastMember(const std::string& MemberName);
};

struct UFunction : UObject
{
	template <typename T>
	T* GetParam(const std::string& ParameterName, void* Params);

	std::vector<int> GetAllParamOffsets();

	unsigned short GetParmsSize();

	void* GetFunc();
};

struct FUObjectItem
{
	UObject* Object;
	int32_t Flags;
	int32_t ClusterRootIndex;
	int32_t SerialNumber;
};

struct FFixedUObjectArray
{
	FUObjectItem* Objects;
	int32_t MaxElements;
	int32_t NumElements;

	INL const int32_t Num() const { return NumElements; }

	INL const int32_t Capacity() const { return MaxElements; }

	INL bool IsValidIndex(int32_t Index) const { return Index < Num() && Index >= 0; }

	INL UObject* GetObjectById(int32_t Index) const
	{
		return Objects[Index].Object;
	}

	INL FUObjectItem* GetItemById(int32_t Index) const
	{
		return &Objects[Index];
	}
};

struct FChunkedFixedUObjectArray
{
	enum
	{
		NumElementsPerChunk = 64 * 1024,
	};

	FUObjectItem** Objects;
	FUObjectItem* PreAllocatedObjects;
	int32_t MaxElements;
	int32_t NumElements;
	int32_t MaxChunks;
	int32_t NumChunks;

	INL const int32_t Num() const { return NumElements; }

	INL const int32_t Capacity() const { return MaxElements; }

	INL UObject* GetObjectById(int32_t Index) const
	{
		if (Index > NumElements || Index < 0) return nullptr;

		const int32_t ChunkIndex = Index / NumElementsPerChunk;
		const int32_t WithinChunkIndex = Index % NumElementsPerChunk;

		if (ChunkIndex > NumChunks) return nullptr;
		FUObjectItem* Chunk = Objects[ChunkIndex];
		if (!Chunk) return nullptr;

		auto obj = (Chunk + WithinChunkIndex)->Object;

		return obj;
	}

	INL FUObjectItem* GetItemById(int32_t Index) const
	{
		if (Index > NumElements || Index < 0) return nullptr;

		const int32_t ChunkIndex = Index / NumElementsPerChunk;
		const int32_t WithinChunkIndex = Index % NumElementsPerChunk;

		if (ChunkIndex > NumChunks) return nullptr;
		FUObjectItem* Chunk = Objects[ChunkIndex];
		if (!Chunk) return nullptr;

		auto obj = (Chunk + WithinChunkIndex);

		return obj;
	}
};

static UObject* (*StaticFindObjectO)(
	UObject* Class,
	UObject* InOuter,
	const TCHAR* Name,
	bool ExactClass);

static UObject* (*StaticLoadObjectO)(
	UObject* Class,
	UObject* InOuter,
	const TCHAR* Name,
	const TCHAR* Filename,
	uint32_t LoadFlags,
	UObject* Sandbox,
	bool bAllowObjectReconciliation,
	void* InSerializeContext
	);

template <typename T = UObject>
static T* StaticLoadObject(UObject* Class, UObject* Outer, const std::string& name, int LoadFlags = 0)
{
	if (!StaticLoadObjectO)
		return nullptr;

	auto Name = std::wstring(name.begin(), name.end()).c_str();
	return (T*)StaticLoadObjectO(Class, Outer, Name, nullptr, LoadFlags, nullptr, false, nullptr);
}

template <typename ReturnType = UObject>
static ReturnType* LoadObject(UObject* Class, UObject* Outer, const std::string& name)
{
	return StaticLoadObject<ReturnType>(Class, Outer, name.substr(name.find(" ") + 1));
}

template <typename ReturnType = UObject>
static ReturnType* StaticFindObject(const std::string& str)
{
	auto Name = std::wstring(str.begin(), str.end()).c_str();
	return (ReturnType*)StaticFindObjectO(nullptr, nullptr, Name, false);
}

template <typename ReturnType = UObject>
static ReturnType* GetByIndex(int Index)
{
	return (ReturnType*)(ObjObjects ? ObjObjects->GetObjectById(Index) : OldObjects->GetObjectById(Index));
}

template <typename ReturnType = UObject>
static ReturnType* FindObjectOld(const std::string& str, bool bIsEqual = false, bool bIsName = false)
{
	if (bIsName) bIsEqual = true;

	for (int32_t i = 0; i < (ObjObjects ? ObjObjects->Num() : OldObjects->Num()); i++)
	{
		auto Object = ObjObjects ? ObjObjects->GetObjectById(i) : OldObjects->GetObjectById(i);

		if (!Object) continue;

		auto ObjectName = bIsName ? Object->GetName() : Object->GetFullName();

		if (bIsEqual)
		{
			if (ObjectName == str)
				return (ReturnType*)Object;
		}
		else
		{
			if (ObjectName.contains(str))
				return (ReturnType*)Object;
		}
	}

	return nullptr;
}

template <typename ReturnType = UObject>
static ReturnType* FindObject(const std::string& str, bool bIsEqual = false, bool bIsName = false, bool bDoNotUseStaticFindObject = false, bool bSkipIfSFOFails = true)
{
	if (StaticFindObjectO && !bDoNotUseStaticFindObject)
	{
		auto Object = StaticFindObject<ReturnType>(str.substr(str.find(" ") + 1));
		if (Object)
		{
			return Object;
		}

		if (bSkipIfSFOFails)
			return nullptr;
	}

	return FindObjectOld<ReturnType>(str, bIsEqual, bIsName);
}

struct UField : UObject
{
	UField* Next;
};

struct UFieldPadding : UObject
{
	UField* Next;
	void* pad_01;
	void* pad_02;
};

struct UProperty_UE : public UField
{
	int32_t ArrayDim;
	int32_t ElementSize;
	uint64_t PropertyFlags;
	uint16_t RepIndex;
	TEnumAsByte<ELifetimeCondition> BlueprintReplicationCondition;
	int32_t Offset_Internal;
	FName RepNotifyFunc;
	UProperty_UE* PropertyLinkNext;
	UProperty_UE* NextRef;
	UProperty_UE* DestructorLinkNext;
	UProperty_UE* PostConstructLinkNext;
};

struct UStruct_FT : public UField
{
	UStruct_FT* SuperStruct;
	UField* ChildProperties;
	int32_t PropertiesSize;
	int32_t MinAlignment;
	TArray<uint8_t> Script;
	UProperty_UE* PropertyLink;
	UProperty_UE* RefLink;
	UProperty_UE* DestructorLink;
	UProperty_UE* PostConstructLink;
	TArray<UObject*> ScriptObjectReferences;
};

struct UProperty_FTO : UField
{
	uint32_t ArrayDim;
	uint32_t ElementSize;
	uint64_t PropertyFlags;
	char pad_40[4];
	uint32_t Offset_Internal;
	char pad_48[0x70 - 0x48];
};

struct UStruct_FTO : public UField
{
	UStruct_FTO* SuperStruct;
	UField* ChildProperties;
	int32_t PropertiesSize;
	int32_t MinAlignment;
	UProperty_FTO* PropertyLink;
	UProperty_FTO* RefLink;
	UProperty_FTO* DestructorLink;
	UProperty_FTO* PostConstructLink;
	TArray<UObject*> ScriptObjectReferences;
};

struct UStruct_FTT : UField
{
	void* Pad;
	void* Pad2;
	UStruct_FTT* SuperStruct;
	UField* ChildProperties;
	uint32_t PropertiesSize;
	char pad_44[0x88 - 0x30 - 0x14];
};

struct FField
{
	void** VFT;
	void* ClassPrivate;
	void* Owner;
	void* pad;
	FField* Next;
	FName NamePrivate;
	EObjectFlags FlagsPrivate;
	std::string GetName() { return NamePrivate.ToString(); }
};

struct FProperty : public FField
{
	int32_t ArrayDim;
	int32_t ElementSize;
	EPropertyFlags PropertyFlags;
	uint16_t RepIndex;
	TEnumAsByte<ELifetimeCondition> BlueprintReplicationCondition;
	int32_t Offset_Internal;
	FName RepNotifyFunc;
	FProperty* PropertyLinkNext;
	FProperty* NextRef;
	FProperty* DestructorLinkNext;
	FProperty* PostConstructLinkNext;
};

class UStruct_CT : public UFieldPadding
{
public:
	UStruct_CT* SuperStruct;
	UFieldPadding* Children;
	FField* ChildProperties;
	int32_t PropertiesSize;
	int32_t MinAlignment;
	TArray<uint8_t> Script;
	FProperty* PropertyLink;
	FProperty* RefLink;
	FProperty* DestructorLink;
	FProperty* PostConstructLink;
	TArray<UObject*> ScriptAndPropertyObjectReferences;
};

struct UClass_FT : public UStruct_FT {};
struct UClass_FTO : public UStruct_FTO {};
struct UClass_FTT : public UStruct_FTT {};
struct UClass_CT : public UStruct_CT {};

template <typename ClassType, typename PropertyType, typename ReturnValue = PropertyType> auto GetMembers(UObject* Object)
{
	std::vector<ReturnValue*> Members;
	if (Object)
	{
		for (auto CurrentClass = (ClassType*)Object->ClassPrivate; CurrentClass; CurrentClass = (ClassType*)CurrentClass->SuperStruct)
		{
			auto Property = CurrentClass->ChildProperties;
			if (Property)
			{
				auto Next = Property->Next;
				if (Next)
				{
					while (Property)
					{
						Members.push_back((ReturnValue*)Property);
						Property = Property->Next;
					}
				}
			}
		}
	}
	return Members;
}

template <typename ClassType, typename PropertyType, typename ReturnValue = PropertyType> auto GetMembersFProperty(UObject* Object, bool bOnlyMembers = false, bool bOnlyFunctions = false)
{
	std::vector<ReturnValue*> Members;
	if (Object)
	{
		for (auto CurrentClass = (ClassType*)Object->ClassPrivate; CurrentClass; CurrentClass = (ClassType*)CurrentClass->SuperStruct)
		{
			auto Property = CurrentClass->ChildProperties;
			auto Child = CurrentClass->Children;
			if ((!bOnlyFunctions && bOnlyMembers) || (!bOnlyFunctions && !bOnlyMembers))
			{
				if (Property)
				{
					Members.push_back((ReturnValue*)Property);
					auto Next = Property->Next;
					if (Next)
					{
						while (Property)
						{
							if (Property->GetName().contains("::"))
							{
								if (!bOnlyMembers)
								{
									Members.push_back((ReturnValue*)Property);
								}
							}
							else
							{
								if (!bOnlyFunctions)
								{
									Members.push_back((ReturnValue*)Property);
								}
							}
							Property = Property->Next;
						}
					}
				}
			}

			if (Child && (!bOnlyMembers || !bOnlyFunctions))
			{
				auto Next = Child->Next;
				if (Next)
				{
					while (Child)
					{
						if (Child->GetName().contains("::"))
						{
							if (!bOnlyMembers)
							{
								Members.push_back((ReturnValue*)Child);
							}
						}
						else
						{
							if (!bOnlyFunctions)
							{
								Members.push_back((ReturnValue*)Child);
							}
						}
						Child = Child->Next;
					}
				}
			}
		}
	}
	return Members;
}

// Structs:
struct FBuildingSupportCellQuery
{
	bool                                               bIncludeLocalPositionsInQuery;
	bool                                               bIncludeCachedCell;
	bool                                               bIncludeFloorInBottom;
	bool                                               bIncludeFloorInTop;
	bool                                               bIncludeCenterCell;
};

struct FBuildingSupportCellIndex
{
	int                                                X;
	int                                                Y;
	int                                                Z;

	bool operator==(const FBuildingSupportCellIndex& A)
	{
		return X == A.X && Y == A.Y && Z == A.Z;
	}
};

enum class EStructuralFloorPosition : uint8_t
{
	Top = 0,
	Bottom = 1,
	EStructuralFloorPosition_MAX = 2
};


enum class EStructuralWallPosition : uint8_t
{
	Left = 0,
	Right = 1,
	Front = 2,
	Back = 3,
	EStructuralWallPosition_MAX = 4
};

struct FTimespan
{
	int Ticks;
};

template <typename T>
struct TEnumAsByte
{
	T Value;
};

struct FGuid
{
	int A;
	int B;
	int C;
	int D;
};

struct FFortPickupTossData
{
	FVector                                        LootInitialPosition;
	FVector                                        LootFinalPosition;
	float                                        FlyTime;
	FVector                                        StartDirection;
	FVector                                        FinalTossRestLocation;
	uint8_t TossState;
	bool                                         bPlayPickupSound;
	uint8_t                                        Pad_3687[0x2];
	FGuid                                 PickupGuid;
};