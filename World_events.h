#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;
vector<WorldInfo> worlds;

/*Dropping the event item*/
inline void SendDropEventItem(const string WorldName, const int netID, const int x, int y, const int item, const int count, const BYTE specialEffect)
{
	if (item >= maxItems) return;
	if (item < 0) return;
	auto world = worldDB.get2(WorldName).ptr;
	DroppedItem itemDropped;
	itemDropped.id = item;
	itemDropped.count = count;
	itemDropped.x = x;
	itemDropped.y = y;
	itemDropped.droppedby = "Special Event";
	world->droppedCount++;
	itemDropped.uid = world->droppedCount;
	world->droppedItems.push_back(itemDropped);
	for (auto currentPeer = server->peers;
	     currentPeer < &server->peers[server->peerCount];
	     ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (EventWorld(currentPeer, WorldName))
		{
			PlayerMoving data;
			data.packetType = 14;
			data.x = x;
			data.y = y;
			data.netID = netID;
			data.plantingTree = item;
			float val = count;
			auto val2 = specialEffect;
			const auto raw = packPlayerMoving(&data);
			memcpy(raw + 16, &val, 4);
			memcpy(raw + 1, &val2, 1);
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

/*Spawning the event items*/
inline void SpawnEventItem(const string WorldName, const int ItemID, const int count, int Time, const int x, const int y, const int Multiple)
{
	for (auto i = 0; i < Multiple; i++)
	{
		const auto DropX = rand() % x * 32;
		const auto DropY = rand() % y * 32;
		SendDropEventItem(WorldName, -1, DropX, DropY, ItemID, count, 0);
	}
}

/*Basically the all world event things, this is a loop which finds active worlds*/
inline void WorldEvents()
{
	while (true)
	{
		Sleep(600000); /*every 10 minutes event happens*/
		{
			auto worlds = worldDB.getRandomWorlds();
			for (auto i = 0; i < worlds.size(); i++)
			{
				if (serverIsFrozen)break;
				if (getPlayersCountInWorld(worlds[i].name) <= 0) continue; /*to avoid events in empty worlds*/
				if (worlds[i].enableevent != true) continue; /*to avoid events in empty worlds*/
				/*Choose event type*/
				string Notification = "";
				auto ItemID = 0;
				auto Count = 0;
				const auto Time = 0; /*Not used for now*/
				auto Multiple = 0; /*How much times the drop will be repeated*/
				int values;
				time_t currentTime;
				time(&currentTime);
				const auto localTime = localtime(&currentTime);
				const auto Hour = localTime->tm_hour;
				const auto Min = localTime->tm_min;
				const auto Sec = localTime->tm_sec;
				srand(time(nullptr));
				if (HarvestEvent) values = rand() % 15 + 1;
				else if (ValentineEvent) values = rand() % 30 + 1;
				else values = rand() % 13 + 1;
				switch (values)
				{
				case 1: /*World Lock Event*/
				{
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **World Lock** event spawned in world **" + worlds[i].name + "**", "EVENT");
					Notification = "`2World Locks Rain! `oYou have `wUnlimited `oseconds to find the `w3 `#World Locks `oHidden in this world!";
					ItemID = 242;
					Count = 1;
					Multiple = 3;
					break;
				}
				case 2: /*Surgery Split Event*/
				{
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **Surgery Pack** event spawned in world **" + worlds[i].name + "**", "EVENT");
					Notification = "`2Surgical Split! `oYou have `wUnlimited `oseconds to find the `#Surgery Tool Pack `oHidden in this world!";
					ItemID = 9644;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 3: /*The Fireworks Event*/
				{
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **Fire Works** event spawned in world **" + worlds[i].name + "**", "EVENT");
					Notification = "`2Bright Lights! `oYou have `wUnlimited `oseconds to find the `w5 `#Fireworks `oHidden in this world!";
					ItemID = 834;
					Count = 1;
					Multiple = 5;
					break;
				}
				case 6: case 4: case 5: /*Beautiful Crystal Event*/
				{
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **Bountiful Crystal** event spawned in world **" + worlds[i].name + "**", "EVENT");
					Notification = "`2Beautiful Crystal! `oYou have `wUnlimited `oseconds to find the `#Crystal Block Seed `oHidden in this world!";
					ItemID = 263;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 7: /*Magical Seeds Event*/
				{
					/*auto SeedID = rand() % maxItems;
					if (!isSeed(SeedID)) SeedID += 1;
					Notification = "`2Magical Seeds! `oYou have `wUnlimited `oseconds to find the `#" + getItemDef(SeedID).name + " `oHidden in this world!";
					ItemID = SeedID;
					Count = 1;
					Multiple = 1;
					break;*/
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **Bountiful Crystal** event spawned in world **" + worlds[i].name + "**", "EVENT");
					Notification = "`2Beautiful Crystal! `oYou have `wUnlimited `oseconds to find the `#Crystal Block Seed `oHidden in this world!";
					ItemID = 263;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 8: /*Luck of the Growish Event*/
				{
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **Lucky Clover** event spawned in world **" + worlds[i].name + "**", "EVENT");
					Notification = "`2Luck of the Growish! `oYou have `wUnlimited `oseconds to find the `#Lucky Clover `oHidden in this world!";
					ItemID = 528;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 10: case 9: /*What's that?*/
				{
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **Doohickey** event spawned in world **" + worlds[i].name + "**", "EVENT");
					Notification = "`2What's that?! `oYou have `wUnlimited `oseconds to find the `#Doohickey `oHidden in this world!";
					ItemID = 1396;
					Count = 1;
					Multiple = 1;
					break;
				}
				case 11: /*Egg Hunt*/
				{
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **Egg hunt** event spawned in world **" + worlds[i].name + "**", "EVENT");
					Notification = "`2Egg Hunt! `oGo find them eggs! `w20 `#Magic Eggs `owill spawn in the world!";
					ItemID = 611;
					Count = 1;
					Multiple = 20;
					break;
				}
				case 12: /*Jackpot*/
				{
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **Jackpot Gems** event spawned in world **" + worlds[i].name + "**", "EVENT");
					Notification = "`2Jackpot! `oGems are spawned throughout the world!";
					ItemID = 112;
					Count = 1;
					Multiple = 100;
					break;
				}
				case 13: /*Songpyeon Hunt (harvest fest only)*/
				{
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **Songpyeon** event spawned in world **" + worlds[i].name + "**", "EVENT");
					Notification = "`2Songpyeon Hunt! `oYou have `wUnlimited `oseconds to find the `w3 `#Songpyeons `oHidden in this world!";
					ItemID = 1056;
					Count = 1;
					Multiple = 3;
					break;
				}
				case 14: /*Mooncake Rain (harvest fest only)*/
				{
					SendConsole("[" + to_string(Hour) + ":" + to_string(Min) + ":" + to_string(Sec) + "] EVENT : **Mooncake Rain** event spawned in world **" + worlds[i].name + "**", "EVENT");
					vector<int> CakeBase{ 1058, 1094, 1096, 1098, 1828, 3870, 7058 };
					const int Index = rand() % CakeBase.size();
					const auto IID = CakeBase[Index];
					Notification = "`2Mooncake Rain! `oYou have `wUnlimited `oseconds to find the `#" + getItemDef(IID).name + " `oHidden in this world!";
					ItemID = IID;
					Count = 1;
					Multiple = 5;
					break;
				}
				default: break;
				}
				for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (EventWorld(currentPeer, worlds[i].name)) /*Display message for all players in world*/
					{
						Player::OnAddNotification(currentPeer, Notification, "audio/cumbia_horns.wav", "interface/large/special_event.rttex");
					}
				}
				if (ItemID != 0) SpawnEventItem(worlds[i].name, ItemID, Count, Time, worlds[i].width, worlds[i].height, Multiple); /*Spawn the Item*/
				break;
			}
		}
	}
}
