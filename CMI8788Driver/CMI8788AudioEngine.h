#ifndef CMI8788Driver_CMI8788AudioEngine_h
#define CMI8788Driver_CMI8788AudioEngine_h

#include "CMI8788Driver.h"

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
    XonarD1Regs *registers;
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
    bool init(XonarD1Regs *registers);
    void free();
    void stop(IOService *provider);
    bool initHardware(IOService *provider);
    static void interruptHandler(OSObject *owner, IOInterruptEventSource *source, int count);
    static bool interruptFilter(OSObject *owner, IOFilterInterruptEventSource *source);
    void filterInterrupt(int index);
};
// ENDCLASS

#endif
