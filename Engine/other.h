#pragma once

/*
* CREDIT TO MILXNOR
*
* This header file contains various utility functions, structures, and enumerations,
* primarily designed to mimic or integrate with Unreal Engine's core types and functionalities.
* It includes mathematical utilities (vectors, rotators, quaternions),
* game-specific enumerations (game phases, death causes, item rarities),
* and helper functions for memory pattern scanning and file operations.
*/

#define _USE_MATH_DEFINES // Ensures M_PI and other math constants are available from <math.h>

#include <Windows.h> // For Windows-specific types like uint32_t, MessageBoxA, GetModuleHandleW, FreeLibraryAndExitThread
#include <vector>    // For std::vector
#include <string>    // For std::string, std::to_string, std::format
#include <math.h>    // For fabsf, sqrtf, fmod, M_PI
#include <random>    // For std::random_device, std::mt19937, std::uniform_int_distribution
#include <fstream>   // For std::ofstream

// Utility functions for floating-point number checks.
// These functions check for NaN (Not a Number) and finiteness using bitwise operations
// on the float's underlying integer representation, as commonly done in game engines
// for performance or specific behavior.
static bool IsNaN(float A)
{
	return ((*(uint32_t*)&A) & 0x7FFFFFFF) > 0x7F800000;
}

static bool IsFinite(float A)
{
	return ((*(uint32_t*)&A) & 0x7F800000) != 0x7F800000;
}

/**
 * @brief Represents a 3D vector or point.
 * Mimics Unreal Engine's FVector structure.
 */
struct FVector
{
	float X;
	float Y;
	float Z;

	// Constructors
	FVector() : X(0.0f), Y(0.0f), Z(0.0f) {}
	FVector(float x, float y, float z) : X(x), Y(y), Z(z) {}
	FVector(int x, int y, int z) : X(static_cast<float>(x)), Y(static_cast<float>(y)), Z(static_cast<float>(z)) {}

	// Operator overloads for vector arithmetic
	FVector operator+(const FVector& A) const
	{
		return FVector{ this->X + A.X, this->Y + A.Y, this->Z + A.Z };
	}

	FVector operator-(const FVector& A) const
	{
		return FVector{ this->X - A.X, this->Y - A.Y, this->Z - A.Z };
	}

	FVector operator*(const float A) const
	{
		return FVector{ this->X * A, this->Y * A, this->Z * A };
	}

	bool operator==(const FVector& A) const
	{
		return X == A.X && Y == A.Y && Z == A.Z;
	}

	void operator+=(const FVector& A)
	{
		*this = *this + A;
	}

	void operator-=(const FVector& A)
	{
		*this = *this - A;
	}

	/**
	 * @brief Returns a string representation of the vector.
	 * Requires C++20 for std::format.
	 */
	std::string Describe() const
	{
		// Note: std::format is a C++20 feature. If using an older standard,
		// you might need to use string streams (std::stringstream) instead.
		return std::format("{} {} {}", std::to_string(X), std::to_string(Y), std::to_string(Z));
	}

	/**
	 * @brief Checks if any component of the vector is NaN (Not a Number).
	 */
	bool ContainsNaN() const
	{
		return (!IsFinite(X) || !IsFinite(Y) || !IsFinite(Z));
	}
};

/**
 * @brief Enumerates the possible statuses of a server.
 */
enum class EServerStatus : uint8_t
{
	Up = 0,
	Down = 1,
	Loading = 2,
	Restarting = 3
};

/**
 * @brief Defines return types for montage playback operations.
 */
enum class EMontagePlayReturnType : uint8_t
{
	MontageLength = 0,
	Duration = 1,
	EMontagePlayReturnType_MAX = 2
};

/**
 * @brief Enumerates various causes of death in the game.
 */
enum class EDeathCause : uint8_t
{
	OutsideSafeZone = 0,
	FallDamage = 1,
	Pistol = 2,
	Shotgun = 3,
	Rifle = 4,
	SMG = 5,
	Sniper = 6,
	SniperNoScope = 7,
	Melee = 8,
	InfinityBlade = 9,
	Grenade = 10,
	C4 = 11,
	GrenadeLauncher = 12,
	RocketLauncher = 13,
	Minigun = 14,
	Bow = 15,
	Trap = 16,
	DBNOTimeout = 17, // Down But Not Out Timeout
	Banhammer = 18,
	RemovedFromGame = 19,
	MassiveMelee = 20,
	MassiveDiveBomb = 21,
	MassiveRanged = 22,
	Vehicle = 23,
	LMG = 24,
	GasGrenade = 25,
	InstantEnvironmental = 26,
	Turret = 27,
	Cube = 28,
	Balloon = 29,
	StormSurge = 30,
	BasicFiend = 31,
	EliteFiend = 32,
	RangedFiend = 33,
	BasicBrute = 34,
	EliteBrute = 35,
	MegaBrute = 36,
	LoggedOut = 37,
	TeamSwitchSuicide = 38,
	WonMatch = 39,
	Unspecified = 40,
	EDeathCause_MAX = 41
};

/**
 * @brief Computes the sine and cosine of an angle simultaneously using a minimax approximation.
 * Optimized for performance, similar to Unreal Engine's FMath::SinCos.
 * @param ScalarSin Pointer to store the computed sine value.
 * @param ScalarCos Pointer to store the computed cosine value.
 * @param Value The input angle in radians.
 */
static void SinCos(float* ScalarSin, float* ScalarCos, float Value)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	float quotient = (0.31830988618f * 0.5f) * Value; // (1 / (2*PI)) * 0.5
	if (Value >= 0.0f)
	{
		quotient = (float)((int)(quotient + 0.5f));
	}
	else
	{
		quotient = (float)((int)(quotient - 0.5f));
	}
	float y = Value - (2.0f * M_PI) * quotient;

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	float sign;
	if (y > 1.57079632679f) // M_PI / 2
	{
		y = M_PI - y;
		sign = -1.0f;
	}
	else if (y < -1.57079632679f) // -M_PI / 2
	{
		y = -M_PI - y;
		sign = -1.0f;
	}
	else
	{
		sign = +1.0f;
	}

	float y2 = y * y;

	// 11-degree minimax approximation for sine
	*ScalarSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

	// 10-degree minimax approximation for cosine
	float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
	*ScalarCos = sign * p;
}

/**
 * @brief Converts an angle from degrees to radians.
 * @tparam T The numeric type of the input value.
 * @param DegVal The angle in degrees.
 * @return The angle in radians.
 */
template <class T>
static auto DegreesToRadians(T const& DegVal) -> decltype(DegVal * (M_PI / 180.f))
{
	return DegVal * (static_cast<float>(M_PI) / 180.f);
}

// Forward declaration for FQuat, as it's used in FRotator.
struct FQuat;

/**
 * @brief Custom floating-point modulo function, similar to UE's FMath::Fmod.
 * Handles edge cases for very small divisors.
 * @param X The dividend.
 * @param Y The divisor.
 * @return The floating-point remainder of X / Y.
 */
float UE_Fmod(float X, float Y)
{
	const float AbsY = fabsf(Y);
	if (AbsY <= 1.e-8f) // Check for near-zero divisor
	{
		// FmodReportError(X, Y); // Original UE comment, indicating error reporting
		return 0.0f;
	}

	// Convert to double for better precision, since intermediate rounding can lose enough precision to skew the result.
	const double DX = static_cast<double>(X);
	const double DY = static_cast<double>(Y);

	const double Div = (DX / DY);
	const double IntPortion = DY * trunc(Div); // trunc discards the fractional part
	const double Result = DX - IntPortion;

	// Convert back to float. This is safe because the result will by definition not exceed the X input.
	return static_cast<float>(Result);
}

/**
 * @brief Enumerates the specific steps within an Athena (Battle Royale) game phase.
 */
enum class EAthenaGamePhaseStep : uint8_t
{
	None = 0,
	Setup = 1,
	Warmup = 2,
	GetReady = 3,
	BusLocked = 4,
	BusFlying = 5,
	StormForming = 6,
	StormHolding = 7,
	StormShrinking = 8,
	Countdown = 9,
	FinalCountdown = 10,
	EndGame = 11,
	Count = 12, // Number of valid steps
	EAthenaGamePhaseStep_MAX = 13, // Maximum enum value
};

/**
 * @brief Represents a rotator (Euler angles) in Pitch, Yaw, Roll.
 * Mimics Unreal Engine's FRotator structure.
 */
struct FRotator
{
	float Pitch;
	float Yaw;
	float Roll;

	/**
	 * @brief Converts this Rotator to a Quaternion.
	 * Implemented after FQuat to resolve circular dependency.
	 */
	FQuat Quaternion() const;

	/**
	 * @brief Clamps an angle to the range [0, 360).
	 * @param Angle The input angle in degrees.
	 * @return The clamped angle.
	 */
	static float ClampAxis(float Angle)
	{
		// returns Angle in the range [0,360) by using Fmod and adjusting for negative results.
		Angle = UE_Fmod(Angle, 360.f);

		if (Angle < 0.f)
		{
			// Shift to [0,360) range if negative
			Angle += 360.f;
		}

		return Angle;
	}

	/**
	 * @brief Normalizes an angle to the range (-180, 180].
	 * @param Angle The input angle in degrees.
	 * @return The normalized angle.
	 */
	static __forceinline float NormalizeAxis(float Angle)
	{
		// First, clamp to [0,360)
		Angle = ClampAxis(Angle);

		if (Angle > 180.f)
		{
			// Shift to (-180,180]
			Angle -= 360.f;
		}

		return Angle;
	}

	bool operator==(const FRotator& A) const
	{
		return Yaw == A.Yaw && Pitch == A.Pitch && Roll == A.Roll;
	}
};

/**
 * @brief Stores information about an aircraft's flight path.
 * Common in games for battle bus or similar flight mechanics.
 */
struct FAircraftFlightInfo
{
public:
	FVector                 FlightStartLocation;    // (Edit, BlueprintVisible, BlueprintReadOnly, NoDestructor, NativeAccessSpecifierPublic)
	FRotator                FlightStartRotation;    // (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, NativeAccessSpecifierPublic)
	float                   FlightSpeed;            // (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                   TimeTillFlightEnd;      // (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                   TimeTillDropStart;      // (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
	float                   TimeTillDropEnd;        // (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData, NoDestructor, HasGetValueTypeHash, NativeAccessSpecifierPublic)
};

/**
 * @brief Represents a localized text string, often used in UI.
 * This is a minimal representation, as Unreal's FText is complex.
 */
struct FText
{
	char UnknownData[0x18]; // Placeholder for internal FText data.
};

/**
 * @brief Defines the rarity levels for items in Fortnite (C2 refers to Chapter 2).
 */
enum class EFortRarityC2 : uint8_t // C2
{
	Common = 0,
	Uncommon = 1,
	Rare = 2,
	Epic = 3,
	Legendary = 4,
	Mythic = 5,
	Transcendent = 6,
	Unattainable = 7,
	NumRarityValues = 8,
	EFortRarity_MAX = 9,
};

/**
 * @brief Enumerates the different states of the safe zone (storm) in a game.
 */
enum class EFortSafeZoneState : uint8_t
{
	None = 0,
	Starting = 1,
	Holding = 2,
	Shrinking = 3,
	EFortSafeZoneState_MAX = 4,
};

/**
 * @brief Defines extrapolation modes for rich curves (e.g., animation curves).
 */
enum ERichCurveExtrapolation
{
	RCCE_Cycle,           // Cycle the curve data.
	RCCE_CycleWithOffset, // Cycle with an offset.
	RCCE_Oscillate,       // Oscillate the curve data.
	RCCE_Linear,          // Linear extrapolation.
	RCCE_Constant,        // Constant value extrapolation.
	RCCE_None,            // No extrapolation.
};

/**
 * @brief Enumerates various property types in the Unreal Engine reflection system.
 * This enum maps to internal engine type IDs.
 */
enum EName
{
	// NOTE: The original file had a `#pragma` here which is not standard C++ syntax
	// and likely a remnant or a specific compiler extension that should be removed
	// if not part of a larger build system.
	// Removed: pragma = (push_macro("TRUE")) pragma(push_macro("FALSE"))
	None = 0,
	ByteProperty = 1,
	IntProperty = 2,
	BoolProperty = 3,
	FloatProperty = 4,
	ObjectProperty = 5,
	NameProperty = 6,
	DelegateProperty = 7,
	DoubleProperty = 8,
	ArrayProperty = 9,
	StructProperty = 10,
	VectorProperty = 11,
	RotatorProperty = 12,
	StrProperty = 13,
	TextProperty = 14,
	InterfaceProperty = 15,
	MulticastDelegateProperty = 16,
	LazyObjectProperty = 18,
	SoftObjectProperty = 19,
	Int64Property = 20,
	Int32Property = 21,
	Int16Property = 22,
	Int8Property = 23,
	UInt64Property = 24,
	UInt32Property = 25,
	UInt16Property = 26,
	MapProperty = 28,
	SetProperty = 29,
	Core = 30,
	Engine = 31,
	Editor = 32,
	CoreUObject = 33,
	EnumProperty = 34,
	Cylinder = 50,
	BoxSphereBounds = 51,
	Sphere = 52,
	Box = 53,
	Vector2D = 54,
	IntRect = 55,
	IntPoint = 56,
	Vector4 = 57,
	Name = 58, // This 'Name' refers to FName
	Vector = 59, // This 'Vector' refers to FVector
	Rotator = 60, // This 'Rotator' refers to FRotator
	SHVector = 61,
	Color = 62,
	Plane = 63,
	Matrix = 64,
	LinearColor = 65,
	AdvanceFrame = 66,
	Pointer = 67,
	Double = 68,
	Quat = 69, // This 'Quat' refers to FQuat
	Self = 70,
	Transform = 71, // This 'Transform' refers to FTransform
	Vector3f = 72,
	Vector3d = 73,
	Plane4f = 74,
	Plane4d = 75,
	Matrix44f = 76,
	Matrix44d = 77,
	Quat4f = 78,
	Quat4d = 79,
	Transform3f = 80,
	Transform3d = 81,
	Box3f = 82,
	Box3d = 83,
	BoxSphereBounds3f = 84,
	BoxSphereBounds3d = 85,
	Vector4f = 86,
	Vector4d = 87,
	Rotator3f = 88,
	Rotator3d = 89,
	Vector2f = 90,
	Vector2d = 91,
	Box2D = 92,
	Box2f = 93,
	Box2d = 94,
	Object = 100,
	Camera = 101,
	Actor = 102,
	ObjectRedirector = 103,
	ObjectArchetype = 104,
	Class = 105,
	ScriptStruct = 106,
	Function = 107,
	Pawn = 108,
	State = 200,
	TRue = 201, // Typo in original (TRue instead of True)
	FAlse = 202, // Typo in original (FAlse instead of False)
	Enum = 203,
	Default = 204,
	Skip = 205,
	Input = 206,
	Package = 207,
	Groups = 208,
	Interface = 209,
	Components = 210,
	Global = 211,
	Super = 212,
	Outer = 213,
	Map = 214,
	Role = 215,
	RemoteRole = 216,
	PersistentLevel = 217,
	TheWorld = 218,
	PackageMetaData = 219,
	InitialState = 220,
	Game = 221,
	SelectionColor = 222,
	UI = 223,
	ExecuteUbergraph = 224,
	DeviceID = 225,
	RootStat = 226,
	MoveActor = 227,
	All = 230,
	MeshEmitterVertexColor = 231,
	TextureOffsetParameter = 232,
	TextureScaleParameter = 233,
	ImpactVel = 234,
	SlideVel = 235,
	TextureOffset1Parameter = 236,
	MeshEmitterDynamicParameter = 237,
	ExpressionInput = 238,
	Untitled = 239,
	Timer = 240,
	Team = 241,
	Low = 242,
	High = 243,
	NetworkGUID = 244,
	GameThread = 245,
	RenderThread = 246,
	OtherChildren = 247,
	Location = 248,
	Rotation = 249,
	BSP = 250,
	EditorSettings = 251,
	AudioThread = 252,
	ID = 253,
	UserDefinedEnum = 254,
	Control = 255,
	Voice = 256,
	Zlib = 257,
	Gzip = 258,
	LZ4 = 259,
	Mobile = 260,
	Oodle = 261,
	DGram = 280,
	Stream = 281,
	GameNetDriver = 282,
	PendingNetDriver = 283,
	BeaconNetDriver = 284,
	FlushNetDormancy = 285,
	DemoNetDriver = 286,
	GameSession = 287,
	PartySession = 288,
	GamePort = 289,
	BeaconPort = 290,
	MeshPort = 291,
	MeshNetDriver = 292,
	LiveStreamVoice = 293,
	LiveStreamAnimation = 294,
	Linear = 300,
	Point = 301,
	Aniso = 302,
	LightMapResolution = 303,
	UnGrouped = 311,
	VoiceChat = 312,
	Playing = 320,
	Spectating = 322,
	Inactive = 325,
	PerfWarning = 350,
	Info = 351,
	Init = 352,
	Exit = 353,
	Cmd = 354,
	Warning = 355,
	Error = 356,
	FontCharacter = 400,
	InitChild2StartBone = 401,
	SoundCueLocalized = 402,
	SoundCue = 403,
	RawDistributionFloat = 404,
	RawDistributionVector = 405,
	InterpCurveFloat = 406,
	InterpCurveVector2D = 407,
	InterpCurveVector = 408,
	InterpCurveTwoVectors = 409,
	InterpCurveQuat = 410,
	AI = 450,
	NavMesh = 451,
	PerformanceCapture = 500,
	EditorLayout = 600,
	EditorKeyBindings = 601,
	GameUserSettings = 602,
	Filename = 700,
	Lerp = 701,
	Root = 702,
	// Removed: pragma = (pop_macro("TRUE")) pragma(pop_macro("FALSE"))
	MaxHardcodedNameIndex, // Sentinel value for the maximum hardcoded name index.
};

/**
 * @brief Defines interpolation modes for rich curves.
 */
enum ERichCurveInterpMode
{
	RCIM_Linear,   // Use linear interpolation between values.
	RCIM_Constant, // Use a constant value. Represents stepped values.
	RCIM_Cubic,    // Cubic interpolation. See TangentMode for different cubic interpolation options.
	RCIM_None      // No interpolation.
};

/**
 * @brief Defines the policy for replicating ability target data.
 */
enum class EFortAbilityTargetDataPolicy : uint8_t
{
	ReplicateToServer = 0,
	SimulateOnServer = 1,
	EFortAbilityTargetDataPolicy_MAX = 2
};

/**
 * @brief Writes a given text to a file.
 * @param Text The string to write.
 * @param FileName The name of the file. Defaults to "DUMP.txt".
 */
void WriteToFile(const std::string& Text, const std::string& FileName = "DUMP.txt")
{
	// Open the file in output mode and append mode.
	std::ofstream stream(FileName, std::ios::out | std::ios::app);

	// Write the text followed by a newline character.
	stream << Text << '\n';

	// Close the file stream.
	stream.close();
}

/**
 * @brief Defines how a montage section should be chosen for playback.
 */
enum class EFortGameplayAbilityMontageSectionToPlay : uint8_t
{
	FirstSection = 0,
	RandomSection = 1,
	TestedRandomSection = 2,
	EFortGameplayAbilityMontageSectionToPlay_MAX = 3
};

// Constant for FASTASIN_HALF_PI, defined before use.
#define FASTASIN_HALF_PI (1.5707963050f) // Approximately PI / 2

/**
 * @brief Computes the ASin (arcsine) of a scalar value using a minimax approximation.
 * Optimized for performance.
 * @param Value The input value, clamped to [-1,1].
 * @return The ASin of Value in radians.
 */
static float FastAsin(float Value)
{
	// Clamp input to [-1,1].
	bool nonnegative = (Value >= 0.0f);
	float x = fabsf(Value);
	float omx = 1.0f - x;
	if (omx < 0.0f)
	{
		omx = 0.0f; // Ensure omx is non-negative
	}
	float root = sqrtf(omx);

	// 7-degree minimax approximation for acos(|x|)
	float result = ((((((-0.0012624911f * x + 0.0066700901f) * x - 0.0170881256f) * x + 0.0308918810f) * x - 0.0501743046f) * x + 0.0889789874f) * x - 0.2145988016f) * x + FASTASIN_HALF_PI;
	result *= root;  // acos(|x|)

	// asin(x) = pi/2 - acos(x). Handle sign based on original Value.
	return (nonnegative ? FASTASIN_HALF_PI - result : result - FASTASIN_HALF_PI);
}
#undef FASTASIN_HALF_PI // Undefine the macro after use to prevent potential conflicts.

/**
 * @brief Custom Atan2 (arctangent of Y/X) function, similar to UE's FMath::Atan2.
 * Uses a minimax approximation for performance and stability, avoiding potential
 * NaN issues with standard library atan2f on some platforms/compilers.
 * @param Y The Y component.
 * @param X The X component.
 * @return The angle in radians between the positive X-axis and the point (X, Y).
 */
float UE_Atan2(float Y, float X)
{
	// On PC this has been measured to be 2x faster than the std C version.
	// atan2f occasionally returns NaN with perfectly valid input (possibly due to a compiler or library bug).
	// We are replacing it with a minimax approximation with a max relative error of 7.15255737e-007 compared to the C library function.

	const float absX = fabsf(X);
	const float absY = fabsf(Y);
	const bool yAbsBigger = (absY > absX);
	float t0 = yAbsBigger ? absY : absX; // Max(absY, absX)
	float t1 = yAbsBigger ? absX : absY; // Min(absX, absY)

	if (t0 == 0.f)
		return 0.f; // Avoid division by zero

	float t3 = t1 / t0;
	float t4 = t3 * t3;

	// Coefficients for the minimap approximation
	static const float c[7] = {
		+7.2128853633444123e-03f,
		-3.5059680836411644e-02f,
		+8.1675882859940430e-02f,
		-1.3374657325451267e-01f,
		+1.9856563505717162e-01f,
		-3.3324998579202170e-01f,
		+1.0f
	};

	// Evaluate the polynomial approximation
	t0 = c[0];
	t0 = t0 * t4 + c[1];
	t0 = t0 * t4 + c[2];
	t0 = t0 * t4 + c[3];
	t0 = t0 * t4 + c[4];
	t0 = t0 * t4 + c[5];
	t0 = t0 * t4 + c[6];
	t3 = t0 * t3;

	// Adjust for quadrants
	t3 = yAbsBigger ? (0.5f * static_cast<float>(M_PI)) - t3 : t3;
	t3 = (X < 0.0f) ? static_cast<float>(M_PI) - t3 : t3;
	t3 = (Y < 0.0f) ? -t3 : t3;

	return t3;
}

/**
 * @brief Represents a quaternion for rotations.
 * Mimics Unreal Engine's FQuat structure.
 */
// alignas(16) // This might be desired for performance on some architectures, but often not necessary for simple structs.
struct FQuat
{
	float W; // Scalar component (real part)
	float X; // Vector component X (i)
	float Y; // Vector component Y (j)
	float Z; // Vector component Z (k)

	/**
	 * @brief Converts this Quaternion to an FRotator (Euler angles).
	 * Mimics Unreal Engine's FQuat::Rotator.
	 * @return An FRotator representing the same rotation.
	 */
	FRotator Rotator() const
	{
		// DiagnosticCheckNaN(); // Original UE comment, indicating NaN checks.
		const float SingularityTest = Z * X - W * Y; // Test for gimbal lock singularities.
		const float YawY = 2.f * (W * Z + X * Y);
		const float YawX = (1.f - 2.f * ((Y * Y) + (Z * Z)));

		// References for quaternion to Euler conversion:
		// http://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
		// http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/

		// This threshold value was found from experience to work well with Unreal Engine's coordinate system.
		const float SINGULARITY_THRESHOLD = 0.4999995f;
		const float RAD_TO_DEG = (180.f) / static_cast<float>(M_PI);
		FRotator RotatorFromQuat;

		if (SingularityTest < -SINGULARITY_THRESHOLD)
		{
			// Gimbal lock: Pitch is -90 degrees (looking straight down)
			RotatorFromQuat.Pitch = -90.f;
			RotatorFromQuat.Yaw = UE_Atan2(YawY, YawX) * RAD_TO_DEG;
			// Roll calculation for this singularity case
			RotatorFromQuat.Roll = FRotator::NormalizeAxis(-RotatorFromQuat.Yaw - (2.f * UE_Atan2(X, W) * RAD_TO_DEG));
		}
		else if (SingularityTest > SINGULARITY_THRESHOLD)
		{
			// Gimbal lock: Pitch is +90 degrees (looking straight up)
			RotatorFromQuat.Pitch = 90.f;
			RotatorFromQuat.Yaw = UE_Atan2(YawY, YawX) * RAD_TO_DEG;
			// Roll calculation for this singularity case
			RotatorFromQuat.Roll = FRotator::NormalizeAxis(RotatorFromQuat.Yaw - (2.f * UE_Atan2(X, W) * RAD_TO_DEG));
		}
		else
		{
			// Standard case: No gimbal lock
			RotatorFromQuat.Pitch = FastAsin(2.f * (SingularityTest)) * RAD_TO_DEG;
			RotatorFromQuat.Yaw = UE_Atan2(YawY, YawX) * RAD_TO_DEG;
			RotatorFromQuat.Roll = UE_Atan2(-2.f * (W * X + Y * Z), (1.f - 2.f * ((X * X) + (Y * Y)))) * RAD_TO_DEG;
		}

		return RotatorFromQuat;
	}
};

/**
 * @brief Implementation of FRotator::Quaternion().
 * Converts this Rotator to a Quaternion.
 * Mimics Unreal Engine's FRotator::Quaternion.
 * @return An FQuat representing the same rotation.
 */
FQuat FRotator::Quaternion() const
{
	const float DEG_TO_RAD = static_cast<float>(M_PI) / (180.f);
	const float RADS_DIVIDED_BY_2 = DEG_TO_RAD / 2.f;

	// Calculate sin and cos of half angles for Pitch, Yaw, Roll.
	// fmod is used to handle angles outside [0, 360) for robust calculation.
	float SP, SY, SR; // Sin of Pitch, Yaw, Roll (half angles)
	float CP, CY, CR; // Cos of Pitch, Yaw, Roll (half angles)

	const float PitchNoWinding = fmod(Pitch, 360.0f);
	const float YawNoWinding = fmod(Yaw, 360.0f);
	const float RollNoWinding = fmod(Roll, 360.0f);

	SinCos(&SP, &CP, PitchNoWinding * RADS_DIVIDED_BY_2);
	SinCos(&SY, &CY, YawNoWinding * RADS_DIVIDED_BY_2);
	SinCos(&SR, &CR, RollNoWinding * RADS_DIVIDED_BY_2);

	FQuat RotationQuat;
	RotationQuat.X = CR * SP * SY - SR * CP * CY;
	RotationQuat.Y = -CR * SP * CY - SR * CP * SY;
	RotationQuat.Z = CR * CP * SY - SR * SP * CY;
	RotationQuat.W = CR * CP * CY + SR * SP * SY;

	return RotationQuat;
}

/**
 * @brief Enumerates different resource types in Fortnite.
 */
enum class EFortResourceType : uint8_t
{
	Wood = 0,
	Stone = 1,
	Metal = 2,
	Permanite = 3, // A special resource type
	None = 4,
	EFortResourceType_MAX = 5
};

/**
 * @brief Represents a transformation (rotation, translation, scale) in 3D space.
 * Mimics Unreal Engine's FTransform structure.
 */
struct FTransform
{
	FQuat Rotation;
	FVector Translation;
	char pad_1C[0x4]; // Padding to maintain memory alignment/layout as in UE
	FVector Scale3D = FVector{ 1.0f, 1.0f, 1.0f }; // Default scale is (1,1,1)
	char pad_2C[0x4]; // Padding

	/*
	* @brief Checks if any component of the transform contains NaN values.
	* This function was commented out in the original. Uncomment and implement if needed.
	bool ContainsNaN() const
	{
		return (Translation.ContainsNaN() || Rotation.ContainsNaN() || Scale3D.ContainsNaN());
	}
	*/
};

/**
 * @brief Defines methods for handling actor spawning collision.
 */
enum ESpawnActorCollisionHandlingMethod
{
	Undefined,                          // Collision handling method is not defined.
	AlwaysSpawn,                        // Always spawn, even if colliding.
	AdjustIfPossibleButAlwaysSpawn,     // Try to adjust if colliding, but always spawn.
	AdjustIfPossibleButDontSpawnIfColliding, // Try to adjust, but don't spawn if still colliding.
	DontSpawnIfColliding,               // Don't spawn if colliding at all.
};

/**
 * @brief A template struct to treat an enum as a byte.
 * Commonly used in Unreal Engine for compact enum storage and network replication.
 * @tparam TEnum The enumeration type.
 */
template<class TEnum>
struct TEnumAsByte // Reference: https://github.com/EpicGames/UnrealEngine/blob/4.21/Engine/Source/Runtime/Core/Public/Containers/EnumAsByte.h#L18
{
	uint8_t Value;

	// Constructor from enum value
	TEnumAsByte(TEnum _value)
		: Value(static_cast<uint8_t>(_value))
	{
	}

	// Default constructor initializes to 0
	TEnumAsByte() : Value(0) {}

	// Explicit conversion operator to the enum type
	operator TEnum() const
	{
		return static_cast<TEnum>(Value);
	}

	// Getter for the enum value
	TEnum Get() const
	{
		return static_cast<TEnum>(Value);
	}
};

/**
 * @brief A generic bitfield structure, likely used for flags or packed booleans.
 * The original naming 'idk' (I don't know) suggests its specific purpose is unknown
 * without further context from the original codebase.
 */
struct bitfield
{
	uint8_t idk1;
	uint8_t idk2;
	uint8_t idk3;
	uint8_t idk4;
	uint8_t idk5;
	uint8_t idk6;
	uint8_t idk7;
	uint8_t idk8;
};

/**
 * @brief Enumerates different types of vehicles.
 */
enum class EVehicleType
{
	Biplane,
	Cannon,
	Baller,
	Mech,
	Turret,
	Boat,
	Helicopter,
	Unknown
};

/**
 * @brief Defines types of interactions in the game.
 */
enum class ETInteractionType : uint8_t
{
	IT_NoInteraction = 0,
	IT_Simple = 1,
	IT_LongPress = 2,
	IT_BuildingEdit = 3,
	IT_BuildingImprovement = 4,
	IT_TrapPlacement = 5,
	IT_MAX = 6
};

/**
 * @brief Enumerates custom body types for characters.
 */
enum class EFortCustomBodyType : uint8_t
{
	Small = 0,
	Medium = 1,
	MediumAndSmall = 2,
	Large = 3,
	LargeAndSmall = 4,
	LargeAndMedium = 5,
	All = 6,
	Deprecated = 7,
	EFortCustomBodyType_MAX = 8
};

/**
 * @brief Enumerates custom gender types for characters.
 */
enum class EFortCustomGender : uint8_t
{
	Invalid = 0,
	Male = 1,
	Female = 2,
	Both = 3,
	EFortCustomGender_MAX = 4
};

/**
 * @brief Defines flags for UProperty in Unreal Engine, indicating its behavior and editor visibility.
 * These flags are crucial for reflection and serialization in Unreal Engine.
 */
enum EPropertyFlags : unsigned __int64
{
	CPF_None = 0,
	CPF_Edit = 0x0000000000000001,	///< Property is user-settable in the editor.
	CPF_ConstParm = 0x0000000000000002,	///< This is a constant function parameter.
	CPF_BlueprintVisible = 0x0000000000000004,	///< This property can be read by blueprint code.
	CPF_ExportObject = 0x0000000000000008,	///< Object can be exported with actor.
	CPF_BlueprintReadOnly = 0x0000000000000010,	///< This property cannot be modified by blueprint code.
	CPF_Net = 0x0000000000000020,	///< Property is relevant to network replication.
	CPF_EditFixedSize = 0x0000000000000040,	///< Indicates that elements of an array can be modified, but its size cannot be changed.
	CPF_Parm = 0x0000000000000080,	///< Function/When call parameter.
	CPF_OutParm = 0x0000000000000100,	///< Value is copied out after function call.
	CPF_ZeroConstructor = 0x0000000000000200,	///< memset is fine for construction.
	CPF_ReturnParm = 0x0000000000000400,	///< Return value.
	CPF_DisableEditOnTemplate = 0x0000000000000800,	///< Disable editing of this property on an archetype/sub-blueprint.
	// 0x0000000000001000 - Unused
	CPF_Transient = 0x0000000000002000,	///< Property is transient: shouldn't be saved or loaded, except for Blueprint CDOs.
	CPF_Config = 0x0000000000004000,	///< Property should be loaded/saved as permanent profile.
	// 0x0000000000008000 - Unused
	CPF_DisableEditOnInstance = 0x0000000000010000,	///< Disable editing on an instance of this class.
	CPF_EditConst = 0x0000000000020000,	///< Property is uneditable in the editor.
	CPF_GlobalConfig = 0x0000000000040000,	///< Load config from base class, not subclass.
	CPF_InstancedReference = 0x0000000000080000,	///< Property is a component references.
	// 0x0000000000100000 - Unused
	CPF_DuplicateTransient = 0x0000000000200000,	///< Property should always be reset to the default value during any type of duplication (copy/paste, binary duplication, etc.).
	// 0x0000000000400000 - Unused
	// 0x0000000000800000 - Unused
	CPF_SaveGame = 0x0000000001000000,	///< Property should be serialized for save games, this is only checked for game-specific archives with ArIsSaveGame.
	CPF_NoClear = 0x0000000002000000,	///< Hide clear (and browse) button.
	// 0x0000000004000000 - Unused
	CPF_ReferenceParm = 0x0000000008000000,	///< Value is passed by reference; CPF_OutParam and CPF_Parm should also be set.
	CPF_BlueprintAssignable = 0x0000000010000000,	///< MC Delegates only. Property should be exposed for assigning in blueprint code.
	CPF_Deprecated = 0x0000000020000000,	///< Property is deprecated. Read it from an archive, but don't save it.
	CPF_IsPlainOldData = 0x0000000040000000,	///< If this is set, then the property can be memcopied instead of CopyCompleteValue / CopySingleValue.
	CPF_RepSkip = 0x0000000080000000,	///< Not replicated. For non-replicated properties in replicated structs.
	CPF_RepNotify = 0x0000000100000000,	///< Notify actors when a property is replicated.
	CPF_Interp = 0x0000000200000000,	///< Interpolatable property for use with matinee (animation sequences).
	CPF_NonTransactional = 0x0000000400000000,	///< Property isn't transacted (undo/redo).
	CPF_EditorOnly = 0x0000000800000000,	///< Property should only be loaded in the editor.
	CPF_NoDestructor = 0x0000001000000000,	///< No destructor.
	// 0x0000002000000000 - Unused
	CPF_AutoWeak = 0x0000004000000000,	///< Only used for weak pointers, means the export type is autoweak.
	CPF_ContainsInstancedReference = 0x0000008000000000,	///< Property contains component references.
	CPF_AssetRegistrySearchable = 0x0000010000000000,	///< Asset instances will add properties with this flag to the asset registry automatically.
	CPF_SimpleDisplay = 0x0000020000000000,	///< The property is visible by default in the editor details view.
	CPF_AdvancedDisplay = 0x0000040000000000,	///< The property is advanced and not visible by default in the editor details view.
	CPF_Protected = 0x0000080000000000,	///< Property is protected from the perspective of script.
	CPF_BlueprintCallable = 0x0000100000000000,	///< MC Delegates only. Property should be exposed for calling in blueprint code.
	CPF_BlueprintAuthorityOnly = 0x0000200000000000,	///< MC Delegates only. This delegate accepts (only in blueprint) only events with BlueprintAuthorityOnly.
	CPF_TextExportTransient = 0x0000400000000000,	///< Property shouldn't be exported to text format (e.g. copy/paste).
	CPF_NonPIEDuplicateTransient = 0x0000800000000000,	///< Property should only be copied in PIE (Play In Editor).
	CPF_ExposeOnSpawn = 0x0001000000000000,	///< Property is exposed on spawn.
	CPF_PersistentInstance = 0x0002000000000000,	///< An object referenced by the property is duplicated like a component. (Each actor should have its own instance.)
	CPF_UObjectWrapper = 0x0004000000000000,	///< Property was parsed as a wrapper class like TSubclassOf<T>, FScriptInterface etc., rather than a USomething*.
	CPF_HasGetValueTypeHash = 0x0008000000000000,	///< This property can generate a meaningful hash value.
	CPF_NativeAccessSpecifierPublic = 0x0010000000000000,	///< Public native access specifier.
	CPF_NativeAccessSpecifierProtected = 0x0020000000000000,	///< Protected native access specifier.
	CPF_NativeAccessSpecifierPrivate = 0x0040000000000000,	///< Private native access specifier.
	CPF_SkipSerialization = 0x0080000000000000,	///< Property shouldn't be serialized, can still be exported to text.
};

/**
 * @brief Defines conditions for network replication lifetime.
 * Determines when a property or object should be replicated to clients.
 */
enum ELifetimeCondition
{
	COND_None = 0,                // Always relevant.
	COND_InitialOnly = 1,         // Only relevant for the initial replication.
	COND_OwnerOnly = 2,           // Only relevant to the owning client.
	COND_SkipOwner = 3,           // Relevant to all clients except the owning client.
	COND_SimulatedOnly = 4,       // Only relevant to simulated proxies.
	COND_AutonomousOnly = 5,      // Only relevant to autonomous proxies.
	COND_SimulatedOrPhysics = 6,  // Relevant to simulated proxies or objects with physics.
	COND_InitialOrOwner = 7,      // Relevant for initial replication or to the owning client.
	COND_Custom = 8,              // Custom replication logic.
	COND_ReplayOrOwner = 9,       // Relevant for replays or to the owning client.
	COND_ReplayOnly = 10,         // Only relevant for replays.
	COND_SimulatedOnlyNoReplay = 11, // Simulated only, but skip in replay.
	COND_SimulatedOrPhysicsNoReplay = 12, // Simulated or physics, but skip in replay.
	COND_SkipReplay = 13,         // Skip in replay.
	COND_Never = 15,              // Never relevant.
	COND_Max = 16                 // Maximum enum value.
};

/**
 * @brief Defines flags for UFunction in Unreal Engine, indicating its behavior and type.
 * These flags determine how a function is called, replicated, and exposed.
 */
enum EFunctionFlags
{
	FUNC_None = 0x00000000,
	FUNC_Final = 0x00000001,           // Function cannot be overridden in derived classes.
	FUNC_RequiredAPI = 0x00000002,      // Function is part of a required API.
	FUNC_BlueprintAuthorityOnly = 0x00000004, // Only callable on server/authority in Blueprint.
	FUNC_BlueprintCosmetic = 0x00000008, // Function is cosmetic only and has no gameplay effect.
	FUNC_Net = 0x00000040,              // Function is network replicated.
	FUNC_NetReliable = 0x00000080,      // Function is network replicated reliably.
	FUNC_NetRequest = 0x00000100,       // Function is a network request (client to server).
	FUNC_Exec = 0x00000200,             // Function can be executed from console.
	FUNC_Native = 0x00000400,           // Function is implemented in C++.
	FUNC_Event = 0x00000800,            // Function is a Blueprint event.
	FUNC_NetResponse = 0x00001000,      // Function is a network response (server to client).
	FUNC_Static = 0x00002000,           // Function is static (does not require an object instance).
	FUNC_NetMulticast = 0x00004000,     // Function is a network multicast event.
	FUNC_UbergraphFunction = 0x00008000, // Function is part of a Blueprint's ubergraph.
	FUNC_MulticastDelegate = 0x00010000, // Function is a multicast delegate.
	FUNC_Public = 0x00020000,
	FUNC_Private = 0x00040000,
	FUNC_Protected = 0x00080000,
	FUNC_Delegate = 0x00100000,         // Function is a delegate.
	FUNC_NetServer = 0x00200000,        // Function is only callable on the server.
	FUNC_HasOutParms = 0x00400000,      // Function has output parameters.
	FUNC_HasDefaults = 0x00800000,      // Function has default parameter values.
	FUNC_NetClient = 0x01000000,        // Function is only callable on the client.
	FUNC_DLLImport = 0x02000000,        // Function is imported from a DLL.
	FUNC_BlueprintCallable = 0x04000000, // Function is callable from Blueprint.
	FUNC_BlueprintEvent = 0x08000000,   // Function is a Blueprint event.
	FUNC_BlueprintPure = 0x10000000,    // Function is a Blueprint pure function (no side effects).
	FUNC_EditorOnly = 0x20000000,       // Function is only available in the editor.
	FUNC_Const = 0x40000000,            // Function does not modify the object's state.
	FUNC_NetValidate = 0x80000000,      // Function performs network validation.
	FUNC_AllFlags = 0xFFFFFFFF,         // All possible function flags.
};

/**
 * @brief Enumerates different types of gliders.
 */
enum class EFortGliderType : uint8_t
{
	Glider = 0,
	Umbrella = 1,
	EFortGliderType_MAX = 2,
};

/**
 * @brief Defines flags for UObject in Unreal Engine.
 * These flags control object lifecycle, serialization, and garbage collection.
 */
enum EObjectFlags
{
	RF_NoFlags = 0x00000000,            // No flags set.
	RF_Public = 0x00000001,             // Object is public.
	RF_Standalone = 0x00000002,         // Object can exist without a package.
	RF_MarkAsNative = 0x00000004,       // Mark as native class.
	RF_Transactional = 0x00000008,      // Object supports transactions (undo/redo).
	RF_ClassDefaultObject = 0x00000010, // Object is a class default object (CDO).
	RF_ArchetypeObject = 0x00000020,    // Object is an archetype.
	RF_Transient = 0x00000040,          // Object is not saved to disk.
	RF_MarkAsRootSet = 0x00000080,      // Object is part of the root set (not garbage collected).
	RF_TagGarbageTemp = 0x00000100,     // Temporary flag for garbage collection.
	RF_NeedInitialization = 0x00000200, // Object needs initialization.
	RF_NeedLoad = 0x00000400,           // Object needs to be loaded.
	RF_KeepForCooker = 0x00000800,      // Keep object for cooking process.
	RF_NeedPostLoad = 0x00001000,       // Object needs PostLoad called.
	RF_NeedPostLoadSubobjects = 0x00002000, // Object needs PostLoadSubobjects called.
	RF_NewerVersionExists = 0x00004000, // A newer version of this object exists.
	RF_BeginDestroyed = 0x00008000,     // Object is beginning destruction.
	RF_FinishDestroyed = 0x00010000,    // Object has finished destruction.
	RF_BeingRegenerated = 0x00020000,   // Object is being regenerated.
	RF_DefaultSubObject = 0x00040000,   // Object is a default sub-object.
	RF_WasLoaded = 0x00080000,          // Object was loaded from disk.
	RF_TextExportTransient = 0x00100000, // Object should not be text exported.
	RF_LoadCompleted = 0x00200000,      // Object has completed loading.
	RF_InheritableComponentTemplate = 0x00400000, // Object is an inheritable component template.
	RF_DuplicateTransient = 0x00800000, // Object should be reset to default on duplication.
	RF_StrongRefOnFrame = 0x01000000,   // Strong reference for one frame.
	RF_NonPIEDuplicateTransient = 0x02000000, // Object should only be copied in PIE.
	RF_Dynamic = 0x04000000,            // Object is dynamically created.
	RF_WillBeLoaded = 0x08000000,       // Object will be loaded.
	RF_HasExternalPackage = 0x10000000, // Object has an external package.
};

/**
 * @brief Defines flags for UClass in Unreal Engine.
 * These flags control class behavior, editor integration, and metadata.
 */
enum EClassFlags
{
	CLASS_None = 0x00000000u,           // No flags set.
	CLASS_Abstract = 0x00000001u,       // Class is abstract, cannot be instantiated.
	CLASS_DefaultConfig = 0x00000002u,  // Uses default config file.
	CLASS_Config = 0x00000004u,         // Can be configured.
	CLASS_Transient = 0x00000008u,      // Class is transient, not saved.
	CLASS_Parsed = 0x00000010u,         // Class has been parsed.
	CLASS_MatchedSerializers = 0x00000020u, // Matched serializers.
	CLASS_ProjectUserConfig = 0x00000040u, // Uses project user config.
	CLASS_Native = 0x00000080u,         // Class is native (C++).
	CLASS_NoExport = 0x00000100u,       // Do not export this class.
	CLASS_NotPlaceable = 0x00000200u,   // Cannot be placed in the editor.
	CLASS_PerObjectConfig = 0x00000400u, // Per-object config file.
	CLASS_ReplicationDataIsSetUp = 0x00000800u, // Replication data is set up.
	CLASS_EditInlineNew = 0x00001000u,  // Allows creation of new objects inline.
	CLASS_CollapseCategories = 0x00002000u, // Collapse categories in editor.
	CLASS_Interface = 0x00004000u,      // Class is an interface.
	CLASS_CustomConstructor = 0x00008000u, // Has a custom constructor.
	CLASS_Const = 0x00010000u,          // Class is const.
	CLASS_LayoutChanging = 0x00020000u, // Layout is changing.
	CLASS_CompiledFromBlueprint = 0x00040000u, // Compiled from Blueprint.
	CLASS_MinimalAPI = 0x00080000u,     // Minimal API.
	CLASS_RequiredAPI = 0x00100000u,    // Required API.
	CLASS_DefaultToInstanced = 0x00200000u, // Default to instanced.
	CLASS_TokenStreamAssembled = 0x00400000u, // Token stream assembled.
	CLASS_HasInstancedReference = 0x00800000u, // Has instanced reference.
	CLASS_Hidden = 0x01000000u,         // Hidden from editor.
	CLASS_Deprecated = 0x02000000u,     // Deprecated.
	CLASS_HideDropDown = 0x04000000u,   // Hide drop down in editor.
	CLASS_GlobalUserConfig = 0x08000000u, // Global user config.
	CLASS_Intrinsic = 0x10000000u,      // Intrinsic class.
	CLASS_Constructed = 0x20000000u,    // Constructed.
	CLASS_ConfigDoNotCheckDefaults = 0x40000000u, // Config does not check defaults.
	CLASS_NewerVersionExists = 0x80000000u, // Newer version exists.
};

/**
 * @brief Defines flags for class casting in Unreal Engine's reflection system.
 * These flags allow for fast type checking.
 */
enum EClassCastFlags
{
	CASTCLASS_None = 0x0000000000000000,
	CASTCLASS_UField = 0x0000000000000001,
	CASTCLASS_FInt8Property = 0x0000000000000002,
	CASTCLASS_UEnum = 0x0000000000000004,
	CASTCLASS_UStruct = 0x0000000000000008,
	CASTCLASS_UScriptStruct = 0x0000000000000010,
	CASTCLASS_UClass = 0x0000000000000020,
	CASTCLASS_FByteProperty = 0x0000000000000040,
	CASTCLASS_FIntProperty = 0x0000000000000080,
	CASTCLASS_FFloatProperty = 0x0000000000000100,
	CASTCLASS_FUInt64Property = 0x0000000000000200,
	CASTCLASS_FClassProperty = 0x0000000000000400,
	CASTCLASS_FUInt32Property = 0x0000000000000800,
	CASTCLASS_FInterfaceProperty = 0x0000000000001000,
	CASTCLASS_FNameProperty = 0x0000000000002000,
	CASTCLASS_FStrProperty = 0x0000000000004000,
	CASTCLASS_FProperty = 0x0000000000008000,
	CASTCLASS_FObjectProperty = 0x0000000000010000,
	CASTCLASS_FBoolProperty = 0x0000000000020000,
	CASTCLASS_FUInt16Property = 0x0000000000040000,
	CASTCLASS_UFunction = 0x0000000000080000,
	CASTCLASS_FStructProperty = 0x0000000000100000,
	CASTCLASS_FArrayProperty = 0x0000000000200000,
	CASTCLASS_FInt64Property = 0x0000000000400000,
	CASTCLASS_FDelegateProperty = 0x0000000000800000,
	CASTCLASS_FNumericProperty = 0x0000000001000000,
	CASTCLASS_FMulticastDelegateProperty = 0x0000000002000000,
	CASTCLASS_FObjectPropertyBase = 0x0000000004000000,
	CASTCLASS_FWeakObjectProperty = 0x0000000008000000,
	CASTCLASS_FLazyObjectProperty = 0x0000000010000000,
	CASTCLASS_FSoftObjectProperty = 0x0000000020000000,
	CASTCLASS_FTextProperty = 0x0000000040000000,
	CASTCLASS_FInt16Property = 0x0000000080000000,
	CASTCLASS_FDoubleProperty = 0x0000000100000000,
	CASTCLASS_FSoftClassProperty = 0x0000000200000000,
	CASTCLASS_UPackage = 0x0000000400000000,
	CASTCLASS_ULevel = 0x0000000800000000,
	CASTCLASS_AActor = 0x0000001000000000,
	CASTCLASS_APlayerController = 0x0000002000000000,
	CASTCLASS_APawn = 0x0000004000000000,
	CASTCLASS_USceneComponent = 0x0000008000000000,
	CASTCLASS_UPrimitiveComponent = 0x0000010000000000,
	CASTCLASS_USkinnedMeshComponent = 0x0000020000000000,
	CASTCLASS_USkeletalMeshComponent = 0x0000040000000000,
	CASTCLASS_UBlueprint = 0x0000080000000000,
	CASTCLASS_UDelegateFunction = 0x0000100000000000,
	CASTCLASS_UStaticMeshComponent = 0x0000200000000000,
	CASTCLASS_FMapProperty = 0x0000400000000000,
	CASTCLASS_FSetProperty = 0x0000800000000000,
	CASTCLASS_FEnumProperty = 0x0001000000000000,
	CASTCLASS_USparseDelegateFunction = 0x0002000000000000,
	CASTCLASS_FMulticastInlineDelegateProperty = 0x0004000000000000,
	CASTCLASS_FMulticastSparseDelegateProperty = 0x0008000000000000,
	CASTCLASS_FFieldPathProperty = 0x0010000000000000,
};

/**
 * @brief Defines network dormancy states for actors.
 * Dormancy is an optimization to reduce network traffic for actors that are not actively changing.
 */
enum class ENetDormancy : uint8_t
{
	DORM_Never = 0,        // Never goes dormant.
	DORM_Awake = 1,        // Currently awake and replicating.
	DORM_DormantAll = 2,   // Fully dormant, no replication.
	DORM_DormantPartial = 3, // Partially dormant, only critical properties replicate.
	DORM_Initial = 4,      // Initial dormancy state.
	DORM_MAX = 5
};

/**
 * @brief Enumerates states for a team member, often related to communication or needs.
 */
enum class ETeamMemberState : uint8_t
{
	None = 0,
	FIRST_CHAT_MESSAGE = 1, // Sentinel for the first chat message related enum.
	NeedAmmoHeavy = 2,
	NeedAmmoLight = 3,
	NeedAmmoMedium = 4,
	NeedAmmoShells = 5,
	NeedAmmoRocket = 6,
	ChatBubble = 7,
	EnemySpotted = 8,
	NeedBandages = 9,
	NeedMaterials = 10,
	NeedShields = 11,
	NeedWeapon = 12,
	LAST_CHAT_MESSAGE = 13, // Sentinel for the last chat message related enum.
	MAX = 14
};

/**
 * @brief Defines types of network channels.
 */
enum EChannelType
{
	CHTYPE_None = 0,      // Invalid type.
	CHTYPE_Control = 1,   // Connection control.
	CHTYPE_Actor = 2,     // Actor-update channel.
	// @todo: Remove and reassign number to CHTYPE_Voice (breaks net compatibility) - Original comment implies this might change.
	CHTYPE_File = 3,      // Binary file transfer.
	CHTYPE_Voice = 4,     // VoIP data channel.
	CHTYPE_MAX = 8,       // Maximum.
};

/**
 * @brief Finds a byte pattern (signature) in memory.
 * Commonly used for finding function addresses or global variables in executables.
 * @param signatureStr The byte signature string (e.g., "48 8B EC ?? ?? FF").
 * @param bRelative If true, calculates a relative address.
 * @param offset An offset to apply.
 * @param bIsVar If true, treats the pattern as a variable address.
 * @return The found memory address, or NULL if not found.
 */
static uint64_t FindPattern(std::string signatureStr, bool bRelative = false, uint32_t offset = 0, bool bIsVar = false)
{
	auto signature = signatureStr.c_str();
	auto base_address = reinterpret_cast<uint64_t>(GetModuleHandleW(NULL)); // Get the base address of the current module (executable).

	// Lambda function to convert a pattern string to a vector of bytes (allowing '??' for wildcards).
	static auto patternToByte = [](const char* pattern)
	{
		auto bytes = std::vector<int>{};
		const auto start = const_cast<char*>(pattern);
		const auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?') ++current; // Handle "??" for a single byte wildcard.
				bytes.push_back(-1); // -1 represents a wildcard.
			}
			else
			{
				bytes.push_back(static_cast<int>(strtoul(current, &current, 16))); // Convert hex string to integer.
			}
		}
		return bytes;
	};

	const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(base_address);
	// Calculate the address of the NT headers.
	const auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(base_address) + dosHeader->e_lfanew);

	const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage; // Size of the executable image in memory.
	auto patternBytes = patternToByte(signature);
	const auto scanBytes = reinterpret_cast<std::uint8_t*>(base_address);

	const auto s = patternBytes.size();
	const auto d = patternBytes.data(); // Get raw pointer to the byte data.

	// Iterate through the image memory to find the pattern.
	for (auto i = 0ul; i < sizeOfImage - s; ++i)
	{
		bool found = true;
		for (auto j = 0ul; j < s; ++j)
		{
			// Compare bytes; if d[j] is -1, it's a wildcard and always matches.
			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			auto address = reinterpret_cast<uint64_t>(&scanBytes[i]); // Address of the found pattern.
			if (bIsVar)
			{
				// For variables, the address might be relative, requiring an additional offset and dereference.
				address = (address + offset + *(int*)(address + 3));
			}
			if (bRelative && !bIsVar)
			{
				// For relative addressing, calculate the target address from the instruction's operand.
				address = ((address + offset + 4) + *(int*)(address + offset));
			}
			return address;
		}
	}
	return NULL; // Pattern not found.
}

/**
 * @brief Enumerates network roles for actors in a multiplayer game.
 * Determines ownership and authority over an actor on the network.
 */
enum class ENetRole : uint8_t
{
	ROLE_None = 0,           // No role (e.g., actor not relevant, or destroyed).
	ROLE_SimulatedProxy = 1, // Client-side representation of an actor whose authoritative instance is on the server or another client.
	ROLE_AutonomousProxy = 2, // Client-side representation of an actor that this client owns and has authority over (e.g., player character).
	ROLE_Authority = 3,      // Server-side authoritative instance of an actor.
	ROLE_MAX = 4
};

// #define PATTERN_TESTING // Never use this unless you know what this is for
// This define controls whether the application exits on a failed pattern find.
// It's commented out by default, meaning the application will exit.

/**
 * @brief Checks if a pattern was found and optionally assigns it to a delegate pointer.
 * Displays an error message and exits the application if the pattern is not found,
 * unless PATTERN_TESTING is defined.
 * @tparam T The type of the delegate pointer.
 * @param Name The name of the pattern being searched for (for error messages).
 * @param Pattern The address found by FindPattern.
 * @param Delegate A pointer to a variable of type T* to store the found address. Can be nullptr.
 */
template <typename T>
void CheckPattern(const std::string& Name, uint64_t Pattern, T** Delegate)
{
	if (!Pattern)
	{
		MessageBoxA(0, ("Failed to find: " + Name).c_str(), "Universal Walking Simulator", MB_ICONERROR);
#ifndef PATTERN_TESTING
		FreeLibraryAndExitThread(GetModuleHandle(0), 0); // Exit the application if pattern not found.
#endif
	}
	else
	{
		if (Delegate)
			*Delegate = reinterpret_cast<T*>(Pattern); // Assign the found address to the delegate pointer.
	}
}

// Type alias for EFortTeam, indicating it's an 8-bit unsigned integer.
using EFortTeam = uint8_t;

/**
 * @brief Enumerates the main phases of an Athena (Battle Royale) game.
 */
enum class EAthenaGamePhase : uint8_t
{
	None = 0,
	Setup = 1,      // Initial game setup.
	Warmup = 2,     // Players are in the lobby/warmup island.
	Aircraft = 3,   // Players are on the battle bus.
	SafeZones = 4,  // The storm is active and shrinking.
	EndGame = 5,    // The game is ending (e.g., winner declared).
	Count = 6,      // Number of valid game phases.
	EAthenaGamePhase_MAX = 7
};

/**
 * @brief Defines network modes for a game instance.
 */
enum ENetMode
{
	NM_Standalone,      // Single-player, no networking.
	NM_DedicatedServer, // Server only, no local client.
	NM_ListenServer,    // Server with a local client.
	NM_Client,          // Client connected to a server.
	NM_MAX,
};

/**
 * @brief Defines types of dynamic foundations for building.
 */
enum class EDynamicFoundationType : uint8_t
{
	Static = 0,               // Stationary and non-moving.
	StartEnabled_Stationary = 1, // Starts enabled but remains stationary.
	StartEnabled_Dynamic = 2,    // Starts enabled and can move.
	StartDisabled = 3,        // Starts disabled.
	EDynamicFoundationType_MAX = 4
};

// The name changes for EBuildingFoundationType and its variables but not size.
/**
 * @brief Defines types of building foundations.
 * Note: The original comment states the name and variables change, but not size.
 */
enum class EBuildingFoundationType : uint8_t
{
	BFT = 0,    // Base Foundation Type
	BFT01 = 1,  // Variation 1
	BFT02 = 2,  // Variation 2
	BFT_None = 3,
	BFT_MAX = 4
};

/**
 * @brief Enumerates custom part types for character customization.
 */
enum class EFortCustomPartType : uint8_t
{
	Head = 0,
	Body = 1,
	Hat = 2,
	Backpack = 3,
	Charm = 4,
	Face = 5,
	NumTypes = 6, // Total number of part types.
	EFortCustomPartType_MAX = 7
};

/**
 * @brief Generates a random integer within a specified range (inclusive).
 * Uses C++11 random number generation facilities.
 * @param min The minimum value (inclusive).
 * @param max The maximum value (inclusive).
 * @return A random integer between min and max.
 */
auto RandomIntInRange(int min, int max)
{
	std::random_device rd;      // Obtain a random number from hardware.
	std::mt19937 gen(rd());     // Seed the generator with a hardware-generated random number.
	std::uniform_int_distribution<> distr(min, max); // Define the range [min, max].

	return distr(gen); // Generate and return a random number within the range.
}

/**
 * @brief Enumerates states for a client's login process.
 */
namespace EClientLoginState
{
	enum Type
	{
		Invalid = 0,        // This must be a client (which doesn't use this state) or uninitialized.
		LoggingIn = 1,      // The client is currently logging in.
		Welcomed = 2,       // Told client to load map and will respond with SendJoin.
		ReceivedJoin = 3,   // NMT_Join received and a player controller has been created.
		CleanedUp = 4       // Cleanup has been called at least once, the connection is considered abandoned/terminated/gone.
	};
}

/**
 * @brief Represents a Globally Unique Identifier (GUID).
 */
struct FGuid
{
	unsigned int A;
	unsigned int B;
	unsigned int C;
	unsigned int D;

	bool operator==(const FGuid& other) const
	{
		return A == other.A && B == other.B && C == other.C && D == other.D;
	}
};

/**
 * @brief Defines types of travel/level transitions.
 */
enum ETravelType
{
	TRAVEL_Absolute, // Full URL path.
	TRAVEL_Partial,  // Relative to current package.
	TRAVEL_Relative, // Relative to current level.
	TRAVEL_MAX
};

/**
 * @brief Enumerates quick bar types in Fortnite.
 * Note: The original comment mentions this might not be fully correct due to Creative Quickbars,
 * but suitable for the intended usage.
 */
enum class EFortQuickBars : uint8_t
{
	Primary = 0,
	Secondary = 1,
	Max_None = 2, // Placeholder for max or none.
	EFortQuickBars_MAX = 3
};

/**
 * @brief Enumerates source types for item pickups.
 */
enum class EFortPickupSourceTypeFlag : uint8_t
{
	Other = 0,
	Player = 1,
	Destruction = 2,
	Container = 3,
	AI = 4,
	Tossed = 5,
	FloorLoot = 6,
	EFortPickupSourceTypeFlag_MAX = 7
};

/**
 * @brief Defines friendly fire settings.
 */
enum class EFriendlyFireType : uint8_t
{
	Off = 0,
	On = 1,
	EFriendlyFireType_MAX = 2
};

/**
 * @brief Enumerates results for structural grid queries in building systems.
 */
enum class EFortStructuralGridQueryResults : uint8_t
{
	CanAdd = 0,
	ExistingActor = 1,
	Obstructed = 2,
	NoStructuralSupport = 3,
	InvalidActor = 4,
	ReachedLimit = 5,
	NoEditPermission = 6,
	PatternNotPermittedByLayoutRequirement = 7,
	ResourceTypeNotPermittedByLayoutRequirement = 8,
	BuildingAtRequirementsDisabled = 9,
	BuildingOtherThanRequirementsDisabled = 10,
	EFortStructuralGridQueryResults_MAX = 11
};

/**
 * @brief Enumerates sources from which pickups can spawn.
 */
enum class EFortPickupSpawnSource : uint8_t
{
	Unset = 0,
	PlayerElimination = 1,
	Chest = 2,
	SupplyDrop = 3,
	AmmoBox = 4,
	EFortPickupSpawnSource_MAX = 5
};

/**
 * @brief Defines flags for Fast Array Serializer delta tracking.
 * Used for optimizing network replication of arrays by only sending changed elements.
 */
enum class EFastArraySerializerDeltaFlags : uint8_t
{
	None = 0,                               // No flags.
	HasBeenSerialized = 1 << 0,             // Set when serialization at least once (i.e., this struct has been written or read).
	HasDeltaBeenRequested = 1 << 1,         // Set if users requested Delta Serialization for this struct.
	IsUsingDeltaSerialization = 1 << 2,     // This will remain unset until we've serialized at least once.
											// At that point, this will be set if delta serialization was requested and we support it.
};

/**
 * @brief Defines the replication policy for gameplay abilities.
 */
enum class EGameplayAbilityReplicationPolicy : uint8_t
{
	ReplicateNo = 0,    // Do not replicate this ability.
	ReplicateYes = 1,   // Replicate this ability.
	EGameplayAbilityReplicationPolicy_MAX = 2
};

/**
 * @brief Enumerates different types of building structures.
 */
enum class EFortBuildingType : uint8_t
{
	Wall = 0,
	Floor = 1,
	Corner = 2,
	Deco = 3,
	Prop = 4,
	Stairs = 5,
	Roof = 6,
	Pillar = 7,
	SpawnedItem = 8,
	Container = 9,
	Trap = 10,
	GenericCenterCellActor = 11,
	None = 12,
	EFortBuildingType_MAX = 13
};

/**
 * @brief Defines flags for channel creation.
 */
enum class EChannelCreateFlags : uint32_t
{
	None = (1 << 0),
	OpenedLocally = (1 << 1)
};

/**
 * @brief A filter for querying building grid actors.
 */
struct FBuildingGridActorFilter
{
	bool bIncludeWalls;         // (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool bIncludeFloors;        // (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool bIncludeFloorInTop;    // (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool bIncludeCenterCell;    // (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

/**
 * @brief Represents an index within a building support cell grid.
 */
struct FBuildingSupportCellIndex
{
	int X; // (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int Y; // (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	int Z; // (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	bool operator==(const FBuildingSupportCellIndex& A) const
	{
		return X == A.X && Y == A.Y && Z == A.Z;
	}
};

/**
 * @brief Enumerates structural floor positions.
 */
enum class EStructuralFloorPosition : uint8_t
{
	Top = 0,
	Bottom = 1,
	EStructuralFloorPosition_MAX = 2
};

// Enum FortniteGame.EStructuralWallPosition
/**
 * @brief Enumerates structural wall positions.
 */
enum class EStructuralWallPosition : uint8_t
{
	Left = 0,
	Right = 1,
	Front = 2,
	Back = 3,
	EStructuralWallPosition_MAX = 4
};

/**
 * @brief Represents a duration of time in ticks.
 * A tick is typically 100 nanoseconds.
 */
struct FTimespan
{
	int Ticks;
};

/**
 * @brief Utility function to get a pointer to an object at a specific offset from an instance.
 * Useful for accessing members of C++ objects when their full definition might not be known
 * or when working with raw memory addresses (e.g., in game hacking/modding contexts).
 * @tparam T The type of the object to retrieve.
 * @param Instance A pointer to the base instance.
 * @param Offset The byte offset from the instance's base address.
 * @return A pointer to the object at the specified offset.
 */
template <typename T>
static T* GetFromOffset(void* Instance, int Offset)
{
	// Cast the void* instance to a __int64 to perform pointer arithmetic,
	// then add the offset, and finally cast back to T*.
	return reinterpret_cast<T*>(reinterpret_cast<__int64>(Instance) + Offset);
}