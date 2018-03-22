// Harrison McGuire
// UE4 Version 4.19
// https://github.com/Harrison1/unrealcpp
// https://severallevels.io
// https://harrisonmcguire.com

// Helpful Links
// http://api.unrealengine.com/INT/API/Runtime/Engine/Camera/UCameraShake/index.html

#include "MyCameraShake.h"

// Sets default values
UMyCameraShake::UMyCameraShake()
{
    OscillationDuration = 2.0f;
    OscillationBlendInTime = 0.1f;
    OscillationBlendOutTime = 0.2f;
    RotOscillation.Pitch.Amplitude = 10.0f;
    RotOscillation.Pitch.Frequency = 10.0f;
}


