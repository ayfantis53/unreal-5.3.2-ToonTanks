// **************************************************************************** //
// ******************** Unreal Engine version 5.3.2 *************************** //
// Toon Tanks ***************************************************************** //
// ----------																	//
// Developed by Andrew Yfantis.													//
// https://github.com/ayfantis53												//
//																				//
// 2025																			//
// **************************************************************************** //

#include "FX/TT_Camera_shake_death.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(spawn_death_shake_test, "UEUnitTests.FX.DeathShake.SpawnDeathShake", 
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

auto spawn_death_shake_test::RunTest(const FString& Parameters) -> bool
{
    //// INITIALIZE ////

    // Create a new UTT_Camera_shake_death instance.
    UTT_Camera_shake_death* shake = NewObject<UTT_Camera_shake_death>();

    //// TEST ////

    // Verify the values.
    TestEqual("OscillationDuration correct",            shake->OscillationDuration,            0.35f);
    TestEqual("OscillationBlendInTime correct",         shake->OscillationBlendInTime,         0.10f);
    TestEqual("OscillationBlendOutTime correct",        shake->OscillationBlendOutTime,        0.10f);

    TestEqual("LocOscillation.X.Amplitude correct",     shake->LocOscillation.X.Amplitude,     50.0f);
    TestEqual("LocOscillation.X.Frequency  correct",    shake->LocOscillation.X.Frequency ,    20.0f);
    TestEqual("LocOscillation.X.InitialOffset correct", shake->LocOscillation.X.InitialOffset, EInitialOscillatorOffset::EOO_OffsetRandom );
    TestEqual("LocOscillation.X.Waveform correct",      shake->LocOscillation.X.Waveform,      EOscillatorWaveform::SineWave);
    
    TestEqual("LocOscillation.Y.Amplitude correct",     shake->LocOscillation.Y.Amplitude,     50.0f);
    TestEqual("LocOscillation.Y.Frequency correct",     shake->LocOscillation.Y.Frequency,     20.0f);
    TestEqual("LocOscillation.Y.InitialOffset correct", shake->LocOscillation.Y.InitialOffset, EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("LocOscillation.Y.Waveform correct",      shake->LocOscillation.Y.Waveform,      EOscillatorWaveform::SineWave);

    TestEqual("LocOscillation.Z.Amplitude correct",     shake->LocOscillation.Z.Amplitude,     50.0f);
    TestEqual("LocOscillation.Z.Frequency  correct",    shake->LocOscillation.Z.Frequency ,    0.0f );
    TestEqual("LocOscillation.Z.InitialOffset correct", shake->LocOscillation.Z.InitialOffset, EInitialOscillatorOffset::EOO_OffsetRandom);
    TestEqual("LocOscillation.Z.Waveform correct",      shake->LocOscillation.Z.Waveform,      EOscillatorWaveform::SineWave);

    //// FINISH ////
    
    // Clean up.
    shake->ConditionalBeginDestroy();
    // Finish test.
    return true;
}