#ifndef _CMI8788_H
#define _CMI8788_H

#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <IOKit/audio/IOAudioDevice.h>
#include <IOKit/audio/IOAudioEngine.h>
#include <IOKit/pci/IOPCIDevice.h>

///////////////////////////////////////////////////////////////////////////////////////

// Forward decl
class CMI8788AudioEngine;
class CMI8788AudioDevice;

// Device registers datastruct decl
typedef struct CMI8788DeviceRegisters {
    UInt32 r1;
    UInt32 r2;
} CMI8788DeviceRegisters;

///////////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788AudioDevice @interface
class CMI8788AudioDevice : public IOAudioDevice 
{
    OSDeclareDefaultStructors(CMI8788AudioDevice);
private:
    typedef IOAudioDevice super;
    // props
    IOPCIDevice *pciCard;
    IOMemoryMap *deviceMap;
    CMI8788DeviceRegisters *deviceRegisters;
    
    // methods
    bool createAudioEngine();
    
public:
    // methods
    bool init(OSDictionary *propTable);
    void free();
    bool attach(IOService *provider);
    void detach(IOService *provider);
    IOService* probe(IOService *provider, SInt32 *score);
    bool initHardware(IOService * provider);
    void stop(IOService *provider);
    bool open(IOService *forClient, IOOptionBits options = 0, void *arg = 0);
    
};
// ENDCLASS

///////////////////////////////////////////////////////////////////////////////////////

//! @class CMI8788AudioEngine @interface
class CMI8788AudioEngine : public IOAudioEngine 
{
    OSDeclareDefaultStructors(CMI8788AudioEngine);
private:
    typedef IOAudioEngine super;
    
public:
    UInt32 getCurrentSampleFrame();
    bool init(CMI8788DeviceRegisters *registers);
    
};
// ENDCLASS

///////////////////////////////////////////////////////////////////////////////////////

#endif