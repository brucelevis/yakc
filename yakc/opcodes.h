#pragma once
// #version:1
// machine generated, do not edit!
#include "yakc/common.h"
namespace yakc {
inline void z80::step() {
    int d;
    uword u16tmp;
    switch (mem.r8(state.PC++)) {
    case 0x0:
        // NOP
        state.T += 4;
        break;
    case 0x1:
        // LD BC,nn
        state.BC = mem.r16(state.PC);
        state.PC += 2;
        state.T += 10;
        break;
    case 0x2:
        // LD (BC),A
        mem.w8(state.BC, state.A);
        state.T += 7;
        break;
    case 0x6:
        // LD B,n
        state.B = mem.r8(state.PC++);
        state.T += 7;
        break;
    case 0x8:
        // EX AF,AF'
        swap16(state.AF, state.AF_);
        state.T += 4;
        break;
    case 0xa:
        // LD A,(BC)
        state.A = mem.r8(state.BC);
        state.T += 7;
        break;
    case 0xe:
        // LD C,n
        state.C = mem.r8(state.PC++);
        state.T += 7;
        break;
    case 0x11:
        // LD DE,nn
        state.DE = mem.r16(state.PC);
        state.PC += 2;
        state.T += 10;
        break;
    case 0x12:
        // LD (DE),A
        mem.w8(state.DE, state.A);
        state.T += 7;
        break;
    case 0x16:
        // LD D,n
        state.D = mem.r8(state.PC++);
        state.T += 7;
        break;
    case 0x1a:
        // LD A,(DE)
        state.A = mem.r8(state.DE);
        state.T += 7;
        break;
    case 0x1e:
        // LD E,n
        state.E = mem.r8(state.PC++);
        state.T += 7;
        break;
    case 0x21:
        // LD HL,nn
        state.HL = mem.r16(state.PC);
        state.PC += 2;
        state.T += 10;
        break;
    case 0x22:
        // LD (nn),HL
        mem.w16(mem.r16(state.PC), state.HL);
        state.PC += 2;
        state.T += 16;
        break;
    case 0x26:
        // LD H,n
        state.H = mem.r8(state.PC++);
        state.T += 7;
        break;
    case 0x2a:
        // LD HL,(nn)
        state.HL = mem.r16(mem.r16(state.PC));
        state.PC += 2;
        state.T += 16;
        break;
    case 0x2e:
        // LD L,n
        state.L = mem.r8(state.PC++);
        state.T += 7;
        break;
    case 0x31:
        // LD SP,nn
        state.SP = mem.r16(state.PC);
        state.PC += 2;
        state.T += 10;
        break;
    case 0x32:
        // LD (nn),A
        mem.w8(mem.r16(state.PC), state.A);
        state.PC += 2;
        state.T += 13;
        break;
    case 0x36:
        // LD (HL),n
        mem.w8(state.HL, mem.r8(state.PC++));
        state.T += 10;
        break;
    case 0x3a:
        // LD A,(nn)
        state.A = mem.r8(mem.r16(state.PC));
        state.PC += 2;
        state.T += 13;
        break;
    case 0x3e:
        // LD A,n
        state.A = mem.r8(state.PC++);
        state.T += 7;
        break;
    case 0x40:
        // LD B,B
        state.B = state.B;
        state.T += 4;
        break;
    case 0x41:
        // LD B,C
        state.B = state.C;
        state.T += 4;
        break;
    case 0x42:
        // LD B,D
        state.B = state.D;
        state.T += 4;
        break;
    case 0x43:
        // LD B,E
        state.B = state.E;
        state.T += 4;
        break;
    case 0x44:
        // LD B,H
        state.B = state.H;
        state.T += 4;
        break;
    case 0x45:
        // LD B,L
        state.B = state.L;
        state.T += 4;
        break;
    case 0x46:
        // LD B,(HL)
        state.B = mem.r8(state.HL);
        state.T += 7;
        break;
    case 0x47:
        // LD B,A
        state.B = state.A;
        state.T += 4;
        break;
    case 0x48:
        // LD C,B
        state.C = state.B;
        state.T += 4;
        break;
    case 0x49:
        // LD C,C
        state.C = state.C;
        state.T += 4;
        break;
    case 0x4a:
        // LD C,D
        state.C = state.D;
        state.T += 4;
        break;
    case 0x4b:
        // LD C,E
        state.C = state.E;
        state.T += 4;
        break;
    case 0x4c:
        // LD C,H
        state.C = state.H;
        state.T += 4;
        break;
    case 0x4d:
        // LD C,L
        state.C = state.L;
        state.T += 4;
        break;
    case 0x4e:
        // LD C,(HL)
        state.C = mem.r8(state.HL);
        state.T += 7;
        break;
    case 0x4f:
        // LD C,A
        state.C = state.A;
        state.T += 4;
        break;
    case 0x50:
        // LD D,B
        state.D = state.B;
        state.T += 4;
        break;
    case 0x51:
        // LD D,C
        state.D = state.C;
        state.T += 4;
        break;
    case 0x52:
        // LD D,D
        state.D = state.D;
        state.T += 4;
        break;
    case 0x53:
        // LD D,E
        state.D = state.E;
        state.T += 4;
        break;
    case 0x54:
        // LD D,H
        state.D = state.H;
        state.T += 4;
        break;
    case 0x55:
        // LD D,L
        state.D = state.L;
        state.T += 4;
        break;
    case 0x56:
        // LD D,(HL)
        state.D = mem.r8(state.HL);
        state.T += 7;
        break;
    case 0x57:
        // LD D,A
        state.D = state.A;
        state.T += 4;
        break;
    case 0x58:
        // LD E,B
        state.E = state.B;
        state.T += 4;
        break;
    case 0x59:
        // LD E,C
        state.E = state.C;
        state.T += 4;
        break;
    case 0x5a:
        // LD E,D
        state.E = state.D;
        state.T += 4;
        break;
    case 0x5b:
        // LD E,E
        state.E = state.E;
        state.T += 4;
        break;
    case 0x5c:
        // LD E,H
        state.E = state.H;
        state.T += 4;
        break;
    case 0x5d:
        // LD E,L
        state.E = state.L;
        state.T += 4;
        break;
    case 0x5e:
        // LD E,(HL)
        state.E = mem.r8(state.HL);
        state.T += 7;
        break;
    case 0x5f:
        // LD E,A
        state.E = state.A;
        state.T += 4;
        break;
    case 0x60:
        // LD H,B
        state.H = state.B;
        state.T += 4;
        break;
    case 0x61:
        // LD H,C
        state.H = state.C;
        state.T += 4;
        break;
    case 0x62:
        // LD H,D
        state.H = state.D;
        state.T += 4;
        break;
    case 0x63:
        // LD H,E
        state.H = state.E;
        state.T += 4;
        break;
    case 0x64:
        // LD H,H
        state.H = state.H;
        state.T += 4;
        break;
    case 0x65:
        // LD H,L
        state.H = state.L;
        state.T += 4;
        break;
    case 0x66:
        // LD H,(HL)
        state.H = mem.r8(state.HL);
        state.T += 7;
        break;
    case 0x67:
        // LD H,A
        state.H = state.A;
        state.T += 4;
        break;
    case 0x68:
        // LD L,B
        state.L = state.B;
        state.T += 4;
        break;
    case 0x69:
        // LD L,C
        state.L = state.C;
        state.T += 4;
        break;
    case 0x6a:
        // LD L,D
        state.L = state.D;
        state.T += 4;
        break;
    case 0x6b:
        // LD L,E
        state.L = state.E;
        state.T += 4;
        break;
    case 0x6c:
        // LD L,H
        state.L = state.H;
        state.T += 4;
        break;
    case 0x6d:
        // LD L,L
        state.L = state.L;
        state.T += 4;
        break;
    case 0x6e:
        // LD L,(HL)
        state.L = mem.r8(state.HL);
        state.T += 7;
        break;
    case 0x6f:
        // LD L,A
        state.L = state.A;
        state.T += 4;
        break;
    case 0x70:
        // LD (HL),B
        mem.w8(state.HL, state.B);
        state.T += 7;
        break;
    case 0x71:
        // LD (HL),C
        mem.w8(state.HL, state.C);
        state.T += 7;
        break;
    case 0x72:
        // LD (HL),D
        mem.w8(state.HL, state.D);
        state.T += 7;
        break;
    case 0x73:
        // LD (HL),E
        mem.w8(state.HL, state.E);
        state.T += 7;
        break;
    case 0x74:
        // LD (HL),H
        mem.w8(state.HL, state.H);
        state.T += 7;
        break;
    case 0x75:
        // LD (HL),L
        mem.w8(state.HL, state.L);
        state.T += 7;
        break;
    case 0x77:
        // LD (HL),A
        mem.w8(state.HL, state.A);
        state.T += 7;
        break;
    case 0x78:
        // LD A,B
        state.A = state.B;
        state.T += 4;
        break;
    case 0x79:
        // LD A,C
        state.A = state.C;
        state.T += 4;
        break;
    case 0x7a:
        // LD A,D
        state.A = state.D;
        state.T += 4;
        break;
    case 0x7b:
        // LD A,E
        state.A = state.E;
        state.T += 4;
        break;
    case 0x7c:
        // LD A,H
        state.A = state.H;
        state.T += 4;
        break;
    case 0x7d:
        // LD A,L
        state.A = state.L;
        state.T += 4;
        break;
    case 0x7e:
        // LD A,(HL)
        state.A = mem.r8(state.HL);
        state.T += 7;
        break;
    case 0x7f:
        // LD A,A
        state.A = state.A;
        state.T += 4;
        break;
    case 0x80:
        // ADD A,B
        state.A = add8(state.A, state.B);
        state.T += 4;
        break;
    case 0x81:
        // ADD A,C
        state.A = add8(state.A, state.C);
        state.T += 4;
        break;
    case 0x82:
        // ADD A,D
        state.A = add8(state.A, state.D);
        state.T += 4;
        break;
    case 0x83:
        // ADD A,E
        state.A = add8(state.A, state.E);
        state.T += 4;
        break;
    case 0x84:
        // ADD A,H
        state.A = add8(state.A, state.H);
        state.T += 4;
        break;
    case 0x85:
        // ADD A,L
        state.A = add8(state.A, state.L);
        state.T += 4;
        break;
    case 0x86:
        // ADD A,(HL)
        state.A = add8(state.A, mem.r8(state.HL));
        state.T += 7;
        break;
    case 0x87:
        // ADD A,A
        state.A = add8(state.A, state.A);
        state.T += 4;
        break;
    case 0x88:
        // ADC A,B
        state.A = adc8(state.A, state.B);
        state.T += 4;
        break;
    case 0x89:
        // ADC A,C
        state.A = adc8(state.A, state.C);
        state.T += 4;
        break;
    case 0x8a:
        // ADC A,D
        state.A = adc8(state.A, state.D);
        state.T += 4;
        break;
    case 0x8b:
        // ADC A,E
        state.A = adc8(state.A, state.E);
        state.T += 4;
        break;
    case 0x8c:
        // ADC A,H
        state.A = adc8(state.A, state.H);
        state.T += 4;
        break;
    case 0x8d:
        // ADC A,L
        state.A = adc8(state.A, state.L);
        state.T += 4;
        break;
    case 0x8e:
        // ADC A,(HL)
        state.A = adc8(state.A, mem.r8(state.HL));
        state.T += 7;
        break;
    case 0x8f:
        // ADC A,A
        state.A = adc8(state.A, state.A);
        state.T += 4;
        break;
    case 0x90:
        // SUB A,B
        state.A = sub8(state.A, state.B);
        state.T += 4;
        break;
    case 0x91:
        // SUB A,C
        state.A = sub8(state.A, state.C);
        state.T += 4;
        break;
    case 0x92:
        // SUB A,D
        state.A = sub8(state.A, state.D);
        state.T += 4;
        break;
    case 0x93:
        // SUB A,E
        state.A = sub8(state.A, state.E);
        state.T += 4;
        break;
    case 0x94:
        // SUB A,H
        state.A = sub8(state.A, state.H);
        state.T += 4;
        break;
    case 0x95:
        // SUB A,L
        state.A = sub8(state.A, state.L);
        state.T += 4;
        break;
    case 0x96:
        // SUB A,(HL)
        state.A = sub8(state.A, mem.r8(state.HL));
        state.T += 7;
        break;
    case 0x97:
        // SUB A,A
        state.A = sub8(state.A, state.A);
        state.T += 4;
        break;
    case 0x98:
        // SBC A,B
        state.A = sbc8(state.A, state.B);
        state.T += 4;
        break;
    case 0x99:
        // SBC A,C
        state.A = sbc8(state.A, state.C);
        state.T += 4;
        break;
    case 0x9a:
        // SBC A,D
        state.A = sbc8(state.A, state.D);
        state.T += 4;
        break;
    case 0x9b:
        // SBC A,E
        state.A = sbc8(state.A, state.E);
        state.T += 4;
        break;
    case 0x9c:
        // SBC A,H
        state.A = sbc8(state.A, state.H);
        state.T += 4;
        break;
    case 0x9d:
        // SBC A,L
        state.A = sbc8(state.A, state.L);
        state.T += 4;
        break;
    case 0x9e:
        // SBC A,(HL)
        state.A = sbc8(state.A, mem.r8(state.HL));
        state.T += 7;
        break;
    case 0x9f:
        // SBC A,A
        state.A = sbc8(state.A, state.A);
        state.T += 4;
        break;
    case 0xa0:
        // AND A,B
        state.A &= state.B;
        state.F = szp(state.A)|HF;
        state.T += 4;
        break;
    case 0xa1:
        // AND A,C
        state.A &= state.C;
        state.F = szp(state.A)|HF;
        state.T += 4;
        break;
    case 0xa2:
        // AND A,D
        state.A &= state.D;
        state.F = szp(state.A)|HF;
        state.T += 4;
        break;
    case 0xa3:
        // AND A,E
        state.A &= state.E;
        state.F = szp(state.A)|HF;
        state.T += 4;
        break;
    case 0xa4:
        // AND A,H
        state.A &= state.H;
        state.F = szp(state.A)|HF;
        state.T += 4;
        break;
    case 0xa5:
        // AND A,L
        state.A &= state.L;
        state.F = szp(state.A)|HF;
        state.T += 4;
        break;
    case 0xa6:
        // AND A,(HL)
        state.A &= mem.r8(state.HL);
        state.F = szp(state.A)|HF;
        state.T += 7;
        break;
    case 0xa7:
        // AND A,A
        state.A &= state.A;
        state.F = szp(state.A)|HF;
        state.T += 4;
        break;
    case 0xc1:
        // POP BC
        state.BC = mem.r16(state.SP);
        state.SP += 2;
        state.T += 10;
        break;
    case 0xc5:
        // PUSH BC
        state.SP -= 2;
        mem.w16(state.SP, state.BC);
        state.T += 11;
        break;
    case 0xc6:
        // ADD A,n
        state.A = add8(state.A, mem.r8(state.PC++));
        state.T += 7;
        break;
    case 0xce:
        // ADC A,n
        state.A = adc8(state.A, mem.r8(state.PC++));
        state.T += 7;
        break;
    case 0xd1:
        // POP DE
        state.DE = mem.r16(state.SP);
        state.SP += 2;
        state.T += 10;
        break;
    case 0xd5:
        // PUSH DE
        state.SP -= 2;
        mem.w16(state.SP, state.DE);
        state.T += 11;
        break;
    case 0xd6:
        // SUB A,n
        state.A = sub8(state.A, mem.r8(state.PC++));
        state.T += 7;
        break;
    case 0xd9:
        // EXX
        swap16(state.BC, state.BC_);
        swap16(state.DE, state.DE_);
        swap16(state.HL, state.HL_);
        state.T += 4;
        break;
    case 0xdd:
        switch (mem.r8(state.PC++)) {
        case 0x21:
            // LD IX,nn
            state.IX = mem.r16(state.PC);
            state.PC += 2;
            state.T += 14;
            break;
        case 0x22:
            // LD (nn),IX
            mem.w16(mem.r16(state.PC), state.IX);
            state.PC += 2;
            state.T += 20;
            break;
        case 0x2a:
            // LD IX,(nn)
            state.IX = mem.r16(mem.r16(state.PC));
            state.PC += 2;
            state.T += 20;
            break;
        case 0x36:
            // LD (IX+d),n
            d = mem.rs8(state.PC++);
            mem.w8(state.IX + d, mem.r8(state.PC++));
            state.T += 19;
            break;
        case 0x46:
            // LD B,(IX+d)
            d = mem.rs8(state.PC++);
            state.B = mem.r8(state.IX + d);
            state.T += 19;
            break;
        case 0x4e:
            // LD C,(IX+d)
            d = mem.rs8(state.PC++);
            state.C = mem.r8(state.IX + d);
            state.T += 19;
            break;
        case 0x56:
            // LD D,(IX+d)
            d = mem.rs8(state.PC++);
            state.D = mem.r8(state.IX + d);
            state.T += 19;
            break;
        case 0x5e:
            // LD E,(IX+d)
            d = mem.rs8(state.PC++);
            state.E = mem.r8(state.IX + d);
            state.T += 19;
            break;
        case 0x66:
            // LD H,(IX+d)
            d = mem.rs8(state.PC++);
            state.H = mem.r8(state.IX + d);
            state.T += 19;
            break;
        case 0x6e:
            // LD L,(IX+d)
            d = mem.rs8(state.PC++);
            state.L = mem.r8(state.IX + d);
            state.T += 19;
            break;
        case 0x70:
            // LD (IX+d),B
            d = mem.rs8(state.PC++);
            mem.w8(state.IX + d, state.B);
            state.T += 19;
            break;
        case 0x71:
            // LD (IX+d),C
            d = mem.rs8(state.PC++);
            mem.w8(state.IX + d, state.C);
            state.T += 19;
            break;
        case 0x72:
            // LD (IX+d),D
            d = mem.rs8(state.PC++);
            mem.w8(state.IX + d, state.D);
            state.T += 19;
            break;
        case 0x73:
            // LD (IX+d),E
            d = mem.rs8(state.PC++);
            mem.w8(state.IX + d, state.E);
            state.T += 19;
            break;
        case 0x74:
            // LD (IX+d),H
            d = mem.rs8(state.PC++);
            mem.w8(state.IX + d, state.H);
            state.T += 19;
            break;
        case 0x75:
            // LD (IX+d),L
            d = mem.rs8(state.PC++);
            mem.w8(state.IX + d, state.L);
            state.T += 19;
            break;
        case 0x77:
            // LD (IX+d),A
            d = mem.rs8(state.PC++);
            mem.w8(state.IX + d, state.A);
            state.T += 19;
            break;
        case 0x7e:
            // LD A,(IX+d)
            d = mem.rs8(state.PC++);
            state.A = mem.r8(state.IX + d);
            state.T += 19;
            break;
        case 0x86:
            // ADD A,(IX+d)
            d = mem.rs8(state.PC++);
            state.A = add8(state.A, mem.r8(state.IX + d));
            state.T += 19;
            break;
        case 0x8e:
            // ADC A,(IX+d)
            d = mem.rs8(state.PC++);
            state.A = adc8(state.A, mem.r8(state.IX + d));
            state.T += 19;
            break;
        case 0x96:
            // SUB A,(IX+d)
            d = mem.rs8(state.PC++);
            state.A = sub8(state.A, mem.r8(state.IX + d));
            state.T += 19;
            break;
        case 0x9e:
            // SBC A,(IX+d)
            d = mem.rs8(state.PC++);
            state.A = sbc8(state.A, mem.r8(state.IX + d));
            state.T += 19;
            break;
        case 0xa6:
            // AND A,(IX+d)
            d = mem.rs8(state.PC++);
            state.A &= mem.r8(state.IX + d);
            state.F = szp(state.A)|HF;
            state.T += 19;
            break;
        case 0xe1:
            // POP IX
            state.IX = mem.r16(state.SP);
            state.SP += 2;
            state.T += 14;
            break;
        case 0xe3:
            // EX (SP),IX
            u16tmp = mem.r16(state.SP);
            mem.w16(state.SP, state.IX);
            state.IX = u16tmp;
            state.T += 23;
            break;
        case 0xe5:
            // PUSH IX
            state.SP -= 2;
            mem.w16(state.SP, state.IX);
            state.T += 15;
            break;
        case 0xf9:
            // LD SP,IX
            state.SP = state.IX;
            state.T += 10;
            break;
        default:
             YAKC_ASSERT(false);
        }
        break;
    case 0xde:
        // SBC A,n
        state.A = sbc8(state.A, mem.r8(state.PC++));
        state.T += 7;
        break;
    case 0xe1:
        // POP HL
        state.HL = mem.r16(state.SP);
        state.SP += 2;
        state.T += 10;
        break;
    case 0xe3:
        // EX (SP),HL
        u16tmp = mem.r16(state.SP);
        mem.w16(state.SP, state.HL);
        state.HL = u16tmp;
        state.T += 19;
        break;
    case 0xe5:
        // PUSH HL
        state.SP -= 2;
        mem.w16(state.SP, state.HL);
        state.T += 11;
        break;
    case 0xe6:
        // AND A,n
        state.A &= mem.r8(state.PC++);
        state.F = szp(state.A)|HF;
        state.T += 7;
        break;
    case 0xeb:
        // EX DE,HL
        swap16(state.DE, state.HL);
        state.T += 4;
        break;
    case 0xed:
        switch (mem.r8(state.PC++)) {
        case 0x43:
            // LD (nn),BC
            mem.w16(mem.r16(state.PC), state.BC);
            state.PC += 2;
            state.T += 20;
            break;
        case 0x47:
            // LD I,A
            state.I = state.A;
            state.T += 9;
            break;
        case 0x4b:
            // LD BC,(nn)
            state.BC = mem.r16(mem.r16(state.PC));
            state.PC += 2;
            state.T += 20;
            break;
        case 0x4f:
            // LD R,A
            state.R = state.A;
            state.T += 9;
            break;
        case 0x53:
            // LD (nn),DE
            mem.w16(mem.r16(state.PC), state.DE);
            state.PC += 2;
            state.T += 20;
            break;
        case 0x5b:
            // LD DE,(nn)
            state.DE = mem.r16(mem.r16(state.PC));
            state.PC += 2;
            state.T += 20;
            break;
        case 0x63:
            // LD (nn),HL
            mem.w16(mem.r16(state.PC), state.HL);
            state.PC += 2;
            state.T += 20;
            break;
        case 0x6b:
            // LD HL,(nn)
            state.HL = mem.r16(mem.r16(state.PC));
            state.PC += 2;
            state.T += 20;
            break;
        case 0x73:
            // LD (nn),SP
            mem.w16(mem.r16(state.PC), state.SP);
            state.PC += 2;
            state.T += 20;
            break;
        case 0x7b:
            // LD SP,(nn)
            state.SP = mem.r16(mem.r16(state.PC));
            state.PC += 2;
            state.T += 20;
            break;
        default:
            YAKC_ASSERT(false);
        }
        break;
    case 0xf1:
        // POP AF
        state.AF = mem.r16(state.SP);
        state.SP += 2;
        state.T += 10;
        break;
    case 0xf5:
        // PUSH AF
        state.SP -= 2;
        mem.w16(state.SP, state.AF);
        state.T += 11;
        break;
    case 0xf9:
        // LD SP,HL
        state.SP = state.HL;
        state.T += 6;
        break;
    case 0xfd:
        switch (mem.r8(state.PC++)) {
        case 0x21:
            // LD IY,nn
            state.IY = mem.r16(state.PC);
            state.PC += 2;
            state.T += 14;
            break;
        case 0x22:
            // LD (nn),IY
            mem.w16(mem.r16(state.PC), state.IY);
            state.PC += 2;
            state.T += 20;
            break;
        case 0x2a:
            // LD IY,(nn)
            state.IY = mem.r16(mem.r16(state.PC));
            state.PC += 2;
            state.T += 20;
            break;
        case 0x36:
            // LD (IY+d),n
            d = mem.rs8(state.PC++);
            mem.w8(state.IY + d, mem.r8(state.PC++));
            state.T += 19;
            break;
        case 0x46:
            // LD B,(IY+d)
            d = mem.rs8(state.PC++);
            state.B = mem.r8(state.IY + d);
            state.T += 19;
            break;
        case 0x4e:
            // LD C,(IY+d)
            d = mem.rs8(state.PC++);
            state.C = mem.r8(state.IY + d);
            state.T += 19;
            break;
        case 0x56:
            // LD D,(IY+d)
            d = mem.rs8(state.PC++);
            state.D = mem.r8(state.IY + d);
            state.T += 19;
            break;
        case 0x5e:
            // LD E,(IY+d)
            d = mem.rs8(state.PC++);
            state.E = mem.r8(state.IY + d);
            state.T += 19;
            break;
        case 0x66:
            // LD H,(IY+d)
            d = mem.rs8(state.PC++);
            state.H = mem.r8(state.IY + d);
            state.T += 19;
            break;
        case 0x6e:
            // LD L,(IY+d)
            d = mem.rs8(state.PC++);
            state.L = mem.r8(state.IY + d);
            state.T += 19;
            break;
        case 0x70:
            // LD (IY+d),B
            d = mem.rs8(state.PC++);
            mem.w8(state.IY + d, state.B);
            state.T += 19;
            break;
        case 0x71:
            // LD (IY+d),C
            d = mem.rs8(state.PC++);
            mem.w8(state.IY + d, state.C);
            state.T += 19;
            break;
        case 0x72:
            // LD (IY+d),D
            d = mem.rs8(state.PC++);
            mem.w8(state.IY + d, state.D);
            state.T += 19;
            break;
        case 0x73:
            // LD (IY+d),E
            d = mem.rs8(state.PC++);
            mem.w8(state.IY + d, state.E);
            state.T += 19;
            break;
        case 0x74:
            // LD (IY+d),H
            d = mem.rs8(state.PC++);
            mem.w8(state.IY + d, state.H);
            state.T += 19;
            break;
        case 0x75:
            // LD (IY+d),L
            d = mem.rs8(state.PC++);
            mem.w8(state.IY + d, state.L);
            state.T += 19;
            break;
        case 0x77:
            // LD (IY+d),A
            d = mem.rs8(state.PC++);
            mem.w8(state.IY + d, state.A);
            state.T += 19;
            break;
        case 0x7e:
            // LD A,(IY+d)
            d = mem.rs8(state.PC++);
            state.A = mem.r8(state.IY + d);
            state.T += 19;
            break;
        case 0x86:
            // ADD A,(IY+d)
            d = mem.rs8(state.PC++);
            state.A = add8(state.A, mem.r8(state.IY + d));
            state.T += 19;
            break;
        case 0x8e:
            // ADC A,(IY+d)
            d = mem.rs8(state.PC++);
            state.A = adc8(state.A, mem.r8(state.IY + d));
            state.T += 19;
            break;
        case 0x96:
            // SUB A,(IY+d)
            d = mem.rs8(state.PC++);
            state.A = sub8(state.A, mem.r8(state.IY + d));
            state.T += 19;
            break;
        case 0x9e:
            // SBC A,(IY+d)
            d = mem.rs8(state.PC++);
            state.A = sbc8(state.A, mem.r8(state.IY + d));
            state.T += 19;
            break;
        case 0xa6:
            // AND A,(IY+d)
            d = mem.rs8(state.PC++);
            state.A &= mem.r8(state.IY + d);
            state.F = szp(state.A)|HF;
            state.T += 19;
            break;
        case 0xe1:
            // POP IY
            state.IY = mem.r16(state.SP);
            state.SP += 2;
            state.T += 14;
            break;
        case 0xe3:
            // EX (SP),IY
            u16tmp = mem.r16(state.SP);
            mem.w16(state.SP, state.IY);
            state.IY = u16tmp;
            state.T += 23;
            break;
        case 0xe5:
            // PUSH IY
            state.SP -= 2;
            mem.w16(state.SP, state.IY);
            state.T += 15;
            break;
        case 0xf9:
            // LD SP,IY
            state.SP = state.IY;
            state.T += 10;
            break;
        default:
            YAKC_ASSERT(false);
        }
        break;
    default:
       YAKC_ASSERT(false);
    }
}
} // namespace yakc
