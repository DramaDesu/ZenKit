// Copyright © 2023 GothicKit Contributors.
// SPDX-License-Identifier: MIT
#pragma once
#include "zenkit/vobs/Sound.hh"

namespace phoenix {
	namespace vobs {
		using sound ZKREM("renamed to zenkit::VSound") = zenkit::VSound;
		using sound_daytime ZKREM("renamed to zenkit::VSoundDaytime") = zenkit::VSoundDaytime;
	} // namespace vobs

	using sound_mode ZKREM("renamed to zenkit::SoundMode") = zenkit::SoundMode;
	using sound_trigger_volume ZKREM("renamed to SoundTriggerVolumeType") = zenkit::SoundTriggerVolumeType;
} // namespace phoenix
