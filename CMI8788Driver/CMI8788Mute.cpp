#include "CMI8788AudioControls.h"

//! @class CMI8788InputMute
IOAudioToggleControl* CMI8788InputMute::init()
{
    return IOAudioToggleControl::createMuteControl(false, kIOAudioControlChannelIDAll, 0, kIOAudioControlUsageInput);
}

//! @class CMI8788OutputMute
IOAudioToggleControl* CMI8788OutputMute::init()
{
    return IOAudioToggleControl::createMuteControl(false, kIOAudioControlChannelIDAll, 0, kIOAudioControlUsageOutput);
}