// *************************************************************************** //
// ******************** Unreal Engine version 5.3.2 ************************** //
// Toon Tanks **************************************************************** //
// ----------  																   //
// Developed by Andrew Yfantis. 											   //
// https://github.com/ayfantis53 											   //
//             																   //
// 2025 																	   //
// *************************************************************************** //

#include "FX/TT_Camera_shake.h"


UTT_Camera_shake::UTT_Camera_shake()
{
	OscillationDuration            = 0.25f;
	OscillationBlendInTime         = 0.05f;
	OscillationBlendOutTime        = 0.05f;

	// LocOscillation Values.
	LocOscillation.X.Amplitude     = 10.f;
	LocOscillation.X.Frequency     = 10.f;
	LocOscillation.X.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	LocOscillation.X.Waveform      = EOscillatorWaveform::SineWave;

	LocOscillation.Y.Amplitude     = 10.f;
	LocOscillation.Y.Frequency     = 10.f;
	LocOscillation.Y.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	LocOscillation.Y.Waveform      = EOscillatorWaveform::SineWave;

	LocOscillation.Z.Amplitude     = 10.f;
	LocOscillation.Z.Frequency     = 10.f;
	LocOscillation.Z.InitialOffset = EInitialOscillatorOffset::EOO_OffsetRandom;
	LocOscillation.Z.Waveform      = EOscillatorWaveform::SineWave;
}
