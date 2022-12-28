//****************************************************************************
//
//    RVDDT (RISC-V Dynamic Debugging Tool)
//
//    Copyright (C) 2020  John Winans
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Lesser General Public
//    License as published by the Free Software Foundation; either
//    version 2.1 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
//    USA
//
//****************************************************************************

#ifndef console_H
#define console_H

#include "general.h"
#include "../devices.h"

#include <stdint.h>

class console : public GeneralDevice
{
public:
    console() : GeneralDevice(0x0, 0xFFFFFFFFFFFFFFFF) {}
    void set8(uint64_t addr, uint8_t val)   { putchar(val); }

    const char *getIdent() const { return "CON"; }

private:
};

#endif
