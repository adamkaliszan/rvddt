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

#include <algorithm>
#include <memory>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#include "devices.h"
#include "dev/general.h"


Devices::Devices()
{
	setWarnings(1);
}

Devices::~Devices()
{
	while (!devs.empty())
	{
		auto item = devs.front();
		delete item;
		devs.pop_front();
	}
}

uint8_t Devices::get8(uint64_t addr) const
{
	auto pdev = std::find_if(std::begin(devs), std::end(devs), [&](const auto &itm) -> bool {
		return (itm->matchAddress(addr, 1));
	});
	if (pdev == std::end(devs))
	{
		errorGet("8", addr);
		return -1;		// invalid devices area, act like a hi-z TTL bus
	}
	auto val = (*pdev)->get8(addr);
	if (!val)
		return 0; //TODO
	return *val;
}

uint16_t Devices::get16(uint64_t addr) const
{
	auto pdev = std::find_if(std::begin(devs), std::end(devs), [&](const auto &itm) -> bool {
		return (itm->matchAddress(addr, 2));
	});
	if (pdev == std::end(devs))
	{
		errorGet("16", addr);
		return -1;		// invalid devices area, act like a hi-z TTL bus
	}
	auto val = (*pdev)->get16(addr);
	if (!val)
		return 0; //TODO
	return *val;
}

uint32_t Devices::get32(uint64_t addr) const
{
	auto pdev = std::find_if(std::begin(devs), std::end(devs), [&](const auto &itm) -> bool {
		return (itm->matchAddress(addr, 4));
	});
	if (pdev == std::end(devs))
	{
		errorGet("32", addr);
		return -1;		// invalid devices area, act like a hi-z TTL bus
	}
	auto val = (*pdev)->get32(addr);
	if (!val)
		return 0; //TODO
	return *val;
}

uint64_t Devices::get64(uint64_t addr) const
{
	auto pdev = std::find_if(std::begin(devs), std::end(devs), [&](const auto &itm) -> bool {
		return (itm->matchAddress(addr, 8));
	});
	if (pdev == std::end(devs))
	{
		errorGet("64", addr);
		return -1;		// invalid devices area, act like a hi-z TTL bus
	}
	auto val = (*pdev)->get64(addr);
	if (!val)
		return 0; //TODO
	return *val;
}

void Devices::set8(uint64_t addr, uint8_t val)
{
	auto pdev = std::find_if(std::begin(devs), std::end(devs), [&](const auto &itm) -> bool {
		return (itm->matchAddress(addr, 1));
	});
	if (pdev == std::end(devs))
	{
		errorSet("8", addr, val);
		return;		// invalid devices area, act like a hi-z TTL bus
	}
	(*pdev)->set8(addr, val);
}

void Devices::set16(uint64_t addr, uint16_t val)
{
	auto pdev = std::find_if(std::begin(devs), std::end(devs), [&](const auto &itm) -> bool {
		return (itm->matchAddress(addr, 2));
	});
	if (pdev == std::end(devs))
	{
		errorSet("16", addr, val);
		return;		// invalid devices area, act like a hi-z TTL bus
	}
	(*pdev)->set16(addr, val);
}

void Devices::set32(uint64_t addr, uint32_t val)
{
	auto pdev = std::find_if(std::begin(devs), std::end(devs), [&](const auto &itm) -> bool {
		return (itm->matchAddress(addr, 4));
	});
	if (pdev == std::end(devs))
	{
		errorSet("32", addr, val);
		return;		// invalid devices area, act like a hi-z TTL bus
	}
	(*pdev)->set16(addr, val);
}

void Devices::set64(uint64_t addr, uint64_t val)
{
	auto pdev = std::find_if(std::begin(devs), std::end(devs), [&](const auto &itm) -> bool {
		return (itm->matchAddress(addr, 8));
	});
	if (pdev == std::end(devs))
	{
		errorSet("64", addr, val);
		return;		// invalid devices area, act like a hi-z TTL bus
	}
	(*pdev)->set64(addr, val);
}

void Devices::errorSet(const char *len, uint64_t addr, uint64_t val)
{
	printf("WARNING: %s-bit write to non-existent device at address: 0x%8.8x = 0x%8.8x\n", len, (uint32_t)addr, (uint32_t)val);
}

void Devices::errorGet(const char *len, uint64_t addr)
{
	printf("WARNING: %s-bit read from non-existent device at address: 0x%8.8x\n", len, (uint32_t)addr);
}

void Devices::errorInvalidWrite(const char *len, uint64_t addr, uint64_t val, const char *msg)
{
	printf("WARNING: %s-bit write to address 0x%8.8x with illegal value 0x%8.8x\n", len, (uint32_t)addr, (uint32_t)val);

	if (msg)
		printf("%s\n", msg);
}
