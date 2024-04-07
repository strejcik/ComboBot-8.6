#include "pch.h"
#include "ComboRune.h"
#pragma warning(disable : 4996)

ComboRune::ComboRune()
{
	m_ComboRune = 0;
	m_TimerAutoAttack = 0;
}

void ComboRune::CastRune(int32_t RUNEID, int32_t targetId)
{
	CSelfCharacter selfCharacter;
	MemReader::GetInstance().ReadSelfCharacter(&selfCharacter);
	std::vector<Entity*> entities = MemReader::GetInstance().ReadVisibleCreatures();
	for (auto& entity : entities)
	{
		if (entity->id == targetId)
			{
				
				Position myPosition = { selfCharacter.xPos, selfCharacter.yPos, selfCharacter.zPos };
				Position toPosition = { entity->xPos, entity->yPos, entity->zPos };
				bool isShootable = MemReader::GetInstance().IsShootable(toPosition, myPosition);
				if (isShootable && Util::isNotExhausted(ComboRune::GetInstance().m_TimerAutoAttack, Cooldowns::GetInstance().BETWEEN_PACKETS))
				{
					PacketSend::GetInstance().UseItemOn(RUNEID, (uint32_t)entity->id);
					std::time_t rawtime;
					std::tm* timeinfo;
					char buffer[80];

					std::time(&rawtime);
					timeinfo = std::localtime(&rawtime);

					std::strftime(buffer, 80, "%H:%M:%S", timeinfo);
					std::cout << "[" << buffer << "]: " << entity->name << "\n";
				}
				else
				{
					return;
				}
			}
	}
}
