#ifndef _CMI8788_H
#define _CMI8788_H

#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <IOKit/IOFilterInterruptEventSource.h>
#include <IOKit/audio/IOAudioDevice.h>
#include <IOKit/audio/IOAudioEngine.h>
#include <IOKit/pci/IOPCIDevice.h>

#include "CMI8788Registers.h"

////////////////////////////////////////////////////////////////////////////////

// Device registers datastruct decl
typedef struct CMI8788DeviceInfo {
    XonarD1XRegs registers;
    IOMemoryMap *deviceMap;
    IOPCIDevice *pciCard;
} CMI8788DeviceInfo;

// Bitdepths & freqs definition
typedef struct CMI8788BitDepths {
    const static UInt8
    b16 = 16,
    b24 = 24;
} CMI8788BitDepths;

typedef struct CMI8788Freqs {
    const static UInt32
    k44 = 44100,
    k48 = 48000,
    k96 = 96000,
    k192 = 192000;
} CMI8788Freqs;


////////////////////////////////////////////////////////////////////////////////

#endif