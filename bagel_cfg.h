#pragma once
#include "Components.h"

using namespace donkeykong;


	constexpr Bagel Params{
		.DynamicResize = false
	};

	BAGEL_STORAGE(RespawnWhen, PackedStorage)
	BAGEL_STORAGE(CollosionDetector, PackedStorage)
	BAGEL_STORAGE(Animation, PackedStorage);



