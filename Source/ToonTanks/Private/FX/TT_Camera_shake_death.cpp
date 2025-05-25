// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "FX/TT_Camera_shake_death.h"


UTT_Camera_shake_death::UTT_Camera_shake_death()
{
	OscillationDuration     	   = 0.35f;
	OscillationBlendInTime  	   = 0.1f;
	OscillationBlendOutTime 	   = 0.1f;

	// LocOscillation Values.
	LocOscillation.X.Amplitude     = 50.f;
	LocOscillation.X.Frequency     = 20.f;
	LocOscillation.X.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	LocOscillation.X.Waveform      = EOscillatorWaveform::SineWave;

	LocOscillation.Y.Amplitude     = 50.f;
	LocOscillation.Y.Frequency     = 20.f;
	LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	LocOscillation.Y.Waveform      = EOscillatorWaveform::SineWave;

	LocOscillation.Z.Amplitude     = 50.f;
	LocOscillation.Z.Frequency     = 0.0f;
	LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	LocOscillation.Z.Waveform      = EOscillatorWaveform::SineWave;
}
