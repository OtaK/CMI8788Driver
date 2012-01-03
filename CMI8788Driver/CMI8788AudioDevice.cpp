#include "CMI8788Driver.h"
#include "CMI8788AudioControls.h"

//! @class CMI8788AudioDevice
OSDefineMetaClassAndStructors(CMI8788AudioDevice, IOAudioDevice);

void CMI8788AudioDevice::free()
{
    IOLog("CMI8788AudioDevice[%p]::free\n", this);
    if (this->deviceInfo.deviceMap)
    {
        this->deviceInfo.deviceMap->release();
        this->deviceInfo.deviceMap = NULL;
    }
    if (this->deviceInfo.pciCard)
    {
        this->deviceInfo.pciCard->release();
        this->deviceInfo.pciCard = NULL;
    }
    if (this->deviceInfo.registers)
    {
        delete [] this->deviceInfo.registers;
        this->deviceInfo.registers = NULL;
    }
    // No need to destroy this->deviceInfo, it's in the heap, will be destroyed automatically
    super::free();
}

bool CMI8788AudioDevice::initHardware(IOService *provider)
{
    bool result = true;
    IOLog("CMI8788AudioDevice[%p]::initHardware[%p]\n", this, provider);
    if (!super::initHardware(provider)) result = false;
    
    if (result)
    {
        this->deviceInfo.pciCard = OSDynamicCast(IOPCIDevice, provider);
        if ((result = (bool)this->deviceInfo.pciCard))
        {
            this->deviceInfo.deviceMap = this->deviceInfo.pciCard->mapDeviceMemoryWithRegister(kIOPCIConfigBaseAddress0);
            if ((result = (bool)this->deviceInfo.deviceMap))
            {
                this->deviceInfo.pciCard->setMemoryEnable(false);
                this->deviceInfo.pciCard->setIOEnable(true);
                this->deviceInfo.pciCard->setBusMasterEnable(true);
                this->deviceInfo.registers = (CMI8788Registers*)this->deviceInfo.deviceMap->getVirtualAddress();
                if ((result = (bool)this->deviceInfo.deviceMap))
                {
                    this->deviceInfo.pciCard->setMemoryEnable(true);
                    
                    this->setDeviceName("C-Media CMI8788 PCI Card");
                    this->setDeviceShortName("CMI8788");
                    this->setManufacturerName("C-Media");
                    // TODO special CMI8788 init code here
                    result = this->createAudioEngine();
                }
            }
        }
    }      
    
    if (!result && this->deviceInfo.deviceMap)
    {
        this->deviceInfo.deviceMap->release();
        this->deviceInfo.deviceMap = NULL;
    }
    
    return result;
}

bool CMI8788AudioDevice::createAudioEngine()
{
    bool result = true;
    CMI8788AudioEngine *audioEngine = new CMI8788AudioEngine();
    IOAudioControl *tmpCtrl;
    
    IOLog("CMI8788AudioDevice[%p]::createAudioEngine()\n", this);
    
    if ((result = (bool)audioEngine) && (result = audioEngine->init(this->deviceInfo.registers)))
    {
        //! @todo Add checks for each tmpCtrl
        
        // Output mute
        tmpCtrl = CMI8788OutputMute::init();
        tmpCtrl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)this->outputMuteChangeHandler, this);
        audioEngine->addDefaultAudioControl(tmpCtrl);
        tmpCtrl->release();
        
        // Input mute
        tmpCtrl = CMI8788InputMute::init();
        tmpCtrl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)this->inputMuteChangeHandler, this);
        audioEngine->addDefaultAudioControl(tmpCtrl);
        tmpCtrl->release();
        
        // Left Volume
        tmpCtrl = CMI8788LeftVolume::init();
        tmpCtrl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)this->volumeChangeHandler, this);
        audioEngine->addDefaultAudioControl(tmpCtrl);
        tmpCtrl->release();
        
        // Right Volume
        tmpCtrl = CMI8788RightVolume::init();
        tmpCtrl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)this->volumeChangeHandler, this);
        audioEngine->addDefaultAudioControl(tmpCtrl);
        tmpCtrl->release();
        
        // Input Gain
        tmpCtrl = CMI8788InputGain::init();
        tmpCtrl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)this->gainChangeHandler, this);
        audioEngine->addDefaultAudioControl(tmpCtrl);
        tmpCtrl->release();
        
        this->activateAudioEngine(audioEngine);
    }
    
    if (audioEngine) audioEngine->release();
    
    return result;
}

IOReturn CMI8788AudioDevice::volumeChangeHandler(IOService *target, IOAudioControl *volumeControl, SInt32 oldValue, SInt32 newValue)
{
    IOReturn result = kIOReturnBadArgument;
    CMI8788AudioDevice *audioDevice;
    
    audioDevice = (CMI8788AudioDevice *)target;
    if (audioDevice) 
        result = audioDevice->volumeChanged(volumeControl, oldValue, newValue);
        
    return result;
}

IOReturn CMI8788AudioDevice::volumeChanged(IOAudioControl *volumeControl, SInt32 oldValue, SInt32 newValue)
{
    //! @todo implement changes
    return kIOReturnSuccess;
}

IOReturn CMI8788AudioDevice::outputMuteChangeHandler(IOService *target, IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue)
{
    IOReturn result = kIOReturnBadArgument;
    CMI8788AudioDevice *audioDevice;
    
    audioDevice = (CMI8788AudioDevice *)target;
    if (audioDevice) 
        result = audioDevice->outputMuteChanged(muteControl, oldValue, newValue);
    
	return result;
}

IOReturn CMI8788AudioDevice::outputMuteChanged(IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue)
{
    //! @todo implement changes
    return kIOReturnSuccess;
}

IOReturn CMI8788AudioDevice::gainChangeHandler(IOService *target, IOAudioControl *gainControl, SInt32 oldValue, SInt32 newValue)
{
    IOReturn result = kIOReturnBadArgument;
    CMI8788AudioDevice *audioDevice;
    
    audioDevice = (CMI8788AudioDevice *)target;
    if (audioDevice) {
        result = audioDevice->gainChanged(gainControl, oldValue, newValue);
    }
    
    return result;
}

IOReturn CMI8788AudioDevice::gainChanged(IOAudioControl *gainControl, SInt32 oldValue, SInt32 newValue)
{
    //! @todo implement changes
    return kIOReturnSuccess;
}

IOReturn CMI8788AudioDevice::inputMuteChangeHandler(IOService *target, IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue)
{
    IOReturn result = kIOReturnBadArgument;
    CMI8788AudioDevice *audioDevice;
    
    audioDevice = (CMI8788AudioDevice *)target;
    if (audioDevice) 
        result = audioDevice->inputMuteChanged(muteControl, oldValue, newValue);
    
    return result;
}

IOReturn CMI8788AudioDevice::inputMuteChanged(IOAudioControl *muteControl, SInt32 oldValue, SInt32 newValue)
{
    //! @todo implement changes
    return kIOReturnSuccess;
}
