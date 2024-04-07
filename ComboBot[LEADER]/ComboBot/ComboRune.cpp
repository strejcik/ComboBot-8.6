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
		

			if (targetId == entity->id)
			{


				
				Position myPosition = { selfCharacter.xPos, selfCharacter.yPos, selfCharacter.zPos };
				Position toPosition = { entity->xPos, entity->yPos, entity->zPos };
				bool isShootable = MemReader::GetInstance().IsShootable(toPosition, myPosition);
				if (isShootable)
				{
					std::time_t rawtime;
					std::tm* timeinfo;
					char buffer[80];

					std::time(&rawtime);
					timeinfo = std::localtime(&rawtime);

					std::strftime(buffer, 80, "%H:%M:%S", timeinfo);

					PacketSend::GetInstance().UseItemOn(RUNEID, (uint32_t)entity->id);
					std::cout << "[" << buffer << "]: " << entity->name << "\n";
					Menu::shotExecuted = true;
				}
				else
				{
					return;
				}
			}
	}
}
