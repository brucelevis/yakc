#pragma once
//------------------------------------------------------------------------------
/**
    @class PIOWindow
    @brief visualize the current PIO state
*/
#include "yakc_ui/HexInputWidget.h"
#include "yakc_ui/WindowBase.h"

namespace YAKC {

class PIOWindow : public WindowBase {
    OryolClassDecl(PIOWindow);
public:
    /// constructor
    PIOWindow(const char* name, z80pio* pio);
    /// setup the window
    virtual void Setup(yakc& emu) override;
    /// draw method
    virtual bool Draw(yakc& emu) override;

    const char* Name = nullptr;
    z80pio* PIO = nullptr;
};

} // namespace YAKC
