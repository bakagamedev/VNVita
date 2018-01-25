#pragma once
#include <psp2/rtc.h>

constexpr SceRtcTick operator "" _secs(uint64_t seconds)
{
return { static_cast<uint64_t>(seconds * 1000 * 1000) };
}

constexpr SceRtcTick operator "" _ticks(uint64_t ticks)
{
return { static_cast<uint64_t>(ticks) };
}

class Timer
{
public:
	using TimeType = SceRtcTick;
	using DurationType = uint64_t;
private:
	bool firstRun = true;
	bool hasElapsed = false;
	TimeType previousTime { 0 };
	TimeType targetDuration { 0 };
public:
	Timer(DurationType targetDuration)
	{
		this->targetDuration.tick = targetDuration;
	}

	DurationType getTargetDuration(void) const
	{
		return this->targetDuration.tick;
	}

	void reset(void)
	{
		this->firstRun = true;
	}

	void update(void)
	{
		if(this->firstRun)
		{
			sceRtcGetCurrentTick(&this->previousTime);
			this->firstRun = false;
			this->hasElapsed = false;
		}

		TimeType now;
		sceRtcGetCurrentTick(&now);
		const auto duration = now.tick - this->previousTime.tick;
		if (duration >= this->targetDuration.tick)
		{
			sceRtcGetCurrentTick(&this->previousTime);
			this->hasElapsed = true;
		}
		else
		{
			this->hasElapsed = false;
		}
	}

	bool HasDurationElapsed(void) const
	{
		return this->hasElapsed;
	}
};