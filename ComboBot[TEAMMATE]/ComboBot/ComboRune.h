#pragma once
#include "pch.h"
class ComboRune : public ISingleton<ComboRune>
{
private:

public:
	ComboRune();
	int32_t m_ComboRune;
	int32_t m_TimerAutoAttack;
	void CastRune(int32_t RUNEID, int32_t targetId);
};