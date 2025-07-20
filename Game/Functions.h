#pragma once

#include "structs.h" // For FName, FString, FVector, FRotator, TArray, FGuid, FGameplayTag, FGameplayTagContainer etc.

// Forward declarations for classes used in parameter structs, if not fully defined in structs.h
class UFortItemDefinition;
enum class EFortQuickBars : uint8_t;
enum class EInputEvent : uint8_t;
class UFortItem;
class UAthenaCosmeticItemDefinition;
enum class EAthenaCustomizationCategory : uint8_t;
class AFortPlayerPawn;
class UFortMontageItemDefinitionBase;
class AFortObjectiveBase;
enum class EFortObjectiveStatus : uint8_t;
enum class EStatCategory : uint8_t;
struct FVector_NetQuantize;
class ABuildingSMActor;
enum class EFortItemType : uint8_t;
class ABuildingActor;
class UGameplayAbility;
class APlayerController;
enum class EFortCrucibleWhitelistLevel : uint8_t;
class USoundBase;
class UAudioComponent;
enum class ERespawnCameraBehavior : uint8_t;
class UFortWeaponItemDefinition;
enum class EDeathCause : uint8_t;
enum class ESubGame : uint8_t;
struct FMcpVariantChannelInfo;
struct FFortAthenaLoadout;
enum class EDadBroHealthType : uint8_t;
class UMeshComponent;
enum class EFortPickupTossState : uint8_t; // From structs.h if fully defined
class UFortWorldItem;
struct FRecipe;
struct FQuickBar;
class UControllerComponent;
class AFortPlayerStateAthena;
class AActor;
struct FFortItemEntry;
struct FFortGameplayAttributeData;
struct FProfileUpdateSingle;
struct FDedicatedServerUrlContext;
class UAthenaItemWrapDefinition;


namespace SDK
{
namespace Params
{

//---------------------------------------------------------------------------------------------------------------------
// PARAMETERS
//---------------------------------------------------------------------------------------------------------------------

// Function Athena_PlayerController.Athena_PlayerController_C.PawnPossessedDispatcher__DelegateSignature
struct Athena_PlayerController_C_PawnPossessedDispatcher__DelegateSignature_Params
{
public:
	class APawn* PossessedPawn;                                     // 0x0(0x8)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function Athena_PlayerController.Athena_PlayerController_C.ExecuteUbergraph_Athena_PlayerController
struct Athena_PlayerController_C_ExecuteUbergraph_Athena_PlayerController_Params
{
public:
	int32                                        EntryPoint;                                        // 0x0(0x4)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function Athena_PlayerController.Athena_PlayerController_C.OnMusicPackLoaded__DelegateSignature
struct Athena_PlayerController_C_OnMusicPackLoaded__DelegateSignature_Params
{
public:
	class USoundBase* Music;                                             // 0x0(0x8)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                        StartTime;                                         // 0x8(0x4)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function Athena_PlayerController.Athena_PlayerController_C.ChangeMusic
struct Athena_PlayerController_C_ChangeMusic_Params
{
public:
	class USoundBase* New_Music;                                         // 0x0(0x8)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                        StartTime;                                         // 0x8(0x4)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};

// Function Athena_PlayerController.Athena_PlayerController_C.FadeAudioComponents
struct Athena_PlayerController_C_FadeAudioComponents_Params
{
public:
	class UAudioComponent* NewMusicComponent;                                 // 0x0(0x8)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class UAudioComponent* PreviousMusicComponent;                            // 0x8(0x8)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	class USoundBase* Music;                                             // 0x10(0x8)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
	float                                        StartTime;                                         // 0x18(0x4)(BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash)
};


// Function FortniteGame.FortPlayerController.AddInventoryItemWithAlterationBasedOnLootLevel
struct FortPlayerController_AddInventoryItemWithAlterationBasedOnLootLevel_Params
{
public:
	struct FFortItemEntry                        ItemDescription;                                   // 0x0(0x54)(Parm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.AddInventoryItemWithAnimation
struct FortPlayerController_AddInventoryItemWithAnimation_Params
{
public:
	struct FFortItemEntry                        ItemDescription;                                   // 0x0(0x54)(Parm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.AddItemToQuickBars
struct FortPlayerController_AddItemToQuickBars_Params
{
public:
	class UFortItemDefinition* ItemDefinition;                                    // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EFortQuickBars                               QuickBarType;                                      // 0x8(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                        SlotIndex;                                         // 0xC(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.AlternateInteractCarryHoldStopped
struct FortPlayerController_AlternateInteractCarryHoldStopped_Params
{
public:
	class FName                                  InputActionName;                                   // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bCompletedSuccessfully;                            // 0x8(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.AreActionsBoundToSameKey
struct FortPlayerController_AreActionsBoundToSameKey_Params
{
public:
	class FName                                  FirstActionName;                                   // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FName                                  SecondActionName;                                  // 0x8(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EInputEvent                                  InputEvent;                                        // 0x10(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         ReturnValue;                                       // 0x11(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.BP_FindItemInstancesFromDefinition
struct FortPlayerController_BP_FindItemInstancesFromDefinition_Params
{
public:
	class UFortItemDefinition* ItemDefinition;                                    // 0x0(0x8)(ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	TArray<class UFortItem*>                     ItemArray;                                         // 0x8(0x10)(Parm, OutParm, ZeroConstructor, ReferenceParm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ChangeActiveVariantForCosmeticItem
struct FortPlayerController_ChangeActiveVariantForCosmeticItem_Params
{
public:
	class FName                                  ItemTemplateToChange;                              // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FGameplayTag                          VariantChannelToChange;                            // 0x8(0x4)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FGameplayTag                          DesiredActiveVariant;                              // 0xC(0x4)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class AFortPlayerPawn* PreviewPawn;                                       // 0x10(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.Cheat
struct FortPlayerController_Cheat_Params
{
public:
	class FString                                Msg;                                               // 0x0(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.Cheat_ForceAthenaCosmeticItemInSlot
struct FortPlayerController_Cheat_ForceAthenaCosmeticItemInSlot_Params
{
public:
	class UAthenaCosmeticItemDefinition* CosmeticItem;                                      // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EAthenaCustomizationCategory                 Slot;                                              // 0x8(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                        Param_Index;                                       // 0xC(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.Cheat_ForceCosmeticVariantChannels
struct FortPlayerController_Cheat_ForceCosmeticVariantChannels_Params
{
public:
	TArray<struct FMcpVariantChannelInfo>        CosmeticVariantChannels;                           // 0x0(0x10)(ConstParm, Parm, OutParm, ReferenceParm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.Cheat_ForcePlayEmoteItem
struct FortPlayerController_Cheat_ForcePlayEmoteItem_Params
{
public:
	class UFortMontageItemDefinitionBase* EmoteAsset;                                        // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.Cheat_StopObjectiveServer
struct FortPlayerController_Cheat_StopObjectiveServer_Params
{
public:
	class AFortObjectiveBase* Objective;                                         // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EFortObjectiveStatus                         Status;                                            // 0x8(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.CheatAll
struct FortPlayerController_CheatAll_Params
{
public:
	class FString                                Msg;                                               // 0x0(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.CheckPossessionOfAmountOfItems
struct FortPlayerController_CheckPossessionOfAmountOfItems_Params
{
public:
	EFortItemType                                Type;                                              // 0x0(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                        AmountToCheck;                                     // 0x4(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         ReturnValue;                                       // 0x8(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ClientActivateSlot
struct FortPlayerController_ClientActivateSlot_Params
{
public:
	EFortQuickBars                               InQuickBar;                                        // 0x0(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	int32                                        Slot;                                              // 0x4(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                        ActivateDelay;                                     // 0x8(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bUpdatePreviousFocusedSlot;                        // 0xC(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bForceExecution;                                   // 0xD(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ClientAddScoreNumber
struct FortPlayerController_ClientAddScoreNumber_Params
{
public:
	int32                                        Score;                                             // 0x0(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EStatCategory                                ScoreCategory;                                     // 0x4(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector_NetQuantize                   ScoreLocation;                                     // 0x8(0xC)(Parm, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bDisplayScoreOnPlayer;                             // 0x14(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ClientBotEnqueueCommand
struct FortPlayerController_ClientBotEnqueueCommand_Params
{
public:
	class FString                                CommandToEnqueue;                                  // 0x0(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ClientBotSetModuleToUse
struct FortPlayerController_ClientBotSetModuleToUse_Params
{
public:
	class FString                                PilotCategory;                                     // 0x0(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FString                                NewModule;                                         // 0x10(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bResetNow;                                         // 0x20(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ClientConfirmTargetData
struct FortPlayerController_ClientConfirmTargetData_Params
{
public:
	uint16                                       UniqueId;                                          // 0x0(0x2)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bSuccess;                                          // 0x2(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	TArray<uint8>                                HitReplaces;                                       // 0x8(0x10)(ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ClientCreateOrJoinChatRoom
struct FortPlayerController_ClientCreateOrJoinChatRoom_Params
{
public:
	class FString                                ChatRoomId;                                        // 0x0(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ClientDeveloper_GetConsoleVariable
struct FortPlayerController_ClientDeveloper_GetConsoleVariable_Params
{
public:
	class FString                                ConsoleVariable;                                   // 0x0(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FString                                Value;                                             // 0x10(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ClientEquipItem
struct FortPlayerController_ClientEquipItem_Params
{
public:
	struct FGuid                                 ItemGuid;                                          // 0x0(0x10)(ConstParm, Parm, OutParm, ReferenceParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bForceExecution;                                   // 0x10(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ClientExecuteInventoryItem
struct FortPlayerController_ClientExecuteInventoryItem_Params
{
public:
	struct FGuid                                 ItemGuid;                                          // 0x0(0x10)(ConstParm, Parm, OutParm, ReferenceParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                        Delay;                                             // 0x10(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bForceExecute;                                     // 0x14(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bActivateSlotAfterSettingFocused;                  // 0x15(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ClientFailedToBeginEditingBuildingActor
struct FortPlayerController_ClientFailedToBeginEditingBuildingActor_Params
{
public:
	class ABuildingSMActor* BuildingActorToStopEditing;                        // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.ProcessMcpProfileUpdate
struct FortPlayerController_ProcessMcpProfileUpdate_Params
{
public:
	struct FProfileUpdateSingle                  Update;                                            // 0x0(0x28)(ConstParm, Parm, OutParm, ReferenceParm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.HasPermissionToEditWorld
struct FortPlayerController_HasPermissionToEditWorld_Params
{
public:
	class ABuildingActor* Building;                                          // 0x0(0x8)(ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector                               Location;                                          // 0x8(0xC)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FRotator                              Rotation;                                          // 0x14(0xC)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, NativeAccessSpecifierPublic)
	bool                                         ReturnValue;                                       // 0x20(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerController.IsActionInputIgnored
struct FortPlayerController_IsActionInputIgnored_Params
{
public:
	bool                                         ReturnValue;                                       // 0x0(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortCheatManager.ShouldUseNewHeroLoadoutUI
struct FortCheatManager_ShouldUseNewHeroLoadoutUI_Params
{
public:
	class APlayerController* PC;                                                // 0x0(0x8)(ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         ReturnValue;                                       // 0x8(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortCheatManager.Crucible_SetWhitelisted
struct FortCheatManager_Crucible_SetWhitelisted_Params
{
public:
	EFortCrucibleWhitelistLevel                  WhitelistLevel;                                    // 0x0(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortCheatManager.McpJoinFromPartyInviteToken
struct FortCheatManager_McpJoinFromPartyInviteToken_Params
{
public:
	class FString                                Token;                                             // 0x0(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bIsFromInvite;                                     // 0x10(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortCheatManager.StartWeatherEvent
struct FortCheatManager_StartWeatherEvent_Params
{
public:
	int32                                        WeatherEventIndex;                                 // 0x0(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                        Intensity;                                         // 0x4(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                                        Duration;                                          // 0x8(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.BuildingFoundation.EditorOnlyUnloadPreviewLevel
struct BuildingFoundation_EditorOnlyUnloadPreviewLevel_Params
{
public:
	bool                                         ReturnValue;                                       // 0x0(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortCharacterAttrSet.OnRep_Resistance
struct FortCharacterAttrSet_OnRep_Resistance_Params
{
public:
	struct FFortGameplayAttributeData            OldValue;                                          // 0x0(0x8)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortCharacterAttrSet.OnRep_Tech
struct FortCharacterAttrSet_OnRep_Tech_Params
{
public:
	struct FFortGameplayAttributeData            OldValue;                                          // 0x0(0x8)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, NativeAccessSpecifierPublic)
};

// Function FortniteGame.BuildingPhoenixRepairActor.GetWeaponHasDurability
struct BuildingPhoenixRepairActor_GetWeaponHasDurability_Params
{
public:
	class UFortWorldItem* WeaponItem;                                        // 0x0(0x8)(ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         ReturnValue;                                       // 0x8(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.BuildingPhoenixRepairActor.GetWeaponRepairRecipe
struct BuildingPhoenixRepairActor_GetWeaponRepairRecipe_Params
{
public:
	class AFortPlayerController* FPC;                                               // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FRecipe                               OutRecipe;                                         // 0x8(0x38)(Parm, OutParm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerControllerAthena.ClientStartRespawnPreparation
struct FortPlayerControllerAthena_ClientStartRespawnPreparation_Params
{
public:
	struct FVector                               RespawnLoc;                                        // 0x0(0xC)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FRotator                              RespawnRot;                                        // 0xC(0xC)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, NativeAccessSpecifierPublic)
	float                                        RespawnCameraDist;                                 // 0x18(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	ERespawnCameraBehavior                       InRespawnCameraBehavior;                           // 0x1C(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class FText                                  HUDReasonText;                                     // 0x20(0x18)(ConstParm, Parm, OutParm, ReferenceParm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerControllerAthena.PlayWinEffects
struct FortPlayerControllerAthena_PlayWinEffects_Params
{
public:
	class APawn* FinisherPawn;                                      // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class UFortWeaponItemDefinition* FinishingWeapon;                                   // 0x8(0x8)(ConstParm, Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	EDeathCause                                  DeathCause;                                        // 0x10(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         bAudioOnly;                                        // 0x11(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerControllerAthena.PostLobbyIslandTeleport
struct FortPlayerControllerAthena_PostLobbyIslandTeleport_Params
{
public:
	class AFortPlayerPawn* PlayerPawn;                                        // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortniteAutomationBlueprintLibrary.GetWrapPreviewObjects
struct FortniteAutomationBlueprintLibrary_GetWrapPreviewObjects_Params
{
public:
	ESubGame                                     SubGame;                                           // 0x0(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	TArray<TSoftObjectPtr<class UObject>>        ReturnValue;                                       // 0x8(0x10)(Parm, OutParm, ZeroConstructor, ReturnParm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortniteAutomationBlueprintLibrary.MakeLoadoutFromVariantChannelInfos
struct FortniteAutomationBlueprintLibrary_MakeLoadoutFromVariantChannelInfos_Params
{
public:
	TArray<struct FMcpVariantChannelInfo>        VariantInfo;                                       // 0x0(0x10)(ConstParm, Parm, OutParm, ReferenceParm, NativeAccessSpecifierPublic)
	struct FFortAthenaLoadout                    ReturnValue;                                       // 0x10(0x50)(Parm, OutParm, ReturnParm, NoDestructor, NativeAccessSpecifierPublic)
};

// Function FortniteGame.DadBroHealthInterface.GetCurrentHealthType
struct DadBroHealthInterface_GetCurrentHealthType_Params
{
public:
	EDadBroHealthType                            ReturnValue;                                       // 0x0(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortAccountBuffItem.IsActive
struct FortAccountBuffItem_IsActive_Params
{
public:
	bool                                         ReturnValue;                                       // 0x0(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.ObjectInteractionBehavior.GetFortPlayerController
struct ObjectInteractionBehavior_GetFortPlayerController_Params
{
public:
	class AFortPlayerController* ReturnValue;                                       // 0x0(0x8)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.DeleteObjects.GetDeleteActorsMeshComponents
struct UDeleteObjects_GetDeleteActorsMeshComponents_Params
{
public:
	TArray<class UMeshComponent*>                Components;                                        // 0x0(0x10)(Parm, OutParm, ZeroConstructor, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortAthenaMutator_TODOverride.GetTimeOfDaySpeedNames
struct FortAthenaMutator_TODOverride_GetTimeOfDaySpeedNames_Params
{
public:
	TArray<class FText>                          ReturnValue;                                       // 0x0(0x10)(Parm, OutParm, ZeroConstructor, ReturnParm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortInGameMapManager.GetStaticCaptureSetupComplete
struct FortInGameMapManager_GetStaticCaptureSetupComplete_Params
{
public:
	bool                                         ReturnValue;                                       // 0x0(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerControllerPvE.ServerUpdateQuickBarRecordsCache
struct FortPlayerControllerPvE_ServerUpdateQuickBarRecordsCache_Params
{
public:
	struct FQuickBar                             PrimaryQuickBarRecord;                             // 0x0(0x48)(ConstParm, Parm, OutParm, ReferenceParm, NativeAccessSpecifierPublic)
	struct FQuickBar                             SecondaryQuickBarRecord;                           // 0x48(0x48)(ConstParm, Parm, OutParm, ReferenceParm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortHealthSet.OnRep_MaxHealth
struct FortHealthSet_OnRep_MaxHealth_Params
{
public:
	struct FFortGameplayAttributeData            OldValue;                                          // 0x0(0x8)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortPlayerPawn.ClientNotifyAbilityFailed
struct FortPlayerPawn_ClientNotifyAbilityFailed_Params
{
public:
	class UGameplayAbility* FailedAbility;                                     // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FGameplayTagContainer                 FailedReason;                                      // 0x8(0x20)(ConstParm, Parm, OutParm, ReferenceParm, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortCheatManager_Quests.CompleteAllQuestsByName
struct FortCheatManager_Quests_CompleteAllQuestsByName_Params
{
public:
	class FString                                QuestPartialName;                                  // 0x0(0x10)(Parm, OutParm, ZeroConstructor, ReferenceParm, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortCheatManagerSTW.SetWorldLevel
struct FortCheatManagerSTW_SetWorldLevel_Params
{
public:
	float                                        Level;                                             // 0x0(0x4)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortMcpProfileCreative.RestoreDeletedIsland
struct FortMcpProfileCreative_RestoreDeletedIsland_Params
{
public:
	class FString                                PlotItemId;                                        // 0x0(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FDedicatedServerUrlContext            Context;                                           // 0x10(0x18)(Parm, OutParm, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic) // Assumed struct
};

// Function FortniteGame.FortKismetLibrary.RemoveControllerComponent
struct FortKismetLibrary_RemoveControllerComponent_Params
{
public:
	class AController* Controller;                                        // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	TSubclassOf<class UControllerComponent>      ControllerCompClass;                               // 0x8(0x8)(Parm, NoDestructor, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortMinigame.OverridePlayerSpawnLocation
struct FortMinigame_OverridePlayerSpawnLocation_Params
{
public:
	class APawn* PlayerPawn;                                        // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class AFortPlayerStateAthena* PlayerState;                                       // 0x8(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector                               OutLocation;                                       // 0x10(0xC)(Parm, OutParm, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FRotator                              OutRotation;                                       // 0x1C(0xC)(Parm, OutParm, NoDestructor, NativeAccessSpecifierPublic)
	bool                                         bOutRespawningOnGround;                            // 0x28(0x1)(Parm, OutParm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	bool                                         ReturnValue;                                       // 0x29(0x1)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.FortWorldMarker.PlayerStateDestroyed
struct FortWorldMarker_PlayerStateDestroyed_Params
{
public:
	class AActor* DestroyedActor;                                    // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.ThreatCloud.OnCloudHiddenChange
struct ThreatCloud_OnCloudHiddenChange_Params
{
public:
	bool                                         bCloudsAreHidden;                                  // 0x0(0x1)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.ThreatCloud.OnLightningStrike
struct ThreatCloud_OnLightningStrike_Params
{
public:
	struct FVector                               StartLocation;                                     // 0x0(0xC)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	struct FVector                               EndLocation;                                       // 0xC(0xC)(ConstParm, Parm, OutParm, ReferenceParm, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.WorldMapPinManager.CreateWorldMapPin
struct WorldMapPinManager_CreateWorldMapPin_Params
{
public:
	class FString                                TheaterId;                                         // 0x0(0x10)(Parm, ZeroConstructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	class AWorldMapPin* ReturnValue;                                       // 0x10(0x8)(Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

// Function FortniteGame.WrapPreviewGridActor.SetWrap
struct WrapPreviewGridActor_SetWrap_Params
{
public:
	class UAthenaItemWrapDefinition* NewWrap;                                           // 0x0(0x8)(Parm, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

}
} // namespace SDK
```

-----

### 2\. `FortniteGame_classes.h` (Generated from `_functions.cpp` files)

This file provides minimal class definitions and forward declarations for all referenced Unreal Engine classes.

```cpp
#pragma once

#include "structs.h" // For UObject, TSubclassOf, FText etc.

// Engine Classes Forward Declarations (common UE classes)
class UWorld;
class AGameStateBase;
class APlayerController;
class APawn;
class USoundBase;
class UAudioComponent;
class UMeshComponent;
class AActor;
class AController;

namespace SDK
{
// Enums (often found in _enums.h, but we'll put them here for simplicity)
enum class EFortQuickBars : uint8_t
{
	Primary = 0,
	Secondary = 1,
	Max_None = 2,
};

enum class EInputEvent : uint8_t
{
	IE_Pressed = 0,
	IE_Released = 1,
	IE_Repeat = 2,
	IE_DoubleClick = 3,
	IE_Axis = 4,
	IE_MAX = 5,
};

enum class EAthenaCustomizationCategory : uint8_t
{
	None = 0,
	Outfit = 1,
	Backpack = 2,
	Pickaxe = 3,
	Glider = 4,
	SkyDiveContrail = 5,
	Emoji = 6,
	ItemWrap = 7,
	LoadingScreen = 8,
	MusicPack = 9,
	Hat = 10,
	Face = 11,
	Pet = 12,
	Dance = 13,
	ItemVariant = 14,
	CharacterPart = 15,
	Emote = 16,
	Spray = 17,
	Toy = 18,
	WeaponCharm = 19,
	Alteration = 20,
	EAthenaCustomizationCategory_MAX = 21,
};

enum class EFortObjectiveStatus : uint8_t
{
	Active = 0,
	Completed = 1,
	Failed = 2,
	Inactive = 3,
	EFortObjectiveStatus_MAX = 4,
};

enum class EStatCategory : uint8_t
{
	Combat = 0,
	Building = 1,
	Utility = 2,
	Team = 3,
	Badges = 4,
	Harvesting = 5,
	Healing = 6,
	Crafting = 7,
	EStatCategory_MAX = 8,
};

enum class EFortItemType : uint8_t
{
	WorldItem = 0,
	Ammo = 1,
	Weapon = 2,
	Trap = 3,
	Consumable = 4,
	Badge = 5,
	Hero = 6,
	Schematic = 7,
	Commander = 8,
	Worker = 9,
	TeamPerk = 10,
	Upgrade = 11,
	AthenaCosmetic = 12,
	AccountResource = 13,
	CollectionBook = 14,
	Quest = 15,
	HomebaseNode = 16,
	Token = 17,
	Voucher = 18,
	NewItem = 19,
	GiftBox = 20,
	Profile = 21,
	Alteration = 22,
	Material = 23,
	GameplayEffect = 24,
	SpecialItem = 25,
	CollectedResource = 26,
	AthenaGadget = 27,
	AthenaWeapon = 28,
	AthenaResource = 29,
	AthenaAmmo = 30,
	Playset = 31,
	EditTool = 32,
	CreativeTool = 33,
	FortCosmetic = 34,
	FortHomebaseNode = 35,
	FortResource = 36,
	FortGadget = 37,
	FortTrap = 38,
	FortWeapon = 39,
	FortAmmo = 40,
	FortConsumable = 41,
	FortBadge = 42,
	FortHero = 43,
	FortSchematic = 44,
	FortWorker = 45,
	FortTeamPerk = 46,
	FortUpgrade = 47,
	FortCollectionBook = 48,
	FortQuest = 49,
	FortToken = 50,
	FortVoucher = 51,
	FortAlteration = 52,
	FortAccountResource = 53,
	FortMaterial = 54,
	FortGameplayEffect = 55,
	FortAccountBuff = 56,
	FortSeasonalResource = 57,
	FortChallengeBundle = 58,
	MAX = 59,
};

enum class EFortCrucibleWhitelistLevel : uint8_t
{
	None = 0,
	WhitelistOnly = 1,
	BlacklistOnly = 2,
	MAX = 3,
};

enum class ERespawnCameraBehavior : uint8_t
{
	RespawnCameraBehavior_None = 0,
	RespawnCameraBehavior_FollowKiller = 1,
	RespawnCameraBehavior_FollowNearestTeammate = 2,
	RespawnCameraBehavior_Spectate = 3,
	RespawnCameraBehavior_MAX = 4,
};

enum class EDeathCause : uint8_t
{
	FallDamage = 0,
	Pistol = 1,
	Shotgun = 2,
	Rifle = 3,
	SMG = 4,
	Sniper = 5,
	Melee = 6,
	Ability = 7,
	Trap = 8,
	Building = 9,
	Commited = 10,
	Minigun = 11,
	Grenade = 12,
	Badged = 13,
	Pickaxe = 14,
	Turret = 15,
	Landed = 16,
	Player = 17,
	Gibbed = 18,
	IED = 19,
	Burned = 20,
	Axe = 21,
	Pet = 22,
	Gas = 23,
	Storm = 24,
	Transform = 25,
	DBNO = 26,
	Other = 27,
	Vehicle = 28,
	Aircraft = 29,
	Projectile = 30,
	Lawnmower = 31,
	Prop = 32,
	SelfDestruct = 33,
	Removed = 34,
	Pushed = 35,
	DBNOCarry = 36,
	DBNORevive = 37,
	DBNOBleedOut = 38,
	EDeathCause_MAX = 39,
};

enum class ESubGame : uint8_t
{
	Campaign = 0,
	Athena = 1,
	Invalid = 2,
	ESubGame_MAX = 3,
};

enum class EDadBroHealthType : uint8_t
{
	None = 0,
	Primary = 1,
	Secondary = 2,
	Tertiary = 3,
	EDadBroHealthType_MAX = 4,
};


// Classes (minimal definitions to allow compilation)
// Note: These are simplified. Real SDKs would have many more members and inheritance.
// We assume 'A' classes inherit from AActor, 'U' classes from UObject.

class ABuildingSMActor : public AActor {}; // Used in ClientFailedToBeginEditingBuildingActor
class ABuildingActor : public AActor {}; // Used in HasPermissionToEditWorld
class AFortObjectiveBase : public AActor {}; // Used in Cheat_StopObjectiveServer
class AARDronePawn : public APawn {}; // Specific Pawn for AR Drone
class ABuildingFoundation : public AActor {}; // Used in EditorOnlyUnloadPreviewLevel
class ABuildingPhoenixRepairActor : public AActor {}; // Used in GetWeaponHasDurability
class AFortAthenaMutator_TODOverride : public AActor {}; // Used in GetTimeOfDaySpeedNames
class AFortInGameMapManager : public AActor {}; // Used in GetStaticCaptureSetupComplete
class AThreatCloud : public AActor {}; // Used in OnCloudHiddenChange
class AWorldMapPin : public AActor {}; // Used in CreateWorldMapPin
class AWrapPreviewGridActor : public AActor {}; // Used in SetWrap
class AFortMinigame : public AActor {}; // Used in OverridePlayerSpawnLocation

class UFortItemDefinition : public UObject {}; // Used in AddItemToQuickBars, BP_FindItemInstancesFromDefinition
class UFortItem : public UObject {}; // Used in BP_FindItemInstancesFromDefinition
class UAthenaCosmeticItemDefinition : public UObject {}; // Used in Cheat_ForceAthenaCosmeticItemInSlot
class UFortMontageItemDefinitionBase : public UObject {}; // Used in Cheat_ForcePlayEmoteItem
class UFortCharacterAttrSet : public UObject {}; // Used in OnRep_Resistance
class UFortWorldItem : public UObject {}; // Used in GetWeaponHasDurability
class UFortWeaponItemDefinition : public UObject {}; // Used in PlayWinEffects
class UFortniteAutomationBlueprintLibrary : public UObject {}; // Used in GetWrapPreviewObjects (static class)
class IDadBroHealthInterface : public UObject {}; // Interface
class UDeathEffectsPawnComponent : public UObject {}; // Used in ClientPlayWinnerDeathEffects
class UFortAccountBuffItem : public UObject {}; // Used in IsActive
class UObjectInteractionBehavior : public UObject {}; // Used in GetFortPlayerController
class UDeleteObjects : public UObject {}; // Used in GetDeleteActorsMeshComponents (static class)
class UFortHealthSet : public UObject {}; // Used in OnRep_MaxHealth
class UGameplayAbility : public UObject {}; // Used in ClientNotifyAbilityFailed
class UFortCheatManager_Affiliation : public UObject {}; // Used in Affiliation_ResetMemberRelations (static class)
class UFortCheatManager_Quests : public UObject {}; // Used in CompleteAllQuestsByName (static class)
class UFortCheatManagerSTW : public UObject {}; // Used in SetWorldLevel (static class)
class UFortMcpProfileCreative : public UObject {}; // Used in RestoreDeletedIsland
class UFortKismetLibrary : public UObject {}; // Used in RemoveControllerComponent (static class)
class UControllerComponent : public UObject {}; // Used in RemoveControllerComponent
class UFortWorldMarker : public UObject {}; // Used in PlayerStateDestroyed
class UAthenaItemWrapDefinition : public UObject {}; // Used in SetWrap

// Specific Player Controllers (inherit from APlayerController)
class AFortPlayerController : public APlayerController {};
class AAthena_PlayerController_C : public AFortPlayerController {}; // Based on Athena_PlayerController_functions.cpp
class AFortPlayerControllerZone : public AFortPlayerController {};
class AFortPlayerControllerAthena : public AFortPlayerController {};
class AFortPlayerControllerPvE : public AFortPlayerController {};
class AFortPlayerControllerOutpost : public AFortPlayerController {};

// Specific Pawns (inherit from APawn)
class AFortPlayerPawn : public APawn {};

// Specific Player States (inherit from APlayerState)
class AFortPlayerStateAthena : public APlayerState {};

// Cheat Managers (inherit from UCheatManager)
class UFortCheatManager : public UCheatManager {};
// (Need a UCheatManager if it's not in structs.h or other.h)
// For now, let's assume UCheatManager is a UObject or similar.
class UCheatManager : public UObject {}; // Add this if not present elsewhere

} // namespace SDK
```

-----

### 3\. `FortniteSDK.h` (Unified Header)

This header includes all necessary components for your SDK.

```cpp
#pragma once

// Include essential SDK files
#include "structs.h"                // Core Unreal Engine structures and global pointers
#include "other.h"                  // Additional math utilities and simple structs
#include "FortniteGame_classes.h"   // Minimal class definitions for referenced types
#include "FortniteGame_parameters.h"// Parameter structs for function calls

// Forward declarations for core Unreal Engine classes used in SDK functions
// These are often already in FortniteGame_classes.h but explicitly listed for clarity
struct UWorld;
struct AGameStateBase;
struct APlayerController;
struct APawn;
struct USoundBase;

namespace FortniteSDK : public FortniteSDK
{
    // --- SDK Initialization Functions ---

    /**
     * @brief Initializes the SDK by finding and setting global pointers.
     * This function must be called once at the start of your application
     * to enable all other SDK functionalities.
     * In a real implementation, this involves memory scanning or hooking.
     */
    void InitializeSDK();

    // --- Core Game Object Accessors ---

    /**
     * @brief Retrieves the main UWorld object.
     * @return Pointer to the UWorld object, or nullptr if not found/initialized.
     */
    UWorld* GetWorld();

    /**
     * @brief Retrieves the current AGameStateBase object from the UWorld.
     * @return Pointer to the AGameStateBase object, or nullptr if not found/initialized.
     */
    AGameStateBase* GetGameState();

    /**
     * @brief Retrieves the local player's APlayerController object.
     * @return Pointer to the APlayerController object, or nullptr if not found/initialized.
     */
    APlayerController* GetLocalPlayerController();

    /**
     * @brief Retrieves the local player's APawn object (the character they control).
     * @return Pointer to the APawn object, or nullptr if not found/initialized.
     */
    APawn* GetLocalPlayerPawn();

    // --- Unified Fortnite Game Functions (Prototypes) ---
    // These are actual game functions that you can call.
    // Their implementations will be in FortniteSDK.cpp

    // From Athena_PlayerController_functions.cpp
    void AAthena_PlayerController_C_PawnPossessedDispatcher__DelegateSignature(class APawn* PossessedPawn);
    void AAthena_PlayerController_C_ExecuteUbergraph_Athena_PlayerController(int32 EntryPoint);
    void AAthena_PlayerController_C_OnMusicPackLoaded__DelegateSignature(class USoundBase* Music, float StartTime);
    void AAthena_PlayerController_C_ChangeMusic(class USoundBase* New_Music, float StartTime);
    void AAthena_PlayerController_C_FadeAudioComponents(class UAudioComponent* NewMusicComponent, class UAudioComponent* PreviousMusicComponent, class USoundBase* Music, float StartTime);

    // From FortniteGame_functions.cpp (subset, you can add more as needed)
    void AFortPlayerController_AddInventoryItemWithAlterationBasedOnLootLevel(AFortPlayerController* Obj, const struct FFortItemEntry& ItemDescription);
    void AFortPlayerController_AddInventoryItemWithAnimation(AFortPlayerController* Obj, const struct FFortItemEntry& ItemDescription);
    void AFortPlayerController_AddItemToQuickBars(AFortPlayerController* Obj, class UFortItemDefinition* ItemDefinition, EFortQuickBars QuickBarType, int32 SlotIndex);
    void AFortPlayerController_AlternateInteractCarryHoldStopped(AFortPlayerController* Obj, class FName InputActionName, bool bCompletedSuccessfully);
    bool AFortPlayerController_AreActionsBoundToSameKey(AFortPlayerController* Obj, class FName FirstActionName, class FName SecondActionName, const EInputEvent InputEvent);
    void AFortPlayerController_BP_FindItemInstancesFromDefinition(AFortPlayerController* Obj, const class UFortItemDefinition* ItemDefinition, TArray<class UFortItem*>& ItemArray);
    void AFortPlayerController_ChangeActiveVariantForCosmeticItem(AFortPlayerController* Obj, class FName ItemTemplateToChange, const struct FGameplayTag& VariantChannelToChange, const struct FGameplayTag& DesiredActiveVariant, class AFortPlayerPawn* PreviewPawn);
    void AFortPlayerController_Cheat(AFortPlayerController* Obj, const class FString& Msg);
    void AFortPlayerController_Cheat_ClearForcedCosmeticItems(AFortPlayerController* Obj);
    void AFortPlayerController_Cheat_ClearForcedCosmeticVariantChannels(AFortPlayerController* Obj);
    void AFortPlayerController_Cheat_ForceAthenaCosmeticItemInSlot(AFortPlayerController* Obj, class UAthenaCosmeticItemDefinition* CosmeticItem, EAthenaCustomizationCategory Slot, int32 Param_Index);
    void AFortPlayerController_Cheat_ForceCosmeticVariantChannels(AFortPlayerController* Obj, const TArray<struct FMcpVariantChannelInfo>& CosmeticVariantChannels);
    void AFortPlayerController_Cheat_ForcePlayEmoteItem(AFortPlayerController* Obj, const class UFortMontageItemDefinitionBase* EmoteAsset);
    void AFortPlayerController_Cheat_StopObjectiveServer(AFortPlayerController* Obj, class AFortObjectiveBase* Objective, const EFortObjectiveStatus Status);
    void AFortPlayerController_CheatAll(AFortPlayerController* Obj, const class FString& Msg);
    bool AFortPlayerController_CheckPossessionOfAmountOfItems(AFortPlayerController* Obj, EFortItemType Type, int32 AmountToCheck);
    void AFortPlayerController_ClientActivateSlot(AFortPlayerController* Obj, EFortQuickBars InQuickBar, int32 Slot, float ActivateDelay, bool bUpdatePreviousFocusedSlot, bool bForceExecution);
    void AFortPlayerController_ClientAddScoreNumber(AFortPlayerController* Obj, int32 Score, EStatCategory ScoreCategory, const struct FVector_NetQuantize& ScoreLocation, bool bDisplayScoreOnPlayer);
    void AFortPlayerController_ClientBotEnqueueCommand(AFortPlayerController* Obj, const class FString& CommandToEnqueue);
    void AFortPlayerController_ClientBotSetModuleToUse(AFortPlayerController* Obj, const class FString& PilotCategory, const class FString& NewModule, bool bResetNow);
    void AFortPlayerController_ClientCancelCrafting(AFortPlayerController* Obj);
    void AFortPlayerController_ClientConfirmTargetData(AFortPlayerController* Obj, uint16 UniqueId, bool bSuccess, const TArray<uint8>& HitReplaces);
    void AFortPlayerController_ClientCreateOrJoinChatRoom(AFortPlayerController* Obj, const class FString& ChatRoomId);
    void AFortPlayerController_ClientDeveloper_GetConsoleVariable(AFortPlayerController* Obj, const class FString& ConsoleVariable, const class FString& Value);
    void AFortPlayerController_ClientEndGameKick(AFortPlayerController* Obj);
    void AFortPlayerController_ClientEquipItem(AFortPlayerController* Obj, const struct FGuid& ItemGuid, bool bForceExecution);
    void AFortPlayerController_ClientExecuteInventoryItem(AFortPlayerController* Obj, const struct FGuid& ItemGuid, float Delay, bool bForceExecute, bool bActivateSlotAfterSettingFocused);
    void AFortPlayerController_ClientFailedToBeginEditingBuildingActor(AFortPlayerController* Obj, class ABuildingSMActor* BuildingActorToStopEditing);
    void AFortPlayerController_ClientFinishedInteractionInZone(AFortPlayerController* Obj);
    void AFortPlayerController_HandleOutpostInventoryLocalUpdate(AFortPlayerController* Obj);
    void AFortPlayerController_HandleViewTargetInventoryLocalUpdate(AFortPlayerController* Obj);
    void AFortPlayerController_PrintEventInfo(AFortPlayerController* Obj);
    void AFortPlayerController_ProcessMcpProfileUpdate(AFortPlayerController* Obj, const struct FProfileUpdateSingle& Update);
    bool AFortPlayerController_HasPermissionToEditWorld(AFortPlayerController* Obj, class ABuildingActor* Building, const struct FVector& Location, const struct FRotator& Rotation);
    bool AFortPlayerController_IsActionInputIgnored(AFortPlayerController* Obj);

    bool UFortCheatManager_ShouldUseNewHeroLoadoutUI(class APlayerController* PC); // Static function
    void UFortCheatManager_Crucible_SetWhitelisted(class UFortCheatManager* Obj, EFortCrucibleWhitelistLevel WhitelistLevel);
    void UFortCheatManager_CycleCurrentEncounterToDebug(class UFortCheatManager* Obj);
    void UFortCheatManager_CycleDebugAbilitySystem(class UFortCheatManager* Obj);
    void UFortCheatManager_CycleEncounterEQSQueryToDebug(class UFortCheatManager* Obj);
    void UFortCheatManager_CycleTheaterDisplayed(class UFortCheatManager* Obj);
    void UFortCheatManager_DBNO(class UFortCheatManager* Obj);
    void UFortCheatManager_McpJoinFromPartyInviteToken(class UFortCheatManager* Obj, const class FString& Token, bool bIsFromInvite);
    void UFortCheatManager_McpLogout(class UFortCheatManager* Obj);
    void UFortCheatManager_ReRandomizeTiles(class UFortCheatManager* Obj);
    void UFortCheatManager_ResetEncounterWave(class UFortCheatManager* Obj);
    void UFortCheatManager_StartMinigame(class UFortCheatManager* Obj);
    void UFortCheatManager_StartWeatherEvent(class UFortCheatManager* Obj, int32 WeatherEventIndex, float Intensity, float Duration);
    void UFortCheatManager_UnlockDebugCamera(class UFortCheatManager* Obj);

    void AARDronePawn_ScaleOut(class AARDronePawn* Obj);
    void AARDronePawn_StopScaling(class AARDronePawn* Obj);

    void UAthenaEmojiItemDefinition_ConfigureParticleSystem(class UAthenaEmojiItemDefinition* Obj);

    bool ABuildingFoundation_EditorOnlyUnloadPreviewLevel(class ABuildingFoundation* Obj);
    void ABuildingFoundation_OnLevelShown(class ABuildingFoundation* Obj);

    void UFortCharacterAttrSet_OnRep_Resistance(class UFortCharacterAttrSet* Obj, const struct FFortGameplayAttributeData& OldValue);
    void UFortCharacterAttrSet_OnRep_Tech(class UFortCharacterAttrSet* Obj, const struct FFortGameplayAttributeData& OldValue);

    void AFortPlayerControllerZone_PopDeathInputComponent(class AFortPlayerControllerZone* Obj);
    void AFortPlayerControllerZone_PushDeathInputComponent(class AFortPlayerControllerZone* Obj);
    void AFortPlayerControllerZone_ResetExecuteJetpackToggle(class AFortPlayerControllerZone* Obj);
    void AFortPlayerControllerZone_RespawnPlayer(class AFortPlayerControllerZone* Obj);

    bool ABuildingPhoenixRepairActor_GetWeaponHasDurability(class ABuildingPhoenixRepairActor* Obj, class UFortWorldItem* WeaponItem);
    void ABuildingPhoenixRepairActor_GetWeaponRepairRecipe(class ABuildingPhoenixRepairActor* Obj, class AFortPlayerController* FPC, struct FRecipe* OutRecipe);

    void AFortPlayerControllerAthena_ClientStartRespawnPreparation(class AFortPlayerControllerAthena* Obj, const struct FVector& RespawnLoc, const struct FRotator& RespawnRot, float RespawnCameraDist, ERespawnCameraBehavior InRespawnCameraBehavior, const class FText& HUDReasonText);
    void AFortPlayerControllerAthena_ClientStartWaitLTMLoading(class AFortPlayerControllerAthena* Obj);
    void AFortPlayerControllerAthena_PlayWinEffects(class AFortPlayerControllerAthena* Obj, class APawn* FinisherPawn, const class UFortWeaponItemDefinition* FinishingWeapon, EDeathCause DeathCause, bool bAudioOnly);
    void AFortPlayerControllerAthena_PostLobbyIslandTeleport(class AFortPlayerControllerAthena* Obj, class AFortPlayerPawn* PlayerPawn);

    TArray<TSoftObjectPtr<class UObject>> UFortniteAutomationBlueprintLibrary_GetWrapPreviewObjects(ESubGame SubGame); // Static function
    struct FFortAthenaLoadout UFortniteAutomationBlueprintLibrary_MakeLoadoutFromVariantChannelInfos(const TArray<struct FMcpVariantChannelInfo>& VariantInfo); // Static function

    EDadBroHealthType IDadBroHealthInterface_GetCurrentHealthType(class IDadBroHealthInterface* Obj); // Interface call
    void UDeathEffectsPawnComponent_ClientPlayWinnerDeathEffects(class UDeathEffectsPawnComponent* Obj);
    bool UFortAccountBuffItem_IsActive(class UFortAccountBuffItem* Obj);
    class AFortPlayerController* UObjectInteractionBehavior_GetFortPlayerController(class UObjectInteractionBehavior* Obj);
    void UDeleteObjects_GetDeleteActorsMeshComponents(TArray<class UMeshComponent*>& Components); // Static function
    TArray<class FText> AFortAthenaMutator_TODOverride_GetTimeOfDaySpeedNames(class AFortAthenaMutator_TODOverride* Obj);
    bool AFortInGameMapManager_GetStaticCaptureSetupComplete(class AFortInGameMapManager* Obj);
    void AFortInGameMapManager_OnRep_ClearAllFog(class AFortInGameMapManager* Obj);
    void AFortPlayerControllerPvE_ResetPlayerDeathReportForForcePlayerRestart(class AFortPlayerControllerPvE* Obj);
    void AFortPlayerControllerPvE_ServerTriggerSetupTeleportCameraEvent(class AFortPlayerControllerPvE* Obj);
    void AFortPlayerControllerPvE_ServerUpdateQuickBarRecordsCache(class AFortPlayerControllerPvE* Obj, const struct FQuickBar& PrimaryQuickBarRecord, const struct FQuickBar& SecondaryQuickBarRecord);

    void UFortHealthSet_OnRep_MaxHealth(class UFortHealthSet* Obj, const struct FFortGameplayAttributeData& OldValue);
    void AFortPlayerPawn_ClientNotifyAbilityFailed(class AFortPlayerPawn* Obj, const class UGameplayAbility* FailedAbility, const struct FGameplayTagContainer& FailedReason);

    void UFortCheatManager_Affiliation_Affiliation_ResetMemberRelations(); // Static function
    void UFortCheatManager_Quests_CompleteAllQuestsByName(class FString& QuestPartialName); // Static function
    void UFortCheatManagerSTW_SetWorldLevel(float Level); // Static function
    void UFortCheatManagerSTW_TestOutpostUI(); // Static function

    void UFortMcpProfileCreative_RestoreDeletedIsland(class UFortMcpProfileCreative* Obj, const class FString& PlotItemId, struct FDedicatedServerUrlContext* Context);
    void UFortKismetLibrary_RemoveControllerComponent(class AController* Controller, TSubclassOf<class UControllerComponent> ControllerCompClass); // Static function

    bool AFortMinigame_OverridePlayerSpawnLocation(class AFortMinigame* Obj, class APawn* PlayerPawn, class AFortPlayerStateAthena* PlayerState, struct FVector* OutLocation, struct FRotator* OutRotation, bool* bOutRespawningOnGround);
    void AFortPlayerControllerOutpost_DumpInventory(class AFortPlayerControllerOutpost* Obj);
    void AFortPlayerControllerOutpost_LeaveOutpostAsParty(class AFortPlayerControllerOutpost* Obj);

    void UFortWorldMarker_PlayerStateDestroyed(class UFortWorldMarker* Obj, class AActor* DestroyedActor);
    void AThreatCloud_OnCloudHiddenChange(class AThreatCloud* Obj, bool bCloudsAreHidden);
    void AThreatCloud_OnCloudStart(class AThreatCloud* Obj);
    void AThreatCloud_OnLightningStrike(class AThreatCloud* Obj, const struct FVector& StartLocation, const struct FVector& EndLocation);

    class AWorldMapPin* AWorldMapPinManager_CreateWorldMapPin(class AWorldMapPinManager* Obj, const class FString& TheaterId); // Static function
    void AWrapPreviewGridActor_SetWrap(class AWrapPreviewGridActor* Obj, class UAthenaItemWrapDefinition* NewWrap);

} // namespace FortniteSDK
```

-----

### 4\. `FortniteSDK.cpp` (Unified Source)

This file contains the implementation of all the functions, including your SDK initialization and the game functions.

```cpp
#include "FortniteSDK.h"
#include <iostream>
#include <vector>
#include <string>

// Global pointers from structs.h. These need to be populated by the actual game's memory addresses.
// In a real scenario, these would be found via signature scanning or other memory analysis.
// We'll assume they are populated externally or through a placeholder 'Setup' function.
// For demonstration, we'll assign dummy values or nullptr and add comments.

namespace FortniteSDK
{
    // Make sure these are the *actual* global pointers or use the ones from structs.h directly.
    // For this example, we'll assign them. In a real scenario, ObjObjects, OldObjects, ProcessEventO, etc.
    // from structs.h would be the targets of your initialization.
    // Ensure that 'structs.h' definitions are properly linked to these external symbols.

    // If structs.h declares these as `static inline` then they are local to each compilation unit.
    // To make them truly global and assignable from InitializeSDK, they should be declared as `extern` in structs.h
    // and then defined *once* in a .cpp file (like this one).
    // For now, we'll use a local copy and assume structs.h will pick these up or be modified.

    // For simplicity and assuming structs.h already makes these accessible:
    // FChunkedFixedUObjectArray* GObjects = nullptr;
    // FFixedUObjectArray* GObjectsOld = nullptr;
    // static inline void (*GToStringO)(struct FName*, class FString*) = nullptr; // Renamed to avoid collision if structs.h has same name
    // static inline void* (*GProcessEventO)(void*, void*, void*) = nullptr; // Renamed
    // UObject* (*GStaticFindObjectO)(UObject* Class, UObject* InOuter, const TCHAR* Name, bool ExactClass) = nullptr;
    // UObject* (*GStaticLoadObjectO)(UObject* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32_t LoadFlags, UObject* Sandbox, bool bAllowObjectReconciliation, void* InSerializeContext) = nullptr;
    // namespace GMemory { void (*Free)(void* Original) = nullptr; void* (*Realloc)(void* Original, SIZE_T Count, uint32_t Alignment) = nullptr; }

    /**
     * @brief Initializes the SDK by finding and setting global pointers.
     * In a real application, this would involve memory scanning or
     * loading function addresses from the game process.
     * For this example, it serves as a placeholder for where that
     * initialization logic would go.
     */
    void InitializeSDK()
    {
        std::cout << "FortniteSDK::InitializeSDK() called.\n";

        // --- IMPORTANT: PLACE YOUR MEMORY SCANNING/HOOKING LOGIC HERE ---
        // This is where you would find the actual addresses of the global
        // Unreal Engine objects and functions in the game's memory.

        // Example:
        // ObjObjects = reinterpret_cast<FChunkedFixedUObjectArray*>(FindPattern("YOUR_GOBJECTS_PATTERN"));
        // OldObjects = reinterpret_cast<FFixedUObjectArray*>(FindPattern("YOUR_GOBJECTS_OLD_PATTERN"));
        // ::ToStringO = reinterpret_cast<decltype(::ToStringO)>(FindPattern("YOUR_TOSTRINGO_PATTERN"));
        // ::ProcessEventO = reinterpret_cast<decltype(::ProcessEventO)>(FindPattern("YOUR_PROCESSEVENTO_PATTERN"));
        // ::StaticFindObjectO = reinterpret_cast<decltype(::StaticFindObjectO)>(FindPattern("YOUR_STATICFINDOBJECTO_PATTERN"));
        // ::StaticLoadObjectO = reinterpret_cast<decltype(::StaticLoadObjectO)>(FindPattern("YOUR_STATICLOADOBJECTO_PATTERN"));
        // FMemory::Free = reinterpret_cast<decltype(FMemory::Free)>(FindPattern("YOUR_FMEMORY_FREE_PATTERN"));
        // FMemory::Realloc = reinterpret_cast<decltype(FMemory::Realloc)>(FindPattern("YOUR_FMEMORY_REALLOC_PATTERN"));

        // For demonstration, we'll assume they are found (set to non-null for function calls to pass checks).
        // In a real scenario, if these are not found, the SDK functions will likely crash or fail.
        ObjObjects = reinterpret_cast<FChunkedFixedUObjectArray*>(0x1); // Dummy address
        OldObjects = reinterpret_cast<FFixedUObjectArray*>(0x2);   // Dummy address
        ::ToStringO = reinterpret_cast<decltype(::ToStringO)>(0x3);      // Dummy address
        ::ProcessEventO = reinterpret_cast<decltype(::ProcessEventO)>(0x4); // Dummy address
        ::StaticFindObjectO = reinterpret_cast<decltype(::StaticFindObjectO)>(0x5); // Dummy address
        ::StaticLoadObjectO = reinterpret_cast<decltype(::StaticLoadObjectO)>(0x6); // Dummy address
        FMemory::Free = reinterpret_cast<decltype(FMemory::Free)>(0x7); // Dummy address
        FMemory::Realloc = reinterpret_cast<decltype(FMemory::Realloc)>(0x8); // Dummy address


        if (ObjObjects) {
            std::cout << "GObjects array initialized (or placeholder).\n";
        } else {
            std::cout << "[WARNING] GObjects array not found/initialized. Object lookups may fail.\n";
        }

        if (::ProcessEventO) {
            std::cout << "ProcessEvent hooked/initialized.\n";
        } else {
            std::cout << "[WARNING] ProcessEvent not found/initialized. UObject function calls may fail.\n";
        }

        std::cout << "FortniteSDK initialization complete (placeholder).\n";
    }

    // --- Core Game Object Accessors ---
    // These functions need a valid GObjects and StaticFindObjectO to work.

    UWorld* GetWorld()
    {
        if (!::StaticFindObjectO)
        {
            std::cerr << "[ERROR] StaticFindObjectO is not initialized! Cannot get UWorld.\n";
            return nullptr;
        }

        // Common paths for UWorld. Actual path may vary by game version.
        UObject* WorldObj = StaticFindObject(std::string("World /Game/Maps/UEDPIE_0_Frontend.Frontend:PersistentLevel.World"));
        if (!WorldObj) WorldObj = StaticFindObject(std::string("World /Game/Maps/UEDPIE_0_FortniteLobby.FortniteLobby:PersistentLevel.World"));
        if (!WorldObj) WorldObj = StaticFindObject(std::string("World /Game/Maps/UEDPIE_0_World.World")); // Generic fallback

        // If StaticFindObject fails, try iterating GObjects as a last resort.
        if (!WorldObj && ObjObjects) {
            for (int i = 0; i < ObjObjects->Num(); ++i) {
                UObject* CurrentObj = ObjObjects->GetObjectById(i);
                if (CurrentObj && CurrentObj->ClassPrivate && CurrentObj->ClassPrivate->GetName() == "World") {
                    std::cout << "Found UWorld by iterating GObjects: " << CurrentObj->GetFullName() << std::endl;
                    return reinterpret_cast<UWorld*>(CurrentObj);
                }
            }
        }
        if (!WorldObj) std::cerr << "[ERROR] UWorld object not found.\n";
        return reinterpret_cast<UWorld*>(WorldObj);
    }

    AGameStateBase* GetGameState()
    {
        UWorld* World = GetWorld();
        if (!World) { std::cerr << "[ERROR] Cannot get GameState: UWorld not found.\n"; return nullptr; }

        if (!::StaticFindObjectO)
        {
            std::cerr << "[ERROR] StaticFindObjectO is not initialized! Cannot get GameState.\n";
            return nullptr;
        }

        // Common paths for GameState.
        UObject* GameStateObj = StaticFindObject(std::string("GameState /Game/Athena/Athena_GameState.Athena_GameState_C"));
        if (!GameStateObj) GameStateObj = StaticFindObject(std::string("FortGameStateAthena_C")); // More generic

        if (!GameStateObj && ObjObjects) {
            for (int i = 0; i < ObjObjects->Num(); ++i) {
                UObject* CurrentObj = ObjObjects->GetObjectById(i);
                if (CurrentObj && CurrentObj->ClassPrivate && CurrentObj->ClassPrivate->GetName().find("GameState") != std::string::npos) {
                    std::cout << "Found GameState by iterating GObjects: " << CurrentObj->GetFullName() << std::endl;
                    return reinterpret_cast<AGameStateBase*>(CurrentObj);
                }
            }
        }
        if (!GameStateObj) std::cerr << "[ERROR] AGameStateBase object not found.\n";
        return reinterpret_cast<AGameStateBase*>(GameStateObj);
    }

    APlayerController* GetLocalPlayerController()
    {
        UWorld* World = GetWorld();
        if (!World) { std::cerr << "[ERROR] Cannot get PlayerController: UWorld not found.\n"; return nullptr; }

        if (!::StaticFindObjectO)
        {
            std::cerr << "[ERROR] StaticFindObjectO is not initialized! Cannot get PlayerController.\n";
            return nullptr;
        }

        // Try to find the specific Athena Player Controller class first
        UObject* AthenaPCClass = StaticFindObject(std::string("Class Athena_PlayerController.Athena_PlayerController_C"));

        APlayerController* PlayerControllerObj = nullptr;
        if (ObjObjects) {
            for (int i = 0; i < ObjObjects->Num(); ++i) {
                UObject* CurrentObj = ObjObjects->GetObjectById(i);
                if (CurrentObj && CurrentObj->ClassPrivate && CurrentObj->ClassPrivate->GetName().find("PlayerController") != std::string::npos) {
                    // This is a simplification. In a real game, you'd check if it's the local player's controller.
                    // This often involves checking UWorld->OwningGameInstance->LocalPlayers[0]->PlayerController
                    std::cout << "Found PlayerController candidate by iterating GObjects: " << CurrentObj->GetFullName() << std::endl;
                    return reinterpret_cast<APlayerController*>(CurrentObj);
                }
            }
        }
        if (!PlayerControllerObj) std::cerr << "[ERROR] APlayerController object not found.\n";
        return PlayerControllerObj;
    }

    APawn* GetLocalPlayerPawn()
    {
        APlayerController* PlayerController = GetLocalPlayerController();
        if (!PlayerController) { std::cerr << "[ERROR] Cannot get Pawn: PlayerController not found.\n"; return nullptr; }

        // This is a placeholder. You would need the actual offset of the Pawn property
        // within the APlayerController class structure to do this reliably.
        // For example: return PlayerController->AcknowledgedPawn; if APlayerController had that member defined.

        if (!::StaticFindObjectO)
        {
            std::cerr << "[ERROR] StaticFindObjectO is not initialized! Cannot get Pawn.\n";
            return nullptr;
        }

        UObject* PawnObj = StaticFindObject(std::string("PlayerPawn_Generic_C")); // Common placeholder

        if (!PawnObj && ObjObjects) {
            for (int i = 0; i < ObjObjects->Num(); ++i) {
                UObject* CurrentObj = ObjObjects->GetObjectById(i);
                if (CurrentObj && CurrentObj->ClassPrivate) {
                    std::string ClassName = CurrentObj->ClassPrivate->GetName();
                    if (ClassName.find("Pawn") != std::string::npos && ClassName.find("PlayerPawn") != std::string::npos) {
                        std::cout << "Found Pawn candidate by iterating GObjects: " << CurrentObj->GetFullName() << std::endl;
                        return reinterpret_cast<APawn*>(CurrentObj);
                    }
                }
            }
        }
        if (!PawnObj) std::cerr << "[ERROR] APawn object not found.\n";
        return reinterpret_cast<APawn*>(PawnObj);
    }

    // --- Unified Fortnite Game Functions (Implementations) ---

    // From Athena_PlayerController_functions.cpp
    void AAthena_PlayerController_C_PawnPossessedDispatcher__DelegateSignature(class APawn* PossessedPawn)
    {
        // This is a delegate signature, typically not called directly like this.
        // It's here for completeness as it was in the original file.
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = AAthena_PlayerController_C::StaticClass()->GetFunction("Athena_PlayerController_C", "PawnPossessedDispatcher__DelegateSignature");
        
        SDK::Params::Athena_PlayerController_C_PawnPossessedDispatcher__DelegateSignature_Params Parms{};
        Parms.PossessedPawn = PossessedPawn;
        UObject::ProcessEvent(Func, &Parms);
    }

    void AAthena_PlayerController_C_ExecuteUbergraph_Athena_PlayerController(int32 EntryPoint)
    {
        // Ubergraph functions are internal to blueprints, usually not called directly from external SDK.
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = AAthena_PlayerController_C::StaticClass()->GetFunction("Athena_PlayerController_C", "ExecuteUbergraph_Athena_PlayerController");
        
        SDK::Params::Athena_PlayerController_C_ExecuteUbergraph_Athena_PlayerController_Params Parms{};
        Parms.EntryPoint = EntryPoint;
        UObject::ProcessEvent(Func, &Parms);
    }

    void AAthena_PlayerController_C_OnMusicPackLoaded__DelegateSignature(class USoundBase* Music, float StartTime)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = AAthena_PlayerController_C::StaticClass()->GetFunction("Athena_PlayerController_C", "OnMusicPackLoaded__DelegateSignature");
        
        SDK::Params::Athena_PlayerController_C_OnMusicPackLoaded__DelegateSignature_Params Parms{};
        Parms.Music = Music;
        Parms.StartTime = StartTime;
        UObject::ProcessEvent(Func, &Parms);
    }

    void AAthena_PlayerController_C_ChangeMusic(class USoundBase* New_Music, float StartTime)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = AAthena_PlayerController_C::StaticClass()->GetFunction("Athena_PlayerController_C", "ChangeMusic");
        
        SDK::Params::Athena_PlayerController_C_ChangeMusic_Params Parms{};
        Parms.New_Music = New_Music;
        Parms.StartTime = StartTime;
        UObject::ProcessEvent(Func, &Parms);
    }

    void AAthena_PlayerController_C_FadeAudioComponents(class UAudioComponent* NewMusicComponent, class UAudioComponent* PreviousMusicComponent, class USoundBase* Music, float StartTime)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = AAthena_PlayerController_C::StaticClass()->GetFunction("Athena_PlayerController_C", "FadeAudioComponents");
        
        SDK::Params::Athena_PlayerController_C_FadeAudioComponents_Params Parms{};
        Parms.NewMusicComponent = NewMusicComponent;
        Parms.PreviousMusicComponent = PreviousMusicComponent;
        Parms.Music = Music;
        Parms.StartTime = StartTime;
        UObject::ProcessEvent(Func, &Parms);
    }

    // From FortniteGame_functions.cpp
    void AFortPlayerController_AddInventoryItemWithAlterationBasedOnLootLevel(AFortPlayerController* Obj, const struct FFortItemEntry& ItemDescription)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "AddInventoryItemWithAlterationBasedOnLootLevel");
        
        SDK::Params::FortPlayerController_AddInventoryItemWithAlterationBasedOnLootLevel_Params Parms{};
        Parms.ItemDescription = ItemDescription;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_AddInventoryItemWithAnimation(AFortPlayerController* Obj, const struct FFortItemEntry& ItemDescription)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "AddInventoryItemWithAnimation");
        
        SDK::Params::FortPlayerController_AddInventoryItemWithAnimation_Params Parms{};
        Parms.ItemDescription = ItemDescription;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_AddItemToQuickBars(AFortPlayerController* Obj, class UFortItemDefinition* ItemDefinition, EFortQuickBars QuickBarType, int32 SlotIndex)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "AddItemToQuickBars");
        
        SDK::Params::FortPlayerController_AddItemToQuickBars_Params Parms{};
        Parms.ItemDefinition = ItemDefinition;
        Parms.QuickBarType = QuickBarType;
        Parms.SlotIndex = SlotIndex;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_AlternateInteractCarryHoldStopped(AFortPlayerController* Obj, class FName InputActionName, bool bCompletedSuccessfully)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "AlternateInteractCarryHoldStopped");
        
        SDK::Params::FortPlayerController_AlternateInteractCarryHoldStopped_Params Parms{};
        Parms.InputActionName = InputActionName;
        Parms.bCompletedSuccessfully = bCompletedSuccessfully;
        Obj->ProcessEvent(Func, &Parms);
    }

    bool AFortPlayerController_AreActionsBoundToSameKey(AFortPlayerController* Obj, class FName FirstActionName, class FName SecondActionName, const EInputEvent InputEvent)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "AreActionsBoundToSameKey");
        
        SDK::Params::FortPlayerController_AreActionsBoundToSameKey_Params Parms{};
        Parms.FirstActionName = FirstActionName;
        Parms.SecondActionName = SecondActionName;
        Parms.InputEvent = InputEvent;
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    void AFortPlayerController_BP_FindItemInstancesFromDefinition(AFortPlayerController* Obj, const class UFortItemDefinition* ItemDefinition, TArray<class UFortItem*>& ItemArray)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "BP_FindItemInstancesFromDefinition");
        
        SDK::Params::FortPlayerController_BP_FindItemInstancesFromDefinition_Params Parms{};
        Parms.ItemDefinition = ItemDefinition;
        Parms.ItemArray = ItemArray;
        Obj->ProcessEvent(Func, &Parms);
        ItemArray = Parms.ItemArray;
    }

    void AFortPlayerController_ChangeActiveVariantForCosmeticItem(AFortPlayerController* Obj, class FName ItemTemplateToChange, const struct FGameplayTag& VariantChannelToChange, const struct FGameplayTag& DesiredActiveVariant, class AFortPlayerPawn* PreviewPawn)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ChangeActiveVariantForCosmeticItem");
        
        SDK::Params::FortPlayerController_ChangeActiveVariantForCosmeticItem_Params Parms{};
        Parms.ItemTemplateToChange = ItemTemplateToChange;
        Parms.VariantChannelToChange = VariantChannelToChange;
        Parms.DesiredActiveVariant = DesiredActiveVariant;
        Parms.PreviewPawn = PreviewPawn;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_Cheat(AFortPlayerController* Obj, const class FString& Msg)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "Cheat");
        
        SDK::Params::FortPlayerController_Cheat_Params Parms{};
        Parms.Msg = Msg;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_Cheat_ClearForcedCosmeticItems(AFortPlayerController* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "Cheat_ClearForcedCosmeticItems");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerController_Cheat_ClearForcedCosmeticVariantChannels(AFortPlayerController* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "Cheat_ClearForcedCosmeticVariantChannels");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerController_Cheat_ForceAthenaCosmeticItemInSlot(AFortPlayerController* Obj, class UAthenaCosmeticItemDefinition* CosmeticItem, EAthenaCustomizationCategory Slot, int32 Param_Index)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "Cheat_ForceAthenaCosmeticItemInSlot");
        
        SDK::Params::FortPlayerController_Cheat_ForceAthenaCosmeticItemInSlot_Params Parms{};
        Parms.CosmeticItem = CosmeticItem;
        Parms.Slot = Slot;
        Parms.Param_Index = Param_Index;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_Cheat_ForceCosmeticVariantChannels(AFortPlayerController* Obj, const TArray<struct FMcpVariantChannelInfo>& CosmeticVariantChannels)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "Cheat_ForceCosmeticVariantChannels");
        
        SDK::Params::FortPlayerController_Cheat_ForceCosmeticVariantChannels_Params Parms{};
        Parms.CosmeticVariantChannels = CosmeticVariantChannels;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_Cheat_ForcePlayEmoteItem(AFortPlayerController* Obj, const class UFortMontageItemDefinitionBase* EmoteAsset)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "Cheat_ForcePlayEmoteItem");
        
        SDK::Params::FortPlayerController_Cheat_ForcePlayEmoteItem_Params Parms{};
        Parms.EmoteAsset = EmoteAsset;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_Cheat_StopObjectiveServer(AFortPlayerController* Obj, class AFortObjectiveBase* Objective, const EFortObjectiveStatus Status)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "Cheat_StopObjectiveServer");
        
        SDK::Params::FortPlayerController_Cheat_StopObjectiveServer_Params Parms{};
        Parms.Objective = Objective;
        Parms.Status = Status;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_CheatAll(AFortPlayerController* Obj, const class FString& Msg)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "CheatAll");
        
        SDK::Params::FortPlayerController_CheatAll_Params Parms{};
        Parms.Msg = Msg;
        Obj->ProcessEvent(Func, &Parms);
    }

    bool AFortPlayerController_CheckPossessionOfAmountOfItems(AFortPlayerController* Obj, EFortItemType Type, int32 AmountToCheck)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "CheckPossessionOfAmountOfItems");
        
        SDK::Params::FortPlayerController_CheckPossessionOfAmountOfItems_Params Parms{};
        Parms.Type = Type;
        Parms.AmountToCheck = AmountToCheck;
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    void AFortPlayerController_ClientActivateSlot(AFortPlayerController* Obj, EFortQuickBars InQuickBar, int32 Slot, float ActivateDelay, bool bUpdatePreviousFocusedSlot, bool bForceExecution)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientActivateSlot");
        
        SDK::Params::FortPlayerController_ClientActivateSlot_Params Parms{};
        Parms.InQuickBar = InQuickBar;
        Parms.Slot = Slot;
        Parms.ActivateDelay = ActivateDelay;
        Parms.bUpdatePreviousFocusedSlot = bUpdatePreviousFocusedSlot;
        Parms.bForceExecution = bForceExecution;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_ClientAddScoreNumber(AFortPlayerController* Obj, int32 Score, EStatCategory ScoreCategory, const struct FVector_NetQuantize& ScoreLocation, bool bDisplayScoreOnPlayer)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientAddScoreNumber");
        
        SDK::Params::FortPlayerController_ClientAddScoreNumber_Params Parms{};
        Parms.Score = Score;
        Parms.ScoreCategory = ScoreCategory;
        Parms.ScoreLocation = ScoreLocation;
        Parms.bDisplayScoreOnPlayer = bDisplayScoreOnPlayer;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_ClientBotEnqueueCommand(AFortPlayerController* Obj, const class FString& CommandToEnqueue)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientBotEnqueueCommand");
        
        SDK::Params::FortPlayerController_ClientBotEnqueueCommand_Params Parms{};
        Parms.CommandToEnqueue = CommandToEnqueue;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_ClientBotSetModuleToUse(AFortPlayerController* Obj, const class FString& PilotCategory, const class FString& NewModule, bool bResetNow)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientBotSetModuleToUse");
        
        SDK::Params::FortPlayerController_ClientBotSetModuleToUse_Params Parms{};
        Parms.PilotCategory = PilotCategory;
        Parms.NewModule = NewModule;
        Parms.bResetNow = bResetNow;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_ClientCancelCrafting(AFortPlayerController* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientCancelCrafting");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerController_ClientConfirmTargetData(AFortPlayerController* Obj, uint16 UniqueId, bool bSuccess, const TArray<uint8>& HitReplaces)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientConfirmTargetData");
        
        SDK::Params::FortPlayerController_ClientConfirmTargetData_Params Parms{};
        Parms.UniqueId = UniqueId;
        Parms.bSuccess = bSuccess;
        Parms.HitReplaces = HitReplaces;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_ClientCreateOrJoinChatRoom(AFortPlayerController* Obj, const class FString& ChatRoomId)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientCreateOrJoinChatRoom");
        
        SDK::Params::FortPlayerController_ClientCreateOrJoinChatRoom_Params Parms{};
        Parms.ChatRoomId = ChatRoomId;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_ClientDeveloper_GetConsoleVariable(AFortPlayerController* Obj, const class FString& ConsoleVariable, const class FString& Value)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientDeveloper_GetConsoleVariable");
        
        SDK::Params::FortPlayerController_ClientDeveloper_GetConsoleVariable_Params Parms{};
        Parms.ConsoleVariable = ConsoleVariable;
        Parms.Value = Value;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_ClientEndGameKick(AFortPlayerController* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientEndGameKick");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerController_ClientEquipItem(AFortPlayerController* Obj, const struct FGuid& ItemGuid, bool bForceExecution)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientEquipItem");
        
        SDK::Params::FortPlayerController_ClientEquipItem_Params Parms{};
        Parms.ItemGuid = ItemGuid;
        Parms.bForceExecution = bForceExecution;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_ClientExecuteInventoryItem(AFortPlayerController* Obj, const struct FGuid& ItemGuid, float Delay, bool bForceExecute, bool bActivateSlotAfterSettingFocused)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientExecuteInventoryItem");
        
        SDK::Params::FortPlayerController_ClientExecuteInventoryItem_Params Parms{};
        Parms.ItemGuid = ItemGuid;
        Parms.Delay = Delay;
        Parms.bForceExecute = bForceExecute;
        Parms.bActivateSlotAfterSettingFocused = bActivateSlotAfterSettingFocused;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_ClientFailedToBeginEditingBuildingActor(AFortPlayerController* Obj, class ABuildingSMActor* BuildingActorToStopEditing)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientFailedToBeginEditingBuildingActor");
        
        SDK::Params::FortPlayerController_ClientFailedToBeginEditingBuildingActor_Params Parms{};
        Parms.BuildingActorToStopEditing = BuildingActorToStopEditing;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerController_ClientFinishedInteractionInZone(AFortPlayerController* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ClientFinishedInteractionInZone");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerController_HandleOutpostInventoryLocalUpdate(AFortPlayerController* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "HandleOutpostInventoryLocalUpdate");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerController_HandleViewTargetInventoryLocalUpdate(AFortPlayerController* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "HandleViewTargetInventoryLocalUpdate");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerController_PrintEventInfo(AFortPlayerController* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "PrintEventInfo");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerController_ProcessMcpProfileUpdate(AFortPlayerController* Obj, const struct FProfileUpdateSingle& Update)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "ProcessMcpProfileUpdate");
        
        SDK::Params::FortPlayerController_ProcessMcpProfileUpdate_Params Parms{};
        Parms.Update = Update;
        Obj->ProcessEvent(Func, &Parms);
    }

    bool AFortPlayerController_HasPermissionToEditWorld(AFortPlayerController* Obj, class ABuildingActor* Building, const struct FVector& Location, const struct FRotator& Rotation)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "HasPermissionToEditWorld");
        
        SDK::Params::FortPlayerController_HasPermissionToEditWorld_Params Parms{};
        Parms.Building = Building;
        Parms.Location = Location;
        Parms.Rotation = Rotation;
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    bool AFortPlayerController_IsActionInputIgnored(AFortPlayerController* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerController", "IsActionInputIgnored");
        
        SDK::Params::FortPlayerController_IsActionInputIgnored_Params Parms{};
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    bool UFortCheatManager_ShouldUseNewHeroLoadoutUI(class APlayerController* PC)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = SDK::UFortCheatManager::StaticClass()->GetFunction("FortCheatManager", "ShouldUseNewHeroLoadoutUI");
        
        SDK::Params::FortCheatManager_ShouldUseNewHeroLoadoutUI_Params Parms{};
        Parms.PC = PC;
        SDK::UFortCheatManager::GetDefaultObj()->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    void UFortCheatManager_Crucible_SetWhitelisted(class UFortCheatManager* Obj, EFortCrucibleWhitelistLevel WhitelistLevel)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "Crucible_SetWhitelisted");
        
        SDK::Params::FortCheatManager_Crucible_SetWhitelisted_Params Parms{};
        Parms.WhitelistLevel = WhitelistLevel;
        Obj->ProcessEvent(Func, &Parms);
    }

    void UFortCheatManager_CycleCurrentEncounterToDebug(class UFortCheatManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "CycleCurrentEncounterToDebug");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortCheatManager_CycleDebugAbilitySystem(class UFortCheatManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "CycleDebugAbilitySystem");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortCheatManager_CycleEncounterEQSQueryToDebug(class UFortCheatManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "CycleEncounterEQSQueryToDebug");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortCheatManager_CycleTheaterDisplayed(class UFortCheatManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "CycleTheaterDisplayed");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortCheatManager_DBNO(class UFortCheatManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "DBNO");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortCheatManager_McpJoinFromPartyInviteToken(class UFortCheatManager* Obj, const class FString& Token, bool bIsFromInvite)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "McpJoinFromPartyInviteToken");
        
        SDK::Params::FortCheatManager_McpJoinFromPartyInviteToken_Params Parms{};
        Parms.Token = Token;
        Parms.bIsFromInvite = bIsFromInvite;
        Obj->ProcessEvent(Func, &Parms);
    }

    void UFortCheatManager_McpLogout(class UFortCheatManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "McpLogout");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortCheatManager_ReRandomizeTiles(class UFortCheatManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "ReRandomizeTiles");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortCheatManager_ResetEncounterWave(class UFortCheatManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "ResetEncounterWave");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortCheatManager_StartMinigame(class UFortCheatManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "StartMinigame");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortCheatManager_StartWeatherEvent(class UFortCheatManager* Obj, int32 WeatherEventIndex, float Intensity, float Duration)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "StartWeatherEvent");
        
        SDK::Params::FortCheatManager_StartWeatherEvent_Params Parms{};
        Parms.WeatherEventIndex = WeatherEventIndex;
        Parms.Intensity = Intensity;
        Parms.Duration = Duration;
        Obj->ProcessEvent(Func, &Parms);
    }

    void UFortCheatManager_UnlockDebugCamera(class UFortCheatManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCheatManager", "UnlockDebugCamera");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AARDronePawn_ScaleOut(class AARDronePawn* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("ARDronePawn", "ScaleOut");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AARDronePawn_StopScaling(class AARDronePawn* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("ARDronePawn", "StopScaling");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UAthenaEmojiItemDefinition_ConfigureParticleSystem(class UAthenaEmojiItemDefinition* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("AthenaEmojiItemDefinition", "ConfigureParticleSystem");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    bool ABuildingFoundation_EditorOnlyUnloadPreviewLevel(class ABuildingFoundation* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("BuildingFoundation", "EditorOnlyUnloadPreviewLevel");
        
        SDK::Params::BuildingFoundation_EditorOnlyUnloadPreviewLevel_Params Parms{};
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    void ABuildingFoundation_OnLevelShown(class ABuildingFoundation* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("BuildingFoundation", "OnLevelShown");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortCharacterAttrSet_OnRep_Resistance(class UFortCharacterAttrSet* Obj, const struct FFortGameplayAttributeData& OldValue)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCharacterAttrSet", "OnRep_Resistance");
        
        SDK::Params::FortCharacterAttrSet_OnRep_Resistance_Params Parms{};
        Parms.OldValue = OldValue;
        Obj->ProcessEvent(Func, &Parms);
    }

    void UFortCharacterAttrSet_OnRep_Tech(class UFortCharacterAttrSet* Obj, const struct FFortGameplayAttributeData& OldValue)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortCharacterAttrSet", "OnRep_Tech");
        
        SDK::Params::FortCharacterAttrSet_OnRep_Tech_Params Parms{};
        Parms.OldValue = OldValue;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerControllerZone_PopDeathInputComponent(class AFortPlayerControllerZone* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerZone", "PopDeathInputComponent");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerControllerZone_PushDeathInputComponent(class AFortPlayerControllerZone* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerZone", "PushDeathInputComponent");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerControllerZone_ResetExecuteJetpackToggle(class AFortPlayerControllerZone* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerZone", "ResetExecuteJetpackToggle");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerControllerZone_RespawnPlayer(class AFortPlayerControllerZone* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerZone", "RespawnPlayer");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    bool ABuildingPhoenixRepairActor_GetWeaponHasDurability(class ABuildingPhoenixRepairActor* Obj, class UFortWorldItem* WeaponItem)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("BuildingPhoenixRepairActor", "GetWeaponHasDurability");
        
        SDK::Params::BuildingPhoenixRepairActor_GetWeaponHasDurability_Params Parms{};
        Parms.WeaponItem = WeaponItem;
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    void ABuildingPhoenixRepairActor_GetWeaponRepairRecipe(class ABuildingPhoenixRepairActor* Obj, class AFortPlayerController* FPC, struct FRecipe* OutRecipe)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("BuildingPhoenixRepairActor", "GetWeaponRepairRecipe");
        
        SDK::Params::BuildingPhoenixRepairActor_GetWeaponRepairRecipe_Params Parms{};
        Parms.FPC = FPC;
        Obj->ProcessEvent(Func, &Parms);
        if (OutRecipe != nullptr) *OutRecipe = Parms.OutRecipe;
    }

    void AFortPlayerControllerAthena_ClientStartRespawnPreparation(class AFortPlayerControllerAthena* Obj, const struct FVector& RespawnLoc, const struct FRotator& RespawnRot, float RespawnCameraDist, ERespawnCameraBehavior InRespawnCameraBehavior, const class FText& HUDReasonText)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerAthena", "ClientStartRespawnPreparation");
        
        SDK::Params::FortPlayerControllerAthena_ClientStartRespawnPreparation_Params Parms{};
        Parms.RespawnLoc = RespawnLoc;
        Parms.RespawnRot = RespawnRot;
        Parms.RespawnCameraDist = RespawnCameraDist;
        Parms.InRespawnCameraBehavior = InRespawnCameraBehavior;
        Parms.HUDReasonText = HUDReasonText;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerControllerAthena_ClientStartWaitLTMLoading(class AFortPlayerControllerAthena* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerAthena", "ClientStartWaitLTMLoading");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerControllerAthena_PlayWinEffects(class AFortPlayerControllerAthena* Obj, class APawn* FinisherPawn, const class UFortWeaponItemDefinition* FinishingWeapon, EDeathCause DeathCause, bool bAudioOnly)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerAthena", "PlayWinEffects");
        
        SDK::Params::FortPlayerControllerAthena_PlayWinEffects_Params Parms{};
        Parms.FinisherPawn = FinisherPawn;
        Parms.FinishingWeapon = FinishingWeapon;
        Parms.DeathCause = DeathCause;
        Parms.bAudioOnly = bAudioOnly;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerControllerAthena_PostLobbyIslandTeleport(class AFortPlayerControllerAthena* Obj, class AFortPlayerPawn* PlayerPawn)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerAthena", "PostLobbyIslandTeleport");
        
        SDK::Params::FortPlayerControllerAthena_PostLobbyIslandTeleport_Params Parms{};
        Parms.PlayerPawn = PlayerPawn;
        Obj->ProcessEvent(Func, &Parms);
    }

    TArray<TSoftObjectPtr<class UObject>> UFortniteAutomationBlueprintLibrary_GetWrapPreviewObjects(ESubGame SubGame)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = SDK::UFortniteAutomationBlueprintLibrary::StaticClass()->GetFunction("FortniteAutomationBlueprintLibrary", "GetWrapPreviewObjects");
        
        SDK::Params::FortniteAutomationBlueprintLibrary_GetWrapPreviewObjects_Params Parms{};
        Parms.SubGame = SubGame;
        SDK::UFortniteAutomationBlueprintLibrary::GetDefaultObj()->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    struct FFortAthenaLoadout UFortniteAutomationBlueprintLibrary_MakeLoadoutFromVariantChannelInfos(const TArray<struct FMcpVariantChannelInfo>& VariantInfo)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = SDK::UFortniteAutomationBlueprintLibrary::StaticClass()->GetFunction("FortniteAutomationBlueprintLibrary", "MakeLoadoutFromVariantChannelInfos");
        
        SDK::Params::FortniteAutomationBlueprintLibrary_MakeLoadoutFromVariantChannelInfos_Params Parms{};
        Parms.VariantInfo = VariantInfo;
        SDK::UFortniteAutomationBlueprintLibrary::GetDefaultObj()->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    EDadBroHealthType IDadBroHealthInterface_GetCurrentHealthType(class IDadBroHealthInterface* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("DadBroHealthInterface", "GetCurrentHealthType");
        
        SDK::Params::DadBroHealthInterface_GetCurrentHealthType_Params Parms{};
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    void UDeathEffectsPawnComponent_ClientPlayWinnerDeathEffects(class UDeathEffectsPawnComponent* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("DeathEffectsPawnComponent", "ClientPlayWinnerDeathEffects");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    bool UFortAccountBuffItem_IsActive(class UFortAccountBuffItem* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortAccountBuffItem", "IsActive");
        
        SDK::Params::FortAccountBuffItem_IsActive_Params Parms{};
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    class AFortPlayerController* UObjectInteractionBehavior_GetFortPlayerController(class UObjectInteractionBehavior* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("ObjectInteractionBehavior", "GetFortPlayerController");
        
        SDK::Params::ObjectInteractionBehavior_GetFortPlayerController_Params Parms{};
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    void UDeleteObjects_GetDeleteActorsMeshComponents(TArray<class UMeshComponent*>& Components)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = SDK::UDeleteObjects::StaticClass()->GetFunction("DeleteObjects", "GetDeleteActorsMeshComponents");
        
        SDK::Params::UDeleteObjects_GetDeleteActorsMeshComponents_Params Parms{};
        SDK::UDeleteObjects::GetDefaultObj()->ProcessEvent(Func, &Parms);
        Components = Parms.Components;
    }

    TArray<class FText> AFortAthenaMutator_TODOverride_GetTimeOfDaySpeedNames(class AFortAthenaMutator_TODOverride* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortAthenaMutator_TODOverride", "GetTimeOfDaySpeedNames");
        
        SDK::Params::FortAthenaMutator_TODOverride_GetTimeOfDaySpeedNames_Params Parms{};
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    bool AFortInGameMapManager_GetStaticCaptureSetupComplete(class AFortInGameMapManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortInGameMapManager", "GetStaticCaptureSetupComplete");
        
        SDK::Params::FortInGameMapManager_GetStaticCaptureSetupComplete_Params Parms{};
        Obj->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    void AFortInGameMapManager_OnRep_ClearAllFog(class AFortInGameMapManager* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortInGameMapManager", "OnRep_ClearAllFog");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerControllerPvE_ResetPlayerDeathReportForForcePlayerRestart(class AFortPlayerControllerPvE* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerPvE", "ResetPlayerDeathReportForForcePlayerRestart");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerControllerPvE_ServerTriggerSetupTeleportCameraEvent(class AFortPlayerControllerPvE* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerPvE", "ServerTriggerSetupTeleportCameraEvent");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerControllerPvE_ServerUpdateQuickBarRecordsCache(class AFortPlayerControllerPvE* Obj, const struct FQuickBar& PrimaryQuickBarRecord, const struct FQuickBar& SecondaryQuickBarRecord)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerPvE", "ServerUpdateQuickBarRecordsCache");
        
        SDK::Params::FortPlayerControllerPvE_ServerUpdateQuickBarRecordsCache_Params Parms{};
        Parms.PrimaryQuickBarRecord = PrimaryQuickBarRecord;
        Parms.SecondaryQuickBarRecord = SecondaryQuickBarRecord;
        Obj->ProcessEvent(Func, &Parms);
    }

    void UFortHealthSet_OnRep_MaxHealth(class UFortHealthSet* Obj, const struct FFortGameplayAttributeData& OldValue)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortHealthSet", "OnRep_MaxHealth");
        
        SDK::Params::FortHealthSet_OnRep_MaxHealth_Params Parms{};
        Parms.OldValue = OldValue;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AFortPlayerPawn_ClientNotifyAbilityFailed(class AFortPlayerPawn* Obj, const class UGameplayAbility* FailedAbility, const struct FGameplayTagContainer& FailedReason)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerPawn", "ClientNotifyAbilityFailed");
        
        SDK::Params::FortPlayerPawn_ClientNotifyAbilityFailed_Params Parms{};
        Parms.FailedAbility = FailedAbility;
        Parms.FailedReason = FailedReason;
        Obj->ProcessEvent(Func, &Parms);
    }

    void UFortCheatManager_Affiliation_Affiliation_ResetMemberRelations()
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = SDK::UFortCheatManager_Affiliation::StaticClass()->GetFunction("FortCheatManager_Affiliation", "Affiliation_ResetMemberRelations");
        
        SDK::UFortCheatManager_Affiliation::GetDefaultObj()->ProcessEvent(Func, nullptr);
    }

    void UFortCheatManager_Quests_CompleteAllQuestsByName(class FString& QuestPartialName)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = SDK::UFortCheatManager_Quests::StaticClass()->GetFunction("FortCheatManager_Quests", "CompleteAllQuestsByName");
        
        SDK::Params::FortCheatManager_Quests_CompleteAllQuestsByName_Params Parms{};
        Parms.QuestPartialName = QuestPartialName;
        SDK::UFortCheatManager_Quests::GetDefaultObj()->ProcessEvent(Func, &Parms);
        QuestPartialName = Parms.QuestPartialName;
    }

    void UFortCheatManagerSTW_SetWorldLevel(float Level)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = SDK::UFortCheatManagerSTW::StaticClass()->GetFunction("FortCheatManagerSTW", "SetWorldLevel");
        
        SDK::Params::FortCheatManagerSTW_SetWorldLevel_Params Parms{};
        Parms.Level = Level;
        SDK::UFortCheatManagerSTW::GetDefaultObj()->ProcessEvent(Func, &Parms);
    }

    void UFortCheatManagerSTW_TestOutpostUI()
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = SDK::UFortCheatManagerSTW::StaticClass()->GetFunction("FortCheatManagerSTW", "TestOutpostUI");
        
        SDK::UFortCheatManagerSTW::GetDefaultObj()->ProcessEvent(Func, nullptr);
    }

    void UFortMcpProfileCreative_RestoreDeletedIsland(class UFortMcpProfileCreative* Obj, const class FString& PlotItemId, struct FDedicatedServerUrlContext* Context)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortMcpProfileCreative", "RestoreDeletedIsland");
        
        SDK::Params::FortMcpProfileCreative_RestoreDeletedIsland_Params Parms{};
        Parms.PlotItemId = PlotItemId;
        Parms.Context = *Context; // Assign the dereferenced pointer
        Obj->ProcessEvent(Func, &Parms);
        // If Context is an out param, you might need to copy back: *Context = Parms.Context;
    }

    void UFortKismetLibrary_RemoveControllerComponent(class AController* Controller, TSubclassOf<class UControllerComponent> ControllerCompClass)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = SDK::UFortKismetLibrary::StaticClass()->GetFunction("FortKismetLibrary", "RemoveControllerComponent");
        
        SDK::Params::FortKismetLibrary_RemoveControllerComponent_Params Parms{};
        Parms.Controller = Controller;
        Parms.ControllerCompClass = ControllerCompClass;
        SDK::UFortKismetLibrary::GetDefaultObj()->ProcessEvent(Func, &Parms);
    }

    bool AFortMinigame_OverridePlayerSpawnLocation(class AFortMinigame* Obj, class APawn* PlayerPawn, class AFortPlayerStateAthena* PlayerState, struct FVector* OutLocation, struct FRotator* OutRotation, bool* bOutRespawningOnGround)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortMinigame", "OverridePlayerSpawnLocation");
        
        SDK::Params::FortMinigame_OverridePlayerSpawnLocation_Params Parms{};
        Parms.PlayerPawn = PlayerPawn;
        Parms.PlayerState = PlayerState;
        Obj->ProcessEvent(Func, &Parms);
        
        if (OutLocation != nullptr) *OutLocation = Parms.OutLocation;
        if (OutRotation != nullptr) *OutRotation = Parms.OutRotation;
        if (bOutRespawningOnGround != nullptr) *bOutRespawningOnGround = Parms.bOutRespawningOnGround;
        
        return Parms.ReturnValue;
    }

    void AFortPlayerControllerOutpost_DumpInventory(class AFortPlayerControllerOutpost* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerOutpost", "DumpInventory");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AFortPlayerControllerOutpost_LeaveOutpostAsParty(class AFortPlayerControllerOutpost* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortPlayerControllerOutpost", "LeaveOutpostAsParty");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void UFortWorldMarker_PlayerStateDestroyed(class UFortWorldMarker* Obj, class AActor* DestroyedActor)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("FortWorldMarker", "PlayerStateDestroyed");
        
        SDK::Params::FortWorldMarker_PlayerStateDestroyed_Params Parms{};
        Parms.DestroyedActor = DestroyedActor;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AThreatCloud_OnCloudHiddenChange(class AThreatCloud* Obj, bool bCloudsAreHidden)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("ThreatCloud", "OnCloudHiddenChange");
        
        SDK::Params::ThreatCloud_OnCloudHiddenChange_Params Parms{};
        Parms.bCloudsAreHidden = bCloudsAreHidden;
        Obj->ProcessEvent(Func, &Parms);
    }

    void AThreatCloud_OnCloudStart(class AThreatCloud* Obj)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("ThreatCloud", "OnCloudStart");
        
        Obj->ProcessEvent(Func, nullptr);
    }

    void AThreatCloud_OnLightningStrike(class AThreatCloud* Obj, const struct FVector& StartLocation, const struct FVector& EndLocation)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("ThreatCloud", "OnLightningStrike");
        
        SDK::Params::ThreatCloud_OnLightningStrike_Params Parms{};
        Parms.StartLocation = StartLocation;
        Parms.EndLocation = EndLocation;
        Obj->ProcessEvent(Func, &Parms);
    }

    class AWorldMapPin* AWorldMapPinManager_CreateWorldMapPin(class AWorldMapPinManager* Obj, const class FString& TheaterId)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = SDK::AWorldMapPinManager::StaticClass()->GetFunction("WorldMapPinManager", "CreateWorldMapPin");
        
        SDK::Params::WorldMapPinManager_CreateWorldMapPin_Params Parms{};
        Parms.TheaterId = TheaterId;
        SDK::AWorldMapPinManager::GetDefaultObj()->ProcessEvent(Func, &Parms);
        return Parms.ReturnValue;
    }

    void AWrapPreviewGridActor_SetWrap(class AWrapPreviewGridActor* Obj, class UAthenaItemWrapDefinition* NewWrap)
    {
        static class UFunction* Func = nullptr;
        if (Func == nullptr) Func = Obj->Class->GetFunction("WrapPreviewGridActor", "SetWrap");
        
        SDK::Params::WrapPreviewGridActor_SetWrap_Params Parms{};
        Parms.NewWrap = NewWrap;
        Obj->ProcessEvent(Func, &Parms);
    }

} 
namespace FortniteSDK
{
    #include <iostream>

    int main()
    {
        // 1. Initialize the SDK (VERY IMPORTANT!)
        FortniteSDK::InitializeSDK();

        // Check if initialization was successful enough to proceed
        if (ObjObjects == nullptr || ::ProcessEventO == nullptr) {
            std::cerr << "SDK initialization failed. Cannot proceed.\n";
            return 1;
        }

        // 2. Get the local player controller
        APlayerController* MyPlayerController = FortniteSDK::GetLocalPlayerController();

        if(MyPlayerController)
        {
            std::cout << "Successfully obtained Player Controller: " << MyPlayerController->GetFullName() << std::endl;

            // Cast to Athena_PlayerController_C if you know it's that specific type
            SDK::AAthena_PlayerController_C* AthenaPC = reinterpret_cast<SDK::AAthena_PlayerController_C*>(MyPlayerController);

            // Example of calling a function on the player controller
            // You would need to create a dummy USoundBase object or find a real one in game
            // For demonstration, let's just try to call it (it will likely fail without a real object)
            std::cout << "Attempting to call ChangeMusic on PlayerController...\n";
            FortniteSDK::AAthena_PlayerController_C_ChangeMusic(nullptr, 0.0f); // Pass nullptr for New_Music for demo

            // Example of a FortniteGame.FortPlayerController function
            std::cout << "Attempting to call Cheat command...\n";
            FortniteSDK::AFortPlayerController_Cheat(MyPlayerController, FString("God")); // Example cheat
            
            // Example of a static function (like from CheatManager)
            std::cout << "Attempting to call Static CheatManager function...\n";
            bool shouldUseNewHeroLoadout = FortniteSDK::UFortCheatManager_ShouldUseNewHeroLoadoutUI(MyPlayerController);
            std::cout << "Should use new hero loadout UI: " << (shouldUseNewHeroLoadout ? "true" : "false") << std::endl;

        }
        else
        {
            std::cerr << "Failed to obtain Player Controller.\n";
        }

        // Your game loop or other logic would go here

        return 0;
    }
};