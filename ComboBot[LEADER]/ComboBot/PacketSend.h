#pragma once
//types of functions
using FnPacketInt = void(__stdcall*)(int32_t num);
using FnPacketByte = void(__stdcall*)(BYTE num);

class PacketSend : public ISingleton<PacketSend>
{
public:
	//Function Pointers
	uintptr_t moduleBase;
	FnPacketInt PacketStart = nullptr;
	FnPacketInt PacketItem = nullptr;
	FnPacketInt PacketContainer = nullptr;
	FnPacketInt PacketChannelId = nullptr;
	FnPacketInt PacketPlayerId = nullptr;


	FnPacketByte PacketEnd = nullptr;


	PacketSend();

	void UseItemOn(int32_t itemId, uint32_t creatureId);
};