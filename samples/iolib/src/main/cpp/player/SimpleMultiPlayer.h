/*
 * Copyright 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _PLAYER_SIMIPLEMULTIPLAYER_H_
#define _PLAYER_SIMIPLEMULTIPLAYER_H_

#include <vector>

#include <oboe/Oboe.h>

#include "OneShotSampleSource.h"
#include "SampleBuffer.h"

namespace iolib {

typedef unsigned char byte;     // an 8-bit unsigned value

/**
 * A simple streaming player for multiple SampleBuffers.
 */
class SimpleMultiPlayer : public oboe::AudioStreamCallback  {
public:
    SimpleMultiPlayer();

    // Inherited from oboe::AudioStreamCallback
    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *oboeStream, void *audioData,
            int32_t numFrames) override;
    virtual void onErrorAfterClose(oboe::AudioStream *oboeStream, oboe::Result error) override;
    virtual void onErrorBeforeClose(oboe::AudioStream * oboeStream, oboe::Result error) override;

    void setupAudioStream(int32_t channelCount, int32_t sampleRate);
    void teardownAudioStream();

    bool openStream();

    // Wave Sample Loading...
    void allocSampleData(int32_t numSampleBuffers);
    void loadSampleDataFromAsset(byte* dataBytes, int32_t dataLen, int32_t index);
    void unloadSampleData();

    void triggerDown(int32_t index);
    void triggerUp(int32_t index);

    void resetAll();

    bool getOutputReset() { return mOutputReset; }
    void clearOutputReset() { mOutputReset = false; }

private:
    // Oboe Audio Stream
    oboe::ManagedStream mAudioStream;

    // Audio attributs
    int32_t mChannelCount;
    int32_t mSampleRate;

    // Sample Data
    int32_t mNumSampleBuffers;
    std::vector<SampleBuffer*> mSampleBuffers;
    std::vector<OneShotSampleSource*>   mSampleSources;

    bool    mOutputReset;
};

}
#endif //_PLAYER_SIMIPLEMULTIPLAYER_H_
