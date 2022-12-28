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

#ifndef devices_H
#define devices_H

#include <stdint.h>
#include <memory>
#include <list>

#include "dev/general.h"
class GeneralDevice;

class Devices
{
public:
	Devices();
	~Devices();

	uint8_t  get8(uint64_t addr)  const;
	uint16_t get16(uint64_t addr) const;
	uint32_t get32(uint64_t addr) const;
	uint64_t get64(uint64_t addr) const;

    void set8(uint64_t addr, uint8_t val);
    void set16(uint64_t addr, uint16_t val);
    void set32(uint64_t addr, uint32_t val);
    void set64(uint64_t addr, uint64_t val);

	void dump();

	void setWarnings(int i) { warnings=i; }
	int getWarnings() const { return warnings; } 

	void addDevice(GeneralDevice *d) { devs.push_back(d); }

	static void errorGet(const char *len, uint64_t addr);
	static void errorSet(const char *len, uint64_t addr, uint64_t val);
	static void errorInvalidWrite(const char *len, uint64_t addr, uint64_t val, const char *msg=nullptr);

private:
	int warnings;

	std::list<GeneralDevice*> devs;
};

#endif
