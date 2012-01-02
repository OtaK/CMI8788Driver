#ifndef _CMI8788CTL_H
#define _CMI8788CTL_H

#include <IOKit/audio/IOAudioControl.h>

///////////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788InputMute
class CMI8788InputMute : public IOAudioControl
{
    OSDeclareDefaultStructors(CMI8788InputMute);
private:
    typedef IOAudioControl super;
    
public:
    
};
// ENDCLASS

//! @class CMI8788InputMute
class CMI8788OutputMute : public IOAudioControl
{
    OSDeclareDefaultStructors(CMI8788OutputMute);
private:
    typedef IOAudioControl super;
    
public:
    
};
// ENDCLASS

///////////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788LeftVolume
class CMI8788LeftVolume : public IOAudioControl
{
    OSDeclareDefaultStructors(CMI8788LeftVolume);
private:
    typedef IOAudioControl super;
    
public:
    
};
// ENDCLASS

//! @class CMI8788RightVolume
class CMI8788RightVolume : public IOAudioControl
{
    OSDeclareDefaultStructors(CMI8788RightVolume);
private:
    typedef IOAudioControl super;
    
public:
    
};
// ENDCLASS

///////////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788InputGain
class CMI8788InputGain : public IOAudioControl
{
    OSDeclareDefaultStructors(CMI8788InputGain);
private:
    typedef IOAudioControl super;
    
public:
    
};
// ENDCLASS



#endif
