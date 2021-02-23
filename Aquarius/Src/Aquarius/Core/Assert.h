#pragma once

#include "Aquarius/Core/Log.h"

#include <string>

namespace Aquarius {

inline void aqCoreAssert(bool expression)
{
	#ifdef AQ_ASSERT_ENABLE
	if (!expression)
	{
		AQ_CORE_ERROR("Assertion failed at %v:%v", __FILE__, __LINE__);
	}
	#endif
}

template<typename Msg, typename ... Ts>
inline void aqCoreAssert(bool expression, Msg message, Ts ... args)
{
	#ifdef AQ_ASSERT_ENABLE
	if (!expression)
	{
		std::string errorMessage = "Assertion failed: " + std::string(message);
		AQ_ERROR(errorMessage.c_str(), args...);
	}
	#endif
}

inline void aqAssert(bool expression)
{
	#ifdef AQ_ASSERT_ENABLE
	if (!expression)
	{
		AQ_ERROR("Assertion failed at %v:%v", __FILE__, __LINE__);
	}
	#endif
}

template<typename Msg, typename ... Ts>
inline void aqAssert(bool expression, Msg message, Ts ... args)
{
	#ifdef AQ_ASSERT_ENABLE
	if (!expression)
	{
		std::string errorMessage = "Assertion failed: " + std::string(message);
		AQ_ERROR(errorMessage.c_str(), args...);
	}
	#endif
}
} // namespace Aquarius
