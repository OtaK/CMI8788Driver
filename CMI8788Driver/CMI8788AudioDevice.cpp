#include "CMI8788Driver.h"

//! @class CMI8788AudioDevice
OSDefineMetaClassAndStructors(CMI8788AudioDevice, IOAudioDevice);

bool CMI8788AudioDevice::init(OSDictionary *propTable)
{
    bool result = super::init(propTable);
    return result;
}

void CMI8788AudioDevice::free()
{
    super::free();
}

bool CMI8788AudioDevice::attach(IOService *provider)
{
    bool result = super::attach(provider);
    return result;
}

void CMI8788AudioDevice::detach(IOService *provider)
{
    super::detach(provider);
}

bool CMI8788AudioDevice::initHardware(IOService *provider)
{
    bool result = true;
    IOLog("CMI8788AudioDevice[%p]::initHardware[%p]\n", this, provider);
    if (!super::initHardware(provider)) result = false;
    
    if (result)
    {
        this->pciCard = OSDynamicCast(IOPCIDevice, provider);
        if ((result = (bool)this->pciCard))
        {
            this->deviceMap = this->pciCard->mapDeviceMemoryWithRegister(kIOPCIConfigBaseAddress0);
            if ((result = (bool)this->deviceMap))
            {
                this->deviceRegisters = (CMI8788DeviceRegisters*)this->deviceMap->getVirtualAddress();
                if ((result = (bool)this->deviceRegisters))
                {
                    this->pciCard->setMemoryEnable(true);
                    
                    this->setDeviceName("C-Media CMI8788 PCI Card");
                    this->setDeviceShortName("CMI8788");
                    this->setManufacturerName("C-Media");
                    result = this->createAudioEngine();
                }
            }
        }
    }      
    
    if (!result && this->deviceMap)
    {
        this->deviceMap->release();
        this->deviceMap = NULL;
    }
    
    return result;
}

bool CMI8788AudioDevice::createAudioEngine()
{
    bool result = true;
    CMI8788AudioEngine *audioEngine = NULL;
    // TODO make and init the IOAudioControl subclasses
    
    audioEngine = new CMI8788AudioEngine();
    if ((result = (bool)audioEngine) && (result = audioEngine->init(this->deviceRegisters)))
    {
        // init the IOAudioControl stuff
        
        this->activateAudioEngine(audioEngine);
    }
    
    if (audioEngine) audioEngine->release();
    
    return result;
}

IOService* CMI8788AudioDevice::probe(IOService *provider, SInt32 *score)
{
    return super::probe(provider, score);
}

void CMI8788AudioDevice::stop(IOService *provider)
{
    super::stop(provider);
}

bool CMI8788AudioDevice::open(IOService *forClient, IOOptionBits options, void *arg)
{
    bool result = super::open(forClient);
    return result;
}

