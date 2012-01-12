#include "CMI8788AudioEngine.h"

#define INITIAL_SAMPLE_RATE	CMI8788Freqs::k44
#define NUM_SAMPLE_FRAMES	16384
#define NUM_CHANNELS		2
#define BIT_DEPTH			CMI8788BitDepths::b16

#define BUFFER_SIZE			(NUM_SAMPLE_FRAMES * NUM_CHANNELS * BIT_DEPTH / 8)

//! @class CMI8788AudioEngine 
OSDefineMetaClassAndStructors(CMI8788AudioEngine, IOAudioEngine);

bool CMI8788AudioEngine::init(UInt8 *registers)
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

void CMI8788AudioEngine::free()
{
    IOLog("CMI8788AudioEngine[%p]::free()\n", this);
    if (this->interruptEventSource)
    {
        this->interruptEventSource->disable();
        this->interruptEventSource->release();
        this->interruptEventSource = NULL;
    }
    if (this->outputBuffer)
    {
        //! @todo unalloc the buffer with the opposite way than the one used in initHardware
        outputBuffer = NULL; // memleak here
    }
    if (this->inputBuffer)
    {
        //! @todo unalloc the buffer with the opposite way than the one used in initHardware
        inputBuffer = NULL; // memleak here
    }
    
    super::free();
}

void CMI8788AudioEngine::stop(IOService *provider)
{
    if (this->interruptEventSource)
    {
        IOWorkLoop *wl = this->getWorkLoop();
        if (wl)
            wl->removeEventSource(this->interruptEventSource);
        this->interruptEventSource->release();
        this->interruptEventSource = NULL;
    }
    super::stop(provider);
}

bool CMI8788AudioEngine::initHardware(IOService *provider)
{
    bool result = true;
    IOAudioSampleRate initialSampleRate;
    IOAudioStream *tmpStream;
    IOWorkLoop *workLoop;
    
    initialSampleRate.fraction = 0;
    initialSampleRate.whole = CMI8788Freqs::k44;
    this->setDescription("CMI8788 driven by OtaK");
    this->setSampleRate(&initialSampleRate);
    this->setNumSampleFramesPerBuffer(NUM_SAMPLE_FRAMES);
    if ((result = (bool)(workLoop = this->getWorkLoop())))
    {
        this->interruptEventSource = IOFilterInterruptEventSource::filterInterruptEventSource(this, CMI8788AudioEngine::interruptHandler, CMI8788AudioEngine::interruptFilter, audioDevice->getProvider());
        if ((result = (bool)this->interruptEventSource))
        {
            this->interruptEventSource->enable();
            workLoop->addEventSource(this->interruptEventSource);
            //! @todo Allocate I/O buffers correct way (IOMallocContiguous deprecated)
            
            //! @todo create a new audio stream for each channel on the card
            tmpStream = this->createNewAudioStream(kIOAudioStreamDirectionOutput, this->outputBuffer, BUFFER_SIZE, 0);
            this->addAudioStream(tmpStream);
            tmpStream->release();
            
            tmpStream = this->createNewAudioStream(kIOAudioStreamDirectionInput, this->inputBuffer, BUFFER_SIZE, 1);
            this->addAudioStream(tmpStream);
            tmpStream->release();
            
            //! @todo and then write the addresses for each one in the card registers, for it to R/W in the buffers
        }
    }
    
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
                kIOAudioStreamNumericRepresentationSignedInt,	// numeric foÒrmat
                CMI8788BitDepths::b16,										// bit depth
                CMI8788BitDepths::b16,										// bit width
                kIOAudioStreamAlignmentHighByte,
                kIOAudioStreamByteOrderBigEndian,
                true,
                channel
            };
            
            // As part of creating a new IOAudioStream, its sample buffer needs to be set
            // It will automatically create a mix buffer should it be needed
            audioStream->setSampleBuffer(sampleBuffer, sampleBufferSize);
            
            rate.fraction = 0;
            rate.whole = CMI8788Freqs::k44;
			this->currentSampleRate = CMI8788Freqs::k44;
			
            audioStream->addAvailableFormat(&format, &rate, &rate); // 16b/44k
            if (direction == kIOAudioStreamDirectionOutput)
            {
                format.fBitDepth = format.fBitWidth = CMI8788BitDepths::b24;
                audioStream->addAvailableFormat(&format, &rate, &rate); // 24b/44k
                rate.whole = CMI8788Freqs::k48;
                audioStream->addAvailableFormat(&format, &rate, &rate); // 24b/48k
                format.fBitDepth = format.fBitWidth = CMI8788BitDepths::b16;
                audioStream->addAvailableFormat(&format, &rate, &rate); // 16b/48k
                rate.whole = CMI8788Freqs::k96;
                audioStream->addAvailableFormat(&format, &rate, &rate); // 16b/96k
                format.fBitDepth = format.fBitWidth = CMI8788BitDepths::b24;
                audioStream->addAvailableFormat(&format, &rate, &rate); // 24b/96k
                rate.whole = CMI8788Freqs::k192;
                audioStream->addAvailableFormat(&format, &rate, &rate); // 24b/192k
                format.fBitDepth = format.fBitWidth = CMI8788BitDepths::b16;
                audioStream->addAvailableFormat(&format, &rate, &rate); // 16b/192k
			}
            // Finally, the IOAudioStream's current format needs to be indicated
            audioStream->setFormat(&format);
        }
    }
    return audioStream;
}


UInt32 CMI8788AudioEngine::getCurrentSampleFrame()
{
    // not complete
    return NUM_SAMPLE_FRAMES;
}

void CMI8788AudioEngine::interruptHandler(OSObject *owner, IOInterruptEventSource *source, int count)
{
    return;
}

bool CMI8788AudioEngine::interruptFilter(OSObject *owner, IOFilterInterruptEventSource *source)
{
    CMI8788AudioEngine *audioEngine = OSDynamicCast(CMI8788AudioEngine, owner);
    if (audioEngine)
        audioEngine->filterInterrupt(source->getIntIndex());
    
    return false;
}

void CMI8788AudioEngine::filterInterrupt(int index)
{
    //! @todo write interrupt code to registers
    return;
}
