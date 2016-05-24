#pragma once
//------------------------------------------------------------------------------
/**
    @class z1013_video
    @brief Z1013 video decoding hardware
*/
#include "core/common.h"
#include "roms/roms.h"

namespace yakc {

class z1013_video {
public:
    /// 1Kbyte video memory
    ubyte irm[0x400];

    /// initialize the video hardware
    void init();
    /// reset the video hardware
    void reset();
    /// decode an entire frame into LinearBuffer
    void decode();

    /// decoded linear RGBA8 video buffer
    uint32_t LinearBuffer[256*256];
};

//------------------------------------------------------------------------------
inline void
z1013_video::init() {
    clear(this->irm, sizeof(this->irm));
}

//------------------------------------------------------------------------------
inline void
z1013_video::reset() {
    // FIXME
}

//------------------------------------------------------------------------------
inline void
z1013_video::decode() {
    uint32_t* dst = LinearBuffer;
    for (int y = 0; y < 32; y++) {
        for (int py = 0; py < 8; py++) {
            for (int x = 0; x < 32; x++) {
                ubyte ascii = this->irm[(y<<5) + x];
                ubyte bits = dump_z1013_font[(ascii<<3)|py];
                for (int px = 7; px >=0; px--) {
                    *dst++ = bits & (1<<px) ? 0xFFFFFFFF : 0xFF000000;
                }
            }
        }
    }
}

} // namespace yakc