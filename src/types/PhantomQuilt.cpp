// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PhantomQuilt.h"

CBaseQuilt::CBaseQuilt(std::shared_ptr<const std::string> data
		, const patch_position length
		, unsigned int secs
		, unsigned int usecs)
	: Quilt(data, length)
	, Seconds(secs)
	, USeconds(usecs)
{
}
