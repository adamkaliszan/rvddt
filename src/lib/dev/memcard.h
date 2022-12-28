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

#ifndef memcard_H
#define memcard_H

#include "general.h"
#include "../devices.h"

#include <stdint.h>
#include <string>

class memcard : public GeneralDevice
{
public:
	memcard(): GeneralDevice(0xf0000000, 0x218) {}
	virtual ~memcard() {}

	std::optional<uint32_t>  io_get32(uint64_t addr) const;

    void set32(uint64_t addr, uint32_t val);

	void writeControl(uint32_t val);
	void writeAddress(uint32_t val);
	void writeBuf(uint64_t addr, uint32_t val);

	//virtual void dump();

	const char *getIdent() const { return "MEMCARD"; }

	constexpr static uint64_t statusRegAddr = { 0xf0000214 };
	constexpr static uint64_t controlRegAddr = { 0xf0000210 };
	constexpr static uint64_t addressRegAddr = { 0xf0000200 };
	constexpr static uint64_t bufFirstAddr = { 0xf0000000 };
	constexpr static uint64_t bufLastAddr = { 0xf00001ff };

	constexpr static uint32_t controlWriteCommand = { 0x80000001 };
	constexpr static uint32_t controlReadCommand = { 0x80000002 };

private:
	uint32_t buf[512/4] = { 0 };		// the device buffer
	uint32_t status = { 0 };		// the current status register value 
	uint32_t control = { 0 };		// the current control register value
	uint32_t address = { 0 };		// the current address register value
};

#endif
