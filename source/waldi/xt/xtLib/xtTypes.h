#pragma once

#include <cstdint>
#include <array>
#include <vector>

#include "dsp56kEmu/types.h"

#include "xtId.h"

namespace xt
{
	static constexpr uint32_t g_ramSize  = 0x00020000;
	static constexpr uint32_t g_romSize  = 0x00040000;
	static constexpr uint32_t g_romAddr  = 0x00100000;
	static constexpr uint32_t g_addrMask = 0x001fffff;

	// The main board. The firmware reads it from the Port GP strap pins and picks the DSP program and clock to match
	enum class Board : uint8_t
	{
		Xt,
		Mw2
	};

	// Any strap value except 0x00, 0x20-0x3f and 0x60 makes the firmware use its Microwave II code path
	static constexpr uint8_t g_mw2PortGpStrap = 0x80;

	// The Microwave II runs its DSP PLL from a 4 MHz crystal (18 x 4 MHz = 72 MHz) instead of the 10,24 MHz audio clock
	static constexpr uint32_t g_mw2DspCrystal = 4'000'000;

	// The Microwave II DSP shifts each stereo pair right by this many bits before it sends it to the DAC
	static constexpr uint32_t g_mw2DacShift = 6;

	template<size_t Count> using TAudioBuffer = std::array<std::vector<dsp56k::TWord>, Count>;
	using TAudioOutputs = TAudioBuffer<4>;
	using TAudioInputs = TAudioBuffer<2>;

	using WaveData = std::array<int8_t, 128>;
	using TableData = std::array<WaveId, 64>;
}
