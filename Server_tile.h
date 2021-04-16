// ReSharper disable All
#pragma once
#include "stdafx.h"
#include <fstream>
// ReSharper disable once CppUnusedIncludeDirective
#include <iostream>
#include "Server_player.h"
#include "Server_world.h"
#include "enet/enet.h"
// ReSharper disable once CppUnusedIncludeDirective
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <locale>
#include <regex>
#include <string>
#include <thread>
#include <vector>
#include <experimental/filesystem>
#include "json.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "Player_mods.h"
#ifdef _WIN32
#include <windows.h>
typedef __int8 __int8_t;
typedef __int16 __int16_t;
#elif __APPLE__ || __linux__
typedef unsigned int DWORD;
#endif
typedef unsigned char BYTE;

inline void sendTileUpdate(int x, int y, int tile, int causedBy, ENetPeer* peer)
{
	if (serverIsFrozen == true) return;
	if (tile > itemDefs.size()) return;
	if (!static_cast<PlayerInfo*>(peer->data)->haveGrowId)
	{
		SendBreakPacket(peer, x, y);
		return;
	}
	if (static_cast<PlayerInfo*>(peer->data)->isIn == false) return;
	if (static_cast<PlayerInfo*>(peer->data)->currentWorld == "EXIT") return;
	auto dicenr = 0;
	PlayerMoving data;
	data.packetType = 0x3;
	data.characterState = 0x0;
	data.x = x;
	data.y = y;
	data.punchX = x;
	data.punchY = y;
	data.XSpeed = 0;
	data.YSpeed = 0;
	data.netID = causedBy;
	data.plantingTree = tile;
	auto isTree = false;
	auto isLock = false;
	auto isHeartMonitor = false;
	auto isgateway = false;
	auto world = getPlyersWorld(peer);
	auto squaresign = x + (y * 100);
	auto iscontains = false;
	if (world == nullptr) return;
	if (x < 0 || y < 0 || x > world->width - 1 || y > world->height - 1 || tile > itemDefs.size()) return;
	bool tanga = false;
	SendBreakPacket(peer, x, y);
	using namespace std::chrono;
	if (world->isworldsave == true) {
		Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wThe world is saving, Please wait!", 0, true);
		return;
	}
	if (world->lastsave + 30000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
	{
		world->lastsave = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
		world->isworldsave = true;
		SaveMyWorld(peer);
	}
	auto exists = experimental::filesystem::exists("worlds/_" + world->name + ".json");
	if (exists) {
		std::streampos fsize = 0;
		std::ifstream myfile("worlds/_" + world->name + ".json", ios::in);
		fsize = myfile.tellg();
		myfile.seekg(0, ios::end);
		fsize = myfile.tellg() - fsize;
		myfile.close();
		static_assert(sizeof(fsize) >= sizeof(long long), "Oops.");
		if (fsize <= 955000)
		{
			SendConsole("World " + world->name + " is corrupted! Saved server from crash...", "ERROR");
			worldDB.remove(world->name);
			for (auto currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, currentPeer))
				{
					Player::OnConsoleMessage(currentPeer, "`4Oh no! ``This world have been corrupted. We had to make you leave!");
					sendPlayerLeave(currentPeer, static_cast<PlayerInfo*>(peer->data));
					sendWorldOffers(currentPeer);
				}
			}
			return;
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer) || isDev(peer) || isWorldAdmin(peer, world)) {
		if (tile == 1276) {
			int x;
			int y;
			bool found_one = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 1276) {

					found_one = true;
				}
			}
			if (found_one) {
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can only place this block once in your world!", 0, true);
				return;
			}
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer) || isDev(peer) || isWorldAdmin(peer, world)) {
		if (tile == 1278) {
			int x;
			int y;
			bool found_one = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 1278) {

					found_one = true;
				}
			}
			if (found_one) {
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can only place this block once in your world!", 0, true);
				return;
			}
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer) || isDev(peer) || isWorldAdmin(peer, world)) {
		if (tile == 3616) {
			int x;
			int y;
			bool found_one = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 3616) {

					found_one = true;
				}
			}
			if (found_one) {
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can only place this block once in your world!", 0, true);
				return;
			}
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer) || isDev(peer) || isWorldAdmin(peer, world)) {
		if (tile == 226) {
			int x;
			int y;
			bool found_one = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 226) {

					found_one = true;
				}
			}
			if (found_one) {
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can only place this block once in your world!", 0, true);
				return;
			}
		}
	}
	if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer) || isDev(peer) || isWorldAdmin(peer, world)) {
		if (tile == 7560) {
			int x;
			int y;
			bool found_one = false;
			for (int i = 0; i < world->width * world->height; i++)
			{
				if (world->items[i].foreground == 7560) {

					found_one = true;
				}
			}
			if (found_one) {
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can only place this block once in your world!", 0, true);
				return;
			}
		}
	}
	if (tile == world->breakid) {
		thread checkPlayerState(ngekngek, peer, x, y);
		if (checkPlayerState.joinable()) {
			checkPlayerState.detach();
		}
	}
	if (tile == 32 && world->items[x + (y * world->width)].foreground == 6954) {
		if (isWorldOwner(peer, world) || isMod(peer) || isDev(peer) || isWorldAdmin(peer, world)) {
			if (static_cast<PlayerInfo*>(peer->data)->rawName!= "hypercold") {
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wSorry, Currently disabled...", 0, true);
				return;
			}
			static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
			static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
			int noclap = 0;
			bool casin = world->isstarted;
			if (casin == true) {
				noclap = 1;
			}
			else {
				noclap = 0;
			}
			if (world->breakid != 0) {
				Player::OnDialogRequest(peer, "\nadd_label_with_icon|big|`$Techno Organic Machine|left|6954|\nadd_spacer|small|\nadd_label_with_icon|small|`2" + getItemDef(world->breakid).name + "|left|" + to_string(world->breakid) + "|\nadd_spacer|small|\nadd_checkbox|techno|Breaking Activated|" + to_string(noclap) + "|\nadd_item_picker|technoitem|Change the item|Choose an item to put in the Machine!|\nadd_spacer|small|\nend_dialog||Close|Update|");
			}
			else {
				Player::OnDialogRequest(peer, "\nadd_label_with_icon|big|`$Techno Organic Machine|left|6954|\nadd_spacer|small|\nadd_item_picker|technoitem|Put item in|Choose an item to put in the Machine!|\nadd_spacer|small|\nend_dialog||Close|");
			}
		}
	}
	/*if (tile == 32 && isWorldOwner(peer, world) || isMod(peer) || isDev(peer)) {
		if (world->items[x + (y * world->width)].foreground == 6954) {
			static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
			static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
			string tanga;
			string bobo;
			string gago;
			string putangina;
			if (world->technogems != 0) {
				putangina = "\nadd_smalltext|`$Your techno contains `5" + to_string(world->technogems) + " `$gems!|left|\nadd_button|technogems|`$Collect your gems|left|\nadd_spacer|small|";
			}
			int count = 0;
			if (world->breakid != 0) {
				tanga = "\nadd_label_with_icon|small|`2" + getItemDef(world->breakid).name + "|left|" + to_string(world->breakid) + "|\nadd_spacer|small|";

			}
			else {
				tanga = "\nadd_item_picker|technoitem|Put item in|Choose an item to put in the Machine!|\nadd_spacer|small|";
			}

			if (world->breakid != 0) {
				for (auto i = 0; i < world->width * world->height; i++) {
					if (world->items[i].foreground == world->breakid) {
						count++;
						bobo = "\nadd_smalltext|`$Your world contains `2" + to_string(count) + " `$" + getItemDef(world->breakid).name + " Placed!|left|\nadd_spacer|small|";
					}
				}
			}
			if (count != 0) {
				gago = "\nadd_button|break|`$Break `5" + to_string(count) + " `$" + getItemDef(world->breakid).name + "|left|\nadd_item_picker|technoitem|Change the item|Choose an item to put in the Machine!|\nadd_spacer|small|";
			}
			else {
				gago = "\nadd_item_picker|technoitem|Change the item|Choose an item to put in the Machine!|\nadd_spacer|small|";
			}
			Player::OnDialogRequest(peer, "\nadd_label_with_icon|big|`$Techno Organic Machine|left|6954|left|\nadd_spacer|small|" + tanga + "\nadd_smalltext|Tired at smashing blocks on your own? Perhaps it's time we meddled in the darker side of science and made our lives easier! Fuel this advanced machinery with enough Gems, tell it to target any block of your choosing, and it will break them AUTOMATICALLY! Note: Blocks broken by this device will not drop gems! It's convenient, but inefficient! Activating this machine will break all of the block that you wan't the machine to break AUTOMATICALLY, It will have 5 minutes cooldown once you activated the machine, you may activate it again once the 5 minutes was done! If you will break farmables, gems will automatically going to the machine so you can collect once the process was done!|left|\nadd_spacer|small|" + bobo + "" + gago + "" + putangina + "\nend_dialog||Close|");
		}
	}*/
	if (world->name == "HELL" && static_cast<PlayerInfo*>(peer->data)->isCursed == true)
	{
		return;
	}
	
	int netID = static_cast<PlayerInfo*>(peer->data)->netID;
	auto contains = false;
	SearchInventoryItem(peer, tile, 1, contains);
	if (!contains)	return;
	if (world->items[x + (y * world->width)].foreground == 3794 && tile != 32 && tile != 18) {
		bool iscontains = false;
		SearchInventoryItem(peer, tile, 1, iscontains);
		if (!iscontains)
		{
			enet_peer_disconnect(peer, 0);
			return;
		}
		if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->adminLevel > 1) {
			if (tile == 5142) {
				return;
			}
			if (world->items[x + (y * world->width)].dshelf1 == 0 && world->items[x + (y * world->width)].dshelf2 == 0 && world->items[x + (y * world->width)].dshelf3 == 0 && world->items[x + (y * world->width)].dshelf4 == 0) {

				world->items[x + (y * world->width)].dshelf1 = tile;
				if (isMod(peer)) {
					SendConsole("[DSHELF] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** displays 1 **" + getItemDef(tile).name + "**", "LOGS2");
				}
				SendConsole("[DSHELF] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** displays 1 **" + getItemDef(tile).name + "**", "LOGS");
				RemoveInventoryItem(tile, 1, peer, "");
			}
			else if (world->items[x + (y * world->width)].dshelf1 != 0 && world->items[x + (y * world->width)].dshelf2 == 0 && world->items[x + (y * world->width)].dshelf3 == 0 && world->items[x + (y * world->width)].dshelf4 == 0) {

				world->items[x + (y * world->width)].dshelf2 = tile;
				if (isMod(peer)) {
					SendConsole("[DSHELF] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** displays 1 **" + getItemDef(tile).name + "**", "LOGS2");
				}
				SendConsole("[DSHELF] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** displays 1 **" + getItemDef(tile).name + "**", "LOGS");
				RemoveInventoryItem(tile, 1, peer, "");
			}
			else if (world->items[x + (y * world->width)].dshelf1 != 0 && world->items[x + (y * world->width)].dshelf2 != 0 && world->items[x + (y * world->width)].dshelf3 == 0 && world->items[x + (y * world->width)].dshelf4 == 0) {

				world->items[x + (y * world->width)].dshelf3 = tile;
				if (isMod(peer)) {
					SendConsole("[DSHELF] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** displays 1 **" + getItemDef(tile).name + "**", "LOGS2");
				}
				SendConsole("[DSHELF] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** displays 1 **" + getItemDef(tile).name + "**", "LOGS");
				RemoveInventoryItem(tile, 1, peer, "");
			}
			else if (world->items[x + (y * world->width)].dshelf1 != 0 && world->items[x + (y * world->width)].dshelf2 != 0 && world->items[x + (y * world->width)].dshelf3 != 0 && world->items[x + (y * world->width)].dshelf4 == 0) {

				world->items[x + (y * world->width)].dshelf4 = tile;
				if (isMod(peer)) {
					SendConsole("[DSHELF] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** displays 1 **" + getItemDef(tile).name + "**", "LOGS2");
				}
				SendConsole("[DSHELF] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** displays 1 **" + getItemDef(tile).name + "**", "LOGS");
				RemoveInventoryItem(tile, 1, peer, "");
			}
			else {
				return;
			}

			ENetPeer* currentPeer;

			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (isHere(peer, currentPeer))
				{
					SendThrowEffect(currentPeer, tile, netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
					sendDShelf(currentPeer, x, y, world->items[x + (y * world->width)].dshelf1, world->items[x + (y * world->width)].dshelf2, world->items[x + (y * world->width)].dshelf3, world->items[x + (y * world->width)].dshelf4);
				}
			}
		}
	}
	if (tile == 732) {
		int xx = data.punchX;
		int yy = data.punchY;
		ENetPeer* currentPeer;
		for (currentPeer = server->peers;
			currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
				continue;
			if (((PlayerInfo*)(currentPeer->data))->x / 32 == xx && ((PlayerInfo*)(currentPeer->data))->y / 32 == yy) {
				bool iscontainseas = false;
				SearchInventoryItem(peer, 732, 1, iscontainseas);
				if (!iscontainseas)
				{
					((PlayerInfo*)(peer->data))->lastInfoAboutPlayer = ((PlayerInfo*)(peer->data))->rawName;
					BanTime(peer, 60, true, "Item undetectable (item id = 732)");
					break;
				}
				else {
					RemoveInventoryItem(732, 1, peer, "");
					ENetPeer* currentPeer2;
					for (currentPeer2 = server->peers;
						currentPeer2 < &server->peers[server->peerCount];
						++currentPeer2)
					{
						if (currentPeer2->state != ENET_PEER_STATE_CONNECTED)
							continue;
						if (((PlayerInfo*)(currentPeer2->data))->haveGrowId == false) continue;
						if (((PlayerInfo*)(currentPeer->data))->rawName == ((PlayerInfo*)(currentPeer2->data))->rawName)
						{
							((PlayerInfo*)(peer->data))->lastInfoAboutPlayer = ((PlayerInfo*)(currentPeer2->data))->rawName;
							BanTime(peer, 10, true, "Player " + ((PlayerInfo*)(peer->data))->rawName + " used banwand on you.");
						}
					}
				}
			}
			else {

			}
		}
	}
	if (tile == 10456) {
		if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
		{
			if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 10426) {
				((PlayerInfo*)(peer->data))->cloth_back = 10456;
				((PlayerInfo*)(peer->data))->noEyes = true;
				((PlayerInfo*)(peer->data))->noBody = true;
				((PlayerInfo*)(peer->data))->noHands = true;
				((PlayerInfo*)(peer->data))->isInvisible = true;
				send_state(peer);
				GamePacket p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), ((PlayerInfo*)(peer->data))->cloth_hair, ((PlayerInfo*)(peer->data))->cloth_shirt, ((PlayerInfo*)(peer->data))->cloth_pants), ((PlayerInfo*)(peer->data))->cloth_feet, ((PlayerInfo*)(peer->data))->cloth_face, ((PlayerInfo*)(peer->data))->cloth_hand), ((PlayerInfo*)(peer->data))->cloth_back, ((PlayerInfo*)(peer->data))->cloth_mask, ((PlayerInfo*)(peer->data))->cloth_necklace), ((PlayerInfo*)(peer->data))->skinColor), 0.0f, 0.0f, 0.0f));
				memcpy(p3.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				ENetPacket* packet3 = enet_packet_create(p3.data,
					p3.len,
					ENET_PACKET_FLAG_RELIABLE);
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						enet_peer_send(currentPeer, 0, packet3);
					}
				}
			}
		}
	}
	if (tile == 7480) {
		if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
		{
			if (static_cast<PlayerInfo*>(peer->data)->cloth_feet == 7384) {
				((PlayerInfo*)(peer->data))->cloth_back = 7480;
				((PlayerInfo*)(peer->data))->noEyes = true;
				((PlayerInfo*)(peer->data))->noBody = true;
				((PlayerInfo*)(peer->data))->noHands = true;
				((PlayerInfo*)(peer->data))->isInvisible = true;
				send_state(peer);
				GamePacket p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), ((PlayerInfo*)(peer->data))->cloth_hair, ((PlayerInfo*)(peer->data))->cloth_shirt, ((PlayerInfo*)(peer->data))->cloth_pants), ((PlayerInfo*)(peer->data))->cloth_feet, ((PlayerInfo*)(peer->data))->cloth_face, ((PlayerInfo*)(peer->data))->cloth_hand), ((PlayerInfo*)(peer->data))->cloth_back, ((PlayerInfo*)(peer->data))->cloth_mask, ((PlayerInfo*)(peer->data))->cloth_necklace), ((PlayerInfo*)(peer->data))->skinColor), 0.0f, 0.0f, 0.0f));
				memcpy(p3.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
				ENetPacket* packet3 = enet_packet_create(p3.data,
					p3.len,
					ENET_PACKET_FLAG_RELIABLE);
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						enet_peer_send(currentPeer, 0, packet3);
					}
				}
			}
		}
	}
	if (world->items[x + (y * world->width)].foreground == 3794) {
		if (tile == 32) {
			if (world->owner == "" || ((PlayerInfo*)(peer->data))->rawName == PlayerDB::getProperName(world->owner) || ((PlayerInfo*)(peer->data))->adminLevel > 3) {
				static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);
				string dshelf1;
				string dshelf2;
				string dshelf3;
				string dshelf4;
				if (world->items[x + (y * world->width)].dshelf1 != 0) {
					dshelf1 = "`$" + getItemDef(world->items[x + (y * world->width)].dshelf1).name + "";
				}
				else {
					dshelf1 = "`$EMPTY";
				}
				if (world->items[x + (y * world->width)].dshelf2 != 0) {
					dshelf2 = "`$" + getItemDef(world->items[x + (y * world->width)].dshelf2).name + "";
				}
				else {
					dshelf2 = "`$EMPTY";
				}
				if (world->items[x + (y * world->width)].dshelf3 != 0) {
					dshelf3 = "`$" + getItemDef(world->items[x + (y * world->width)].dshelf3).name + "";
				}
				else {
					dshelf3 = "`$EMPTY";
				}
				if (world->items[x + (y * world->width)].dshelf4 != 0) {
					dshelf4 = "`$" + getItemDef(world->items[x + (y * world->width)].dshelf4).name + "";
				}
				else {
					dshelf4 = "`$EMPTY";
				}
				string gscan = "set_default_color|`o\nadd_label_with_icon|big|`wDisplay Shelf``|left|3794|\nadd_spacer|small|\nadd_button|dshelf1|`wShelf 1 : " + dshelf1 + "|left|\nadd_button|dshelf2|`wShelf 2 : " + dshelf2 + "|left|\nadd_button|dshelf3|`wShelf 3 : " + dshelf3 + "|left|\nadd_button|dshelf4|`wShelf 4 : " + dshelf4 + "|left|\nadd_spacer|small|\nend_dialog||Close|";
				GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), gscan));
				ENetPacket* packet = enet_packet_create(p.data,
					p.len,
					ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(peer, 0, packet);
				delete p.data;
			}
		}
	}
	switch (tile)
	{
	case 18: /*punch*/
	{
		if (world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214 || world->items[x + (y * world->width)].foreground == 9202 || world->items[x + (y * world->width)].foreground == 10072 || world->items[x + (y * world->width)].foreground == 10074 || world->items[x + (y * world->width)].foreground == 10076 || world->items[x + (y * world->width)].foreground == 10078)
		{
			if (world->owner == "" || isWorldAdmin(peer, world) || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || isDev(peer) || isMod(peer))
			{
				auto seedexist = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (seedexist)
				{
					json j;
					ifstream fs("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					fs >> j;
					fs.close();
					bool found = false, success = false;
					if (j["clothHead"].get<string>() != "0")
					{
						SaveItemMoreTimes(atoi(j["clothHead"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
						found = true;
						if (isMod(peer)) {
							SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothHead"].get<string>().c_str())).name + "**", "LOGS2");
						}
						SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothHead"].get<string>().c_str())).name + "**", "LOGS");
						j["clothHead"] = "0";
					}
					else if (j["clothHair"].get<string>() != "0")
					{
						SaveItemMoreTimes(atoi(j["clothHair"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
						found = true;
						if (isMod(peer)) {
							SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothHair"].get<string>().c_str())).name + "**", "LOGS2");
						}
						SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothHair"].get<string>().c_str())).name + "**", "LOGS");
						j["clothHair"] = "0";
					}
					else if (j["clothMask"].get<string>() != "0")
					{
						SaveItemMoreTimes(atoi(j["clothMask"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
						found = true;
						if (isMod(peer)) {
							SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothMask"].get<string>().c_str())).name + "**", "LOGS2");
						}
						SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothMask"].get<string>().c_str())).name + "**", "LOGS");
						j["clothMask"] = "0";
					}
					else if (j["clothNeck"].get<string>() != "0")
					{
						SaveItemMoreTimes(atoi(j["clothNeck"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
						found = true;
						if (isMod(peer)) {
							SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothNeck"].get<string>().c_str())).name + "**", "LOGS2");
						}
						SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothNeck"].get<string>().c_str())).name + "**", "LOGS");
						j["clothNeck"] = "0";
					}
					else if (j["clothBack"].get<string>() != "0")
					{
						SaveItemMoreTimes(atoi(j["clothBack"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
						found = true;
						if (isMod(peer)) {
							SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothBack"].get<string>().c_str())).name + "**", "LOGS2");
						}
						SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothBack"].get<string>().c_str())).name + "**", "LOGS");
						j["clothBack"] = "0";
					}
					else if (j["clothShirt"].get<string>() != "0")
					{
						SaveItemMoreTimes(atoi(j["clothShirt"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
						found = true;
						if (isMod(peer)) {
							SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothShirt"].get<string>().c_str())).name + "**", "LOGS2");
						}
						SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothShirt"].get<string>().c_str())).name + "**", "LOGS");
						j["clothShirt"] = "0";
					}
					else if (j["clothPants"].get<string>() != "0")
					{
						SaveItemMoreTimes(atoi(j["clothPants"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
						found = true;
						if (isMod(peer)) {
							SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothPants"].get<string>().c_str())).name + "**", "LOGS2");
						}
						SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothPants"].get<string>().c_str())).name + "**", "LOGS");
						j["clothPants"] = "0";
					}
					else if (j["clothFeet"].get<string>() != "0")
					{
						SaveItemMoreTimes(atoi(j["clothFeet"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
						found = true;
						if (isMod(peer)) {
							SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothFeet"].get<string>().c_str())).name + "**", "LOGS2");
						}
						SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothFeet"].get<string>().c_str())).name + "**", "LOGS");
						j["clothFeet"] = "0";
					}
					else if (j["clothHand"].get<string>() != "0")
					{
						SaveItemMoreTimes(atoi(j["clothHand"].get<string>().c_str()), 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from Mannequin");
						found = true;
						if (isMod(peer)) {
							SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothHand"].get<string>().c_str())).name + "**", "LOGS2");
						}
						SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** removed 1 **" + getItemDef(atoi(j["clothHand"].get<string>().c_str())).name + "**", "LOGS");
						j["clothHand"] = "0";
					}
					if (found)
					{
						updateMannequin(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].sign,
							atoi(j["clothHair"].get<string>().c_str()), atoi(j["clothHead"].get<string>().c_str()),
							atoi(j["clothMask"].get<string>().c_str()), atoi(j["clothHand"].get<string>().c_str()), atoi(j["clothNeck"].get<string>().c_str()),
							atoi(j["clothShirt"].get<string>().c_str()), atoi(j["clothPants"].get<string>().c_str()), atoi(j["clothFeet"].get<string>().c_str()),
							atoi(j["clothBack"].get<string>().c_str()), true, 0);

						ofstream of("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						of << j;
						of.close();
					}
				}
			}
		}
		if (world->items[x + (y * world->width)].foreground == 2398) {
			Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wWinter Quest``|left|18|\nadd_spacer|small|\nadd_button|claimquest|`wClaim : `cWinterfest Wings|left|\nadd_spacer|small|\nend_dialog||Later, Thankyou!|\nadd_quick_exit");
		}
		if (world->items[x + (y * world->width)].foreground == 758) sendRoulete(peer);
		if (world->owner != "" && !isWorldOwner(peer, world))
		{
			if (!isMod(peer))
			{
				if (isWorldAdmin(peer, world))
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
				else if (world->isPublic)
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
				else if (world->isEvent)
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
					else if (world->items[x + (y * world->width)].foreground != world->interactableid)
					{
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
				else
				{
					if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false)
					{
						Player::OnTextOverlay(peer, "`#Create `9Grow-ID `#First`9!");
					}
					else
					{
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
			}
			if (tile == 18 && isMod(peer))
			{
				if (isWorldAdmin(peer, world) && !isWorldOwner(peer, world))
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
					}
				}
				else if (world->isPublic && !isWorldOwner(peer, world))
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
					}
				}
				else if (world->isEvent && !isWorldOwner(peer, world))
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
					}
				}
			}
		}
		if (!isDev(peer))
		{
			if (world->items[x + (y * world->width)].foreground == 6)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wIt's too strong to break.", 0, true);
				return;
			}
			if (world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 7372 || world->items[x + (y * world->width)].foreground == 3760)
			{
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 8452)
				{
				}
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wIt's too strong to break.", 0, true);
					return;
				}
			}
			if (tile == 9444)
			{
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2952 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9430 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9448 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9452 || static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2592)
				{
				}
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5This stone is too strong!", 0, true);
					return;
				}
			}
			if (tile == 6 || tile == 3760 || tile == 1000 || tile == 7372 || tile == 1770 || tile == 1832 || tile == 4720)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wIt's too heavy to place.", 0, true);
				return;
			}
		}
		
		if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::WEATHER && isWorldOwner(peer, world)) SendWeather(peer, tile, world, x, y);
		if (world->items[x + (y * world->width)].foreground == 10026 || world->items[x + (y * world->width)].foreground == 9474)
		{
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 5480)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `wRayman`@!");
				return;
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9430)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `9Golden Spade`@!");
				return;
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9452)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `#Rainbow Spade`@!");
				return;
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9454)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `4Demon Spade`@!");
				return;
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9456)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `9Golden `4Demon Spade`@!");
				return;
			}
			if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 10390)
			{
				Player::OnTextOverlay(peer, "`@You can't break this `4Block `@With `4Burning Spade`@!");
				return;
			}
		}
		if (world->items[x + (y * world->width)].foreground == 1008)
		{
			if (static_cast<PlayerInfo*>(peer->data)->haveGrowId && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner || isMod(peer))
			{
				int valgem;
				valgem = rand() % 40;
				std::ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
				using namespace std::chrono;
				if (static_cast<PlayerInfo*>(peer->data)->lastATM + 1200 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
				{
					static_cast<PlayerInfo*>(peer->data)->lastATM = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				}
				else
				{
					int kiekDar = (static_cast<PlayerInfo*>(peer->data)->lastATM + 1200 - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count());
					long milli = kiekDar;
					auto hr = milli / 3600000;
					milli = milli - 3600000 * hr;
					auto min = milli / 60000;
					milli = milli - 60000 * min;
					auto sec = milli / 1000;
					Player::OnConsoleMessage(peer, "`9Cooldown `@Please Wait `9" + to_string(sec) + "s. `@To Use ATM!");
					return;
				}
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`^You found `9" + std::to_string(valgem) + " `2Gems`w!", 0, true);
				auto gembux = atoi(content.c_str());
				auto fingembux = gembux + valgem;
				ofstream myfile;
				myfile.open("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				myfile << fingembux;
				myfile.close();
				auto gemcalc = gembux + valgem;
				Player::OnSetBux(peer, gemcalc, 0);
				auto hi = data.punchX * 32;
				auto hi2 = data.punchY * 32;
				Player::OnParticleEffect(peer, 29, hi, hi2, 0);
			}
			else
			{
				Player::OnConsoleMessage(peer, "`@You don't have access to break this `eATM Machine`@!");
			}
		}
		if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEMICAL_COMBINER || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEST)
		{
			if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isDev(peer) || isWorldAdmin(peer, world))
			{
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEMICAL_COMBINER)
				{
					if (world->items[x + (y * world->width)].activated)
					{

						SendCombiner(peer, x, y, 1096, 1098, 1828, 4, 4, 6, 1056, true); /*Songpyeon*/
						SendCombiner(peer, x, y, 1056, 1096, 1828, 15, 30, 15, 1804, true); /*Zeus Lightning Bolt*/
						SendCombiner(peer, x, y, 611, 874, 0, 100, 15, 0, 1552, false); /*Pet Bunny Recipe*/
						SendCombiner(peer, x, y, 1056, 1804, 3870, 5, 10, 15, 1824, true); /*AutumnWings*/
						SendCombiner(peer, x, y, 1056, 7058, 10030, 3, 10, 1, 1826, true); /*AutumnBomb*/
						SendCombiner(peer, x, y, 1056, 1804, 10030, 1, 5, 1, 3074, true); /*FloatingLeaf*/
						SendCombiner(peer, x, y, 10322, 10324, 10326, 1, 1, 1, 10328, false); /*Dark Kings Offering*/
						SendCombiner(peer, x, y, 898, 4538, 5018, 2, 1, 1, 5022, false); /*Chicken Plow*/
						SendCombiner(peer, x, y, 2274, 5026, 5028, 1, 5, 20, 5060, false); /*Verdant Gate*/
						SendCombiner(peer, x, y, 2274, 5028, 5024, 1, 5, 20, 5054, false); /*Inferno Gate*/
						SendCombiner(peer, x, y, 2274, 5024, 5030, 1, 5, 20, 5058, false); /*Typhoon Gate*/
						SendCombiner(peer, x, y, 2274, 5030, 5026, 1, 5, 20, 5056, false); /*Tidal Gate*/
						SendCombiner(peer, x, y, 2492, 5028, 5026, 1, 20, 5, 5050, false); /*Earth Asteroid*/
						SendCombiner(peer, x, y, 2492, 5024, 5028, 1, 20, 5, 5046, false); /*Fire Asteroid*/
						SendCombiner(peer, x, y, 2492, 5030, 5024, 1, 20, 5, 5052, false); /*Wind Asteroid*/
						SendCombiner(peer, x, y, 2492, 5026, 5030, 1, 20, 5, 5048, false); /*Water Asteroid*/
						SendCombiner(peer, x, y, 3946, 5060, 5028, 100, 4, 5, 5070, false); /*Crystallized Reality*/
						SendCombiner(peer, x, y, 3838, 5054, 5024, 200, 4, 5, 5072, false); /*Crystallized Wealth*/
						SendCombiner(peer, x, y, 340, 5058, 5030, 200, 4, 5, 5074, false); /*Crystallized Brilliance*/
						SendCombiner(peer, x, y, 2272, 5056, 5026, 30, 4, 5, 5076, false); /*Crystallized Nature*/
						SendCombiner(peer, x, y, 5050, 5048, 5028, 2, 2, 5, 5066, false); /*Ancient Bracket*/
						SendCombiner(peer, x, y, 5046, 5052, 5024, 2, 2, 5, 5062, false); /*Ancient Hinge*/
						SendCombiner(peer, x, y, 5052, 5050, 5030, 2, 2, 5, 5068, false); /*Ancient Lens*/
						SendCombiner(peer, x, y, 5048, 5046, 5026, 2, 2, 5, 5064, false); /*Ancient Pin*/
						SendCombiner(peer, x, y, 5070, 5066, 5064, 1, 2, 5, 5080, false); /*Ancestral Tesseract of Dimensions*/
						SendCombiner(peer, x, y, 5076, 5068, 5066, 1, 2, 5, 5082, false); /*Ancestral Seed of Life*/
						SendCombiner(peer, x, y, 5072, 5064, 5062, 1, 2, 5, 5084, false); /*Ancestral Lens of Riches*/
						SendCombiner(peer, x, y, 5074, 5062, 5068, 1, 2, 5, 5078, false); /*Ancestral Totem of Wisdom*/
						SendCombiner(peer, x, y, 362, 386, 1458, 1, 200, 1, 1460, false); /*Golden Angel Wings*/
						SendCombiner(peer, x, y, 364, 386, 1458, 1, 200, 1, 1462, false); /*Golden Diaper*/
						SendCombiner(peer, x, y, 1470, 386, 1458, 1, 200, 1, 1466, false); /*Golden Diamond Necklace*/
						SendCombiner(peer, x, y, 366, 386, 1458, 1, 200, 1, 1464, false); /*Golden Heartbow*/
						SendCombiner(peer, x, y, 2388, 386, 1458, 1, 20, 1, 2386, false); /*Heavenly Scythe*/
						SendCombiner(peer, x, y, 2390, 386, 1458, 1, 20, 1, 2392, false); /*Teeny Golden Wings*/
						SendCombiner(peer, x, y, 2384, 386, 1458, 1, 20, 1, 2394, false); /*Golden Love Bug*/
						SendCombiner(peer, x, y, 4412, 386, 1458, 1, 20, 1, 4414, false); /*Golden Pegasus*/
						SendCombiner(peer, x, y, 4416, 386, 1458, 1, 20, 1, 4420, false); /*Golden Heart Glasses*/
						SendCombiner(peer, x, y, 5644, 386, 1458, 1, 20, 1, 5646, false); /*Golden Heart Shirt*/
						SendCombiner(peer, x, y, 5648, 386, 1458, 1, 20, 1, 5650, false); /*Golden Talaria*/
						SendCombiner(peer, x, y, 7826, 386, 1458, 1, 200, 1, 7828, false); /*Golden Heartstaff*/
						SendCombiner(peer, x, y, 7830, 386, 1458, 1, 200, 1, 7832, false); /*Golden Heartsword*/
						SendCombiner(peer, x, y, 7826, 7830, 1458, 1, 1, 1, 7834, false); /*Stained Glass Heartwings*/
						SendCombiner(peer, x, y, 9320, 386, 1458, 1, 200, 1, 9322, false); /*Golden Sunset Cape*/
						SendCombiner(peer, x, y, 9342, 9340, 1458, 1, 1, 1, 9344, false); /*Datemaster's Heart Locket*/
						SendCombiner(peer, x, y, 9324, 386, 1458, 1, 200, 1, 9326, false); /*Golden Heartthrob Helm*/
						SendCombiner(peer, x, y, 9314, 1800, 186, 1, 1, 200, 9316, false); /*Beefy Biceps*/
						SendCombiner(peer, x, y, 1506, 8794, 4406, 1, 1, 1, 9318, false); /*Snuggly Kitty Scarf*/



						UpdateBlockState(peer, x, y, true, world);
						world->items[x + (y * world->width)].activated = false;
					}
					else
					{
						UpdateBlockState(peer, x, y, true, world);
						world->items[x + (y * world->width)].activated = true;
					}
				}
				else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SWITCH_BLOCK || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEST || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SWITCH_BLOCK || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::WRENCH)
				{
					if (world->items[x + (y * world->width)].activated)
					{
						if (world->items[x + (y * world->width)].foreground == 3616) {
							world->enableevent = true;
						}
						if (world->items[x + (y * world->width)].foreground == 226) {
							world->isjammed = false;
						}
						if (world->items[x + (y * world->width)].foreground == 1278) {
							world->zombie = false;
						}
						if (world->items[x + (y * world->width)].foreground == 1276) {
							world->ispunch = false;
						}
						UpdateBlockState(peer, x, y, true, world);
						world->items[x + (y * world->width)].activated = false;
					}
					else
					{
						if (world->items[x + (y * world->width)].foreground == 3616) {
							world->enableevent = false;
						}
						if (world->items[x + (y * world->width)].foreground == 226) {
							world->isjammed = true;
						}
						if (world->items[x + (y * world->width)].foreground == 1278) {
							world->zombie = true;
						}
						if (world->items[x + (y * world->width)].foreground == 1276) {
							world->ispunch = true;
						}
						UpdateBlockState(peer, x, y, true, world);
						world->items[x + (y * world->width)].activated = true;
					}
				}
			}
		}
		if (isSeed(world->items[x + (y * world->width)].foreground))
		{
			if (getPlyersWorld(peer)->isPublic || isWorldAdmin(peer, world) || static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer))
			{
				ENetPeer* net_peer;
				for (net_peer = server->peers;
					net_peer < &server->peers[server->peerCount];
					++net_peer)
				{
					if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, net_peer))
					{
					treeModify(net_peer, x, y, static_cast<PlayerInfo*>(peer->data)->netID);
					}
				}
				auto chance = (rand() % 100) + 1;
				int numb;
				if (getItemDef(world->items[x + (y * world->width)].foreground).rarity == 999)
				{
					numb = (rand() % 1) + 1;
				}
				else
				{
					numb = (rand() % 3) + 1;
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 6840)
				{
					auto chance1 = (rand() % 100) + 1;
					if (chance1 <= 30)
					{
						numb += 1;
						Player::OnParticleEffect(peer, 49, data.punchX * 32, data.punchY * 32, 0);
					}
				}
				if (chance < 30)
				{
					DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 112, 1, 0);
				}
				if (chance < 15 && getItemDef(world->items[x + (y * world->width)].foreground).rarity != 999)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "A " + getItemDef(world->items[x + (y * world->width)].foreground).name + " seed falls out!", 0, true);
					DropItem(peer, -1, x * 32 - (rand() % 8), y * 32 + (rand() % 8), world->items[x + (y * world->width)].foreground, 1, 0);
				}
				DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), world->items[x + (y * world->width)].foreground - 1, numb, 0);
				auto squaresign = x + (y * 100);
				auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
				remove(("misc/seeds/" + currentworld + ".txt").c_str());
				SendGuildPoints(peer, 3);
				if (HarvestEvent)
				{
					SendHarvestFestivalDrop(peer, x, y, getItemDef(world->items[x + (y * world->width)].foreground).rarity);
				}
				world->items[x + (y * world->width)].foreground = 0;
				return;
			}
			return;
		}
		if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9482)
		{
			if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner && static_cast<PlayerInfo*>(peer->data)->haveGrowId == true || isMod(peer))
			{
				auto xlast = static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
				auto ylast = static_cast<PlayerInfo*>(peer->data)->lastPunchX = y;
				changetile(peer, xlast, ylast);
				auto hi = static_cast<PlayerInfo*>(peer->data)->lastPunchX;
				auto hi2 = static_cast<PlayerInfo*>(peer->data)->lastPunchY;
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
						continue;
					if (isHere(peer, currentPeer))
					{
						Player::OnParticleEffect(currentPeer, 168, hi, hi2, 0);
					}
				}
			}
		}
		if (!static_cast<PlayerInfo*>(peer->data)->Fishing) break;
	}
	case 2480:
	{
		using namespace std::chrono;
		if (((PlayerInfo*)(peer->data))->lastSB + 60000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
		{
			((PlayerInfo*)(peer->data))->lastSB = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			int x = static_cast<PlayerInfo*>(peer->data)->x;
			int y = static_cast<PlayerInfo*>(peer->data)->y;
			bool iscontains = false;
			SearchInventoryItem(peer, 2480, 1, iscontains);
			if (!iscontains)
			{
				return;
			}
			GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "set_default_color|`w\n\nadd_label_with_icon|big|`wMegaphone|left|2480|\nadd_spacer|small|\nadd_label_with_icon|small|`oThis will broadcast to all players in the server!|left|486|\nadd_spacer|small|\nadd_text_input|sbtext|||50|\nend_dialog|sendsb|Cancel|Broadcast!|\n"));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);

			enet_peer_send(peer, 0, packet2);
			delete p2.data;
			return;
		}
		else {
			int kiekDar = (((PlayerInfo*)(peer->data))->lastSB + 60000 - (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count()) / 1000;
			GamePacket p2 = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), "`wCooldown, wait `5" + to_string(kiekDar) + " `wseconds `wto broadcast again!"));
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet2);
			delete p2.data;
		}
	}
	
	case 32: /*wrench*/
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer) || isWorldAdmin(peer, world)) {
			if (world->items[x + (y * world->width)].foreground == 7560) {
				string bobo;
				if (world->hgem != 0) {
					bobo = "\nadd_label|small|`6This machine contains `2" + to_string(world->hgem) + "`6!|left|\nadd_button|retgem|Retrieve gems|left|\nadd_spacer|small|";
				}
				else {
					bobo = "\nadd_label|small|`6This machine is currently empty!|left|\nadd_spacer|small|";
				}
				Player::OnDialogRequest(peer, "\nadd_label_with_icon|big|Heavenly Gem Collector|left|7560|\nadd_spacer|small|\nadd_label_with_icon|small|`2Gems|left|112|\nadd_spacer|small|" + bobo + "\nend_dialog||Close|");
			}
		}
		if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
		{
			if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer) || tile == world->interactableid || tile == 5640)
			{
				int ispub = world->isPublic;
				string str = "";
				string offname = "";
				for (std::vector<string>::const_iterator i = world->accessed.begin(); i != world->accessed.end(); ++i) {
					offname = *i;
					str += "\nadd_checkbox|unaccess_" + offname + "|" + offname + "|1|\n";
				}
				int muted = world->silence;
				string wlmenu = "";
				static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);
				if (world->items[x + (y * world->width)].foreground == 4802)
				{
					if (str == "")
					{
						wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left|\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_button|allowMod|`wAllow Noclip``|\nadd_button|allowMod1|`wDisallow Noclip``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|\nadd_checkbox|checkbox_muted|Silence, Peasants!|" + to_string(muted) + "|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
					}
					else
					{
						wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left|\nadd_smalltext|`$To `4unaccess`$, click the button name to the accessed player|left|\nadd_spacer|small|\nadd_label|small|" + str + "|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_button|allowMod|`wAllow Noclip``|\nadd_button|allowMod1|`wDisallow Noclip``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|\nadd_checkbox|checkbox_muted|Silence, Peasants!|" + to_string(muted) + "|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
					}
					Player::OnDialogRequest(peer, wlmenu);
				}
				else if (world->items[x + (y * world->width)].foreground == 2408)
				{
					static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
					static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
					static_cast<PlayerInfo*>(peer->data)->suckerid = 2408;
					auto squaresign = x + (y * 100);
					string label = "";
					auto ismag = std::experimental::filesystem::exists("bfg/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt"); /*Check if item sucker data file exists*/
					if (ismag)
					{
						auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
						auto itemid = 0;
						ifstream fdss("bfg/" + currentworld + ".txt"); /*Read the storeditem IDS*/
						fdss >> itemid;
						fdss.close();
						if (itemid != 0)
						{
							label = "|\nadd_label_with_icon|small|`oVisitors can interact with `2" + getItemDef(itemid).name + "|left|" + to_string(itemid) + "|";
						}
						else
						{
							label = "|\nadd_textbox|`oVisitors cannot interact with any blocks|";
						}
					}
					else
					{
						label = "|\nadd_textbox|`oVisitors cannot interact with any blocks|";
					}
					if (str == "")
					{
						wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left|\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|" + label + "|\nadd_item_picker|emeraldbfg|`wChange Block|Choose an item to put in the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "!|\nadd_button|allowMod|`wAllow Noclip``|\nadd_button|allowMod1|`wDisallow Noclip``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
					}
					else
					{
						wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left|\nadd_smalltext|`$To `4unaccess`$, click the button name to the accessed player|left|\nadd_spacer|small|\nadd_label|small|" + str + "|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|" + label + "|\nadd_item_picker|emeraldbfg|`wChange Block|Choose an item to put in the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "!|\nadd_button|allowMod|`wAllow Noclip``|\nadd_button|allowMod1|`wDisallow Noclip``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
					}
					Player::OnDialogRequest(peer, wlmenu);
				}
				else
				{
					if (str == "")
					{
						wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left|\nadd_spacer|small|\nadd_label|small|Currently, you're the only one with access.``|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_button|allowMod|`wAllow Noclip``|\nadd_button|allowMod1|`wDisallow Noclip``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
					}
					else
					{
						wlmenu = "set_default_color|`o\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "`|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_label|small|`wAccess list:``|left|\nadd_smalltext|`$To `4unaccess`$, click the button name to the accessed player|left|\nadd_spacer|small|\nadd_label|small|" + str + "|left\nadd_spacer|small|\nadd_player_picker|playerNetID|`wAdd``|\nadd_button|allowMod|`wAllow Noclip``|\nadd_button|allowMod1|`wDisallow Noclip``|\nadd_button|WorldDropPickup|`wEnable/Disable Collecting Items``|\nadd_checkbox|checkbox_public|Allow anyone to Build and Break|" + to_string(ispub) + "\nadd_checkbox|checkbox_disable_music|Disable Custom Music Blocks|0|\nadd_checkbox|checkbox_disable_music_render|Make Custom Music Blocks invisible|noflags|0|0|\nend_dialog|lock_edit|Cancel|OK|";
					}
					Player::OnDialogRequest(peer, wlmenu);
				}
			}
			else
			{
				if (isWorldAdmin(peer, world))
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
				else if (world->isPublic)
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
				else if (world->isEvent)
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
						Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
						return;
					}
				}
			}
			return;
		}
		else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SWITCH_BLOCK || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::CHEST || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::TOGGLE_FOREGROUND || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SWITCH_BLOCK || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::WRENCH)
		{
			return;
		}
		else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SUCKER) /*magplant gaia ut*/
		{
			if (world->isPublic) return; /*Item suckers cannot be used in public worlds*/
			auto squaresign = x + (y * 100);
			auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
			string Sucker = "";
			if (world->items[x + (y * world->width)].foreground == 5638)
			{
				Sucker = "magplant";
				static_cast<PlayerInfo*>(peer->data)->suckername = "magplant";
				static_cast<PlayerInfo*>(peer->data)->suckerid = 5638;
			}
			if (world->items[x + (y * world->width)].foreground == 6946)
			{
				Sucker = "gaiabeacon";
				static_cast<PlayerInfo*>(peer->data)->suckername = "gaiabeacon";
				static_cast<PlayerInfo*>(peer->data)->suckerid = 6946;
			}
			if (world->items[x + (y * world->width)].foreground == 6948)
			{
				Sucker = "unstabletesseract";
				static_cast<PlayerInfo*>(peer->data)->suckername = "unstabletesseract";
				static_cast<PlayerInfo*>(peer->data)->suckerid = 6948;
			}
			static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
			static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
			if (static_cast<PlayerInfo*>(peer->data)->rawName != getPlyersWorld(peer)->owner && !isMod(peer)) /*Make sure the player has rights to use item suckers*/
			{
				string publicremoteis = "false";
				auto remmag = std::experimental::filesystem::exists(Sucker + "/publicremote/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt"); /*Check if item sucker data file exists*/
				if (remmag)
				{
					ifstream fdss3(Sucker + "/publicremote/" + currentworld + ".txt"); /*Read the storeditem counts*/
					fdss3 >> publicremoteis;
					fdss3.close();
				}
				if (publicremoteis == "true")
				{
					auto itemid = 0;
					ifstream fdss(Sucker + "/storeditem/" + currentworld + ".txt"); /*Read the storeditem IDS*/
					fdss >> itemid;
					fdss.close();
					auto count = 0;
					ifstream fdss3(Sucker + "/count/" + currentworld + ".txt"); /*Read the storeditem counts*/
					fdss3 >> count;
					fdss3.close();
					string label = "`6The machine is currently empty!";
					string RemoteDialog = "";
					if (count >= 1)
					{
						RemoteDialog = "\nadd_textbox|`oUse the " + getItemDef(world->items[x + (y * world->width)].foreground).name + " Remote to build `2" + getItemDef(itemid).name + " `odirectly from the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "'s storage.|\nadd_button|getremote|`oGet Remote|";
						label = "`oThe machine contains " + to_string(count) + " `2" + getItemDef(itemid).name + ""; /*The message if something exists in item sucker*/
					}
					Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_label_with_icon|small|`2" + getItemDef(itemid).name + "|left|" + to_string(itemid) + "|\nadd_spacer|small|\nadd_textbox|" + label + "|\nadd_spacer|small||" + RemoteDialog + "|\nadd_spacer|small|\nend_dialog|magplantupdate|Close||");
				}
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This magplant public mode is disabled!", 0, false);
				}
				return;
			}
			auto ismag = std::experimental::filesystem::exists(Sucker + "/storeditem/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt"); /*Check if item sucker data file exists*/
			if (ismag)
			{
				auto itemid = 0;
				ifstream fdss(Sucker + "/storeditem/" + currentworld + ".txt"); /*Read the storeditem IDS*/
				fdss >> itemid;
				fdss.close();
				auto count = 0;
				ifstream fdss3(Sucker + "/count/" + currentworld + ".txt"); /*Read the storeditem counts*/
				fdss3 >> count;
				fdss3.close();
				string label = "`6The machine is currently empty!"; /*The message if nothing is in item sucker*/
				string RemoteDialog = "";
				string publicremotecheck = "";
				bool Farmable = false;
				if (itemid == 5136 || itemid == 5138 || itemid == 5140) Farmable = true;
				if (Sucker == "magplant" && getItemDef(itemid).blockType == BlockTypes::FOREGROUND || Sucker == "magplant" && Farmable || Sucker == "magplant" && getItemDef(itemid).blockType == BlockTypes::BACKGROUND || Sucker == "magplant" && getItemDef(itemid).blockType == BlockTypes::GROUND_BLOCK)
				{
					string publicremoteis = "false";
					auto remmag = std::experimental::filesystem::exists(Sucker + "/publicremote/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign) + ".txt"); /*Check if item sucker data file exists*/
					if (remmag)
					{
						ifstream basic_ifstream(Sucker + "/publicremote/" + currentworld + ".txt"); /*Read the storeditem counts*/
						basic_ifstream >> publicremoteis;
						basic_ifstream.close();
					}
					if (publicremoteis == "true")
					{
						publicremotecheck = "\nadd_checkbox|checkbox_publicremote|`oAllow visitors to take remote|1|";
					}
					else
					{
						publicremotecheck = "\nadd_checkbox|checkbox_publicremote|`oAllow visitors to take remote|0|";
					}
					RemoteDialog = "\nadd_textbox|`oUse the " + getItemDef(world->items[x + (y * world->width)].foreground).name + " Remote to build `2" + getItemDef(itemid).name + " `odirectly from the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "'s storage.|\nadd_button|getremote|`oGet Remote|";
				}
				if (count >= 1)
				{
					label = "`oThe machine contains " + to_string(count) + " `2" + getItemDef(itemid).name + ""; /*The message if something exists in item sucker*/
					Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_label_with_icon|small|`5" + getItemDef(itemid).name + "|left|" + to_string(itemid) + "|\nadd_textbox|" + label + "|\nadd_button|retrieveitem|`oRetrieve Items|" + RemoteDialog + "|" + publicremotecheck + "|\nadd_spacer|small|\nend_dialog|magplantupdate|Close|`wUpdate|");
				}
				else
				{
					Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_label_with_icon|small|`2" + getItemDef(itemid).name + "|left|" + to_string(itemid) + "|\nadd_textbox|" + label + "|\nadd_item_picker|magplantitem|Change Item|Choose an item to put in the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "!|" + publicremotecheck + "|\nadd_spacer|small|\nend_dialog|magplantupdate|Close|`wUpdate|");
				}
			}
			else
			{
				Player::OnDialogRequest(peer, "set_default_color|\nadd_label_with_icon|big|`w" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|\nadd_spacer|small|\nadd_textbox|`6The machine is empty.|\nadd_item_picker|magplantitem|Choose Item|Choose an item to put in the " + getItemDef(world->items[x + (y * world->width)].foreground).name + "!|\nend_dialog|magplant|Close||");
			}
			return;
		}
		if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DOOR || getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::PORTAL)
		{
			if (world->owner != "")
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer))
				{
					static_cast<PlayerInfo*>(peer->data)->wrenchsession = x + (y * world->width);
					auto item = world->items[x + (y * world->width)];
					auto a = item.destWorld + ":" + item.destId;
					if (a == ":") a = "";
					Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(item.foreground) + "|\n\nadd_text_input|dest|`oTarget World|" + a + "|100|\nadd_text_input|label|Display Label (optional)|" + item.label + "|100|\nadd_text_input|doorid|ID (optional)|" + item.currId + "|35|\nend_dialog|editdoor|Cancel|OK|");
				}
			}
			return;
		}
		
		if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SIGN || world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214 || world->items[x + (y * world->width)].foreground == 9202 || world->items[x + (y * world->width)].foreground == 10072 || world->items[x + (y * world->width)].foreground == 10074 || world->items[x + (y * world->width)].foreground == 10076 || world->items[x + (y * world->width)].foreground == 10078)
		{
			if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || isMod(peer))
			{
				auto signtext = world->items[x + (y * world->width)].sign;
				Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wEdit " + getItemDef(world->items[x + (y * world->width)].foreground).name + "``|left|" + to_string(world->items[x + (y * world->width)].foreground) + "|nadd_textbox|What would you like to write on this sign?``|left|\nadd_text_input|signtextas||" + signtext + "|200|\nend_dialog|editsign|Cancel|OK|");
				static_cast<PlayerInfo*>(peer->data)->wrenchedBlockLocation = x + (y * world->width);
			}
			return;
		}
		if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::GATEWAY)
		{
			if (world->owner == "") return;
			if (static_cast<PlayerInfo*>(peer->data)->rawName != PlayerDB::getProperName(world->owner) && !isMod(peer)) return;
			string enable = "";
			auto isheartm = std::experimental::filesystem::exists("gateway/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".txt");
			if (isheartm)
			{
				ifstream ifff("gateway/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".txt");
				ifff >> enable;
				ifff.close();
			}
			else
			{
				ofstream of("gateway/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".txt");
				of << 0 << std::endl;
				of.close();
				enable = "0";
			}

			static_cast<PlayerInfo*>(peer->data)->wrenchx = x;
			static_cast<PlayerInfo*>(peer->data)->wrenchy = y;

			if (enable == "0") {
				Player::OnDialogRequest(peer, "add_label_with_icon|big|" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_spacer|small|\nadd_checkbox|opentopublic|`ois Open to Public?  |0|\nend_dialog|entrance||OK|\n");
			}
			else {
				Player::OnDialogRequest(peer, "add_label_with_icon|big|" + getItemDef(world->items[x + (y * world->width)].foreground).name + "|left|" + to_string(getItemDef(world->items[x + (y * world->width)].foreground).id) + "|\nadd_spacer|small|\nadd_checkbox|opentopublic|`ois Open to Public?  |1|\nend_dialog|entrance||OK|\n");
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 9288)
		{
			Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wThe Underground Trader``|left|9288|0|0|\n\nadd_spacer|small|\nadd_textbox|`oWelcome Traveler! Here you can exchange `bDark Fragments `oInto `9Powerful `oItems Or Blocks! Click `^View Offers `oTo See!|\n\nadd_spacer|small|\nadd_button|undergroundtrader|`9View Offers|0|0|\nadd_quick_exit|");

		}
		if (world->items[x + (y * world->width)].foreground == 1790)
		{
			if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer))
			{
				string cQuest = "None";
				ifstream fileStream213("quests/currentquest/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
				fileStream213 >> cQuest;
				fileStream213.close();
				if (cQuest == "None")
				{
					Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Legendary Wizard``|left|1790|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Select a `^Quest `5Which you want to complete, each `^Quest `5Has `210 `5Steps, after completing all of them you will earn the `^Quest Item`5!|\n\nadd_spacer|small|\nadd_button|questkatana|`9Quest For Legendary Katana|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
				}
				else if (cQuest == "Katana")
				{
					auto sQuest = 1;
					ifstream fileStream216("quests/currentqueststep/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					fileStream216 >> sQuest;
					fileStream216.close();
					if (sQuest == 1)
					{
						auto s1Quest = 0;
						ifstream basic_ifstream("quests/katana/step1/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						basic_ifstream >> s1Quest;
						basic_ifstream.close();
						std::ifstream ifsz("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						std::string content((std::istreambuf_iterator<char>(ifsz)), (std::istreambuf_iterator<char>()));
						auto b = atoi(content.c_str());
						auto togive = 3000000 - s1Quest;
						auto cangive = b - togive;
						if (cangive >= 0)
						{
							cangive = 3000000 - s1Quest;
						}
						else
						{
							cangive = b;
						}
						Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 1: Welcome adventurer, your first `^Quest `5Will be to bring me `43m `9Gems`5, Hope that not too much for you`5!|\nadd_textbox|`5Progress: `^" + to_string(s1Quest) + "/3000000 `5Gems|\nadd_button|s1sgemsgive|`9Give `^" + to_string(cangive) + " `9Gems|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
					}
					else if (sQuest == 2)
					{
						auto s2Quest = 0;
						ifstream basic_ifstream("quests/katana/step2/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						basic_ifstream >> s2Quest;
						basic_ifstream.close();
						if (s2Quest < 50000)
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 2: This step will be maybe more challenging, but i want you to earn `450k `5Experience`5!|\nadd_textbox|`5Progress: `^" + to_string(s2Quest) + "/50000 `5Experience|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
						else
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 2: This step will be maybe more challenging, but i want you to earn `450k `5Experience`5!|\nadd_textbox|`5Progress: `^50000/50000 `5Experience|\nadd_button|s2scomplete|`9Complete!|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
					}
					else if (sQuest == 3)
					{
						auto s3Quest = 0;
						ifstream basic_ifstream("quests/katana/step3/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						basic_ifstream >> s3Quest;
						basic_ifstream.close();
						if (s3Quest < 3)
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 3: I challenge you to earn `43 `5Store Tokens, You can keep them. I'm more popular than you can imagine`5!|\nadd_textbox|`5Progress: `^" + to_string(s3Quest) + "/3 `5Store Tokens|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
						else
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 3: I challenge you to earn `43 `5Store Tokens, You can keep them. I'm more popular than you can imagine`5!|\nadd_textbox|`5Progress: `^3/3 `5Store Tokens|\nadd_button|s3scomplete|`9Complete!|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
					}
					else if (sQuest == 4)
					{
						auto s4Quest = 0;
						ifstream basic_ifstream("quests/katana/step4/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						basic_ifstream >> s4Quest;
						basic_ifstream.close();
						auto iscontains = false;
						SearchInventoryItem(peer, 9430, 1, iscontains);
						if (!iscontains)
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 4: I challenge you to bring me `4One `5Golden Digger Spade`5!|\nadd_textbox|`5Progress: `^" + to_string(s4Quest) + "/1 `5Golden Digger Spade|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
						else
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 4: I challenge you to bring me `4One `5Golden Digger Spade`5!|\nadd_textbox|`5Progress: `^1/1 `5Golden Digger Spade|\nadd_button|s4scomplete|`9Complete!|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
					}
					else if (sQuest == 5)
					{
						auto s5Quest = 0;
						ifstream basic_ifstream("quests/katana/step5/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						basic_ifstream >> s5Quest;
						basic_ifstream.close();
						auto iscontains = false;
						SearchInventoryItem(peer, 1794, 1, iscontains);
						if (!iscontains)
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 5: Congratulations on Beating all of my Steps, Now bring me The Legendary Orb`5!|\nadd_textbox|`5Progress: `^" + to_string(s5Quest) + "/1 `5Legendary Orb|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
						else
						{
							Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`#Quest For The Katana``|left|2592|0|0|\n\nadd_spacer|small|\nadd_textbox|`5Your current step: `^" + to_string(sQuest) + "/5|\nadd_textbox|`5Step 5: Congratulations on Beating all of my Steps, Now bring me The Legendary Orb`5!|\nadd_textbox|`5Progress: `^1/1 `5Legendary Orb|\nadd_button|s5scomplete|`cDary!|\nadd_button|chc0|`9Close|0|0|\nadd_quick_exit|");
						}
					}
				}
			}
			else
			{
				Player::OnTextOverlay(peer, "`#You must be world owner to use `#Legendary Wizard`#!");
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 2978)
		{
			if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
			{
				static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
				static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
				if (world->owner != "" && !isWorldOwner(peer, world))
				{
					SendBuyerVendDialog(peer);
					return;
				}
				SendVendDialog(peer);
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 4296)
		{
			if (world->owner == "" || isWorldOwner(peer, world) || isMod(peer))
			{

				if (static_cast<PlayerInfo*>(peer->data)->SurgeryCooldown)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "I know it's just a robot, but the authorities don't even trust you operating on that with your malpractice issues.", 0, true);
					return;
				}
				if (static_cast<PlayerInfo*>(peer->data)->PerformingSurgery)
				{
					end_surgery(peer, true);
				}
				static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
				static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
				string surgerywarning = "";
				vector<int> Tools;
				SearchInventoryItem(peer, 1258, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1258 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Sponge ";

					if (KiekTuri != 0) Tools.push_back(1258);

				}
				else Tools.push_back(1258);
				SearchInventoryItem(peer, 1260, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1260 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Scalpel ";

					if (KiekTuri != 0) Tools.push_back(1260);

				}
				else Tools.push_back(1260);
				SearchInventoryItem(peer, 1262, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1262 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Anesthetic ";

					if (KiekTuri != 0) Tools.push_back(1262);

				}
				else Tools.push_back(1262);
				SearchInventoryItem(peer, 1264, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1264 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Antiseptic ";

					if (KiekTuri != 0) Tools.push_back(1264);

				}
				else Tools.push_back(1264);
				SearchInventoryItem(peer, 1266, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1266 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Antibiotics ";

					if (KiekTuri != 0 && static_cast<PlayerInfo*>(peer->data)->UnlockedAntibiotic) Tools.push_back(1266);

				}
				else if (static_cast<PlayerInfo*>(peer->data)->UnlockedAntibiotic) Tools.push_back(1266);
				SearchInventoryItem(peer, 1268, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1268 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Splint ";

					if (KiekTuri != 0) Tools.push_back(1268);

				}
				else Tools.push_back(1268);
				SearchInventoryItem(peer, 1270, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 1270 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Stitches ";

					if (KiekTuri != 0) Tools.push_back(1270);

				}
				else Tools.push_back(1270);
				SearchInventoryItem(peer, 4308, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4308 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Pins ";

					if (KiekTuri != 0) Tools.push_back(4308);

				}
				else Tools.push_back(4308);
				SearchInventoryItem(peer, 4310, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4310 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Transfusion ";

					if (KiekTuri != 0) Tools.push_back(4310);

				}
				else Tools.push_back(4310);
				SearchInventoryItem(peer, 4312, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4312 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Defibrillator ";

					if (KiekTuri != 0 && static_cast<PlayerInfo*>(peer->data)->PatientHeartStopped) Tools.push_back(4312);

				}
				else if (static_cast<PlayerInfo*>(peer->data)->PatientHeartStopped) Tools.push_back(4312);
				SearchInventoryItem(peer, 4314, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4314 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Clamp ";

					if (KiekTuri != 0) Tools.push_back(4314);

				}
				else Tools.push_back(4314);
				SearchInventoryItem(peer, 4316, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4316 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Ultrasound ";

					if (KiekTuri != 0) Tools.push_back(4316);

				}
				else Tools.push_back(4316);
				SearchInventoryItem(peer, 4318, 20, iscontains);
				if (!iscontains)
				{
					auto KiekTuri = 0;
					for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
					{
						if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == 4318 && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
						{
							KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
						}
					}
					//surgerywarning += "`4" + to_string(KiekTuri) + "`` Surgical Lab Kit";

					if (KiekTuri != 0) Tools.push_back(4318);

				}
				else Tools.push_back(4318);

				for (int i = 0; i < Tools.size(); i++)
				{
					if (i == 0) static_cast<PlayerInfo*>(peer->data)->SurgItem1 = Tools[i];
					if (i == 1) static_cast<PlayerInfo*>(peer->data)->SurgItem2 = Tools[i];
					if (i == 2) static_cast<PlayerInfo*>(peer->data)->SurgItem3 = Tools[i];
					if (i == 3) static_cast<PlayerInfo*>(peer->data)->SurgItem4 = Tools[i];
					if (i == 4) static_cast<PlayerInfo*>(peer->data)->SurgItem5 = Tools[i];
					if (i == 5) static_cast<PlayerInfo*>(peer->data)->SurgItem6 = Tools[i];
					if (i == 6) static_cast<PlayerInfo*>(peer->data)->SurgItem7 = Tools[i];
					if (i == 7) static_cast<PlayerInfo*>(peer->data)->SurgItem8 = Tools[i];
					if (i == 8) static_cast<PlayerInfo*>(peer->data)->SurgItem9 = Tools[i];
					if (i == 9) static_cast<PlayerInfo*>(peer->data)->SurgItem10 = Tools[i];
					if (i == 10) static_cast<PlayerInfo*>(peer->data)->SurgItem11 = Tools[i];
					if (i == 11) static_cast<PlayerInfo*>(peer->data)->SurgItem12 = Tools[i];
					if (i == 12) static_cast<PlayerInfo*>(peer->data)->SurgItem13 = Tools[i];
				}

				vector<int> VisiTools{ 1258, 1260, 1262, 1264, 1266, 1268, 1270, 4308, 4310, 4312, 4314, 4316, 4318 };

				int TuriKartu = 1;
				bool Taip = false;
				for (int isd = 0; isd < VisiTools.size(); isd++)
				{
					bool Pirmas = false;
					SearchInventoryItem(peer, VisiTools[isd], 20, Pirmas);
					if (Pirmas)
					{
						continue;
					}
					bool Antras = false;
					SearchInventoryItem(peer, VisiTools[isd], 20, Antras);
					if (!Antras)
					{
						//cout << "keistas yra " + to_string(TuriKartu) << endl;
						int arrayd = VisiTools.size() - TuriKartu;
						//cout << "array yra " + to_string(arrayd) << endl;
						auto KiekTuri = 0;
						for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
						{
							if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == VisiTools[isd] && static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount >= 1)
							{
								KiekTuri = static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount;
							}
						}
						if (!Taip) surgerywarning += "You only have `4" + to_string(KiekTuri) + "`` " + getItemDef(VisiTools[isd]).name + ", ";
						else if (isd == arrayd)  surgerywarning += "and `4" + to_string(KiekTuri) + "`` " + getItemDef(VisiTools[isd]).name + " ";
						else surgerywarning += "`4" + to_string(KiekTuri) + "`` " + getItemDef(VisiTools[isd]).name + ", ";
						Taip = true;
					}
				}



				static_cast<PlayerInfo*>(peer->data)->RequestedSurgery = true;



				string LowSupplyWarning = "";
				if (surgerywarning != "") LowSupplyWarning = "\nadd_smalltext|`9Low Supply Warning: ``" + surgerywarning + "``|left|";
				Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`9Surg-E Anatomical Dummy``|left|4296|\nadd_spacer|small|\nadd_smalltext|Surgeon Skill: " + to_string(static_cast<PlayerInfo*>(peer->data)->SurgerySkill) + "|left|\nadd_textbox|Are you sure you want to perform surgery on this robot? Whether you succeed or fail, the robot will be destroyed in the process.|left|" + LowSupplyWarning + "\nend_dialog|surge|Cancel|Okay!|");
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 6016)
		{
			if (world->owner == "" || isWorldOwner(peer, world) || isMod(peer) || isWorldAdmin(peer, world))
			{
				Player::OnDialogRequest(peer, "set_default_color|`o\nadd_label_with_icon|big|`wWorld Stats``|left|6016|\nadd_spacer|small|\nadd_smalltext|`$Please write the item ID of the item you wanted to search in your world. Once u click '`1Search`$' down below, it will automatically search the dropped item and placed block of the ID. If you don't know what is the item ID of you wanted to search, do `1/itemid <item name> `$then all items will popped out with its ID.|left|\nadd_spacer|small|\nadd_text_input|gscanid|||5|\nadd_spacer|small|\nadd_quick_exit|\nend_dialog|gscan|Close|Search|");
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 9432)
		{
			if (static_cast<PlayerInfo*>(peer->data)->haveGrowId && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner || isMod(peer))
			{
				Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`5World Generation Machine``|left|9432|0|0|\n\nadd_spacer|small|\nadd_textbox|`oWelcome captain! This machine allows you to generate any world you wish, you can choose the width, height, blocks and even more! Press Start Machine to continue...|\n\nadd_spacer|small|\nadd_button|worldgenmachine|`9Start Machine|0|0|\nadd_quick_exit|");
			}
			else
			{
				Player::OnConsoleMessage(peer, "`#You must be world owner to use this machine!");
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 1436)
		{
			if (static_cast<PlayerInfo*>(peer->data)->haveGrowId && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner || isMod(peer))
			{
				string line;
				GTDialog allLog;
				ifstream breaklog("securitycam/logs/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + ".txt");
				allLog.addLabelWithIcon("`wBreak Block Logs", 1434, LABEL_SMALL);
				allLog.addSpacer(SPACER_SMALL);
				while (getline(breaklog, line))
				{
					allLog.addTextBox(line);
				}
				if (isDev(peer))
				{
					Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wSecurity Camera``|left|1436||\nadd_textbox|`oThis camera is suitable for logging actions which was made by other peoples such as `#Moderators `oand `6Developers`o!|" + allLog.finishDialog() + "|\nadd_spacer|small|\nadd_button|clearworldlogs|`4Clear Logs|0|0|\nadd_button|asfasfasd|`wClose|0|0|\nadd_quick_exit|");
				}
				else if (isMod(peer))
				{
					Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wSecurity Camera``|left|1436||\nadd_textbox|`oThis camera is suitable for logging actions which was made by other peoples such as `#Moderators `oand `6Developers`o!|" + allLog.finishDialog() + "|\nadd_spacer|small|\nadd_button|asfasfasd|`wClose|0|0|\nadd_quick_exit|");
				}
				else
				{
					Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wSecurity Camera``|left|1436||\nadd_textbox|`oThis camera is suitable for logging actions which was made by other peoples such as `#Moderators `oand `6Developers`o!|" + allLog.finishDialog() + "|\nadd_spacer|small|\nadd_button|clearworldlogs|`4Clear Logs|0|0|\nadd_button|asfasfasd|`wClose|0|0|\nadd_quick_exit|");
				}
			}
			else
			{
				Player::OnTextOverlay(peer, "`#Only world owner can view world logs!");
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 9170)
		{
			if (static_cast<PlayerInfo*>(peer->data)->haveGrowId && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner || isMod(peer))
			{
				Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wMagic Machine``|left|9170|0|0|\n\nadd_spacer|small|\nadd_textbox|`oThis machine is stronger than you think! It has ability to convert premium blocks into crystals! `4Warning! `oYou must have at least 100 blocks! Click `9Start `oTo get started!|\n\nadd_spacer|small|\nadd_button|magicmachine|`9Start|0|0|\nadd_quick_exit|");
			}
			else
			{
				Player::OnTextOverlay(peer, "`#You must be world owner to use this machine!");
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 3898)
		{
			Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wTelephone`|left|3898|\n\nadd_spacer|small|\nadd_label|small|`oDial a number to call somebody in Growtopia. Phone numbers have 5 digits. Most numbers are not in service!|\nadd_spacer|small|\nadd_text_input|telephonenumber|Phone #||5|\nend_dialog|usetelephone|Hang Up|`wDial|\n");
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 658)
		{
			auto squaresign = x + (y * 100);
			auto isdbox = std::experimental::filesystem::exists("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
			if (!isdbox)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the bulletin board.", 0, true);
			}
			else
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
				{
					GTDialog myLetterBox;
					myLetterBox.addLabelWithIcon("`wBulletin Board", 658, LABEL_BIG);
					myLetterBox.addSpacer(SPACER_SMALL);
					try
					{
						ifstream ifff("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();
						if (j["inmail"] <= 0)
						{
							myLetterBox.addTextBox("`oThe Bulletin Board is empty.");
							myLetterBox.addSpacer(SPACER_SMALL);
						}
						else
						{
							for (int i = 0; i < 20; i++)
							{
								if (j["mails"][i]["growid"] != "")
								{
									if (j["hidenames"] == 0)
									{
										int apos = j["mails"][i]["aposition"];
										myLetterBox.addLabelWithIconButton("`w" + j["mails"][i]["growid"].get<string>() + ":`2 " + j["mails"][i]["text"].get<string>() + "", 660, "removeselectedbulletin_" + to_string(squaresign) + "_" + to_string(apos));
										//myLetterBox.addSpacer(SPACER_SMALL);
									}
									else
									{
										myLetterBox.addTextBox("`2" + j["mails"][i]["text"].get<string>());
										//myLetterBox.addSpacer(SPACER_SMALL);
									}
								}
							}
						}

						if (j["inmail"] < 90)
						{
							myLetterBox.addSpacer(SPACER_SMALL);
							myLetterBox.addTextBox("`oAdd to conversation?");
							myLetterBox.addInputBox("addbulletinletterinput", "", "", 50);
							myLetterBox.addSpacer(SPACER_SMALL);
							myLetterBox.addButton("addbulletinletter_" + to_string(squaresign), "`2Add");
							myLetterBox.addSpacer(SPACER_SMALL);
						}

						myLetterBox.addLabelWithIcon("`wOwner Options", 242, LABEL_BIG);
						myLetterBox.addSpacer(SPACER_SMALL);
						if (j["hidenames"] == 1)
						{
							myLetterBox.addTextBox("`oUncheck `5Hide names `oto enable individual comment removal options.");
							myLetterBox.addSpacer(SPACER_SMALL);
						}
						else
						{
							myLetterBox.addTextBox("`oTo remove an individual comment, press the icon to the left of it.");
							myLetterBox.addSpacer(SPACER_SMALL);
						}
						if (j["inmail"] > 0)
						{
							myLetterBox.addButton("bulletinboardclear_" + to_string(squaresign), "`4Clear Board");
							myLetterBox.addSpacer(SPACER_SMALL);
						}
						if (j["publiccanadd"] == 1)
							myLetterBox.addCheckbox("publiccanaddbulletinboard", "`oPublic can add", CHECKBOX_SELECTED);
						else
							myLetterBox.addCheckbox("publiccanaddbulletinboard", "`oPublic can add", CHECKBOX_NOT_SELECTED);

						if (j["hidenames"] == 1)
							myLetterBox.addCheckbox("hidenamesbulletinboard", "`oHide names", CHECKBOX_SELECTED);
						else
							myLetterBox.addCheckbox("hidenamesbulletinboard", "`oHide names", CHECKBOX_NOT_SELECTED);
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("bulletinletterok_" + to_string(squaresign), "`wOK");
						myLetterBox.addQuickExit();
						myLetterBox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myLetterBox.finishDialog());
					}
					catch (std::exception&)
					{
						cout << "bulletin tile failed" << endl;
						return; /*tipo jeigu nera*/
					}
				}
				else
				{
					GTDialog myLetterBox;
					myLetterBox.addLabelWithIcon("`wBulletin Board", 658, LABEL_BIG);
					myLetterBox.addSpacer(SPACER_SMALL);
					try
					{
						ifstream ifff("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						json j;
						ifff >> j;
						ifff.close();

						if (j["inmail"] > 0)
						{
							for (int i = 0; i < 20; i++)
							{
								if (j["mails"][i]["growid"] != "")
								{
									if (j["hidenames"] == 0)
									{
										myLetterBox.addLabelWithIcon("`w" + j["mails"][i]["growid"].get<string>() + ":`2 " + j["mails"][i]["text"].get<string>() + "", 660, LABEL_SMALL);
										myLetterBox.addSpacer(SPACER_SMALL);
									}
									else
									{
										myLetterBox.addTextBox("`2" + j["mails"][i]["text"].get<string>());
										myLetterBox.addSpacer(SPACER_SMALL);
									}
								}
							}
						}

						if (j["publiccanadd"] == 1 && j["inmail"] < 90)
						{
							myLetterBox.addSpacer(SPACER_SMALL);
							myLetterBox.addTextBox("`oAdd to conversation?");
							myLetterBox.addInputBox("addbulletinletterinput", "", "", 50);
							myLetterBox.addSpacer(SPACER_SMALL);
							myLetterBox.addButton("addbulletinletter_" + to_string(squaresign), "`2Add");
							myLetterBox.addSpacer(SPACER_SMALL);
						}

						myLetterBox.addQuickExit();
						myLetterBox.endDialog("Close", "", "Cancel");
						Player::OnDialogRequest(peer, myLetterBox.finishDialog());
					}
					catch (std::exception&)
					{
						cout << "bulletin tile failed" << endl;
						return; /*tipo jeigu nera*/
					}
				}
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 656)
		{
			auto squaresign = x + (y * 100);
			auto isdbox = std::experimental::filesystem::exists("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
			if (!isdbox)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the mailbox.", 0, true);
			}
			else
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
				{
					GTDialog myLetterBox;
					myLetterBox.addLabelWithIcon("`wMail Box", 656, LABEL_BIG);
					ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					ifff >> j;
					ifff.close();
					if (j["inmail"] <= 0)
					{
						myLetterBox.addTextBox("`oThe mailbox is currently empty.");
					}
					else
					{
						int donated = j["inmail"];

						myLetterBox.addTextBox("`oYou have `w" + to_string(donated) + " `oletters:");
						myLetterBox.addSpacer(SPACER_SMALL);
						for (int i = 0; i < 20; i++)
						{
							if (j["mails"][i]["growid"] != "")
							{
								myLetterBox.addLabelWithIcon("`5\"" + j["mails"][i]["text"].get<string>() + "\" - `w" + j["mails"][i]["growid"].get<string>() + "", 660, LABEL_SMALL);
								myLetterBox.addSpacer(SPACER_SMALL);
							}
						}
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("mailempty_" + to_string(squaresign), "`4Empty mailbox");
					}
					myLetterBox.addTextBox("`oWrite a letter to yourself?");
					myLetterBox.addInputBox("addletterinput_" + to_string(squaresign), "", "", 50);
					myLetterBox.addSpacer(SPACER_SMALL);
					myLetterBox.addButton("addletter", "`2Send Letter");
					myLetterBox.addSpacer(SPACER_SMALL);
					myLetterBox.addQuickExit();
					myLetterBox.endDialog("Close", "", "Cancel");
					Player::OnDialogRequest(peer, myLetterBox.finishDialog());
				}
				else
				{
					GTDialog myLetterBox;
					myLetterBox.addLabelWithIcon("`wMail Box", 656, LABEL_BIG);
					ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					ifff >> j;
					ifff.close();

					myLetterBox.addTextBox("`$Want to leave a message for the owner?");
					myLetterBox.addSpacer(SPACER_SMALL);
					myLetterBox.addInputBox("addletterinput_" + to_string(squaresign), "", "", 50);
					myLetterBox.addSpacer(SPACER_SMALL);
					myLetterBox.addButton("addletter", "`2Send Letter");

					myLetterBox.addSpacer(SPACER_SMALL);
					myLetterBox.addQuickExit();
					myLetterBox.endDialog("Close", "", "Cancel");
					Player::OnDialogRequest(peer, myLetterBox.finishDialog());
				}
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 6286)
		{
			auto squaresign = x + (y * 100);
			auto isdbox = std::experimental::filesystem::exists("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
			if (!isdbox)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the box.", 0, true);
			}
			else
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
				{
					GTDialog myBox;
					myBox.addLabelWithIcon("`wStorage Box Xtreme - Level 1", 6286, LABEL_BIG);
					ifstream ifff("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					ifff >> j;
					ifff.close();

					int stored = j["instorage"];

					if (stored > 0)
					{
						myBox.addSpacer(SPACER_SMALL);
					}

					int count = 0;
					int id = 0;
					int aposition = 0;
					for (int i = 0; i < 20; i++)
					{
						if (j["storage"][i]["itemid"] != 0)
						{
							count = j["storage"][i]["itemcount"];
							id = j["storage"][i]["itemid"];
							aposition = j["storage"][i]["aposition"];

							if (i % 6 == 0 && i != 0)
							{
								myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl1DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
							}
							else
							{
								myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl1DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
							}
						}
					}

					if (stored > 0)
					{
						myBox.addNewLineAfterFrame();
					}

					myBox.addTextBox("`w" + to_string(stored) + "/20 `$items stored.");
					myBox.addSpacer(SPACER_SMALL);
					myBox.addPicker("boxlvl1deposit_" + to_string(squaresign), "Deposit item", "Select an item");
					myBox.addSpacer(SPACER_SMALL);
					myBox.addQuickExit();
					myBox.endDialog("Close", "", "Exit");
					Player::OnDialogRequest(peer, myBox.finishDialog());
				}
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 6288)
		{
			auto squaresign = x + (y * 100);
			auto isdbox = std::experimental::filesystem::exists("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
			if (!isdbox)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the box.", 0, true);
			}
			else
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
				{
					GTDialog myBox;
					myBox.addLabelWithIcon("`wStorage Box Xtreme - Level 2", 6288, LABEL_BIG);
					ifstream ifff("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					ifff >> j;
					ifff.close();

					int stored = j["instorage"];

					if (stored > 0)
					{
						myBox.addSpacer(SPACER_SMALL);
					}

					int count = 0;
					int id = 0;
					int aposition = 0;
					for (int i = 0; i < 40; i++)
					{
						if (j["storage"][i]["itemid"] != 0)
						{
							count = j["storage"][i]["itemcount"];
							id = j["storage"][i]["itemid"];
							aposition = j["storage"][i]["aposition"];

							if (i % 6 == 0 && i != 0)
							{
								myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl2DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
							}
							else
							{
								myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl2DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
							}
						}
					}

					if (stored > 0)
					{
						myBox.addNewLineAfterFrame();
					}

					myBox.addTextBox("`w" + to_string(stored) + "/40 `$items stored.");
					myBox.addSpacer(SPACER_SMALL);
					myBox.addPicker("boxlvl2deposit_" + to_string(squaresign), "Deposit item", "Select an item");
					myBox.addSpacer(SPACER_SMALL);
					myBox.addQuickExit();
					myBox.endDialog("Close", "", "Exit");
					Player::OnDialogRequest(peer, myBox.finishDialog());
				}
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 6290)
		{
			auto squaresign = x + (y * 100);
			auto isdbox = std::experimental::filesystem::exists("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
			if (!isdbox)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the box.", 0, true);
			}
			else
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
				{
					GTDialog myBox;
					myBox.addLabelWithIcon("`wStorage Box Xtreme - Level 3", 6290, LABEL_BIG);
					ifstream ifff("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					ifff >> j;
					ifff.close();

					int stored = j["instorage"];

					if (stored > 0)
					{
						myBox.addSpacer(SPACER_SMALL);
					}

					int count = 0;
					int id = 0;
					int aposition = 0;
					for (int i = 0; i < 90; i++)
					{
						if (j["storage"][i]["itemid"] != 0)
						{
							count = j["storage"][i]["itemcount"];
							id = j["storage"][i]["itemid"];
							aposition = j["storage"][i]["aposition"];

							if (i % 6 == 0 && i != 0)
							{
								myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl3DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
							}
							else
							{
								myBox.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "boxlvl3DepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
							}
						}
					}

					if (stored > 0)
					{
						myBox.addNewLineAfterFrame();
					}

					myBox.addTextBox("`w" + to_string(stored) + "/90 `$items stored.");
					myBox.addSpacer(SPACER_SMALL);
					myBox.addPicker("boxlvl3deposit_" + to_string(squaresign), "Deposit item", "Select an item");
					myBox.addSpacer(SPACER_SMALL);
					myBox.addQuickExit();
					myBox.endDialog("Close", "", "Exit");
					Player::OnDialogRequest(peer, myBox.finishDialog());
				}
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 8878)
		{
			auto squaresign = x + (y * 100);
			auto isdbox = std::experimental::filesystem::exists("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
			if (!isdbox)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the safe.", 0, true);
			}
			else
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
				{
					ifstream ifff("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + to_string(squaresign) + ".json");
					json j;
					ifff >> j;
					ifff.close();

					int stored = j["insafe"];
					string password = j["password"];

					if (password != "")
					{
						GTDialog mySafeConfirm;
						mySafeConfirm.addLabelWithIcon("`wSafe Vault", 8878, LABEL_BIG);
						mySafeConfirm.addTextBox("Please enter your password to access the Save Vault.");
						mySafeConfirm.addInputBox("safeconfirmpassInput_" + to_string(squaresign), "", "", 18);
						mySafeConfirm.addButton("safe_confirmpass", "Enter Password");
						mySafeConfirm.addButton("saferecoverPasswordInConfirm_" + to_string(squaresign), "Recover Password");
						mySafeConfirm.addSpacer(SPACER_SMALL);
						mySafeConfirm.addQuickExit();
						mySafeConfirm.endDialog("Close", "", "Exit");
						Player::OnDialogRequest(peer, mySafeConfirm.finishDialog());
						return;
					}

					GTDialog mySafe;
					mySafe.addLabelWithIcon("`wSafe Vault", 8878, LABEL_BIG);

					if (stored > 0)
					{
						mySafe.addSpacer(SPACER_SMALL);
					}

					int count = 0;
					int id = 0;
					int aposition = 0;
					for (int i = 0; i < 20; i++)
					{
						if (j["safe"][i]["itemid"] != 0)
						{
							count = j["safe"][i]["itemcount"];
							id = j["safe"][i]["itemid"];
							aposition = j["safe"][i]["aposition"];

							if (i % 3 == 0 && i != 0)
							{
								mySafe.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "safeBoxDepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), true);
							}
							else
							{
								mySafe.addStaticBlueFrameWithIdCountText(to_string(id), to_string(count), getItemDef(id).name, "safeBoxDepositedItem_" + to_string(aposition) + "_" + to_string(squaresign), false);
							}
						}
					}

					if (stored > 0)
					{
						mySafe.addNewLineAfterFrame();
					}

					mySafe.addTextBox("`w" + to_string(stored) + "/20 `$items stored.");
					mySafe.addSpacer(SPACER_SMALL);
					mySafe.addPicker("safedeposit_" + to_string(squaresign), "Deposit item", "Select an item");
					if (j["password"] == "")
					{
						mySafe.addTextBox("`$This Safe Vault is not `4password protected`$!");
					}
					else
					{
						mySafe.addTextBox("`$This Safe Vault is `2password protected`$!");
					}
					mySafe.addSpacer(SPACER_SMALL);
					mySafe.addTextBox("`$Change your password.");
					mySafe.addButton("safeupdatepass_" + to_string(squaresign), "Update Password");

					mySafe.addSpacer(SPACER_SMALL);
					mySafe.addQuickExit();
					mySafe.endDialog("Close", "", "Exit");
					Player::OnDialogRequest(peer, mySafe.finishDialog());
				}
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 1452)
		{
			auto squaresign = x + (y * 100);
			auto isdbox = std::experimental::filesystem::exists("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
			if (!isdbox)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the donation box.", 0, true);
			}
			else
			{
				static_cast<PlayerInfo*>(peer->data)->lastPunchX = x;
				static_cast<PlayerInfo*>(peer->data)->lastPunchY = y;
				static_cast<PlayerInfo*>(peer->data)->lastPunchForeground = world->items[x + (y * world->width)].foreground;
				static_cast<PlayerInfo*>(peer->data)->lastPunchBackground = world->items[x + (y * world->width)].background;
				if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
				{
					GTDialog myDbox;
					myDbox.addLabelWithIcon("`wDonation Box", 1452, LABEL_BIG);
					ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					ifff >> j;
					ifff.close();
					if (j["donated"] <= 0)
					{
						myDbox.addTextBox("`$The box is currently empty.");
					}
					else
					{
						int donated = j["donated"];
						int count = 0;
						myDbox.addTextBox("`oYou have `w" + to_string(donated) + " `ogifts waiting:");
						myDbox.addSpacer(SPACER_SMALL);
						for (int i = 0; i < 20; i++)
						{
							if (j["donatedItems"][i]["itemid"] != 0)
							{
								count = j["donatedItems"][i]["itemcount"];
								myDbox.addLabelWithIcon("`o" + getItemDef(j["donatedItems"][i]["itemid"]).name + " (`w" + to_string(count) + "`o) from `w" + j["donatedItems"][i]["sentBy"].get<string>() + "`#- '" + j["donatedItems"][i]["note"].get<string>() + "'", j["donatedItems"][i]["itemid"], LABEL_SMALL);
								myDbox.addSpacer(SPACER_SMALL);
							}
						}
						myDbox.addSpacer(SPACER_SMALL);
						myDbox.addButton("retrieveGifts_" + to_string(squaresign), "`4Retrieve Gifts");
					}
					myDbox.addSpacer(SPACER_SMALL);
					myDbox.addPicker("addDonationItem_" + to_string(squaresign), "`wGive Gift `o(Min rarity: `52`o)", "Select an item");
					myDbox.addSpacer(SPACER_SMALL);
					myDbox.addQuickExit();
					myDbox.endDialog("Close", "", "Cancel");
					Player::OnDialogRequest(peer, myDbox.finishDialog());
				}
				else
				{
					GTDialog myDbox;
					myDbox.addLabelWithIcon("`wDonation Box", 1452, LABEL_BIG);
					ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					ifff >> j;
					ifff.close();

					int donated = j["donated"];

					myDbox.addTextBox("`$You see `w" + to_string(donated) + "`$ gifts in the box!");
					myDbox.addTextBox("`$Want to leave a gift for the owner?");
					myDbox.addSpacer(SPACER_SMALL);

					myDbox.addPicker("addDonationItem_" + to_string(squaresign), "`wGive Gift `o(Min rarity: `52`o)", "Select an item");

					myDbox.addSpacer(SPACER_SMALL);
					myDbox.addQuickExit();
					myDbox.endDialog("Close", "", "Cancel");
					Player::OnDialogRequest(peer, myDbox.finishDialog());
				}
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 1006)
		{
			auto squaresign = x + (y * 100);
			auto isdbox = std::experimental::filesystem::exists("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
			if (!isdbox)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`4An error occured. Break the mailbox.", 0, true);
			}
			else
			{
				if (static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || world->owner == "" || isMod(peer))
				{
					GTDialog myLetterBox;
					myLetterBox.addLabelWithIcon("`wBlue Mail Box", 1006, LABEL_BIG);
					ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					ifff >> j;
					ifff.close();
					if (j["inmail"] <= 0)
					{
						myLetterBox.addTextBox("`oThe mailbox is currently empty.");
					}
					else
					{
						int donated = j["inmail"];

						myLetterBox.addTextBox("`oYou have `w" + to_string(donated) + " `oletters:");
						myLetterBox.addSpacer(SPACER_SMALL);
						for (int i = 0; i < 20; i++)
						{
							if (j["mails"][i]["growid"] != "")
							{
								myLetterBox.addLabelWithIcon("`5\"" + j["mails"][i]["text"].get<string>() + "\" - `w" + j["mails"][i]["growid"].get<string>() + "", 660, LABEL_SMALL);
								myLetterBox.addSpacer(SPACER_SMALL);
							}
						}
						myLetterBox.addSpacer(SPACER_SMALL);
						myLetterBox.addButton("bluemailempty_" + to_string(squaresign), "`4Empty mailbox");
					}
					myLetterBox.addTextBox("`oWrite a letter to yourself?");
					myLetterBox.addInputBox("addblueletterinput_" + to_string(squaresign), "", "", 50);
					myLetterBox.addSpacer(SPACER_SMALL);
					myLetterBox.addButton("addblueletter", "`2Send Letter");
					myLetterBox.addSpacer(SPACER_SMALL);
					myLetterBox.addQuickExit();
					myLetterBox.endDialog("Close", "", "Cancel");
					Player::OnDialogRequest(peer, myLetterBox.finishDialog());
				}
				else
				{
					GTDialog myLetterBox;
					myLetterBox.addLabelWithIcon("`wMail Box", 1006, LABEL_BIG);
					ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					json j;
					ifff >> j;
					ifff.close();

					myLetterBox.addTextBox("`$Want to leave a message for the owner?");
					myLetterBox.addSpacer(SPACER_SMALL);
					myLetterBox.addInputBox("addblueletterinput_" + to_string(squaresign), "", "", 50);
					myLetterBox.addSpacer(SPACER_SMALL);
					myLetterBox.addButton("addblueletter", "`2Send Letter");

					myLetterBox.addSpacer(SPACER_SMALL);
					myLetterBox.addQuickExit();
					myLetterBox.endDialog("Close", "", "Cancel");
					Player::OnDialogRequest(peer, myLetterBox.finishDialog());
				}
			}
			return;
		}
		if (world->items[x + (y * world->width)].foreground == 2946)
		{
			if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || getPlyersWorld(peer)->isPublic || isMod(peer))
			{
				auto targetworld = getPlyersWorld(peer);
				int itemid = world->items[x + (y * world->width)].foreground;
				int itembg = world->items[x + (y * world->width)].background;
				static_cast<PlayerInfo*>(peer->data)->displayfg = itemid;
				static_cast<PlayerInfo*>(peer->data)->displaybg = itembg;
				static_cast<PlayerInfo*>(peer->data)->displaypunchx = data.punchX;
				static_cast<PlayerInfo*>(peer->data)->displaypunchy = data.punchY;
				if (targetworld->items[x + (y * targetworld->width)].intdata != 0 && static_cast<PlayerInfo*>(peer->data)->rawName == getPlyersWorld(peer)->owner)
				{
					Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(targetworld->items[x + (y * targetworld->width)].intdata).name + " is on display here.|\nadd_button|pickupdisplayitem|Pick it up|0|0|\nadd_quick_exit|\n");
				}
				else if (targetworld->items[x + (y * targetworld->width)].intdata != 0 && (isMod(peer)))
				{
					Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(targetworld->items[x + (y * targetworld->width)].intdata).name + " is on display here.|\nadd_button|chc000|Okay|0|0|\nadd_quick_exit|\n");
				}
				else if (getPlyersWorld(peer)->isPublic && targetworld->items[x + (y * targetworld->width)].intdata != 0 && static_cast<PlayerInfo*>(peer->data)->rawName != getPlyersWorld(peer)->owner)
				{
					Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(targetworld->items[x + (y * targetworld->width)].intdata).name + " is on display here.|\nadd_button|chc000|Okay|0|0|\nadd_quick_exit|\n");
				}
				else if (getPlyersWorld(peer)->owner == "" && targetworld->items[x + (y * targetworld->width)].intdata != 0)
				{
					Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oA " + getItemDef(targetworld->items[x + (y * targetworld->width)].intdata).name + " is on display here.|\nadd_button|pickupdisplayitem|Pick it up|0|0|\nadd_quick_exit|\n");
				}
				else
				{
					Player::OnDialogRequest(peer, "add_label_with_icon|big|`wDisplay Block|left|" + to_string(itemid) + "|\nadd_spacer|small||\nadd_label|small|`oThe Display Block is empty. Use an item on it to display the item!|\nend_dialog||Close||\n");
				}
				return;
			}
			else
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
				return;
			}
			return;
		}
		return;
	}
	case 6336:
	{
		thread OwnerScan(scan_owner, peer, static_cast<PlayerInfo*>(peer->data)->rawName);
		if (OwnerScan.joinable()) OwnerScan.detach();
		return;
	}
	case 10034: /*merge*/
	{
		SendMergeBook(peer);
		return;
	}
	case 764:
	{
		if (static_cast<PlayerInfo*>(peer->data)->isZombie == true) return;
		if (static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks == true)
		{
			static_cast<PlayerInfo*>(peer->data)->canWalkInBlocks = false;
			static_cast<PlayerInfo*>(peer->data)->skinColor = 0x8295C3FF;
			send_state(peer);
		}
		sendSound(peer, "skel.wav");
		static_cast<PlayerInfo*>(peer->data)->isZombie = true;
		send_state(peer);
		RemoveInventoryItem(764, 1, peer, true);
		playerconfig(peer, 1150, 130, 0x14);
		return;
	}
	case 782:
	{
		if (static_cast<PlayerInfo*>(peer->data)->isZombie == false) return;
		static_cast<PlayerInfo*>(peer->data)->isZombie = false;
		send_state(peer);
		RemoveInventoryItem(782, 1, peer, true);
		playerconfig(peer, 1150, 300, 0x14);
		return;
	}
	case 6286: case 6288: case 6290: case 9202: case 1420: case 6214: case 10072: case 10074: case 10076: case 10078: case 656: case 658: case 1006: case 8878: case 1240: case 1452:
	{
		if (world->owner == "" || isWorldOwner(peer, world) || isMod(peer) || isWorldAdmin(peer, world))
		{
			if (world->name == "CON" || world->name == "PRN" || world->name == "AUX" || world->name == "NUL" || world->name == "COM1" || world->name == "COM2" || world->name == "COM3" || world->name == "COM4" || world->name == "COM5" || world->name == "COM6" || world->name == "COM7" || world->name == "COM8" || world->name == "COM9" || world->name == "LPT1" || world->name == "LPT2" || world->name == "LPT3" || world->name == "LPT4" || world->name == "LPT5" || world->name == "LPT6" || world->name == "LPT7" || world->name == "LPT8" || world->name == "LPT9") return;
			if (tile == 6286 || tile == 6288 || tile == 6290)
			{
				auto Space = 20;
				string Directory = "storageboxlvl1";
				if (tile == 6288)
				{
					Space = 40;
					Directory = "storageboxlvl2";
				}
				else if (tile == 6290)
				{
					Space = 90;
					Directory = "storageboxlvl3";
				}
				namespace fs = std::experimental::filesystem;
				if (!fs::is_directory(Directory + "/" + world->name) || !fs::exists(Directory + "/" + world->name))
				{
					fs::create_directory(Directory + "/" + world->name);
				}
				ofstream of(Directory + "/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				json j;
				j["instorage"] = 0;
				auto jArray = json::array();
				json jmid;
				for (auto i = 1; i <= Space; i++)
				{
					jmid["aposition"] = i;
					jmid["itemid"] = 0;
					jmid["placedby"] = static_cast<PlayerInfo*>(peer->data)->rawName;
					jmid["itemcount"] = 0;
					jArray.push_back(jmid);
				}
				j["storage"] = jArray;
				of << j << std::endl;
				of.close();
			}
			if (tile == 1240)
			{
				namespace fs = std::experimental::filesystem;
				if (!fs::is_directory("heartmonitor/" + getPlyersWorld(peer)->name) || !fs::exists("heartmonitor/" + getPlyersWorld(peer)->name))
				{
					fs::create_directory("heartmonitor/" + getPlyersWorld(peer)->name);
				}
				ofstream of("heartmonitor/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".txt");

				of << static_cast<PlayerInfo*>(peer->data)->rawName << std::endl;
				of.close();
				isHeartMonitor = true;
			}
			if (tile == 8878)
			{
				namespace fs = std::experimental::filesystem;
				if (!fs::is_directory("safevault/" + getPlyersWorld(peer)->name) || !fs::exists("safevault/" + getPlyersWorld(peer)->name))
				{
					fs::create_directory("safevault/" + getPlyersWorld(peer)->name);
				}
				ofstream of("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				json j;
				j["insafe"] = 0;
				j["password"] = "";
				j["recovery"] = "";
				json jArray = json::array();
				json jmid;
				for (int i = 1; i <= 20; i++)
				{
					jmid["aposition"] = i;
					jmid["itemid"] = 0;
					jmid["placedby"] = static_cast<PlayerInfo*>(peer->data)->rawName;
					jmid["itemcount"] = 0;
					jArray.push_back(jmid);
				}
				j["safe"] = jArray;
				of << j << std::endl;
				of.close();
			}
			if (tile == 656)
			{
				namespace fs = std::experimental::filesystem;
				if (!fs::is_directory("mailbox/" + getPlyersWorld(peer)->name) || !fs::exists("mailbox/" + getPlyersWorld(peer)->name))
				{
					fs::create_directory("mailbox/" + getPlyersWorld(peer)->name);
				}
				ofstream of("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				json j;
				j["x"] = x;
				j["y"] = y;
				j["inmail"] = 0;
				json jArray = json::array();
				json jmid;
				for (int i = 1; i <= 90; i++)
				{
					jmid["aposition"] = i;
					jmid["growid"] = "";
					jmid["text"] = "";
					jArray.push_back(jmid);
				}
				j["mails"] = jArray;
				of << j << std::endl;
				of.close();
			}
			if (tile == 658)
			{
				namespace fs = std::experimental::filesystem;
				if (!fs::is_directory("bulletinboard/" + getPlyersWorld(peer)->name) || !fs::exists("bulletinboard/" + getPlyersWorld(peer)->name))
				{
					fs::create_directory("bulletinboard/" + getPlyersWorld(peer)->name);
				}
				ofstream of("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				json j;
				j["inmail"] = 0;
				j["publiccanadd"] = 1;
				j["hidenames"] = 0;
				json jArray = json::array();
				json jmid;
				for (int i = 1; i <= 90; i++)
				{
					jmid["aposition"] = i;
					jmid["growid"] = "";
					jmid["text"] = "";
					jArray.push_back(jmid);
				}
				j["mails"] = jArray;
				of << j << std::endl;
				of.close();
			}
			if (tile == 1006)
			{
				namespace fs = std::experimental::filesystem;
				if (!fs::is_directory("bluemailbox/" + getPlyersWorld(peer)->name) || !fs::exists("bluemailbox/" + getPlyersWorld(peer)->name))
				{
					fs::create_directory("bluemailbox/" + getPlyersWorld(peer)->name);
				}
				ofstream of("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				json j;
				j["x"] = x;
				j["y"] = y;
				j["inmail"] = 0;
				json jArray = json::array();
				json jmid;
				for (int i = 1; i <= 90; i++)
				{
					jmid["aposition"] = i;
					jmid["growid"] = "";
					jmid["text"] = "";
					jArray.push_back(jmid);
				}
				j["mails"] = jArray;

				of << j << std::endl;
				of.close();
			}
			if (tile == 1420 || tile == 6214 || tile == 9202 || tile == 10072 || tile == 10074 || tile == 10076 || tile == 10078)
			{
				namespace fs = std::experimental::filesystem;
				if (!fs::is_directory("mannequin/" + getPlyersWorld(peer)->name) || !fs::exists("mannequin/" + getPlyersWorld(peer)->name))
				{
					fs::create_directory("mannequin/" + getPlyersWorld(peer)->name);
				}
				json j;
				auto seedexist = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				if (!seedexist)
				{
					j["clothHead"] = "0";
					j["clothHair"] = "0";
					j["clothMask"] = "0";
					j["clothNeck"] = "0";
					j["clothBack"] = "0";
					j["clothShirt"] = "0";
					j["clothPants"] = "0";
					j["clothFeet"] = "0";
					j["clothHand"] = "0";
					ofstream of("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					of << j;
					of.close();
				}
			}
			if (tile == 1452)
			{
				namespace fs = std::experimental::filesystem;
				if (!fs::is_directory("donationboxes/" + getPlyersWorld(peer)->name) || !fs::exists("donationboxes/" + getPlyersWorld(peer)->name))
				{
					fs::create_directory("donationboxes/" + getPlyersWorld(peer)->name);
				}
				ofstream of("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
				json j;
				j["donated"] = 0;
				json jArray = json::array();
				json jmid;
				for (int i = 1; i <= 20; i++)
				{
					jmid["aposition"] = i;
					jmid["sentBy"] = "";
					jmid["note"] = "";
					jmid["itemid"] = 0;
					jmid["itemcount"] = 0;
					jArray.push_back(jmid);
				}
				j["donatedItems"] = jArray;
				of << j << std::endl;
				of.close();
			}
			break;
		}
	}
	case 2978: /*vend*/
	{
		if (world->owner == "" || isWorldOwner(peer, world) || isMod(peer) || isWorldAdmin(peer, world))
		{
			namespace fs = std::experimental::filesystem;
			if (!fs::is_directory("vend/id/" + getPlyersWorld(peer)->name + "X" + std::to_string(squaresign) + ""))
			{
				ofstream vend1("vend/id/" + getPlyersWorld(peer)->name + "X" + std::to_string(squaresign) + ".txt");
				vend1 << "";
				vend1.close();
			}
			if (!fs::is_directory("vend/count/" + getPlyersWorld(peer)->name + "X" + std::to_string(squaresign) + ""))
			{
				ofstream vend2("vend/count/" + getPlyersWorld(peer)->name + "X" + std::to_string(squaresign) + ".txt");
				vend2 << "";
				vend2.close();
			}
			if (!fs::is_directory("vend/withdraw/" + getPlyersWorld(peer)->name + "X" + std::to_string(squaresign) + ""))
			{
				ofstream vend3("vend/withdraw/" + getPlyersWorld(peer)->name + "X" + std::to_string(squaresign) + ".txt");
				vend3 << "";
				vend3.close();
			}
			if (!fs::is_directory("vend/price/" + getPlyersWorld(peer)->name + "X" + std::to_string(squaresign) + ""))
			{
				ofstream vend3("vend/price/" + getPlyersWorld(peer)->name + "X" + std::to_string(squaresign) + ".txt");
				vend3 << "";
				vend3.close();
			}
			break;
		}
		else return;
	}
	case 2410: case 4426: case 1212: case 1234: case 3110: case 1976: case 2000: case 3122: case 10386: case 5664: case 5662: case 9644:
	{

		if (tile == 9644)
		{
			SearchInventoryItem(peer, 9644, 1, iscontains);
			if (!iscontains) return;
			else
			{
				if (CheckItemMaxed(peer, 1258, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1258).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 1260, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1260).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 1262, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1262).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 1264, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1264).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 1266, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1266).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 1268, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1268).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 1270, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(1270).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 4308, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4308).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 4310, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4310).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 4312, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4312).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 4314, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4314).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 4316, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4316).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 4318, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4318).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}

				if (CheckItemMaxed(peer, 4296, 5))
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "" + getItemDef(4296).name + " wouldnt fit into my inventory!", 0, true);
					return;
				}


				RemoveInventoryItem(9644, 1, peer, true);
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received 5 Surgical Sponge, 5 Surgical Scalpel, 5 Surgical Anesthetic, 5 Surgical Antiseptic, 5 Surgical Antibiotics, 5 Surgical Splint, 1 Surgical Stitches, 5 Surgical Pins, 5 Surgical Transfusion, 5 Surgical Defibrillator, 5 Surgical Clamp, 5 Surgical Ultrasound, 5 Surgical Lab Kit and a 1 Surg-E", 0, true);
				Player::OnConsoleMessage(peer, "`oYou received 5 Surgical Sponge, 5 Surgical Scalpel, 5 Surgical Anesthetic, 5 Surgical Antiseptic, 5 Surgical Antibiotics, 5 Surgical Splint, 1 Surgical Stitches, 5 Surgical Pins, 5 Surgical Transfusion, 5 Surgical Defibrillator, 5 Surgical Clamp, 5 Surgical Ultrasound, 5 Surgical Lab Kit and a 1 Surg-E");
				bool success = true;
				SaveItemMoreTimes(1258, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(1260, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(1262, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(1264, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(1266, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(1268, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(1270, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(4308, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(4310, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(4312, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(4314, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(4316, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(4318, 5, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");
				SaveItemMoreTimes(4296, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from surgery tool pack");

				ENetPeer* currentPeer;
				for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer))
					{
						SendTradeEffect(currentPeer, 1258, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 1260, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 1262, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 1264, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 1266, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 1268, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 1270, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 4308, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 4310, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 4312, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 4314, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 4316, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 4318, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
						SendTradeEffect(currentPeer, 4296, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);

					}
				}


			}
		}

		if (tile == 5662)
		{
			SearchInventoryItem(peer, 5662, 200, iscontains);
			if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6You will need more dust than that!", 0, true);
			else
			{
				RemoveInventoryItem(5662, 200, peer, true);
				bool success = true;
				SaveItemMoreTimes(5642, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5The dust stirs and begins to swirl! Cupid appears before you.", 0, true);
				static_cast<PlayerInfo*>(peer->data)->cloth_hand = 5642;
				sendClothes(peer);
			}
		}

		if (tile == 5664)
		{
			SearchInventoryItem(peer, 5664, 1, iscontains);
			if (!iscontains) return;
			else
			{
				RemoveInventoryItem(5664, 1, peer, true);
				bool success = true;
				SaveItemMoreTimes(5662, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
				//Player::OnConsoleMessage(peer, "`oYou received `21 " + getItemDef(itemid).name + " `ofrom the Gift of Growganoth.");
			}
		}
		if (tile == 10386)
		{
			SearchInventoryItem(peer, 10386, 1, iscontains);
			if (!iscontains) return;
			else
			{
				RemoveInventoryItem(10386, 1, peer, true);
				int itemuMas[59] = { 1216, 1218, 1992, 1982, 1994, 1972, 1980, 1988, 1984, 3116, 3102, 3106, 3110, 4160, 4162, 4164, 4154, 4158, 5224, 5222, 5232, 5240, 5248, 5238, 5256, 7116, 7108, 7110, 7128, 7112, 7114, 7130, 1198, 1208, 1222, 1200, 1220, 1202, 1238, 1168, 1172, 1230, 1194, 1192, 1226, 1196, 1236, 1182, 1184, 1186, 1188, 1170, 10198, 10196, 10202, 10204, 10326, 10324, 10322 };
				auto randIndex = rand() % 59;
				int itemid = itemuMas[randIndex];
				bool success = true;
				SaveItemMoreTimes(itemid, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
				Player::OnConsoleMessage(peer, "`oYou received `21 " + getItemDef(itemid).name + " `ofrom the Gift of Growganoth.");
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received `21 " + getItemDef(itemid).name + " `wfrom the Gift of Growganoth.", 0, true);
			}
		}
		if (tile == 3122)
		{
			SearchInventoryItem(peer, 3122, 16, iscontains);
			if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough fragments here to make anything. Get more!", 0, true);
			else
			{
				RemoveInventoryItem(3122, 16, peer, true);
				bool success = true;
				SaveItemMoreTimes(3120, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The fragments forms into a teeny devil wings!", 0, true);
				static_cast<PlayerInfo*>(peer->data)->cloth_back = 3120;
				Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
				sendClothes(peer);
			}
		}
		if (tile == 2000)
		{
			SearchInventoryItem(peer, 2000, 20, iscontains);
			if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough bones here to make anything. Get more!", 0, true);
			else
			{
				RemoveInventoryItem(2000, 20, peer, true);
				bool success = true;
				SaveItemMoreTimes(1998, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The bones forms into a skeletal dragon claw!", 0, true);
				static_cast<PlayerInfo*>(peer->data)->cloth_hand = 1998;
				Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
				sendClothes(peer);
			}
		}
		if (tile == 1976)
		{
			SearchInventoryItem(peer, 1976, 10, iscontains);
			if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough skulls here to make anything. Get more!", 0, true);
			else
			{
				RemoveInventoryItem(1976, 10, peer, true);
				bool success = true;
				SaveItemMoreTimes(1974, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The skulls forms into a nightmare magnifying glass!", 0, true);
				static_cast<PlayerInfo*>(peer->data)->cloth_hand = 1974;
				Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
				sendClothes(peer);
			}
		}
		if (tile == 1212)
		{
			SearchInventoryItem(peer, 1212, 25, iscontains);
			if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough fur here to make anything. Get more!", 0, true);
			else
			{
				RemoveInventoryItem(1212, 25, peer, true);
				bool success = true;
				SaveItemMoreTimes(1190, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The fur forms into a cuddly black cat!", 0, true);
				static_cast<PlayerInfo*>(peer->data)->cloth_hand = 1190;
				Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
				sendClothes(peer);
			}
		}
		if (tile == 1234)
		{
			SearchInventoryItem(peer, 1234, 4, iscontains);
			if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough shards here to make anything. Get more!", 0, true);
			else
			{
				RemoveInventoryItem(1234, 4, peer, true);
				bool success = true;
				SaveItemMoreTimes(1206, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The shards forms into a devil wings!", 0, true);
				static_cast<PlayerInfo*>(peer->data)->cloth_back = 1206;
				Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
				sendClothes(peer);
			}
		}
		if (tile == 3110)
		{
			SearchInventoryItem(peer, 3110, 25, iscontains);
			if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`6There's just not enough tatters here to make anything. Get more!", 0, true);
			else
			{
				RemoveInventoryItem(3110, 25, peer, true);
				if ((rand() % 100) <= 15)
				{
					bool success = true;
					SaveItemMoreTimes(3112, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The tatters forms into a inside-out vampire cape!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_back = 3112;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
				else
				{
					bool success = true;
					SaveItemMoreTimes(1166, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`5SQUISH! The tatters forms into a vampire cape!", 0, true);
					static_cast<PlayerInfo*>(peer->data)->cloth_back = 1166;
					Player::PlayAudio(peer, "audio/change_clothes.wav", 0);
					sendClothes(peer);
				}
			}
		}
		if (tile == 2410)
		{
			SearchInventoryItem(peer, 2410, 200, iscontains);
			if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oYou will need more `^Emerald Shards `oFor that!", 0, true);
			else
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oThe power of `^Emerald Shards `oCompressed into `2Emerald Lock`o!", 0, true);
				RemoveInventoryItem(2410, 200, peer, true);
				bool success = true;
				SaveItemMoreTimes(2408, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
				Player::OnConsoleMessage(peer, "`o>> You received emerald lock!");
			}
		}
		if (tile == 4426)
		{
			SearchInventoryItem(peer, 4426, 200, iscontains);
			if (!iscontains) Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oYou will need more `4Ruby Shards `oFor that!", 0, true);
			else
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oThe power of `4Ruby Shards `oCompressed into `4Ruby Lock`o!", 0, true);
				RemoveInventoryItem(4426, 200, peer, true);
				auto success = true;
				SaveItemMoreTimes(4428, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(tile).name + "");
				Player::OnConsoleMessage(peer, "`o>> You received ruby lock!");
			}
		}
		return;
	}
	case 6856: case 6858: case 6860: case 6862: case 9266: /*subtokens*/
	{
		auto contains = false;
		SearchInventoryItem(peer, tile, 1, contains);
		if (!contains)
		{
			autoBan(peer, false, 24 * 30, "Used sub exploit");
			break;
		}
		auto Sub_Days = 3;
		string Sub_Type = "free";
		if (tile == 9266) Sub_Days = 1;
		if (tile == 6856) Sub_Days = 3;
		if (tile == 6858) Sub_Days = 14;
		if (tile == 6860) Sub_Days = 30; Sub_Type = "premium";
		if (tile == 6862) Sub_Days = 365; Sub_Type = "premium";
		if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
		{
			if (static_cast<PlayerInfo*>(peer->data)->Subscriber)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have a Subscription!", 0, false);
				return;
			}

			ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
			json j;
			fg >> j;
			fg.close();

			j["subtype"] = Sub_Type;
			j["subdate"] = to_string(Sub_Days);

			ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
			fs << j;
			fs.close();
			RemoveInventoryItem(tile, 1, peer, true);
			SendTradeEffect(peer, tile, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
			static_cast<PlayerInfo*>(peer->data)->Subscriber = true;
			static_cast<PlayerInfo*>(peer->data)->haveSuperSupporterName = true;
			static_cast<PlayerInfo*>(peer->data)->SubscribtionEndDay = Sub_Days;
			Player::OnParticleEffect(peer, 46, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, 0);
			Player::OnAddNotification(peer, "`wYou've unlocked `5Premium Subscribtion `$benefits`w!", "audio/hub_open.wav", "interface/cash_icon_overlay.rttex");
			Player::PlayAudio(peer, "audio/thunderclap.wav", 0);
			static_cast<PlayerInfo*>(peer->data)->NickPrefix = j["title"].get<string>();
			static_cast<PlayerInfo*>(peer->data)->chatcolor = j["chatcolor"].get<string>();
			if (static_cast<PlayerInfo*>(peer->data)->NickPrefix != "")
			{
				restoreplayernick(peer);
				GamePacket p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), static_cast<PlayerInfo*>(peer->data)->NickPrefix + ". " + static_cast<PlayerInfo*>(peer->data)->tankIDName));
				memcpy(p7.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
				ENetPacket* packet7 = enet_packet_create(p7.data, p7.len, ENET_PACKET_FLAG_RELIABLE);
				ENetPeer* currentPeer;
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer))
					{
						enet_peer_send(currentPeer, 0, packet7);
					}
				}
				delete p7.data;
			}

			send_state(peer);
			auto iscontains = false;
			SearchInventoryItem(peer, 6260, 1, iscontains);
			if (!iscontains)
			{
				bool success = true;
				SaveItemMoreTimes(6260, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from subscription");
				Player::OnAddNotification(peer, "`wYou've obtained `5Amulet Of Force`w!", "audio/hub_open.wav", "interface/cash_icon_overlay.rttex");
			}
		}
		return;
	}
	case 196: case 528: case 540: case 6918: case 6924: case 1662: case 3062: case 822: /*consumables*/
	{
		if (tile == 196) /*blueberry*/
		{
			if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
			{
				SendTradeEffect(peer, 196, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
				string txt = "A `1blueberry`o slides down your throat! (`$Feelin' Blue`o mod added, `$5 secs`o left)";
				static_cast<PlayerInfo*>(peer->data)->skinColor = 4278190335;
				sendClothes(peer);
				sendSound(peer, "audio/spray.wav");
				RemoveInventoryItem(196, 1, peer, true);
				if (static_cast<PlayerInfo*>(peer->data)->blueBerry == false)
				{
					Player::OnConsoleMessage(peer, txt);
					static_cast<PlayerInfo*>(peer->data)->lastBerry = 5;
					static_cast<PlayerInfo*>(peer->data)->usedBerry = GetCurrentTimeInternalSeconds();
				}
				static_cast<PlayerInfo*>(peer->data)->blueBerry = true;
			}
			ENetPeer* peer2;
			for (peer2 = server->peers; peer2 < &server->peers[server->peerCount]; ++peer2)
			{
				if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
				if (isHere(peer, peer2))
				{
					PlayerInfo* cpinfo = static_cast<PlayerInfo*>(peer2->data);
					if (x == cpinfo->x / 32 && y == cpinfo->y / 32)
					{
						SendTradeEffect(peer2, 196, static_cast<PlayerInfo*>(peer->data)->netID, cpinfo->netID, 150);
						SendTradeEffect(peer, 196, static_cast<PlayerInfo*>(peer->data)->netID, cpinfo->netID, 150);
						string txt = "A `1blueberry`o slides down your throat! (`$Feelin' Blue`o mod added, `$5 secs`o left)";
						cpinfo->skinColor = 4278190335;
						sendClothes(peer2);
						sendSound(peer2, "audio/spray.wav");
						if (cpinfo->blueBerry == false)
						{
							Player::OnConsoleMessage(peer2, txt);
							static_cast<PlayerInfo*>(peer2->data)->lastBerry = 5;
							static_cast<PlayerInfo*>(peer2->data)->usedBerry = GetCurrentTimeInternalSeconds();
						}
						cpinfo->blueBerry = true;
						break;
					}
				}
			}
		}
		if (tile == 528) /*luckyclover*/
		{
			if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
			{
				if (static_cast<PlayerInfo*>(peer->data)->LuckyClover == false)
				{
					SendTradeEffect(peer, 528, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					sendSound(peer, "audio/spray.wav");
					RemoveInventoryItem(528, 1, peer, true);
					Player::OnConsoleMessage(peer, "You're `$luckier `othan before! (`$Lucky! `omod added, `$5 mins`o left)");
					static_cast<PlayerInfo*>(peer->data)->lastClover = 300;
					static_cast<PlayerInfo*>(peer->data)->usedClover = GetCurrentTimeInternalSeconds();
					static_cast<PlayerInfo*>(peer->data)->LuckyClover = true;
				}
				else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active lucky clover!", 0, true);
			}
		}
		if (tile == 6918) /*punchpotion*/
		{
			if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
			{
				if (static_cast<PlayerInfo*>(peer->data)->PunchPotion == false)
				{
					SendTradeEffect(peer, 6918, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					sendSound(peer, "audio/spray.wav");
					RemoveInventoryItem(6918, 1, peer, true);
					Player::OnConsoleMessage(peer, "You're `$stronger `othan before! (`$One HIT! `omod added, `$5 mins`o left)");
					static_cast<PlayerInfo*>(peer->data)->lastPunchPotion = 300;
					static_cast<PlayerInfo*>(peer->data)->usedPunchPotion = GetCurrentTimeInternalSeconds();
					static_cast<PlayerInfo*>(peer->data)->PunchPotion = true;
				}
				else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active punch potion!", 0, true);
			}
		}
		if (tile == 6924) /*placepotion*/
		{
			if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
			{
				if (static_cast<PlayerInfo*>(peer->data)->PlacePotion == false)
				{
					SendTradeEffect(peer, 6924, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					sendSound(peer, "audio/spray.wav");
					RemoveInventoryItem(6924, 1, peer, true);
					Player::OnConsoleMessage(peer, "Your hands are `$exceeding`o! (`$Triple Place! `omod added, `$5 mins`o left)");
					static_cast<PlayerInfo*>(peer->data)->lastPlacePotion = 300;
					static_cast<PlayerInfo*>(peer->data)->usedPlacePotion = GetCurrentTimeInternalSeconds();
					static_cast<PlayerInfo*>(peer->data)->PlacePotion = true;
				}
				else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active place potion!", 0, true);
			}
		}
		if (tile == 1662) /*spikejuice*/
		{
			if (x == static_cast<PlayerInfo*>(peer->data)->x / 32 && y == static_cast<PlayerInfo*>(peer->data)->y / 32)
			{
				if (static_cast<PlayerInfo*>(peer->data)->SpikeJuice == false)
				{
					SendTradeEffect(peer, 1662, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					sendSound(peer, "audio/spray.wav");
					RemoveInventoryItem(1662, 1, peer, true);
					Player::OnConsoleMessage(peer, "You are immune to spikes and lava! (`$Spikeproof! `omod added, `$5 secs`o left)");
					static_cast<PlayerInfo*>(peer->data)->lastSpike = 5;
					static_cast<PlayerInfo*>(peer->data)->usedSpike = GetCurrentTimeInternalSeconds();
					static_cast<PlayerInfo*>(peer->data)->SpikeJuice = true;
				}
				else Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You already have active spike juice!", 0, true);
			}
		}
		if (tile == 540)
		{
			RemoveInventoryItem(540, 1, peer, true);
			Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2BURRRPPP...!", 0, true);
		}
		if (tile == 3062)
		{
			if (world->items[x + (y * world->width)].fire == false && world->items[x + (y * world->width)].water == false)
			{
				if (world->items[x + (y * world->width)].foreground != 6 && world->items[x + (y * world->width)].foreground != 8 && getItemDef(world->items[x + (y * world->width)].foreground).blockType != BlockTypes::LOCK)
				{
					if (world->isPineappleGuard)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou cant use consumables here!", 0, true);
						return;
					}
					if (world->items[x + (y * world->width)].foreground == 0 && world->items[x + (y * world->width)].background == 0)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wTheres nothing to burn!", 0, true);
						return;
					}
					world->items[x + (y * world->width)].fire = !world->items[x + (y * world->width)].fire;
					ENetPeer* net_peer;
					for (net_peer = server->peers;
						net_peer < &server->peers[server->peerCount];
						++net_peer)
					{
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer))
						{
							Player::OnParticleEffect(net_peer, 150, x * 32 + 16, y * 32 + 16, 0);
							Player::OnTalkBubble(net_peer, static_cast<PlayerInfo*>(peer->data)->netID, "`7[```4MWAHAHAHA!! FIRE FIRE FIRE```7]``", 0, false);
						}
					}
					RemoveInventoryItem(3062, 1, peer, true);
					UpdateVisualsForBlock(peer, true, x, y, world);
				}
			}
		}
		if (tile == 822)
		{
			if (world->items[x + (y * world->width)].water == false)
			{
				if (world->items[x + (y * world->width)].foreground != 6 && world->items[x + (y * world->width)].foreground != 8 && getItemDef(world->items[x + (y * world->width)].foreground).blockType != BlockTypes::LOCK)
				{
					if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer))
					{
						UpdateBlockState(peer, x, y, true, world);
						if (world->isPineappleGuard)
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou cant use consumables here!", 0, true);
							return;
						}
						world->items[x + (y * world->width)].water = true;
						SendThrowEffect(peer, 822, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
						UpdateVisualsForBlock(peer, true, x, y, world);
					}
				}
			}
			else {
				if (world->items[x + (y * world->width)].foreground != 6 && world->items[x + (y * world->width)].foreground != 8 && getItemDef(world->items[x + (y * world->width)].foreground).blockType != BlockTypes::LOCK)
				{
					if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer))
					{
						UpdateBlockState(peer, x, y, true, world);
						if (world->isPineappleGuard)
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou cant use consumables here!", 0, true);
							return;
						}
						world->items[x + (y * world->width)].water = false;
						SendThrowEffect(peer, 822, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
						UpdateVisualsForBlock(peer, true, x, y, world);
					}
				}
			}
		}
		return;
	}
	case 1866:
	{
		if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || isMod(peer))
		{
			if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
			{
				return;
			}
			world->items[x + (y * world->width)].glue = !world->items[x + (y * world->width)].glue;
			UpdateVisualsForBlock(peer, true, x, y, world);
		}
		return;
	}
	case 1402:
	{
		auto iscontainsss = false;
		SearchInventoryItem(peer, 8428, 1, iscontainsss);
		if (!iscontainsss)
		{
			autoBan(peer, true, 1, "he tried to punch 8428 item, but did not has it.");
		}
		else
		{
			Player::OnDialogRequest(peer, "set_default_color|`o\n\nadd_label_with_icon|big|`wThermonuclear Blast`|left|1402|\n\nadd_spacer|small|\nadd_label|small|`oThis item creates a new world! Enter a unique name for it.|\nadd_spacer|small|\nadd_text_input|uranusname|New World Name||30|\nend_dialog|useuranusblast|Cancel|`5Create!|\n");
		}
		return;
	}
	case 1826:
	{
		if (!isWorldOwner(peer, world)) return;
		auto iscontainsss = false;
		SearchInventoryItem(peer, 1826, 1, iscontainsss);
		if (!iscontainsss)
		{
			autoBan(peer, true, 1, "he tried to punch 1826 item, but did not has it.");
		}
		else
		{
			auto FoundSomething = false;
			for (auto i = 0; i < world->width * world->height; i++)
			{
				if (isSeed(world->items[i].foreground))
				{
					sendTileUpdate((i % world->width), (i / world->width), 18, static_cast<PlayerInfo*>(peer->data)->netID, peer);
					ENetPeer* net_peer;
					for (net_peer = server->peers;
						net_peer < &server->peers[server->peerCount];
						++net_peer)
					{
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer))
						{
							Player::OnParticleEffect(net_peer, 182, (i % world->width) * 32, (i / world->width) * 32, 0);
						}
					}
					FoundSomething = true;
				}
			}
			if (FoundSomething) RemoveInventoryItem(1826, 1, peer, true);
		}
		return;
	}
	case 5640: /*magplantremote*/
	{
		bool aryra = false;
		for (int i = 0; i < world->width * world->height; i++)
		{
			if (world->items[i].foreground == 5638)
			{
				aryra = true;
			}
		}
		if (aryra == true)
		{
			if (static_cast<PlayerInfo*>(peer->data)->magplantx != 0 && static_cast<PlayerInfo*>(peer->data)->magplanty != 0)
			{
				int squaresign = static_cast<PlayerInfo*>(peer->data)->magplantx + (static_cast<PlayerInfo*>(peer->data)->magplanty * 100);
				string currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
				int itemid = 0;
				ifstream fdss("magplant/storeditem/" + currentworld + ".txt");
				fdss >> itemid;
				fdss.close();
				int count = 0;
				ifstream fdss3("magplant/count/" + currentworld + ".txt");
				fdss3 >> count;
				fdss3.close();
				if (itemid == static_cast<PlayerInfo*>(peer->data)->magplantitemid && count > 0)
				{
					int magplantid = static_cast<PlayerInfo*>(peer->data)->magplantitemid;
					bool RotatedRight = false;
					auto xpos = x * 32;
					auto ppos = static_cast<PlayerInfo*>(peer->data)->x;
					if (static_cast<PlayerInfo*>(peer->data)->x < x * 32) RotatedRight = true;
					if (RotatedRight) ppos += 19;
					xpos = xpos / 32;
					ppos = ppos / 32;
					if (world->items[x + (y * world->width)].foreground != 0 && getItemDef(magplantid).blockType != BlockTypes::BACKGROUND && getItemDef(magplantid).blockType != BlockTypes::GROUND_BLOCK) return;
					ENetPeer* currentPeer;
					for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount];
						++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer))
						{
							bool RotatedRight = false;
							auto xpos = x * 32;
							auto ppos = static_cast<PlayerInfo*>(currentPeer->data)->x;
							if (static_cast<PlayerInfo*>(currentPeer->data)->x < x * 32) RotatedRight = true;
							if (RotatedRight) ppos += 19;
							xpos = xpos / 32;
							ppos = ppos / 32;
							if (ppos == xpos && static_cast<PlayerInfo*>(currentPeer->data)->y / 32 == y && getItemDef(magplantid).properties != Property_NoSeed && getItemDef(magplantid).properties != Property_Foreground && getItemDef(magplantid).properties != Property_MultiFacing && getItemDef(magplantid).blockType != BlockTypes::SEED && getItemDef(magplantid).blockType != BlockTypes::STEAM && getItemDef(magplantid).blockType != BlockTypes::UNKNOWN && getItemDef(magplantid).blockType != BlockTypes::VENDING && getItemDef(magplantid).blockType != BlockTypes::ANIM_FOREGROUND && getItemDef(magplantid).blockType != BlockTypes::BULLETIN_BOARD && getItemDef(magplantid).blockType != BlockTypes::FACTION && getItemDef(magplantid).blockType != BlockTypes::CHEST && getItemDef(magplantid).blockType != BlockTypes::GEMS && getItemDef(magplantid).blockType != BlockTypes::MAGIC_EGG && getItemDef(magplantid).blockType != BlockTypes::CRYSTAL && getItemDef(magplantid).blockType != BlockTypes::MAILBOX && getItemDef(magplantid).blockType != BlockTypes::PORTAL && getItemDef(magplantid).blockType != BlockTypes::PLATFORM && getItemDef(magplantid).blockType != BlockTypes::SFX_FOREGROUND && getItemDef(magplantid).blockType != BlockTypes::CHEMICAL_COMBINER && getItemDef(magplantid).blockType != BlockTypes::SWITCH_BLOCK && getItemDef(magplantid).blockType != BlockTypes::TRAMPOLINE && getItemDef(magplantid).blockType != BlockTypes::TOGGLE_FOREGROUND && getItemDef(magplantid).blockType != BlockTypes::GROUND_BLOCK && getItemDef(magplantid).blockType != BlockTypes::BACKGROUND && getItemDef(magplantid).blockType != BlockTypes::MAIN_DOOR && getItemDef(magplantid).blockType != BlockTypes::SIGN && getItemDef(magplantid).blockType != BlockTypes::DOOR && getItemDef(magplantid).blockType != BlockTypes::CHECKPOINT && getItemDef(magplantid).blockType != BlockTypes::GATEWAY && getItemDef(magplantid).blockType != BlockTypes::TREASURE && getItemDef(magplantid).blockType != BlockTypes::WEATHER) return;
						}
					}
					world->items[x + (y * world->width)].foreground = magplantid;
					count -= 1;
					ofstream savemag("magplant/count/" + currentworld + ".txt");
					savemag << count;
					savemag.close();
					PlayerMoving data3;
					data3.packetType = 0x3;
					data3.characterState = 0x0;
					data3.x = x;
					data3.y = y;
					data3.punchX = x;
					data3.punchY = y;
					data3.XSpeed = 0;
					data3.YSpeed = 0;
					data3.netID = -1;
					data3.plantingTree = magplantid;
					for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer))
						{
							auto raw = packPlayerMoving(&data3);
							raw[2] = dicenr;
							raw[3] = dicenr;
							SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
						}
					}
					for (currentPeer = server->peers;
						currentPeer < &server->peers[server->peerCount];
						++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer))
						{
							if (count <= 0)
							{
								SendItemSucker(currentPeer, 5638, static_cast<PlayerInfo*>(peer->data)->magplantx, static_cast<PlayerInfo*>(peer->data)->magplanty, itemid, 0, true, true);
							}
							else if (count >= 5000)
							{
								SendItemSucker(currentPeer, 5638, static_cast<PlayerInfo*>(peer->data)->magplantx, static_cast<PlayerInfo*>(peer->data)->magplanty, itemid, -1, true, true);
							}
							else
							{
								SendItemSucker(currentPeer, 5638, static_cast<PlayerInfo*>(peer->data)->magplantx, static_cast<PlayerInfo*>(peer->data)->magplanty, itemid, 1, true, true);
							}
						}
					}
				}
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wThe `2MAGPLANT 5000 `wis empty!", 0, false);
				}
			}
		}
		return;
	}
	case 1436: /*securitycamera*/
	{
		bool aryra = false;
		for (int i = 0; i < world->width * world->height; i++)
		{
			if (world->items[i].foreground == 1436)
			{
				aryra = true;
			}
		}
		if (aryra == false)
		{
			if (static_cast<PlayerInfo*>(peer->data)->rawName != world->owner)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0You need to be world owner to place `cSecurity Camera`0!", 0, true);
				return;
			}
		}
		else
		{
			Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0You cant place more than one `cSecurity Camera`0!", 0, true);
			return;
		}
		break;
	}
	case 1790: /*legendarywizard*/
	{
		if (static_cast<PlayerInfo*>(peer->data)->rawName != world->owner)
		{
			Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0You need to be world owner to place `#Legendary Wizard`0!", 0, true);
			return;
		}
		else if (getPlyersWorld(peer)->isPublic == true)
		{
			Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0You cannot place `#Legendary Wizard `0In public worlds`0!", 0, true);
			return;
		}
		break;
	}
	case 6204: case 6202: case 6200: case 7484: case 7954: case 1360: /*chest*/
	{
		if (tile == 1360)
		{
			vector<int> Dailyb{ 242, 242, 242, 10028, 828, 68, 82, 10032, 98, 404, 400, 3402, 3400 };
			const int Index = rand() % Dailyb.size();
			const auto ItemID = Dailyb[Index];
			RemoveInventoryItem(1360, 1, peer, true);
			Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wYou received " + getItemDef(ItemID).name + "", 0, true);
			Player::OnConsoleMessage(peer, "`oYou received " + getItemDef(ItemID).name + "");
			bool success = true;
			SaveItemMoreTimes(ItemID, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from daily gift");
		}
		if (tile == 6204)
		{
			if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
			auto iscontains = false;
			SearchInventoryItem(peer, 6204, 1, iscontains);
			if (!iscontains)
			{
				return;
			}
			else
			{
				RemoveInventoryItem(6204, 1, peer, true);
				auto kuriPrizaDuot = rand() % 2 + 1;
				if (kuriPrizaDuot == 1)
				{
					auto gemChance = rand() % 20000;
					GiveChestPrizeGems(peer, gemChance);
				}
				if (kuriPrizaDuot == 2)
				{
					int itemuMas[5] = { 7912, 7912, 7912, 5078, 8834 };
					auto randIndex = rand() % 5;
					auto itemId = itemuMas[randIndex];
					send_item(peer, itemId, 1, 6204);
				}
			}
		}
		if (tile == 6202)
		{
			if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
			auto iscontains = false;
			SearchInventoryItem(peer, 6202, 1, iscontains);
			if (!iscontains)
			{
				return;
			}
			else
			{
				RemoveInventoryItem(6202, 1, peer, true);
				auto kuriPrizaDuot = rand() % 2 + 1;
				if (kuriPrizaDuot == 1)
				{
					auto gemChance = rand() % 70000;
					GiveChestPrizeGems(peer, gemChance);
				}
				if (kuriPrizaDuot == 2)
				{
					int itemuMas[5] = { 7912, 5078, 5078, 5078, 8834 };
					auto randIndex = rand() % 5;
					auto itemId = itemuMas[randIndex];
					send_item(peer, itemId, 1, 6202);
				}
			}
		}
		if (tile == 6200)
		{
			if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
			auto iscontains = false;
			SearchInventoryItem(peer, 6200, 1, iscontains);
			if (!iscontains)
			{
				return;
			}
			else
			{
				RemoveInventoryItem(6200, 1, peer, true);
				auto kuriPrizaDuot = rand() % 2 + 1;
				if (kuriPrizaDuot == 1)
				{
					auto gemChance = rand() % 120000;
					GiveChestPrizeGems(peer, gemChance);
				}
				if (kuriPrizaDuot == 2)
				{
					int itemuMas[8] = { 7912, 7912, 7912, 7912, 5078, 5078, 5078, 8834 };
					auto randIndex = rand() % 8;
					auto itemId = itemuMas[randIndex];
					send_item(peer, itemId, 1, 6200);
				}
			}
		}
		if (tile == 7484)
		{
			if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
			auto iscontains = false;
			SearchInventoryItem(peer, 7484, 1, iscontains);
			if (!iscontains)
			{
				return;
			}
			else
			{
				RemoveInventoryItem(7484, 1, peer, true);
				auto kuriPrizaDuot = rand() % 2 + 1;
				if (kuriPrizaDuot == 1)
				{
					auto gemChance = rand() % 170000;
					GiveChestPrizeGems(peer, gemChance);
				}
				if (kuriPrizaDuot == 2)
				{
					int itemuMas[12] = { 7912, 7912, 7912, 7912, 5078, 5078, 5078, 8834, 8834, 8834, 8834, 8834 };
					auto randIndex = rand() % 12;
					int itemId = itemuMas[randIndex];
					send_item(peer, itemId, 1, 7484);
				}
			}
		}
		if (tile == 7954)
		{
			if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false) return;
			auto iscontains = false;
			SearchInventoryItem(peer, 7954, 1, iscontains);
			if (!iscontains)
			{
				return;
			}
			else
			{
				RemoveInventoryItem(7954, 1, peer, true);
				auto kuriPrizaDuot = rand() % 2 + 1;
				if (kuriPrizaDuot == 1)
				{
					int gemChance = rand() % 200000;
					GiveChestPrizeGems(peer, gemChance);
				}
				if (kuriPrizaDuot == 2)
				{
					int itemuMas[12] = { 7912, 7912, 7912, 7912, 5078, 5078, 5078, 8834, 8834, 8834, 8834, 8834 };
					auto randIndex = rand() % 12;
					auto itemId = itemuMas[randIndex];
					send_item(peer, itemId, 1, 7954);
				}
			}
		}
		return;
	}
	case 1404: /*doormover*/
	{
		if (world->width != 100 && world->height != 60)
		{
			Player::OnTextOverlay(peer, "`@Door Mover Cant Be Used In Mutated Worlds`@!");
			return;
		}
		if (static_cast<PlayerInfo*>(peer->data)->rawName != world->owner && !isMod(peer))
		{
			Player::OnTextOverlay(peer, "`@You Must Be `2World-Owner `@To Use `wDoor Mover`@!");
			return;
		}
		if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner)
		{
			if (world->items[x + (y * world->width)].foreground != 0)
			{
				Player::OnTextOverlay(peer, "`@There Is `4No `@Space For `wMain Door`@!");
				return;
			}
			else
			{
				RemoveInventoryItem(1404, 1, peer, true);
				for (auto i = 0; i < world->width * world->height; i++)
				{
					if (i >= 5400)
					{
						world->items[i].foreground = 8;
					}
					else if (world->items[i].foreground == 6)
					{
						world->items[i].foreground = 0;
					}
					else if (world->items[i].foreground != 6)
					{
						world->items[x + (y * world->width)].foreground = 6;
					}
				}
				ENetPeer* net_peer;
				for (net_peer = server->peers; net_peer < &server->peers[server->peerCount]; ++net_peer)
				{
					if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, net_peer))
					{
						string act = static_cast<PlayerInfo*>(peer->data)->currentWorld;
						sendPlayerLeave(net_peer, static_cast<PlayerInfo*>(net_peer->data));
						joinWorld(net_peer, act, 0, 0);
						Player::OnTextOverlay(peer, "`^You Have `2Used `wDoor Mover`^!");
					}
				}
			}
			return;
		}
		return;
	}
	case 5460: case 4520: case 382: case 3116: case 1792: case 2994: case 4368: case 274: case 276: case 278: case 5708: case 5709: case 5780: case 5781: case 5782: case 5783: case 5784: case 5785: case 5710: case 5711: case 5786: case 5787: case 5788: case 5789: case 5790: case 5791: case 6146: case 6147: case 6148: case 6149: case 6150: case 6151: case 6152: case 6153: case 5670: case 5671: case 5798: case 5799: case 5800: case 5801: case 5802: case 5803: case 5668: case 5669: case 5792: case 5793: case 5794: case 5795: case 5796: case 5797: case 544: case 54600: case 1902: case 1508: case 428: case 3808: case 5132: case 7166: case 5078: case 5080: case 5082: case 5084: case 5126: case 5128: case 5130: case 5144: case 5146: case 5148: case 5150: case 5162: case 5164: case 5166: case 5168: case 5180: case 5182: case 5184: case 5186: case 7168: case 7170: case 7172: case 7174: case 9999: case 980: case 3212: case 4742: case 3496: case 3270: case 4722: case 9212: case 5134: case 5152: case 5170: case 5188: case 611:
	{
		return;
	}
	default:
	{

		if (getItemDef(tile).blockType == BlockTypes::GATEWAY)
		{
			namespace fs = std::experimental::filesystem;
			if (!fs::is_directory("gateway/" + getPlyersWorld(peer)->name) || !fs::exists("gateway/" + getPlyersWorld(peer)->name))
			{
				fs::create_directory("gateway/" + getPlyersWorld(peer)->name);
			}
			ofstream of("gateway/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".txt");

			of << 0 << std::endl;
			of.close();
			isgateway = true;
		}

		if (world->items[x + (y * world->width)].foreground == 1420 || world->items[x + (y * world->width)].foreground == 6214 || world->items[x + (y * world->width)].foreground == 9202 || world->items[x + (y * world->width)].foreground == 10072 || world->items[x + (y * world->width)].foreground == 10074 || world->items[x + (y * world->width)].foreground == 10076 || world->items[x + (y * world->width)].foreground == 10078 && tile != 18) {
			
			if (getItemDef(tile).blockType == BlockTypes::CLOTHING)
			{
				if (getItemDef(tile).properties & Property_Untradable) {
					Player::OnTextOverlay(peer, "You'd be sorry if u lost that!");
					return;
				}
				if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner))
				{
					auto seedexist = std::experimental::filesystem::exists("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
					if (seedexist)
					{
						json j;
						ifstream fs("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
						fs >> j;
						fs.close();

						int c = getItemDef(tile).clothType;
						if (c == 0) {
							//world->items[x + (y * world->width)].clothHead = tile;
							if (j["clothHead"].get<string>() != "0") return;
							j["clothHead"] = to_string(tile);
						}
						else if (c == 7) {
							//world->items[x + (y * world->width)].clothHair = tile;
							if (j["clothHair"].get<string>() != "0") return;
							j["clothHair"] = to_string(tile);
						}
						else if (c == 4) {
							//world->items[x + (y * world->width)].clothMask = tile;
							if (j["clothMask"].get<string>() != "0") return;
							j["clothMask"] = to_string(tile);
						}
						else if (c == 8) {
							//world->items[x + (y * world->width)].clothNeck = tile;
							if (j["clothNeck"].get<string>() != "0") return;
							j["clothNeck"] = to_string(tile);
						}
						else if (c == 6) {
							//world->items[x + (y * world->width)].clothBack = tile;
							if (j["clothBack"].get<string>() != "0") return;
							j["clothBack"] = to_string(tile);
						}
						else if (c == 1) {
							//world->items[x + (y * world->width)].clothShirt = tile;
							if (j["clothShirt"].get<string>() != "0") return;
							j["clothShirt"] = to_string(tile);
						}
						else if (c == 2) {
							//world->items[x + (y * world->width)].clothPants = tile;
							if (j["clothPants"].get<string>() != "0") return;
							j["clothPants"] = to_string(tile);
						}
						else if (c == 3) {
							//world->items[x + (y * world->width)].clothFeet = tile;
							if (j["clothFeet"].get<string>() != "0") return;
							j["clothFeet"] = to_string(tile);
						}
						else if (c == 5) {
							//world->items[x + (y * world->width)].clothHand = tile;
							if (j["clothHand"].get<string>() != "0") return;
							j["clothHand"] = to_string(tile);
						}
						if (isMod(peer)) {
							SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** display 1 **" + getItemDef(tile).name + "**", "LOGS2");
						}
						SendConsole("[MANNE] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** display 1 **" + getItemDef(tile).name + "**", "LOGS");
						if (c != 10) {
							auto iscontains = false;
							SearchInventoryItem(peer, tile, 1, iscontains);
							if (iscontains)
							{
								updateMannequin(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, world->items[x + (y * world->width)].sign,
									atoi(j["clothHair"].get<string>().c_str()), atoi(j["clothHead"].get<string>().c_str()),
									atoi(j["clothMask"].get<string>().c_str()), atoi(j["clothHand"].get<string>().c_str()), atoi(j["clothNeck"].get<string>().c_str()),
									atoi(j["clothShirt"].get<string>().c_str()), atoi(j["clothPants"].get<string>().c_str()), atoi(j["clothFeet"].get<string>().c_str()),
									atoi(j["clothBack"].get<string>().c_str()), true, 0);

								ofstream of("mannequin/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								of << j;
								of.close();
								RemoveInventoryItem(tile, 1, peer, true);
							}
						}
					}
				}
			}
		}

		if (static_cast<PlayerInfo*>(peer->data)->Fishing && static_cast<PlayerInfo*>(peer->data)->TriggerFish)
		{
			try {
				static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
				static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
				static_cast<PlayerInfo*>(peer->data)->Fishing = false;
				send_state(peer);
				if (static_cast<PlayerInfo*>(peer->data)->TriggerFish)
				{
					static_cast<PlayerInfo*>(peer->data)->TriggerFish = false;
					vector<int> FishBase{ 3000, 3024, 3026, 3030, 3032, 3034, 3036, 3038, 3092, 3094, 3096, 3220, 3222, 3224, 3226, 3434, 3436, 3438, 3440, 3450, 3452, 3454, 3456, 3458, 3460, 3544, 3550, 3620, 3746, 3814, 3820, 4958, 5100, 5448, 5450, 5538, 5542, 5548, 5552, 5574, 5580, 7744, 8460 };
					srand(GetTickCount());
					const int Index = rand() % FishBase.size();
					const auto ItemID = FishBase[Index];
					vector<int> GearBase{ 344, 242, 3042, 3016, 10032, 5232, 5604, 5606, 5608, 6902, 6996, 9746 };
					const int GearIndex = rand() % GearBase.size();
					const auto GearID = GearBase[GearIndex];
					vector<int> BlockBase{ 444, 242, 1522, 3016, 3810, 4658, 5530, 5602, 5614, 5624, 6328, 7002, 8964, 8966 };
					const int BlockIndex = rand() % BlockBase.size();
					const auto BlockID = BlockBase[BlockIndex];
					auto count = 1;
					int ChanceOfGear = 0;
					int HowMuchLbs;
					int ChanceOfBlock = 0;
					if (static_cast<PlayerInfo*>(peer->data)->LastBait == "Fishing Fly")
					{
						ChanceOfBlock = (rand() % 400) + 1;
					}
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2912) /*regular*/
					{
						HowMuchLbs = (rand() % 25) + 1;
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3008) /*ezrod*/
					{
						HowMuchLbs = (rand() % 40) + 1;
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3010) /*licorice*/
					{
						HowMuchLbs = (rand() % 60) + 1;
						ChanceOfGear = (rand() % 450) + 1;
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3100) /*cursed*/
					{
						HowMuchLbs = (rand() % 200) + 1;
						ChanceOfGear = (rand() % 150) + 1;
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3040) /*golden*/
					{
						HowMuchLbs = (rand() % 200) + 1;
						ChanceOfGear = (rand() % 200) + 1;
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 5740) /*magical*/
					{
						HowMuchLbs = (rand() % 90) + 1;
						ChanceOfGear = (rand() % 350) + 1;
					}
					else
					{
						return;
					}
					count = HowMuchLbs;
					if (ChanceOfBlock <= 30 && ChanceOfBlock != 0)
					{
						auto success = true;
						SaveItemMoreTimes(BlockID, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from fishing");
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2You caught `5" + getItemDef(BlockID).name + "`2!", 0, false);
						auto Gems = (rand() % 100) + 1;
						auto currentGems = 0;
						ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						ifs >> currentGems;
						ifs.close();
						currentGems += Gems;
						ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						ofs << currentGems;
						ofs.close();
						SendXP(peer, 3);
						Player::OnSetBux(peer, currentGems, 0);
						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer))
							{
								Player::OnConsoleMessage(currentPeer, "`$" + static_cast<PlayerInfo*>(peer->data)->displayName + " `oCaught `$" + getItemDef(BlockID).name + " `oAnd got `$" + to_string(Gems) + " `oGems!");
								Player::PlayAudio(currentPeer, "audio/choir.wav", 0);
							}
						}
						Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
						SendBreakPacket(peer, x, y);
						return;
					}
					if (ChanceOfGear <= 10 && ChanceOfGear != 0)
					{
						auto success = true;
						SaveItemMoreTimes(GearID, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from fishing");
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2You caught `5" + getItemDef(GearID).name + "`2!", 0, false);
						auto Gems = (rand() % 200) + 1;
						auto currentGems = 0;
						ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						ifs >> currentGems;
						ifs.close();
						currentGems += Gems;
						ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
						ofs << currentGems;
						ofs.close();
						SendXP(peer, 5);
						Player::OnSetBux(peer, currentGems, 0);
						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer))
							{
								Player::OnConsoleMessage(currentPeer, "`$" + static_cast<PlayerInfo*>(peer->data)->displayName + " `oCaught `$" + getItemDef(GearID).name + " `oAnd got `$" + to_string(Gems) + " `oGems!");
								Player::PlayAudio(currentPeer, "audio/choir.wav", 0);
							}
						}
						Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
						SendBreakPacket(peer, x, y);
						return;
					}
					auto iscontains = false;
					SearchInventoryItem(peer, ItemID, 1, iscontains);
					if (!iscontains)
					{
						auto success = true;
						SaveItemMoreTimes(ItemID, count, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from fishing");
					}
					else
					{
						DropItem(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y, ItemID, count, 0);
					}
					if (getItemDef(ItemID).blockType == BlockTypes::FISH)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2You caught `5" + getItemDef(ItemID).name + "`2! (`5" + to_string(count) + "`2 LBS)", 0, false);
					}
					else
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`2You caught `5" + getItemDef(ItemID).name + "`2!", 0, false);
					}
					auto Gems = 0;
					if (count >= 1 && count < 30)
					{
						Gems = (rand() % 100) + 1;
					}
					else if (count >= 30 && count < 60)
					{
						Gems = (rand() % 105) + 1;
					}
					else if (count >= 60 && count < 90)
					{
						Gems = (rand() % 110) + 1;
					}
					else if (count >= 90 && count < 120)
					{
						Gems = (rand() % 115) + 1;
					}
					else if (count >= 120 && count < 150)
					{
						Gems = (rand() % 120) + 1;
					}
					else if (count >= 150 && count < 199)
					{
						Gems = (rand() % 125) + 1;
					}
					else if (count >= 200)
					{
						Gems = (rand() % 140) + 1;
					}
					auto currentGems = 0;
					ifstream ifs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					ifs >> currentGems;
					ifs.close();
					currentGems += Gems;
					ofstream ofs("gemdb/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".txt");
					ofs << currentGems;
					ofs.close();
					SendXP(peer, 2);
					Player::OnSetBux(peer, currentGems, 0);
					ENetPeer* currentPeer;
					for (currentPeer = server->peers;
						currentPeer < &server->peers[server->peerCount];
						++currentPeer)
					{
						if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, currentPeer))
						{
							Player::OnConsoleMessage(currentPeer, "`$" + static_cast<PlayerInfo*>(peer->data)->displayName + " `oCaught `$" + getItemDef(ItemID).name + " `o(`$" + to_string(count) + "`o LBS) And got `$" + to_string(Gems) + " `oGems!");
							Player::PlayAudio(currentPeer, "audio/keypad_hit.wav", 0);
						}
					}
				}
				Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
				SendBreakPacket(peer, x, y);
				return;
			}
			catch (std::exception&) {
				SendConsole("Critical error fishing : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
			catch (std::runtime_error&) {
				SendConsole("Critical error fishing : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
			catch (...) {
				SendConsole("Critical error fishing : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
		}
		if (tile == 2914 && isFishingRod(peer) || tile == 3016 && isFishingRod(peer))
		{
			try {
				if (world->items[x + (y * world->width)].water)
				{
					int PlayerPos = round(static_cast<PlayerInfo*>(peer->data)->x / 32);
					int PlayerPosY = round(static_cast<PlayerInfo*>(peer->data)->y / 32);
					if (PlayerPos != x && PlayerPos + 1 != x && PlayerPos - 1 != x || PlayerPosY != y && PlayerPosY + 1 != y)
					{
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Too far away...", 0, true);
						return;
					}
					if (static_cast<PlayerInfo*>(peer->data)->x != 0 && !static_cast<PlayerInfo*>(peer->data)->Fishing)
					{
						RemoveInventoryItem(tile, 1, peer, true);
						static_cast<PlayerInfo*>(peer->data)->FishPosX = x * 32;
						static_cast<PlayerInfo*>(peer->data)->FishPosY = y * 32;
						static_cast<PlayerInfo*>(peer->data)->Fishing = true;
						static_cast<PlayerInfo*>(peer->data)->LastBait = getItemDef(tile).name;
						SendFishingState(peer);
						ENetPeer* currentPeer;
						for (currentPeer = server->peers;
							currentPeer < &server->peers[server->peerCount];
							++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer))
							{
								SendFishing(currentPeer, static_cast<PlayerInfo*>(peer->data)->netID, x, y);
							}
						}
					}
					else
					{
						static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
						static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
						static_cast<PlayerInfo*>(peer->data)->Fishing = false;
						send_state(peer);
						Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
					}
				}
				return;
			}
			catch (std::exception&) {
				SendConsole("Critical error fishing : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
			catch (std::runtime_error&) {
				SendConsole("Critical error fishing : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
			catch (...) {
				SendConsole("Critical error fishing : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
		}
		if (static_cast<PlayerInfo*>(peer->data)->Fishing)
		{
			try {
				static_cast<PlayerInfo*>(peer->data)->FishPosX = 0;
				static_cast<PlayerInfo*>(peer->data)->FishPosY = 0;
				static_cast<PlayerInfo*>(peer->data)->Fishing = false;
				send_state(peer);
				Player::OnSetPos(peer, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->x, static_cast<PlayerInfo*>(peer->data)->y);
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`wSit perfectly while fishing`w!", 0, true);
				return;
			}
			catch (std::exception&) {
				SendConsole("Critical error fishing : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
			catch (std::runtime_error&) {
				SendConsole("Critical error fishing : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
			catch (...) {
				SendConsole("Critical error fishing : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
		}
		if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3494)
		{
			try {
				if (world->owner == "" || static_cast<PlayerInfo*>(peer->data)->rawName == PlayerDB::getProperName(world->owner) || isMod(peer))
				{
					switch (tile)
					{
					case 3478:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							return;
						}
						world->items[x + (y * world->width)].red = true;
						world->items[x + (y * world->width)].green = false;
						world->items[x + (y * world->width)].blue = false;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3480:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							return;
						}
						world->items[x + (y * world->width)].red = true;
						world->items[x + (y * world->width)].green = true;
						world->items[x + (y * world->width)].blue = false;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3482:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
						{
							return;
						}
						world->items[x + (y * world->width)].red = false;
						world->items[x + (y * world->width)].green = true;
						world->items[x + (y * world->width)].blue = false;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3484:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
						{
							return;
						}
						world->items[x + (y * world->width)].red = false;
						world->items[x + (y * world->width)].green = true;
						world->items[x + (y * world->width)].blue = true;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3486:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
						{
							return;
						}
						world->items[x + (y * world->width)].red = false;
						world->items[x + (y * world->width)].green = false;
						world->items[x + (y * world->width)].blue = true;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3488:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
						{
							return;
						}
						world->items[x + (y * world->width)].red = true;
						world->items[x + (y * world->width)].green = false;
						world->items[x + (y * world->width)].blue = true;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3490:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
						{
							return;
						}
						world->items[x + (y * world->width)].red = true;
						world->items[x + (y * world->width)].green = true;
						world->items[x + (y * world->width)].blue = true;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					case 3492:
						if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK || world->items[x + (y * world->width)].foreground == 2946)
						{
							return;
						}
						world->items[x + (y * world->width)].red = false;
						world->items[x + (y * world->width)].green = false;
						world->items[x + (y * world->width)].blue = false;
						UpdateVisualsForBlock(peer, true, x, y, world);
						return;
					default: break;
					}
				}
			}
			catch (std::exception&) {
				SendConsole("Critical error paint : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
			catch (std::runtime_error&) {
				SendConsole("Critical error paint : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
			catch (...) {
				SendConsole("Critical error paint : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
		}
		if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 3066 && world->items[x + (y * world->width)].fire)
		{
			try {
				if (tile == 822)
				{
					SendThrowEffect(peer, 822, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
					world->items[x + (y * world->width)].fire = false;
					UpdateBlockState(peer, x, y, true, world);
					ENetPeer* net_peer;
					for (net_peer = server->peers;
						net_peer < &server->peers[server->peerCount];
						++net_peer)
					{
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer))
						{
							Player::OnParticleEffect(net_peer, 149, x * 32, y * 32, 0);
						}
					}
				}
				else
				{
					ENetPeer* net_peer;
					for (net_peer = server->peers;
						net_peer < &server->peers[server->peerCount];
						++net_peer)
					{
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer))
						{
							Player::OnParticleEffect(net_peer, 149, x * 32, y * 32, 0);
						}
					}
					world->items[x + (y * world->width)].fire = false;
					UpdateBlockState(peer, x, y, true, world);
				}
			}
			catch (std::exception&) {
				SendConsole("Critical error fire : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
			catch (std::runtime_error&) {
				SendConsole("Critical error fire : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
			catch (...) {
				SendConsole("Critical error fire : rawName(" + static_cast<PlayerInfo*>(peer->data)->rawName + ")", "ERROR");
				enet_peer_disconnect_now(peer, 0);
				return;
			}
		}
		if (world->owner != "" && !isWorldOwner(peer, world) && !isWorldAdmin(peer, world) && !isMod(peer))
		{
			if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer) || tile == world->interactableid || tile == 5640)
			{
				// everything ok
			}
			else if (isWorldAdmin(peer, world))
			{
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
				{
					string ownername = PlayerDB::getProperName(world->owner);
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
					Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
					return;
				}
			}
			else if (world->isPublic)
			{
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
				{
					string ownername = PlayerDB::getProperName(world->owner);
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
					Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
					return;
				}
			}
			else if (world->isEvent)
			{
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
				{
					string ownername = PlayerDB::getProperName(world->owner);
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
					Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
					return;
				}
				else if (world->items[x + (y * world->width)].foreground != world->interactableid)
				{
					Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
					return;
				}
			}
			else
			{
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId == false)
				{
					Player::OnTextOverlay(peer, "`#Create `9Grow-ID `#First`9!");
				}
				else
				{
					Player::PlayAudio(peer, "audio/punch_locked.wav", 0);
					return;
				}
			}
			if (tile == 18 && isMod(peer))
			{
				if (isWorldAdmin(peer, world) && !isWorldOwner(peer, world))
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`2Access Granted`w)", 0, true);
					}
				}
				else if (world->isPublic && !isWorldOwner(peer, world))
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`9Open to Public`w)", 0, true);
					}
				}
				else if (world->isEvent && !isWorldOwner(peer, world))
				{
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK)
					{
						string ownername = PlayerDB::getProperName(world->owner);
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`w" + ownername + "'s `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`w. (`4No Access`w)", 0, true);
					}
				}
			}
			if (tile == 242 || tile == 2408 || tile == 1796 || tile == 4428 || tile == 7188 || tile == 8470 || tile == 9290 || tile == 9308 || tile == 9504 || tile == 2950 || tile == 4802 || tile == 5260 || tile == 5814 || tile == 5980 || tile == 9640)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0Only one `$World Lock `0Can be placed in a world!", 0, true);
				return;
			}
		}
		if (world->owner != "")
		{
			if (tile == 242 || tile == 2408 || tile == 1796 || tile == 4428 || tile == 7188 || tile == 8470 || tile == 9290 || tile == 9308 || tile == 9504 || tile == 2950 || tile == 4802 || tile == 5260 || tile == 5814 || tile == 5980 || tile == 9640)
			{
				Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`0Only one `$World Lock `0Can be placed in a world!", 0, true);
				return;
			}
		}

		if (world->items[x + (y * world->width)].foreground == 10 && tile == 3400)
		{
			if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer) || world->owner == "")
			{
				RemoveInventoryItem(3400, 1, peer, true);
				world->items[x + (y * world->width)].foreground = 392;
				PlayerMoving data3;
				data3.packetType = 0x3;
				data3.characterState = 0x0;
				data3.x = x;
				data3.y = y;
				data3.punchX = x;
				data3.punchY = y;
				data3.XSpeed = 0;
				data3.YSpeed = 0;
				data3.netID = -1;
				data3.plantingTree = 392;
				ENetPeer* currentPeer;
				for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer))
					{
						auto raw = packPlayerMoving(&data3);
						raw[2] = dicenr;
						raw[3] = dicenr;
						SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
					}
				}
				for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					Player::OnParticleEffect(currentPeer, 44, x * 32, y * 32, 0);
				}
			}
		}

		if (world->items[x + (y * world->width)].foreground == 2946 && tile != 18 && tile != 32 && tile > 0)
		{
			if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || isMod(peer))
			{
				using namespace std::chrono;
				if (static_cast<PlayerInfo*>(peer->data)->lastDISPLAY + 1000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count())
				{
					static_cast<PlayerInfo*>(peer->data)->lastDISPLAY = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
					auto iscontains = false;
					SearchInventoryItem(peer, tile, 1, iscontains);
					if (!iscontains) return;
					else
					{
						auto xSize = world->width;
						auto ySize = world->height;
						if (xSize == 100 && ySize == 60)
						{
							auto n = tile;
							if (getItemDef(n).properties & Property_Untradable || n == 5142 || n == 6336 || n == 8552 || n == 9472 || n == 5640 || n == 9482 || n == 9356 || n == 9492 || n == 9498 || n == 8774 || n == 1790 || n == 2592 || n == 1784 || n == 1792 || n == 1794 || n == 7734 || n == 8306 || n == 9458)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You can't display untradeable items.", 0, true);
								return;
							}
							if (getItemDef(n).blockType == BlockTypes::LOCK || n == 2946)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Sorry, no displaying Display Blocks or Locks.", 0, true);
								return;
							}
							auto targetworld = getPlyersWorld(peer);
							if (targetworld->items[x + (y * targetworld->width)].intdata == 0)
							{
								targetworld->items[x + (y * targetworld->width)].intdata = tile;
								ENetPeer* currentPeer;
								for (currentPeer = server->peers;
									currentPeer < &server->peers[server->peerCount];
									++currentPeer)
								{
									if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
									if (isHere(peer, currentPeer))
									{
										UpdateVisualsForBlock(currentPeer, true, x, y, targetworld);
										SendThrowEffect(currentPeer, tile, static_cast<PlayerInfo*>(peer->data)->netID, -1, 150, 0, x * 32 + 16, y * 32 + 16);
									}
								}
								if (isMod(peer)) {
									SendConsole("[DBLOCK] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** display 1 **" + getItemDef(tile).name + "**", "LOGS2");
								}
								SendConsole("[DBLOCK] Player **" + static_cast<PlayerInfo*>(peer->data)->rawName + "** display 1 **" + getItemDef(tile).name + "**", "LOGS");
								RemoveInventoryItem(n, 1, peer, true);
								updateplayerset(peer, n);
							}
							else
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Remove what's in there first!", 0, true);
							}
							return;
						}
						else
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Display blocks cannot be used in uranus worlds!", 0, true);
							return;
						}
					}
				}
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Slow down while using display blocks!", 0, true);;
					return;
				}
			}
			else
			{
				if (world->owner == "")
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This area must be locked to put your item on display!", 0, true);
				}
				else if (getPlyersWorld(peer)->isPublic)
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
				}
				else
				{
					Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "That area is owned by " + world->owner + "", 0, true);
				}
				return;
			}
		}
		if (getItemDef(tile).blockType == BlockTypes::CONSUMABLE || getItemDef(tile).blockType == BlockTypes::CLOTHING) return;
		if (getItemDef(tile).blockType == BlockTypes::SEED)
		{
			if (world->items[x + (y * world->width)].foreground != 0)
			{
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SEED)
				{
					if (getPlyersWorld(peer)->isPublic || isWorldAdmin(peer, world) || static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer))
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).name == getItemDef(tile).name || getItemDef(world->items[x + (y * world->width)].foreground).rarity == 999 || getItemDef(tile).rarity == 999)
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You cant splice them", 0, true);
							return;
						}
						auto iscontains = false;
						SearchInventoryItem(peer, tile, 1, iscontains);
						if (!iscontains) return;
						auto squaresign = x + (y * 100);
						auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
						auto seedexist = std::experimental::filesystem::exists("misc/seeds/" + currentworld + ".txt");
						if (!seedexist)
						{
							auto targetvalue = getItemDef(world->items[x + (y * world->width)].foreground).rarity + getItemDef(tile).rarity;
							for (auto i = 0; i < 10490; i++)
							{
								if (getItemDef(i).rarity == targetvalue)
								{
									RemoveInventoryItem(tile, 1, peer, true);
									ofstream seedapply("misc/seeds/" + currentworld + ".txt");
									seedapply << "true";
									seedapply.close();
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You spliced " + getItemDef(world->items[x + (y * world->width)].foreground).name + " with " + getItemDef(tile).name + " and got " + getItemDef(i + 1).name, 0, true);
									Player::PlayAudio(peer, "audio/success.wav", 0);
									world->items[x + (y * world->width)].foreground = i + 1;
									PlayerMoving data3;
									data3.packetType = 0x3;
									data3.characterState = 0x0;
									data3.x = x;
									data3.y = y;
									data3.punchX = x;
									data3.punchY = y;
									data3.XSpeed = 0;
									data3.YSpeed = 0;
									data3.netID = -1;
									data3.plantingTree = i + 1;
									ENetPeer* currentPeer;
									for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
									{
										if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
										if (isHere(peer, currentPeer))
										{
											auto raw = packPlayerMoving(&data3);
											raw[2] = dicenr;
											raw[3] = dicenr;
											SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
										}
									}
									auto numb = (rand() % 4) + 1;
									UpdateTreeVisuals(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, numb, 8006000, true, 0);
									break;
								}
								else if (i >= 10490)
								{
									Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You cant splice them", 0, true);
									return;
								}
							}
						}
						else
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "This seed was already spliced!", 0, true);
							return;
						}
						return;
					}
					else
					{
						return;
					}
				}
				else
				{
					return;
				}
			}
			else
			{
				isTree = true;
			}
		}
		break;
	}
	}
	if (causedBy != -1)
	{
		auto iscontains = false;
		SearchInventoryItem(peer, tile, 1, iscontains);
		if (!iscontains) return;
	}
	ItemDefinition def;
	try {
		def = getItemDef(tile);
		if (def.clothType != ClothTypes::NONE) return;
	}
	catch (int e) {
		def.breakHits = 5;
		if (def.blockType = BlockTypes::SEED) return;
		def.blockType = BlockTypes::UNKNOWN;
	}
	int test;
	if (((PlayerInfo*)(peer->data))->cloth_hand == 2952) {
		test = 1;
	}
	else {
		test = getItemDef(world->items[x + (y * world->width)].foreground).breakHits;
	}
	ENetPeer* currentPeer;
	if (tile == 18)
	{
		if (world->items[x + (y * world->width)].background == 6864 && world->items[x + (y * world->width)].foreground == 0) return;
		if (world->items[x + (y * world->width)].background == 0 && world->items[x + (y * world->width)].foreground == 0) return;
		ItemDefinition brak;
		if (world->items[x + (y * world->width)].foreground != 0)
		{
			brak = getItemDef(world->items[x + (y * world->width)].foreground);
		}
		else
		{
			brak = getItemDef(world->items[x + (y * world->width)].background);
		}
		data.packetType = 0x8;
		data.plantingTree = 6;
		using namespace std::chrono;

		if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 10390 && tile == 18)
		{
			if (isWorldOwner(peer, world) || isMod(peer) || world->isPublic || world->owner == "")
			{
				//data.packetType = 0x3;
				//data.netID = causedBy;
				int kek = world->items[x + (y * world->width)].foreground;
				//data.plantingTree = 18;
				if (world->items[x + (y * world->width)].foreground != 0)
				{
					kek = world->items[x + (y * world->width)].foreground;
					//world->items[x + (y * world->width)].foreground = 0;
				}
				else
				{
					kek = world->items[x + (y * world->width)].background;
					//world->items[x + (y * world->width)].foreground = 0;
					//world->items[x + (y * world->width)].background = 0;
				}
				ENetPeer* net_peer;
				for (net_peer = server->peers;
					net_peer < &server->peers[server->peerCount];
					++net_peer)
				{
					if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, net_peer))
					{
						//auto rawx = packPlayerMoving(&data);
						//SendPacketRaw(4, rawx, 56, nullptr, net_peer, ENET_PACKET_FLAG_RELIABLE);
						SendParticleEffect(net_peer, x * 32, y * 32, kek, 97, 0);
					}
				}
			}
		}

		if (static_cast<PlayerInfo*>(peer->data)->PunchPotion && tile == 18 || static_cast<PlayerInfo*>(peer->data)->cloth_necklace == 6260 && tile == 18 && static_cast<PlayerInfo*>(peer->data)->Subscriber)
		{
			if (world->items[x + (y * world->width)].foreground == 5138 || world->items[x + (y * world->width)].foreground == 5136 || world->items[x + (y * world->width)].foreground == 5140 || world->items[x + (y * world->width)].foreground == 5156 || world->items[x + (y * world->width)].foreground == 5158 || world->items[x + (y * world->width)].foreground == 2 || world->items[x + (y * world->width)].background == 14)
			{
				if (isWorldOwner(peer, world) || isMod(peer) || world->isPublic || world->owner == "")
				{
					if (world->items[x + (y * world->width)].foreground == 5136) /*amethyst*/
					{
						SendFarmableDrop(peer, 150);
						auto val = rand() % 700;
						if (val == 297) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						if (val == 398) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						if (val == 112) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						SendGuildPoints(peer, 1);
						SendXP(peer, 2);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					}
					else if (world->items[x + (y * world->width)].foreground == 5138) /*Onyx*/
					{
						SendFarmableDrop(peer, 350);
						SendGuildPoints(peer, 2);
						SendXP(peer, 2);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
						auto val = rand() % 600;
						if (val == 297) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						if (val == 398) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						if (val == 112) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
					}
					else if (world->items[x + (y * world->width)].foreground == 5140) /*Diamondstone*/
					{
						SendFarmableDrop(peer, 600);
						SendGuildPoints(peer, 3);
						SendXP(peer, 5);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
						auto val = rand() % 570;
						if (val == 297) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						if (val == 398) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						if (val == 112) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
					}
					else if (world->items[x + (y * world->width)].foreground == 5156) /*Diamondstone*/
					{
						SendFarmableDrop(peer, 1200);
						SendGuildPoints(peer, 5);
						SendXP(peer, 3);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
						auto val = rand() % 560;
						if (val == 297) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						if (val == 398) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						if (val == 112) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
					}
					else if (world->items[x + (y * world->width)].foreground == 5158) /*Diamondstone*/
					{
						SendFarmableDrop(peer, 1900);
						SendGuildPoints(peer, 5);
						SendXP(peer, 3);
						SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
						auto val = rand() % 550;
						if (val == 297) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						if (val == 398) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
						if (val == 112) {
							DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
						}
					}
					else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						for (auto i = 0; i < world->width * world->height; i++)
						{
							if (world->items[i].foreground == 1790)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oTake all `cUntradeable `oBlocks, before breaking The `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`o!", 0, true);
								return;
							}
						}
						if (static_cast<PlayerInfo*>(peer->data)->NickPrefix == "") updateworldremove(peer);
						auto success = true;
						auto info = getPlyersWorld(peer);
						auto nameworld = info->name;
						SaveItemMoreTimes(info->items[x + (y * info->width)].foreground, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						ENetPeer* net_peer;
						for (net_peer = server->peers;
							net_peer < &server->peers[server->peerCount];
							++net_peer)
						{
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer))
							{
								Player::OnConsoleMessage(net_peer, "`5[`w" + nameworld + " `ohas had its `$" + getItemDef(info->items[x + (y * info->width)].foreground).name + " `oremoved!`5]");
								Player::PlayAudio(peer, "audio/fireball.wav", 0);
							}
						}
						if (info->owner != static_cast<PlayerInfo*>(peer->data)->rawName)
						{
							ofstream removelocklogs("logs/removelock.txt", ios::app);
							removelocklogs << "User " << static_cast<PlayerInfo*>(peer->data)->rawName << " removed lock from " << nameworld << " world. This world was locked by " << info->owner << endl;
							removelocklogs.close();
						}
						info->owner = "";
						info->ownerID = 0;
						info->isPublic = false;
						info->ownerDisplayName = "";
						info->accessed.clear();
						info->silence = false;
						info->items[x + (y * info->width)].foreground = 0;
						((PlayerInfo*)(peer->data))->worldsowned.erase(std::remove(((PlayerInfo*)(peer->data))->worldsowned.begin(), ((PlayerInfo*)(peer->data))->worldsowned.end(), nameworld), ((PlayerInfo*)(peer->data))->worldsowned.end());
					}
					else {
						SendXP(peer, 1);
					}

					data.packetType = 0x3;
					data.netID = causedBy;
					int kek = world->items[x + (y * world->width)].foreground;
					data.plantingTree = 18;
					
					if (world->items[x + (y * world->width)].foreground != 0)
					{
						kek = world->items[x + (y * world->width)].foreground;
						world->items[x + (y * world->width)].foreground = 0;
					}
					else
					{
						kek = world->items[x + (y * world->width)].background;
						world->items[x + (y * world->width)].foreground = 0;
						world->items[x + (y * world->width)].background = 0;
					}
					ENetPeer* net_peer;
					for (net_peer = server->peers;
						net_peer < &server->peers[server->peerCount];
						++net_peer)
					{
						if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
						if (isHere(peer, net_peer))
						{
							auto rawx = packPlayerMoving(&data);
							SendPacketRaw(4, rawx, 56, nullptr, net_peer, ENET_PACKET_FLAG_RELIABLE);
							SendParticleEffect(net_peer, x * 32, y * 32, kek, 97, 0);
						}
					}
					return;
				}
			}
		}
		if ((duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() - world->items[x + (y * world->width)].breakTime >= 5000)
		{
			world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
			world->items[x + (y * world->width)].breakLevel = 5; // TODO
		}
		else
			if (y < world->height && world->items[x + (y * world->width)].breakLevel + 5 >= def.breakHits * 4) {
			
				data.packetType = 0x3;
				data.netID = causedBy;
				data.plantingTree = 18;
				data.punchX = x;
				data.punchY = y;
				world->items[x + (y * world->width)].breakLevel = 0;
				auto hi = data.punchX * 32;
				auto hi2 = data.punchY * 32;
				if (world->items[x + (y * world->width)].foreground == 5136) /*amethyst*/
				{
					SendFarmableDrop(peer, 150);
					auto val = rand() % 700;
					if (val == 297) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					if (val == 398) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					if (val == 112) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					SendGuildPoints(peer, 1);
					SendXP(peer, 2);
					SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
				}
				else if (world->items[x + (y * world->width)].foreground == 5138) /*Onyx*/
				{
					SendFarmableDrop(peer, 350);
					SendGuildPoints(peer, 2);
					SendXP(peer, 2);
					SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					auto val = rand() % 600;
					if (val == 297) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					if (val == 398) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					if (val == 112) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 5140) /*Diamondstone*/
				{
					SendFarmableDrop(peer, 600);
					SendGuildPoints(peer, 3);
					SendXP(peer, 5);
					SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					auto val = rand() % 570;
					if (val == 297) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					if (val == 398) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					if (val == 112) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 5156) /*Diamondstone*/
				{
					SendFarmableDrop(peer, 1200);
					SendGuildPoints(peer, 5);
					SendXP(peer, 3);
					SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					auto val = rand() % 560;
					if (val == 297) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					if (val == 398) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					if (val == 112) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 5158) /*Diamondstone*/
				{
					SendFarmableDrop(peer, 1900);
					SendGuildPoints(peer, 5);
					SendXP(peer, 3);
					SendDropSeed(peer, x, y, world->items[x + (y * world->width)].foreground);
					auto val = rand() % 550;
					if (val == 297) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					if (val == 398) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
					if (val == 112) {
						DropItem(peer, -1, x * 32 + (rand() % 16), y * 32 + (rand() % 16), 5160, 1, 0);
					}
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9454)
				{
					Player::OnParticleEffect(peer, 108, hi, hi2, 0);
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9452)
				{
					Player::OnParticleEffect(peer, 44, hi, hi2, 0);
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9448)
				{
					Player::OnParticleEffect(peer, 58, hi, hi2, 0);
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 2952)
				{
					Player::OnParticleEffect(peer, 97, hi, hi2, 0);
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 1874)
				{
					Player::OnParticleEffect(peer, 97, hi, hi2, 0);
				}
				if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 9430)
				{
					Player::OnParticleEffect(peer, 97, hi, hi2, 0);
				}
				if (world->items[x + (y * world->width)].foreground == 10024)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4426 };
					int index = rand() % list.size();
					auto value = list[index];
					if (value == 4426)
					{
						srand(GetTickCount());
						auto droploc = rand() % 18;
						auto droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 4426, 1, 0);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 9460)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2410 };
					int index = rand() % list.size(); // pick a random index
					int value = list[index];
					if (value == 2410)
					{
						bool success = true;
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 2410, 1, 0);
						int hi = data.punchX * 32;
						int hi2 = data.punchY * 32;
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 7382)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9240 };
					int index = rand() % list.size(); // pick a random index
					int value = list[index];
					if (value == 9240)
					{
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 9240, 1, 0);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 9414)
				{
					world->items[x + (y * world->width)].foreground = 0;
					int kuriPrizaDuot = rand() % 3 + 1;
					if (kuriPrizaDuot == 1)
					{
						int gemChance = rand() % 12000;
						GiveChestPrizeGems(peer, gemChance);
					}
					if (kuriPrizaDuot == 2)
					{
						int luck = rand() % 3 + 1;
						if (luck == 1)
						{
							GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`^Your `1Luck `^Shines Away..."), 0));
							ENetPacket* packet2 = enet_packet_create(p2.data,
								p2.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet2);
							delete p2.data;
						}
						if (luck == 2)
						{
							GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`^The `1Ocean `9Gods `^Didn't Want To Play With You..."), 0));
							ENetPacket* packet2 = enet_packet_create(p2.data,
								p2.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet2);
							delete p2.data;
						}
						if (luck == 3)
						{
							GamePacket p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), "`^You `9Starting `^To Feel `1Tired`^..."), 0));
							ENetPacket* packet2 = enet_packet_create(p2.data,
								p2.len,
								ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send(peer, 0, packet2);
							delete p2.data;
						}
					}
					if (kuriPrizaDuot == 3)
					{
						int itemuMas[62] = { 9416, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 9416, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 9414, 9414, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 9414, 1796, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328, 7328 };
						int randIndex = rand() % 62;
						int itemId = itemuMas[randIndex];
						send_item(peer, itemId, 1, 9414);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 3402 || world->items[x + (y * world->width)].foreground == 392 || world->items[x + (y * world->width)].foreground == 9350)
				{
					if (world->items[x + (y * world->width)].foreground == 3402) static_cast<PlayerInfo*>(peer->data)->bootybreaken++;
					if (static_cast<PlayerInfo*>(peer->data)->bootybreaken >= 30)
					{
						static_cast<PlayerInfo*>(peer->data)->bootybreaken = 0;
						bool success = true;
						SaveItemMoreTimes(9350, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						SendTradeEffect(peer, 9350, static_cast<PlayerInfo*>(peer->data)->netID, static_cast<PlayerInfo*>(peer->data)->netID, 150);
					}
					vector<int> list{ 362, 3398, 386, 4422, 364, 9340, 9342, 9332, 9334, 9336, 9338, 366, 2388, 7808, 7810, 4416, 7818, 7820, 5652, 7822, 7824, 5644, 390, 7826, 7830, 9324, 5658, 3396, 2384, 5660, 3400, 4418, 4412, 388, 3408, 1470, 3404, 3406, 2390, 5656, 5648, 2396, 384, 5664, 4424, 4400, 1458 };
					int itemid = list[rand() % list.size()];
					if (itemid == 1458)
					{
						int target = 5;
						if (world->items[x + (y * world->width)].foreground == 9350) target = 10;
						if ((rand() % 10000) <= target) {}
						else itemid = 7808;
					}
					DropItem(peer, -1, x * 32 + rand() % 18, y * 32 + rand() % 18, itemid, 1, 0);
				}
				else if (world->items[x + (y * world->width)].foreground == 192 || world->items[x + (y * world->width)].foreground == 1004)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9490 };
					int index = rand() % list.size();
					int value = list[index];
					if (value == 9490)
					{
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 9490, 1, 0);
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 2)
				{
					if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9506)
					{
						std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7382 };
						int index = rand() % list.size();
						int value = list[index];
						if (value == 7382)
						{
							srand(GetTickCount());
							int droploc = rand() % 18;
							int droplocs = rand() % 18;
							DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 7382, 1, 0);
						}
					}
				}
				else if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 10028 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 9460 || world->items[x + (y * world->width)].foreground == 9468)
				{
					std::vector<int> list{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9462 };
					int index = rand() % list.size();
					int value = list[index];
					if (value == 9462)
					{
						srand(GetTickCount());
						int droploc = rand() % 18;
						int droplocs = rand() % 18;
						DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, 9462, 1, 0);
					}
				}
				else if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 8452)
				{
					int i = data.punchX * 32;
					int i1 = data.punchY * 32;
					Player::OnParticleEffect(peer, 149, i, i1, 0);
				}
				if (world->items[x + (y * world->width)].foreground == 3794)
				{
					if (world->items[x + (y * world->width)].dshelf1 != 0 || world->items[x + (y * world->width)].dshelf2 != 0 || world->items[x + (y * world->width)].dshelf4 != 0 || world->items[x + (y * world->width)].dshelf3 != 0) {
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Empty the shelf before breaking it!", 0, true);
						tanga = true;
						return;
					}
				}
				if (world->items[x + (y * world->width)].foreground == 6954)
				{
					if (world->technogems != 0) {
						tanga = true;
						Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Empty the technogems before breaking it!", 0, true);
						return;
					}
					else {
						bool success = false;
						SaveShopsItemMoreTimes(6954, 1, peer, success, "");
					}
				}
				if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::WEATHER)
				{
					tanga = true;
				}
				
				if (world->items[x + (y * world->width)].foreground != 0)
				{
					if (world->items[x + (y * world->width)].foreground == 2978)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
							string itemcount = "";
							ifstream fdsss("vend/count/" + currentworld + ".txt");
							fdsss >> itemcount;
							fdsss.close();
							string withcount = "";
							ifstream fdsss3("vend/withdraw/" + currentworld + ".txt");
							fdsss3 >> withcount;
							fdsss3.close();
							if (itemcount != "" && itemcount != "0" || withcount != "" && withcount != "0")
							{
								tanga = true;
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Empty the machine before breaking it!", 0, true);
								return;
							}
							auto isvend = std::experimental::filesystem::exists("vend/id/" + currentworld + ".txt");
							if (isvend)
							{
								remove(("vend/id/" + currentworld + ".txt").c_str());
							}
							auto isvend3 = std::experimental::filesystem::exists("vend/count/" + currentworld + ".txt");
							if (isvend3)
							{
								remove(("vend/count/" + currentworld + ".txt").c_str());
							}
							auto isvend6 = std::experimental::filesystem::exists("vend/withdraw/" + currentworld + ".txt");
							if (isvend6)
							{
								remove(("vend/withdraw/" + currentworld + ".txt").c_str());
							}
							auto isvend9 = std::experimental::filesystem::exists("vend/price/" + currentworld + ".txt");
							if (isvend9)
							{
								remove(("vend/price/" + currentworld + ".txt").c_str());
							}
							auto success = true;
							SaveItemMoreTimes(2978, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
					}
					if (world->items[x + (y * world->width)].foreground == 6286)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								if (j["instorage"] > 0)
								{
									tanga = true;
									Player::OnTextOverlay(peer, "Empty the box first!");
									return;
								}
								remove(("storageboxlvl1/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
							bool success = true;
							SaveItemMoreTimes(6286, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the box!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 6288)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								if (j["instorage"] > 0)
								{
									tanga = true;
									Player::OnTextOverlay(peer, "Empty the box first!");
									return;
								}
								remove(("storageboxlvl2/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
							bool success = true;
							SaveItemMoreTimes(6288, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the box!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 6290)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								if (j["instorage"] > 0)
								{
									tanga = true;
									Player::OnTextOverlay(peer, "Empty the box first!");
									return;
								}
								remove(("storageboxlvl3/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
							bool success = true;
							SaveItemMoreTimes(6290, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the box!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 656)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								int count = j["inmail"];
								if (j["inmail"] > 0)
								{
									Player::OnTextOverlay(peer, "`wThere are `5" + to_string(count) + " `wletter(s) in the mailbox.");
								}
								remove(("mailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the mailbox!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 658)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								remove(("bulletinboard/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the bulletin board!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 1006)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								int count = j["inmail"];
								if (j["inmail"] > 0)
								{
									Player::OnTextOverlay(peer, "`wThere are `5" + to_string(count) + " `wletter(s) in the mailbox.");
								}
								remove(("bluemailbox/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the mailbox!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 8878)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								if (j["insafe"] > 0)
								{
									tanga = true;
									Player::OnTextOverlay(peer, "Empty the safe first!");
									return;
								}
								remove(("safevault/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
							bool success = true;
							SaveItemMoreTimes(8878, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the safe fault!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 1240)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("heartmonitor/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".txt");
							if (isdbox)
							{
								remove(("heartmonitor/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".txt").c_str());
							}
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the heart monitor!");
							return;
						}
					}
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::GATEWAY)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("gateway/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".txt");
							if (isdbox)
							{
								remove(("gateway/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".txt").c_str());
							}
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break the heart monitor!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 1452)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto squaresign = x + (y * 100);
							auto isdbox = std::experimental::filesystem::exists("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
							if (isdbox)
							{
								ifstream ifff("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json");
								json j;
								ifff >> j;
								ifff.close();
								if (j["donated"] > 0)
								{
									Player::OnTextOverlay(peer, "Empty donation box first!");
									return;
								}
								remove(("donationboxes/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "/X" + std::to_string(squaresign) + ".json").c_str());
							}
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break donation box!");
							return;
						}
					}
					if (world->items[x + (y * world->width)].foreground == 1436)
					{
						if (isWorldOwner(peer, world) || world->owner == "")
						{
							remove(("securitycam/logs/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + ".txt").c_str());
							bool success = true;
							SaveItemMoreTimes(1436, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						}
						else
						{
							Player::OnTextOverlay(peer, "only world owner can break security camera!");
							return;
						}
					}
					if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::DOOR)
					{
						if (isWorldOwner(peer, world) || world->owner == "" || isMod(peer))
						{
							auto squaresign = x + (y * 100);
							remove(("door/currid/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + to_string(squaresign) + ".txt").c_str());
							remove(("door/destid/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + to_string(squaresign) + ".txt").c_str());
							remove(("door/destworld/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + to_string(squaresign) + ".txt").c_str());
							remove(("door/label/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + to_string(squaresign) + ".txt").c_str());
							remove(("door/password/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + to_string(squaresign) + ".txt").c_str());
						}
					}
					int valgem;
					if (world->items[x + (y * world->width)].foreground == 5172) /*darkstone*/
					{
						if (static_cast<PlayerInfo*>(peer->data)->cloth_hand != 5480 || static_cast<PlayerInfo*>(peer->data)->cloth_hand != 7558) {
							srand(GetTickCount());
							int droploc = rand() % 18;
							int droplocs = rand() % 18;
							int itemid = rand() % 10490;
							if (getItemDef(itemid).name.find("null_item") != string::npos) {
								itemid = 2;
							}
							if (getItemDef(itemid).name.find("Subscription") != string::npos) {
								itemid = 2;
							}
							if (getItemDef(itemid).properties == Property_Untradable) {
								itemid = 2;
							}
							string name = getItemDef(itemid).name;
							if (itemid % 2 == 0)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "The power of the mystery dropped " + name + "!", 0, true);
								DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, itemid, 1, 0);
								int x1 = data.punchX * 32;
								int y1 = data.punchY * 32;
								ENetPeer* peer2;
								for (peer2 = server->peers;
									peer2 < &server->peers[server->peerCount];
									++peer2)
								{
									if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
									if (isHere(peer, peer2))
									{
										Player::OnParticleEffect(peer2, 182, x1, y1, 0);
									}
								}
							}
							else
							{
								itemid += 1;
								string name321 = getItemDef(itemid).name;
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "The power of the mystery dropped " + name321 + "!", 0, true);
								DropItem(peer, -1, x * 32 + droploc, y * 32 + droplocs, itemid, 1, 0);
								int hi1 = data.punchX * 32;
								int hi3 = data.punchY * 32;
								ENetPeer* peer2;
								for (peer2 = server->peers;
									peer2 < &server->peers[server->peerCount];
									++peer2)
								{
									if (peer2->state != ENET_PEER_STATE_CONNECTED) continue;
									if (isHere(peer, peer2))
									{
										Player::OnParticleEffect(peer2, 182, hi1, hi3, 0);
									}
								}
							}
						}
					}
					
					else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::LOCK && world->items[x + (y * world->width)].foreground != 4994 && world->items[x + (y * world->width)].foreground != 202 && world->items[x + (y * world->width)].foreground != 204 && world->items[x + (y * world->width)].foreground != 206)
					{
						for (auto i = 0; i < world->width * world->height; i++)
						{
							if (world->items[i].foreground == 1790)
							{
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "`oTake all `cUntradeable `oBlocks, before breaking The `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`o!", 0, true);
								return;
							}
						}
						if (static_cast<PlayerInfo*>(peer->data)->NickPrefix == "") updateworldremove(peer);
						auto success = true;
						auto info = getPlyersWorld(peer);
						auto nameworld = info->name;
						SaveItemMoreTimes(info->items[x + (y * info->width)].foreground, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
						ENetPeer* net_peer;
						for (net_peer = server->peers;
							net_peer < &server->peers[server->peerCount];
							++net_peer)
						{
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer))
							{
								Player::OnConsoleMessage(net_peer, "`5[`w" + nameworld + " `ohas had its `$" + getItemDef(info->items[x + (y * info->width)].foreground).name + " `oremoved!`5]");
								Player::PlayAudio(net_peer, "audio/fireball.wav", 0);
							}
						}
						if (info->owner != static_cast<PlayerInfo*>(peer->data)->rawName)
						{
							ofstream removelocklogs("logs/removelock.txt", ios::app);
							removelocklogs << "User " << static_cast<PlayerInfo*>(peer->data)->rawName << " removed lock from " << nameworld << " world. This world was locked by " << info->owner << endl;
							removelocklogs.close();
						}
						info->owner = "";
						info->ownerID = 0;
						info->isPublic = false;
						info->ownerDisplayName = "";
						info->accessed.clear();
						info->silence = false;
						info->items[x + (y * info->width)].foreground = 0;
						((PlayerInfo*)(peer->data))->worldsowned.erase(std::remove(((PlayerInfo*)(peer->data))->worldsowned.begin(), ((PlayerInfo*)(peer->data))->worldsowned.end(), nameworld), ((PlayerInfo*)(peer->data))->worldsowned.end());
					}
					else if (world->items[x + (y * world->width)].foreground == 9488)
					{
						auto success = true;
						SaveItemMoreTimes(9488, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 6016)
					{
						auto success = true;
						SaveItemMoreTimes(6016, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 9432)
					{
						auto success = true;
						SaveItemMoreTimes(9432, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 9170)
					{
						auto success = true;
						SaveItemMoreTimes(9170, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 1008)
					{
						auto success = true;
						SaveItemMoreTimes(1008, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 1790)
					{
						auto success = true;
						SaveItemMoreTimes(1790, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
					}
					else if (world->items[x + (y * world->width)].foreground == 2946)
					{
						if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer) || isWorldAdmin(peer, world))
						{
							auto targetworld = getPlyersWorld(peer);
							if (targetworld->items[x + (y * targetworld->width)].intdata != 0)
							{
								auto success = true;
								SaveItemMoreTimes(targetworld->items[x + (y * targetworld->width)].intdata, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
								Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "You picked up 1 " + getItemDef(targetworld->items[x + (y * targetworld->width)].intdata).name + ".", 0, true);
								targetworld->items[x + (y * targetworld->width)].intdata = 0;
								ngentot(peer);
							}
						}
						else
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Only the block's owner can break it!", 0, true);
							return;
						}
					}
					else if (getItemDef(world->items[x + (y * world->width)].foreground).blockType == BlockTypes::SUCKER)
					{
						if (static_cast<PlayerInfo*>(peer->data)->rawName == world->owner || world->owner == "" || isMod(peer))
						{
							auto squaresign = x + (y * 100);
							string Sucker = "";
							if (world->items[x + (y * world->width)].foreground == 5638)
							{
								Sucker = "magplant";
							}
							if (world->items[x + (y * world->width)].foreground == 6946)
							{
								Sucker = "gaiabeacon";
							}
							if (world->items[x + (y * world->width)].foreground == 6948)
							{
								Sucker = "unstabletesseract";
							}
							auto currentworld = static_cast<PlayerInfo*>(peer->data)->currentWorld + "X" + std::to_string(squaresign);
							auto existmagplant = std::experimental::filesystem::exists(Sucker + "/storeditem/" + currentworld + ".txt");
							if (existmagplant)
							{
								auto existmagplantcount = std::experimental::filesystem::exists(Sucker + "/count/" + currentworld + ".txt");
								if (existmagplantcount)
								{
									auto count = 0;
									ifstream fdss(Sucker + "/count/" + currentworld + ".txt");
									fdss >> count;
									fdss.close();
									if (count == 0)
									{
										remove((Sucker + "/storeditem/" + currentworld + ".txt").c_str());
										remove((Sucker + "/count/" + currentworld + ".txt").c_str());
										auto success = true;
										SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
									}
									else
									{
										tanga = true;
										Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Empty the " + getItemDef(world->items[x + (y * world->width)].foreground).name + " before breaking it!", 0, true);
										return;
									}
								}
							}
							else
							{
								auto success = true;
								SaveItemMoreTimes(world->items[x + (y * world->width)].foreground, 1, peer, success, static_cast<PlayerInfo*>(peer->data)->rawName + " from break " + getItemDef(world->items[x + (y * world->width)].foreground).name + "");
							}
						}
						else
						{
							Player::OnTalkBubble(peer, static_cast<PlayerInfo*>(peer->data)->netID, "Only the block's owner can break it!", 0, true);
							return;
						}
					}
					else if (getItemDef(world->items[x + (y * world->width)].foreground).rarity != 999)
					{
						if (getItemDef(world->items[x + (y * world->width)].foreground).properties & Property_Dropless) return;
						SendTileData(peer, x, y, data.punchX, data.punchY);
					}
					if (static_cast<PlayerInfo*>(peer->data)->rawName != world->owner && isMod(peer) && world->owner != "") /*Log moderator actions into security camera*/
					{
						auto islegitnow = false;
						for (auto i = 0; i < world->width * world->height; i++)
						{
							if (world->items[i].foreground == 1436)
							{
								islegitnow = true;
								break;
							}
						}
						if (islegitnow == true)
						{
							string toLogs = "";
							toLogs = static_cast<PlayerInfo*>(peer->data)->displayName + " `w(" + static_cast<PlayerInfo*>(peer->data)->rawName + "`w) `5Break `2" + getItemDef(world->items[x + (y * world->width)].foreground).name + "`5.";
							ofstream breaklogs("securitycam/logs/" + static_cast<PlayerInfo*>(peer->data)->currentWorld + ".txt", ios::app);
							breaklogs << toLogs << endl;
							breaklogs.close();
						}
					}
					if (static_cast<PlayerInfo*>(peer->data)->cloth_hand == 7912)
					{
						if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 9460 || world->items[x + (y * world->width)].foreground == 9468 || world->items[x + (y * world->width)].foreground == 9462 || world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308)
						{
							world->items[x + (y * world->width)].foreground = 0;
						}
						else
						{
							if (world->items[x + (y * world->width)].foreground == 2)
							{
								world->items[x + (y * world->width)].foreground = 0;
								srand(GetTickCount());
								valgem = rand() % 10;
								SendXP(peer, 1);
								AddPlayerFragmentEarth(peer, valgem);
							}
							else
							{
								world->items[x + (y * world->width)].foreground = 0;
								SendXP(peer, 1);
							}
						}
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_ances == 7166)
					{
						if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 9460 || world->items[x + (y * world->width)].foreground == 9468 || world->items[x + (y * world->width)].foreground == 9462 || world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308)
						{
							world->items[x + (y * world->width)].foreground = 0;
						}
						else
						{
							if (world->items[x + (y * world->width)].foreground == 2)
							{
								world->items[x + (y * world->width)].foreground = 0;
								srand(GetTickCount());
								valgem = rand() % 10;
								SendXP(peer, 1);
								AddPlayerFragmentEarth(peer, valgem);
							}
							else
							{
								world->items[x + (y * world->width)].foreground = 0;
								SendXP(peer, 1);
							}
						}
					}
					else if (static_cast<PlayerInfo*>(peer->data)->cloth_feet == 8834)
					{
						if (world->items[x + (y * world->width)].foreground == 7382 || world->items[x + (y * world->width)].foreground == 4762 || world->items[x + (y * world->width)].foreground == 9240 || world->items[x + (y * world->width)].foreground == 9460 || world->items[x + (y * world->width)].foreground == 9468 || world->items[x + (y * world->width)].foreground == 9462 || world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308)
						{
							world->items[x + (y * world->width)].foreground = 0;
						}
						else
						{
							if (world->items[x + (y * world->width)].foreground == 2)
							{
								world->items[x + (y * world->width)].foreground = 0;
								srand(GetTickCount());
								valgem = rand() % 10;
								SendXP(peer, 1);
								AddPlayerFragmentEarth(peer, valgem);
							}
							else
							{
								world->items[x + (y * world->width)].foreground = 0;
								SendXP(peer, 1);
							}
						}
					}
					else
					{
						if (world->items[x + (y * world->width)].foreground == 2)
						{
							world->items[x + (y * world->width)].foreground = 0;
							srand(GetTickCount());
							SendXP(peer, 1);
							valgem = rand() % 10;
							AddPlayerFragmentEarth(peer, valgem);
						}
						else
						{
							valgem = rand() % 5;
							world->items[x + (y * world->width)].foreground = 0;
						}
					}
#pragma region crystals
					if (world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308)
					{
						world->items[x + (y * world->width)].foreground = 0;
					}
#pragma endregion
					if (static_cast<PlayerInfo*>(peer->data)->xp >= (static_cast<PlayerInfo*>(peer->data)->level * 1500) && static_cast<PlayerInfo*>(peer->data)->level < 125)
					{
						static_cast<PlayerInfo*>(peer->data)->xp = 0;
						static_cast<PlayerInfo*>(peer->data)->level = static_cast<PlayerInfo*>(peer->data)->level + 1;
						ENetPeer* net_peer;
						for (net_peer = server->peers;
							net_peer < &server->peers[server->peerCount];
							++net_peer)
						{
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer))
							{
								auto name = static_cast<PlayerInfo*>(peer->data)->displayName;
								auto p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), name + " `wis now level " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "!"));
								string text = "action|play_sfx\nfile|audio/levelup2.wav\ndelayMS|0\n";
								auto dst = new BYTE[5 + text.length()];
								BYTE zero = 0;
								auto type = 3;
								memcpy(dst, &type, 4);
								memcpy(dst + 4, text.c_str(), text.length());
								memcpy(dst + 4 + text.length(), &zero, 1);
								auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet);
								auto packet2 = enet_packet_create(dst, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet2);
								delete dst;
								delete p.data;
								auto p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), name + " `wis now level " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "!"));
								auto packet3 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet3);
							}
						}
						ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
						json j;
						fg >> j;
						fg.close();

						j["level"] = static_cast<PlayerInfo*>(peer->data)->level;
						j["xp"] = static_cast<PlayerInfo*>(peer->data)->xp;

						ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
						fs << j;
						fs.close();
					}
				}
				else
				{
					if (getItemDef(world->items[x + (y * world->width)].background).rarity != 999 && tile == 18)
					{
						if (getItemDef(world->items[x + (y * world->width)].background).properties & Property_Dropless) return;
						SendTileData(peer, x, y, data.punchX, data.punchY);
					}
					SendDropSeed(peer, x, y, world->items[x + (y * world->width)].background);
					
					world->items[x + (y * world->width)].background = 6864;
					if (world->items[x + (y * world->width)].foreground == 1008 || world->items[x + (y * world->width)].foreground == 1796 || world->items[x + (y * world->width)].foreground == 242 || world->items[x + (y * world->width)].foreground == 9290 || world->items[x + (y * world->width)].foreground == 8470 || world->items[x + (y * world->width)].foreground == 8 || world->items[x + (y * world->width)].foreground == 9308)
					{
						world->items[x + (y * world->width)].foreground = 0;
					}
					if (static_cast<PlayerInfo*>(peer->data)->xp >= (static_cast<PlayerInfo*>(peer->data)->level * 1500) && static_cast<PlayerInfo*>(peer->data)->level < 125)
					{
						static_cast<PlayerInfo*>(peer->data)->xp = 0;
						static_cast<PlayerInfo*>(peer->data)->level = static_cast<PlayerInfo*>(peer->data)->level + 1;
						ENetPeer* net_peer;
						for (net_peer = server->peers;
							net_peer < &server->peers[server->peerCount];
							++net_peer)
						{
							if (net_peer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, net_peer))
							{
								auto name = static_cast<PlayerInfo*>(peer->data)->displayName;
								auto p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), name + " `wis now level " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "!"));
								string text = "action|play_sfx\nfile|audio/levelup2.wav\ndelayMS|0\n";
								auto dst = new BYTE[5 + text.length()];
								BYTE zero = 0;
								auto type = 3;
								memcpy(dst, &type, 4);
								memcpy(dst + 4, text.c_str(), text.length());
								memcpy(dst + 4 + text.length(), &zero, 1);
								auto packet = enet_packet_create(p.data, p.len, ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet);
								auto packet2 = enet_packet_create(dst, 5 + text.length(), ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet2);
								delete dst;
								delete p.data;
								auto p3 = packetEnd(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), static_cast<PlayerInfo*>(peer->data)->netID), name + " `wis now level " + std::to_string(static_cast<PlayerInfo*>(peer->data)->level) + "!"));
								auto packet3 = enet_packet_create(p3.data, p3.len, ENET_PACKET_FLAG_RELIABLE);
								enet_peer_send(net_peer, 0, packet3);
							}
							data.plantingTree = tile;
						}
						ifstream fg("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
						json j;
						fg >> j;
						fg.close();

						j["level"] = static_cast<PlayerInfo*>(peer->data)->level;
						j["xp"] = static_cast<PlayerInfo*>(peer->data)->xp;

						ofstream fs("players/" + static_cast<PlayerInfo*>(peer->data)->rawName + ".json");
						fs << j;
						fs.close();
					}
				}
			}
			else
			{
			if (y < world->height)
			{
				world->items[x + (y * world->width)].breakTime = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				world->items[x + (y * world->width)].breakLevel += 4;
			}
			}
	}
	else
	{
		if (world->items[x + (y * world->width)].foreground != 0 && getItemDef(tile).blockType != BlockTypes::BACKGROUND && getItemDef(tile).blockType != BlockTypes::GROUND_BLOCK) return;
		for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount];
			++currentPeer)
		{
			if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
			if (isHere(peer, currentPeer))
			{
				bool RotatedRight = false;
				auto xpos = x * 32;
				auto ppos = static_cast<PlayerInfo*>(currentPeer->data)->x;
				if (static_cast<PlayerInfo*>(currentPeer->data)->x < x * 32) RotatedRight = true;
				if (RotatedRight) ppos += 19;
				xpos = xpos / 32;
				ppos = ppos / 32;
				if (ppos == xpos && static_cast<PlayerInfo*>(currentPeer->data)->y / 32 == y && getItemDef(tile).properties != Property_NoSeed && getItemDef(tile).properties != Property_Foreground && getItemDef(tile).properties != Property_MultiFacing && getItemDef(tile).blockType != BlockTypes::SEED && getItemDef(tile).blockType != BlockTypes::STEAM && getItemDef(tile).blockType != BlockTypes::UNKNOWN && getItemDef(tile).blockType != BlockTypes::VENDING && getItemDef(tile).blockType != BlockTypes::ANIM_FOREGROUND && getItemDef(tile).blockType != BlockTypes::BULLETIN_BOARD && getItemDef(tile).blockType != BlockTypes::FACTION && getItemDef(tile).blockType != BlockTypes::CHEST && getItemDef(tile).blockType != BlockTypes::GEMS && getItemDef(tile).blockType != BlockTypes::MAGIC_EGG && getItemDef(tile).blockType != BlockTypes::CRYSTAL && getItemDef(tile).blockType != BlockTypes::MAILBOX && getItemDef(tile).blockType != BlockTypes::PORTAL && getItemDef(tile).blockType != BlockTypes::PLATFORM && getItemDef(tile).blockType != BlockTypes::SFX_FOREGROUND && getItemDef(tile).blockType != BlockTypes::CHEMICAL_COMBINER && getItemDef(tile).blockType != BlockTypes::SWITCH_BLOCK && getItemDef(tile).blockType != BlockTypes::TRAMPOLINE && getItemDef(tile).blockType != BlockTypes::TOGGLE_FOREGROUND && getItemDef(tile).blockType != BlockTypes::GROUND_BLOCK && getItemDef(tile).blockType != BlockTypes::BACKGROUND && getItemDef(tile).blockType != BlockTypes::MAIN_DOOR && getItemDef(tile).blockType != BlockTypes::SIGN && getItemDef(tile).blockType != BlockTypes::DOOR && getItemDef(tile).blockType != BlockTypes::CHECKPOINT && getItemDef(tile).blockType != BlockTypes::GATEWAY && getItemDef(tile).blockType != BlockTypes::TREASURE && getItemDef(tile).blockType != BlockTypes::WEATHER) return;
			}
		}
		if (causedBy != -1)
		{
			auto iscontains = false;
			SearchInventoryItem(peer, tile, 1, iscontains);
			if (!iscontains) return;
		}
		for (auto i = 0; i < static_cast<PlayerInfo*>(peer->data)->inventory.items.size(); i++)
		{
			if (static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemID == tile)
			{
				if (static_cast<unsigned int>(static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount) > 1)
				{
					static_cast<PlayerInfo*>(peer->data)->inventory.items.at(i).itemCount--;
					static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
				}
				else
				{
					static_cast<PlayerInfo*>(peer->data)->inventory.items.erase(static_cast<PlayerInfo*>(peer->data)->inventory.items.begin() + i);
					static_cast<PlayerInfo*>(peer->data)->needsaveinventory = true;
				}
			}
		}
		if (tile != 18 && tile != 32 && getItemDef(tile).blockType != BlockTypes::CONSUMABLE)
		{
			bool Farmable = false;
			if (tile == 5136 || tile == 5138 || tile == 5140 || tile == 5156 || tile == 5158) Farmable = true;
			if (static_cast<PlayerInfo*>(peer->data)->PlacePotion && Farmable)
			{
				SendPlacingEffect(peer, data.punchX, data.punchY, 229);
			}
			else if (static_cast<PlayerInfo*>(peer->data)->cloth_back == 9466)
			{
				SendPlacingEffect(peer, data.punchX, data.punchY, 125);
			}
		}
		if (getItemDef(tile).blockType == BlockTypes::BACKGROUND || getItemDef(tile).blockType == BlockTypes::GROUND_BLOCK)
		{
			world->items[x + (y * world->width)].background = tile;
		}
		else if (getItemDef(tile).blockType == BlockTypes::SEED)
		{
			world->items[x + (y * world->width)].foreground = tile;
		}
		else
		{
			world->items[x + (y * world->width)].foreground = tile;
		}
		if (world->areLogsEnabled == true)
		{
			ofstream savelogs("worldlogs/" + world->name + ".txt", std::ios_base::app);
			savelogs << static_cast<PlayerInfo*>(peer->data)->rawName << " placed " << getItemDef(tile).name << "(" << tile << ")" << endl;
		}
		if (getItemDef(tile).blockType == BlockTypes::LOCK)
		{
			if (tile == 202 || tile == 204 || tile == 206 || tile == 4994)
			{
				//cout << "lock packet send" << endl;				
			}
			else
			{
				world->owner = static_cast<PlayerInfo*>(peer->data)->rawName;
				world->ownerDisplayName = static_cast<PlayerInfo*>(peer->data)->displayName;
				world->ownerID = static_cast<PlayerInfo*>(peer->data)->userID;
				world->isPublic = false;
				if (static_cast<PlayerInfo*>(peer->data)->haveGrowId)
				{
					if (static_cast<PlayerInfo*>(peer->data)->isNicked == false && !isMod(peer))
					{
						static_cast<PlayerInfo*>(peer->data)->displayName = "`2" + static_cast<PlayerInfo*>(peer->data)->displayName;
						auto p7 = packetEnd(appendString(appendString(createPacket(), "OnNameChanged"), "`2" + static_cast<PlayerInfo*>(peer->data)->displayName));
						memcpy(p7.data + 8, &(static_cast<PlayerInfo*>(peer->data)->netID), 4);
						auto packet7 = enet_packet_create(p7.data, p7.len, ENET_PACKET_FLAG_RELIABLE);
						delete p7.data;
						for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
						{
							if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
							if (isHere(peer, currentPeer))
							{
								if (static_cast<PlayerInfo*>(peer->data)->adminLevel >= 0)
								{
									enet_peer_send(currentPeer, 0, packet7);
								}
							}
						}
					}
				}
				for (currentPeer = server->peers;
					currentPeer < &server->peers[server->peerCount];
					++currentPeer)
				{
					if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
					if (isHere(peer, currentPeer))
					{
						((PlayerInfo*)(peer->data))->worldsowned.push_back(world->name);
						std::ifstream ifff("players/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
						if (ifff.fail()) {
							ifff.close();
						}
						if (ifff.is_open()) {
						}
						json j;
						ifff >> j;
						j["worldsowned"] = ((PlayerInfo*)(peer->data))->worldsowned;
						std::ofstream o("players/" + ((PlayerInfo*)(peer->data))->rawName + ".json"); //save
						if (!o.is_open()) {
							cout << GetLastError() << endl;
						}
						o << j << std::endl;
						Player::OnConsoleMessage(currentPeer, "`3[`w" + world->name + " `ohas been `$" + getItemDef(world->items[x + (y * world->width)].foreground).name + "ed `oBy `w" + static_cast<PlayerInfo*>(peer->data)->rawName + "`3]");
						Player::PlayAudio(currentPeer, "audio/use_lock.wav", 0);
					}
				}
				isLock = true;
			}
		}
		world->items[x + (y * world->width)].breakLevel = 0;
	}
	for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer))
		{
			auto raw = packPlayerMoving(&data);
			raw[2] = dicenr;
			raw[3] = dicenr;
			SendPacketRaw(4, raw, 56, nullptr, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
	
	if (getItemDef(tile).properties & Property_MultiFacing)
	{
		if (static_cast<PlayerInfo*>(peer->data)->isRotatedLeft)
		{
			world->items[x + (y * world->width)].flipped = true;
			UpdateBlockState(peer, x, y, true, world);
		}
	}
	if (isLock)
	{
		sendTileData(peer, x, y, 0x10, world->items[x + (y * world->width)].foreground, world->items[x + (y * world->width)].background, lockTileDatas(0x20, ((PlayerInfo*)(peer->data))->netID, 0, 0, false, 100));
	}
	if (isTree)
	{
		auto numb = (rand() % 4) + 1;
		UpdateTreeVisuals(peer, world->items[x + (y * world->width)].foreground, x, y, world->items[x + (y * world->width)].background, numb, 8006000, true, 0);
	}
	if (isHeartMonitor)
	{
		sendHMonitor(peer, x, y, static_cast<PlayerInfo*>(peer->data)->rawName, true);
	}
	if (isgateway)
	{
		updateEntrance(peer, world->items[x + (y * world->width)].foreground, x, y, 0, world->items[x + (y * world->width)].background, true);
	}
}
