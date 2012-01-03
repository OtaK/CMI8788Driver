#ifndef _CMI8788CTL_H
#define _CMI8788CTL_H

#include <IOKit/audio/IOAudioToggleControl.h>
#include <IOKit/audio/IOAudioLevelControl.h>
#include <IOKit/audio/IOAudioSelectorControl.h>

////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788InputMute @interface
class CMI8788InputMute
{
public:
    static IOAudioToggleControl* init();
};
// ENDCLASS

//! @class CMI8788InputMute @interface
class CMI8788OutputMute
{
public:
    static IOAudioToggleControl* init();
};
// ENDCLASS

////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788LeftVolume @interface
class CMI8788LeftVolume
{
public:
    static IOAudioLevelControl* init();
};
// ENDCLASS

//! @class CMI8788RightVolume @interface
class CMI8788RightVolume
{
public:
    static IOAudioLevelControl* init();
};
// ENDCLASS

////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788InputGain @interface
class CMI8788InputGain
{
public:
    static IOAudioLevelControl* init();    
};
// ENDCLASS

////////////////////////////////////////////////////////////////////////////////

#endif
