#ifndef _CMI8788_H
#define _CMI8788_H

#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <IOKit/IOFilterInterruptEventSource.h>
#include <IOKit/audio/IOAudioDevice.h>
#include <IOKit/audio/IOAudioEngine.h>
#include <IOKit/pci/IOPCIDevice.h>

////////////////////////////////////////////////////////////////////////////////

// Forward decl
class CMI8788AudioEngine;
class CMI8788AudioDevice;

typedef struct CMI8788Registers {
    
} CMI8788Registers;

// Device registers datastruct decl
typedef struct CMI8788DeviceInfo {
    CMI8788Registers *registers;
    IOMemoryMap *deviceMap;
    IOPCIDevice *pciCard;
} CMI8788DeviceInfo;

// Bitdepths & freqs definition
enum CMI8788BitDepths {
    b16 = 16,
    b24 = 24
};

enum CMI8788Freqs {
    k44 = 44100,
    k48 = 48000,
    k96 = 96000,
    k192 = 192000
};

////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788AudioEngine @interface
class CMI8788AudioEngine : public IOAudioEngine 
{
    OSDeclareDefaultStructors(CMI8788AudioEngine);
private:
    //! @typedef
    typedef IOAudioEngine super;
    
    //! @property
    UInt32 currentSampleRate;
    UInt32 currentResolution;
    CMI8788Registers *registers;
    SInt16	*outputBuffer;
    SInt16	*inputBuffer;
	IOPhysicalAddress physicalAddressOutput;
	IOPhysicalAddress physicalAddressInput;
    IOFilterInterruptEventSource *interruptEventSource;
    
    //! @method
    IOAudioStream *createNewAudioStream(IOAudioStreamDirection direction, void *sampleBuffer, UInt32 sampleBufferSize, UInt32 channel);
    
public:
    //! @method
    virtual UInt32 getCurrentSampleFrame();
    bool init(CMI8788Registers *registers);
    void free();
    void stop(IOService *provider);
    bool initHardware(IOService *provider);
    static void interruptHandler(OSObject *owner, IOInterruptEventSource *source, int count);
    static bool interruptFilter(OSObject *owner, IOFilterInterruptEventSource *source);
    void filterInterrupt(int index);
};
// ENDCLASS

////////////////////////////////////////////////////////////////////////////////

#endif