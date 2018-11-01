/*
 * This file is part of Gen7TimeFinder
 * Copyright (C) 2018 by Admiral_Fish
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SFMT_HPP
#define SFMT_HPP

#include <cstdint>

using u64 = uint64_t;
using u32 = uint32_t;

class SFMT
{

private:
    const u32 CMSK1 = 0xdfffffef;
    const u32 CMSK2 = 0xddfecb7f;
    const u32 CMSK3 = 0xbffaffff;
    const u32  CMSK4 = 0xbffffff6;
    const int CSL1 = 18;
    const int CSR1 = 11;
    const int N32 = 624;
    const u32 PARITY[4] = { 0x1, 0x0, 0x0, 0x13c9e684 };
    u32 *sfmt;
    u32 index;

    void initialize(u32 seed);
    void periodCertificaion();
    void shuffle();

public:
    SFMT(u32 seed, u32 frames = 0);
    ~SFMT() { delete[] sfmt; }
    void advanceFrames(u32 frames);
    u32 nextUInt();
    u64 nextULong();

};

#endif // SFMT_HPP
