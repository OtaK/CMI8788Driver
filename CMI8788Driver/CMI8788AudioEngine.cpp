#include "CMI8788Driver.h"

//! @class CMI8788AudioEngine 
OSDefineMetaClassAndStructors(CMI8788AudioEngine, IOAudioEngine);

bool CMI8788AudioEngine::init(CMI8788Registers *registers)
{
    bool result = (bool)registers;
    
    IOLog("CMI8788AudioEngine[%p]::init(%p)\n", this, registers);
    
    if (super::init(NULL) && result)
    {
        this->registers = registers;
        this->currentSampleRate = 0;
        this->currentResolution = 0;
    }
    else result = false;
    
    return result;
}

bool CMI8788AudioEngine::initHardware(IOService *provider)
{
    bool result = true;
    IOAudioSampleRate initialSampleRate;
    IOAudioStream *tmpStream;
    
    initialSampleRate.fraction = 0;
    
    
    return result;
}

IOAudioStream* CMI8788AudioEngine::createNewAudioStream(IOAudioStreamDirection direction, void *sampleBuffer, UInt32 sampleBufferSize, UInt32 channel)
{
    IOAudioStream *audioStream = new IOAudioStream();
    if (audioStream) 
    {
        if (!audioStream->initWithAudioEngine(this, direction, 1)) 
            audioStream->release();
        else 
        {
            IOAudioSampleRate rate;
            IOAudioStreamFormat format = {
                2,												// num channels
                kIOAudioStreamSampleFormatLinearPCM,			// sample format
                kIOAudioStreamNumericRepresentationSignedInt,	// numeric format
                16,										// bit depth
                16,										// bit width
                kIOAudioStreamAlignmentHighByte,				// high byte aligned - unused because bit depth == bit width
                kIOAudioStreamByteOrderBigEndian,				// big endian
                true,											// format is mixable
                channel											// number of channel
            };
            
            // As part of creating a new IOAudioStream, its sample buffer needs to be set
            // It will automatically create a mix buffer should it be needed
            audioStream->setSampleBuffer(sampleBuffer, sampleBufferSize);
            
            // This device only allows a single format and a choice of 2 different sample rates
            rate.fraction = 0;
            rate.whole = 44100;
			this->currentSampleRate = 44100;
			
            audioStream->addAvailableFormat(&format, &rate, &rate);
            rate.whole = 48000;
            audioStream->addAvailableFormat(&format, &rate, &rate);
			rate.whole = 96000;
            audioStream->addAvailableFormat(&format, &rate, &rate);
            rate.whole = 192000;
            audioStream->addAvailableFormat(&format, &rate, &rate);
            
			// Finally, the IOAudioStream's current format needs to be indicated
            audioStream->setFormat(&format);
        }
    }
    return audioStream;
}


UInt32 CMI8788AudioEngine::getCurrentSampleFrame()
{
    return 0;
}
