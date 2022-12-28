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

#ifndef device_H
#define device_H

#include <stdint.h>
#include <stdio.h>
#include <optional>

class devices;
class GeneralDevice
{
public:
	GeneralDevice(uint64_t addressBase, uint64_t addressRange): memAddrBase(addressBase), memAddrRange(addressRange) {}
	virtual ~GeneralDevice() {}

	std::optional<uint8_t>  get8(uint64_t addr)  const 
	{ 
		if (!matchAddress(addr, 1))
		{
			errorGetWrongAddr("8", addr);
			return std::nullopt;
		}
		return io_get8(addr);
	}

	std::optional<uint16_t>  get16(uint64_t addr)  const 
	{ 
		if (!matchAddress(addr, 1))
		{
			errorGetWrongAddr("16", addr);
			return std::nullopt;
		}
		return io_get16(addr);
	}
	
	std::optional<uint32_t>  get32(uint64_t addr)  const 
	{ 
		if (!matchAddress(addr, 1))
		{
			errorGetWrongAddr("32", addr);
			return std::nullopt;
		}
		return io_get32(addr);
	}

	std::optional<uint64_t>  get64(uint64_t addr)  const 
	{ 
		if (!matchAddress(addr, 1))
		{
			errorGetWrongAddr("64", addr);
			return std::nullopt;
		}
		return io_get64(addr);
	}

    virtual void set8 (uint64_t addr, uint16_t val) { errorSet("8", addr, val); }
    virtual void set16(uint64_t addr, uint16_t val) { errorSet("16", addr, val); }
    virtual void set32(uint64_t addr, uint32_t val) { errorSet("32", addr, val); }
    virtual void set64(uint64_t addr, uint64_t val) { errorSet("64", addr, val); }

	virtual void dump() {}

	virtual bool matchAddress(uint64_t addr, uint64_t range) const { return (addr >= memAddrBase && addr + range <= memAddrBase + memAddrRange); }

	virtual const char *getIdent() const = 0;

	static void errorGetWrongAddr(const char *len, uint64_t addr) { printf("Error %s-bit read from wrong address: 0x%8.8x\n", len, (uint32_t)addr); }
	static void errorGet(const char *len, uint64_t addr) { printf("WARNING: %s-bit read from non-implemented read mode by device at address: 0x%8.8x\n", len, (uint32_t)addr); }
	static void errorSet(const char *len, uint64_t addr, uint64_t val) {printf("WARNING: %s-bit write to non-implemented by device at address: 0x%8.8x = 0x%8.8x\n", len, (uint32_t)addr, (uint32_t)val);}

protected:
	uint64_t memAddrBase{0};
	uint64_t memAddrRange{0};

	virtual std::optional<uint8_t>  io_get8 (uint64_t addr)  const { errorGet(" 8", addr); return std::nullopt; }
	virtual std::optional<uint16_t> io_get16(uint64_t addr)  const { errorGet("16", addr); return std::nullopt; }
	virtual std::optional<uint32_t> io_get32(uint64_t addr)  const { errorGet("32", addr); return std::nullopt; }
	virtual std::optional<uint64_t> io_get64(uint64_t addr)  const { errorGet("64", addr); return std::nullopt; }

    virtual void io_set8 (uint64_t addr, uint16_t val) { errorSet("8", addr, val); }
    virtual void io_set16(uint64_t addr, uint16_t val) { errorSet("16", addr, val); }
    virtual void io_set32(uint64_t addr, uint32_t val) { errorSet("32", addr, val); }
    virtual void io_set64(uint64_t addr, uint64_t val) { errorSet("64", addr, val); }

};

#endif
