//------------------------------------------------------------------------------
//  Disasm.cc
//------------------------------------------------------------------------------
#include "Disasm.h"
#include "z80dasm.h"

using namespace z80dasm;
using namespace yakc;

//------------------------------------------------------------------------------
Disasm::Disasm() :
context(0) {
    memset(this->buffer, 0, sizeof(this->buffer));
}

//------------------------------------------------------------------------------
ubyte
Disasm::fetch(uword base, int offset, void* userdata) {
    Disasm* self = (Disasm*) userdata;
    return self->context->cpu.mem.r8(base + offset);
}

//------------------------------------------------------------------------------
uword
Disasm::Disassemble(const kc85& kc, uword addr) {
    this->context = &kc;
    int res = z80disasm(fetch, addr, this->buffer, this);
    return (res & 0xFFFF);
}

//------------------------------------------------------------------------------
const char*
Disasm::Result() const {
    return this->buffer;
}