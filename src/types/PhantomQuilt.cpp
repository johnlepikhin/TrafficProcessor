
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
