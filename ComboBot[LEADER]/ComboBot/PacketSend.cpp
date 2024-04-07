#pragma once

#include "pch.h"
#include "structs.h"

PacketSend::PacketSend()
{
	moduleBase = (uintptr_t)GetModuleHandle(NULL);

	PacketStart = FnPacketInt(moduleBase + 0xF8290);

	PacketContainer = FnPacketInt(moduleBase + 0xF8700);
	PacketChannelId = FnPacketInt(moduleBase + 0xF8560);


	PacketEnd = FnPacketByte(moduleBase + 0xF8E40);
	PacketPlayerId = FnPacketInt(moduleBase + 0xF88A0);
}

void PacketSend::UseItemOn(int32_t itemId, uint32_t creatureId)
{
	PacketStart(0x84);
	PacketContainer(65535);
	PacketContainer(0);
	PacketChannelId(0);
	PacketContainer(itemId);
	PacketChannelId(0);
	PacketPlayerId(creatureId);
	PacketEnd(1);
}
