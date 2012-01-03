#include "CMI8788AudioControls.h"

//! @class CMI8788LeftVolume
IOAudioLevelControl* CMI8788LeftVolume::init()
{
    return IOAudioLevelControl::createVolumeControl(
        50000, 0, 65535, 0, (-22 << 16) + (32768), 
        kIOAudioControlChannelIDDefaultLeft, 0, kIOAudioControlUsageOutput
    );
}

//! @class CMI8788RightVolume
IOAudioLevelControl* CMI8788RightVolume::init()
{
    return IOAudioLevelControl::createVolumeControl(
        50000, 0, 65535, 0, (-22 << 16) + (32768), 
        kIOAudioControlChannelIDDefaultRight, 0, kIOAudioControlUsageOutput
    );
}

//! @class CMI8788InputGain
IOAudioLevelControl* CMI8788InputGain::init()
{
    return IOAudioLevelControl::createVolumeControl(
        65535, 0, 65535, 0, (22 << 16) + (32768), 
        kIOAudioControlChannelIDAll, 0, kIOAudioControlUsageOutput
    );
}