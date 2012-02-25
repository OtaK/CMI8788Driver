#include "CMI8788AudioDevice.h"
#include "CMI8788AudioEngine.h"
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
                this->deviceInfo.registers.cs4398_regs = (UInt8*)this->deviceInfo.deviceMap->getVirtualAddress();
                if ((result = (bool)this->deviceInfo.registers.cs4398_regs))
                {
                    this->deviceInfo.pciCard->setMemoryEnable(true);
                    
                    this->setDeviceName("C-Media CMI8788 PCI Card");
                    this->setDeviceShortName("CMI8788");
                    this->setManufacturerName("C-Media");
                    //! @todo special CMI8788 init code here
                    /* set CPEN (control port mode) and power down */
                    this->writeUInt8(this->deviceInfo.registers.cs4398_regs[7], CS4398_CPEN | CS4398_PDN);
                    //this->writeUInt8(this->deviceInfo.registers.cs4362a_regs[0x01], CS4392A_PDN | CS4392A_CPEN);
                    // now configure the chip
                    /*
                    this->writeUInt8(this->deviceInfo.registers.cs4398_regs[2], data->cs4398_regs[2]);
                    this->writeUInt8(chip, 3, CS4398_ATAPI_B_R | CS4398_ATAPI_A_L);
                    this->writeUInt8(chip, 4, data->cs4398_regs[4]);
                    this->writeUInt8(chip, 5, data->cs4398_regs[5]);
                    this->writeUInt8(chip, 6, data->cs4398_regs[6]);
                    this->writeUInt8(chip, 7, data->cs4398_regs[7]);
                    */
                    
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
    
    if ((result = (bool)audioEngine) && (result = audioEngine->init(&this->deviceInfo.registers)))
    {
        // Output mute
        if ((result = (bool)(tmpCtrl = CMI8788OutputMute::init())))
        {
            tmpCtrl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)this->outputMuteChangeHandler, this);
            audioEngine->addDefaultAudioControl(tmpCtrl);
            tmpCtrl->release();
            
            // Input mute
            if ((result = (bool)(tmpCtrl = CMI8788InputMute::init())))
            {
                tmpCtrl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)this->inputMuteChangeHandler, this);
                audioEngine->addDefaultAudioControl(tmpCtrl);
                tmpCtrl->release();
                
                // Left Volume
                if ((result = (bool)(tmpCtrl = CMI8788LeftVolume::init())))
                {
                    tmpCtrl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)this->volumeChangeHandler, this);
                    audioEngine->addDefaultAudioControl(tmpCtrl);
                    tmpCtrl->release();
                        
                    // Right Volume
                    if ((result = (bool)(tmpCtrl = CMI8788RightVolume::init())))
                    {
                        tmpCtrl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)this->volumeChangeHandler, this);
                        audioEngine->addDefaultAudioControl(tmpCtrl);
                        tmpCtrl->release();
                                
                        // Input Gain
                        if ((result = (bool)(tmpCtrl = CMI8788InputGain::init())))
                        {
                            tmpCtrl->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)this->gainChangeHandler, this);
                            audioEngine->addDefaultAudioControl(tmpCtrl);
                            tmpCtrl->release();
                                        
                            this->activateAudioEngine(audioEngine);
                        }
                    }
                }
            }
        }
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

UInt8 CMI8788AudioDevice::readUInt8(UInt16 reg)
{
	return this->deviceInfo.pciCard->ioRead8(reg, this->deviceInfo.deviceMap);
}

void CMI8788AudioDevice::writeUInt8(UInt16 reg, UInt8 value)
{
	this->deviceInfo.pciCard->ioWrite8(reg, value, this->deviceInfo.deviceMap);
}

void CMI8788AudioDevice::setUInt8Bit(UInt16 reg, UInt8 bit)
{
	this->deviceInfo.pciCard->ioWrite8(reg, this->deviceInfo.pciCard->ioRead8(reg, this->deviceInfo.deviceMap) | bit, this->deviceInfo.deviceMap);
}

void CMI8788AudioDevice::clearUInt8Bit(UInt16 reg, UInt8 bit)
{
	this->deviceInfo.pciCard->ioWrite8(reg, this->deviceInfo.pciCard->ioRead8(reg, this->deviceInfo.deviceMap) & ~bit, this->deviceInfo.deviceMap);
}

UInt16 CMI8788AudioDevice::readUInt16(UInt16 reg)
{
	return this->deviceInfo.pciCard->ioRead16(reg, this->deviceInfo.deviceMap);
}

void CMI8788AudioDevice::writeUInt16(UInt16 reg, UInt16 value)
{
	this->deviceInfo.pciCard->ioWrite16(reg, value, this->deviceInfo.deviceMap);
}

UInt32 CMI8788AudioDevice::readUInt32(UInt16 reg)
{
	return this->deviceInfo.pciCard->ioRead32(reg, this->deviceInfo.deviceMap);
}

void CMI8788AudioDevice::writeUInt32(UInt16 reg, UInt32 value)
{
	this->deviceInfo.pciCard->ioWrite32(reg, value, this->deviceInfo.deviceMap);
}

void CMI8788AudioDevice::setUInt32Bit(UInt16 reg, UInt32 bit)
{
	this->deviceInfo.pciCard->ioWrite32(reg, this->deviceInfo.pciCard->ioRead32(reg, this->deviceInfo.deviceMap) | bit, this->deviceInfo.deviceMap);
}

void CMI8788AudioDevice::clearUInt32Bit(UInt16 reg, UInt32 bit)
{
	this->deviceInfo.pciCard->ioWrite32(reg, this->deviceInfo.pciCard->ioRead32(reg, this->deviceInfo.deviceMap) & ~bit, this->deviceInfo.deviceMap);
}
