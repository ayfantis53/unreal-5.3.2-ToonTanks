// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //

#include "FX/TT_Camera_shake.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_camera_shake_test, "UEUnitTests.FX.CameraShake.SpawnCameraShake", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_camera_shake_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////
    
    // Create a new UTT_Camera_shake instance.
    UTT_Camera_shake* shake = NewObject<UTT_Camera_shake>();

    //// TEST ////

    // Verify the values.
    TestEqual("OscillationDuration correct",            shake->OscillationDuration,         0.25f);
    TestEqual("OscillationBlendInTime correct",         shake->OscillationBlendInTime,      0.05f);
    TestEqual("OscillationBlendOutTime correct",        shake->OscillationBlendOutTime,     0.05f);

    TestEqual("LocOscillation.X.Amplitude correct",     shake->LocOscillation.X.Amplitude,  10.0f);
    TestEqual("LocOscillation.X.Frequency  correct",    shake->LocOscillation.X.Frequency , 10.0f);
    TestEqual("LocOscillation.X.InitialOffset correct", shake->LocOscillation.X.InitialOffset, EInitialOscillatorOffset::EOO_OffsetRandom );
    TestEqual("LocOscillation.X.Waveform correct",      shake->LocOscillation.X.Waveform,      EOscillatorWaveform::SineWave);
    
    TestEqual("LocOscillation.Y.Amplitude correct",     shake->LocOscillation.Y.Amplitude, 10.0f);
    TestEqual("LocOscillation.Y.Frequency correct",     shake->LocOscillation.Y.Frequency, 10.0f);
    TestEqual("LocOscillation.Y.InitialOffset correct", shake->LocOscillation.Y.InitialOffset, EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("LocOscillation.Y.Waveform correct",      shake->LocOscillation.Y.Waveform,      EOscillatorWaveform::SineWave);

    TestEqual("LocOscillation.Z.Amplitude correct",     shake->LocOscillation.Z.Amplitude,  10.0f);
    TestEqual("LocOscillation.Z.Frequency  correct",    shake->LocOscillation.Z.Frequency , 10.0f);
    TestEqual("LocOscillation.Z.InitialOffset correct", shake->LocOscillation.Z.InitialOffset, EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("LocOscillation.Z.Waveform correct",      shake->LocOscillation.Z.Waveform,      EOscillatorWaveform::SineWave);

    //// FINISH ////

    // Clean up.
    shake->ConditionalBeginDestroy();
    // Finish test.
    return true;
}