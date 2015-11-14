#pragma once
//------------------------------------------------------------------------------
/**
    @class yakc::z80ctc
    @brief incomplete Z80 CTC emulation (only what's needed for KC85)
    
    CTC channels 0 and 1 seem to be triggered per video scanline,
    and channels 2 and 3 once per vertical refresh @50Hz 
    (see here: https://github.com/mamedev/mame/blob/dfa148ff8022e9f1a544c8603dd0e8c4aa469c1e/src/mame/machine/kc.cpp#L710)
*/
#include "yakc_core/common.h"
#include <stdio.h>

namespace yakc {

class z80ctc {
public:
    /// channels
    enum channel {
        CTC0 = 0,
        CTC1,
        CTC2,
        CTC3,
        
        num_channels,
    };

    /// pulse-callback for channels CTC0 to CTC3
    typedef void (*cb_pulse)(void* userdata, channel c);

    /// CTC channel mode bits
    enum mode_bits {
        INTERRUPT = (1<<7),         // 1: interrupt enabled, 0: interrupt disabled
        INTERRUPT_ENABLED = INTERRUPT,
        INTERRUPT_DISABLED = 0,

        MODE = (1<<6),              // 1: counter mode, 0: timer mode
        MODE_COUNTER = MODE,
        MODE_TIMER = 0,

        PRESCALER = (1<<5),         // 1: prescaler 256, 0: prescaler 16
        PRESCALER_256 = PRESCALER,
        PRESCALER_16 = 0,

        EDGE = (1<<4),              // 1: rising edge, 0: falling edge
        EDGE_RISING = EDGE,
        EDGE_FALLING = 0,

        TRIGGER = (1<<3),           // 1: CLK/TRG pulse starts timer, 0: automatic trigger when time constant is loaded
        TRIGGER_PULSE = TRIGGER,
        TRIGGER_AUTOMATIC = 0,

        CONSTANT_FOLLOWS = (1<<2),          // 1: time constant followes, 0: no time constant follows

        RESET = (1<<1),             // 1: software reset, 0: continued operation

        CONTROL = (1<<0),           // 1: control word, 0: vector
        CONTROL_WORD = CONTROL,
        CONTROL_VECTOR = 0,
    };

    /// channel state
    struct channel_state {
        uword mode = 0;                 // current mode bits
        uword constant = 0;             // the time constant
        uword counter = 0;              // current trigger-counter value
        bool waiting_for_trigger = false;
        int timer = 0;                  // timer cycle-counter
        bool timer_enabled = false;
    } channels[num_channels];
    ubyte interrupt_vector = 0;

    /// initialize the ctc
    void init(cb_pulse pulse_callback, void* userdata);
    /// reset the ctc
    void reset();
    /// update the CTC for a number of ticks, a tick is equal to a Z80 T-cycle
    void update(int ticks);
    /// trigger a channel (0 and 1 per scanline, 2 and 3 per 50Hz frame)
    void trigger(channel c);
    /// write value to channel
    void write(channel c, ubyte v);
    /// read value from channel
    ubyte read(channel c);

private:
    /// software-reset on a single channel
    void reset_channel(channel c);
    /// disable timer on channel
    void disable_timer(channel c);
    /// enable timer on channel
    void enable_timer(channel c);
    /// update timer on a channel
    void update_timer(channel c, int ticks);
    /// execute timer callback (interrupt and trigger callbacks)
    void timer_callback(channel c);

    void* userdata = nullptr;
    cb_pulse pulse_callback = nullptr;
};

//------------------------------------------------------------------------------
inline void
z80ctc::init(cb_pulse pulse_cb, void* ud) {
    pulse_callback = pulse_cb;
    userdata = ud;
    for (unsigned int i = 0; i < num_channels; i++) {
        channels[i] = channel_state();
    }
    interrupt_vector = 0;
}

//------------------------------------------------------------------------------
inline void
z80ctc::reset() {
    // FIXME: ???
    for (unsigned int i = 0; i < num_channels; i++) {
        channels[i] = channel_state();
    }
}

//------------------------------------------------------------------------------
inline void
z80ctc::update(int ticks) {
    for (int i = 0; i < num_channels; i++) {
        if (channels[i].timer_enabled) {
            update_timer((channel)i, ticks);
        }
    }
}

//------------------------------------------------------------------------------
inline void
z80ctc::trigger(channel c) {
    YAKC_ASSERT((c >= 0) && (c < num_channels));

    // if channel is in timer mode and waiting for trigger, start the time
    channel_state& chn = channels[c];
    if (((chn.mode & MODE) == MODE_TIMER) && chn.waiting_for_trigger) {
        enable_timer(c);
    }
    chn.waiting_for_trigger = false;

    // if in counter mode, decrement the counter and check if it hits zero
    if ((chn.mode & MODE) == MODE_COUNTER) {
        if (--chn.counter == 0) {
            timer_callback(c);
        }
    }
}

//------------------------------------------------------------------------------
inline void
z80ctc::timer_callback(channel c) {
    channel_state& chn = channels[c];
    chn.counter = chn.constant;
    if ((chn.mode & INTERRUPT) == INTERRUPT_ENABLED) {
        YAKC_PRINTF("CTC FIXME: INTERRUPT REQUEST");
    }
    if (pulse_callback) {
        pulse_callback(this->userdata, c);
    }
}

//------------------------------------------------------------------------------
inline void
z80ctc::disable_timer(channel c) {
    channels[c].timer_enabled = false;
}

//------------------------------------------------------------------------------
inline void
z80ctc::enable_timer(channel c) {
    int val = (channels[c].mode & PRESCALER ? 256 : 16) * channels[c].constant;
    channels[c].timer = val;
    channels[c].timer_enabled = true;
}

//------------------------------------------------------------------------------
inline void
z80ctc::update_timer(channel c, int num_cycles) {
    channel_state& chn = channels[c];
    chn.timer -= num_cycles;
    while (chn.timer < 0) {
        YAKC_PRINTF("CTC CHANNEL %d TIMER TRIGGERED!\n", c);
        chn.timer += (chn.mode & PRESCALER ? 256 : 16) * chn.constant;
    }
}

//------------------------------------------------------------------------------
inline void
z80ctc::reset_channel(channel c) {
    YAKC_ASSERT((c >= 0) && (c<num_channels));
    this->channels[c].constant = 0x100;
    this->disable_timer(c);
}

//------------------------------------------------------------------------------
inline void
z80ctc::write(channel c, ubyte v) {
    YAKC_ASSERT((c >= 0) && (c<num_channels));

    channel_state& chn = channels[c];
    if (chn.mode & CONSTANT_FOLLOWS) {
        // time constant value following a control word
        chn.constant = v ? v : 0x100;   // 0 ==> 256
        chn.counter = chn.constant;
        chn.mode &= ~CONSTANT_FOLLOWS;
        chn.mode &= ~RESET;
        if ((chn.mode & MODE) == MODE_TIMER) {
            if ((chn.mode & TRIGGER) == TRIGGER_AUTOMATIC) {
                this->enable_timer(c);
            }
            else {
                this->channels[c].waiting_for_trigger = true;
            }
        }
    }
    else if ((v & CONTROL) == CONTROL_WORD) {
        // a control word
        chn.mode = v;
        if (v & RESET) {
            this->reset_channel(c);
        }
    }
    else {
        // an interrupt vector for the whole CTC must be written
        // to channel 0, interrupt vectors for following channels
        // are computed from the base vector plus 2 byte per channel
        if (CTC0 == c) {
            interrupt_vector = v & 0xF8;
        }
    }
}

//------------------------------------------------------------------------------
inline ubyte
z80ctc::read(channel c) {
    YAKC_ASSERT((c >= 0) && (c<num_channels));
    YAKC_PRINTF("FIXME: CTC %d READ!\n", c);
    return 0;
}

} // namespace yakc
    