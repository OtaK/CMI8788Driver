#ifndef CMI8788Driver_CMI8788AudioDevice_h
#define CMI8788Driver_CMI8788AudioDevice_h

#include "CMI8788Driver.h"

//! @class CMI8788AudioDevice @interface
class CMI8788AudioDevice : public IOAudioDevice 
{
    OSDeclareDefaultStructors(CMI8788AudioDevice);
    friend class CMI8788AudioEngine;
private:
    //! @typedef
    typedef IOAudioDevice super;
    
    //! @property
    CMI8788DeviceInfo deviceInfo;
    
    //! @method
    bool createAudioEngine();
    
public:
    //! @method
    void free();
    virtual bool initHardware(IOService * provider);
    
    static IOReturn volumeChangeHandler(IOService *target, IOAudioControl *volumeControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn volumeChanged(IOAudioControl *volumeControl, SInt32 oldValue, SInt32 newValue);
    
    static IOReturn outputMuteChangeHandler(IOService *target, IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn outputMuteChanged(IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    
    static IOReturn gainChangeHandler(IOService *target, IOAudioControl *gainControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn gainChanged(IOAudioControl *gainControl, SInt32 oldValue, SInt32 newValue);
    
    static IOReturn inputMuteChangeHandler(IOService *target, IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    virtual IOReturn inputMuteChanged(IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue);
    
    virtual UInt8	readUInt8(UInt16 reg);
	virtual void	writeUInt8(UInt16 reg, UInt8 value);
	virtual void	clearUInt8Bit(UInt16 reg, UInt8 bit);
	virtual void	setUInt8Bit(UInt16 reg, UInt8 bit);
    
	virtual UInt16	readUInt16(UInt16 reg);
	virtual void	writeUInt16(UInt16 reg, UInt16 value);
    
	virtual UInt32	readUInt32(UInt16 reg);
	virtual void	writeUInt32(UInt16 reg, UInt32 value);
	virtual void	clearUInt32Bit(UInt16 reg, UInt32 bit);
	virtual void	setUInt32Bit(UInt16 reg, UInt32 bit);
    
};
// ENDCLASS


#endif
