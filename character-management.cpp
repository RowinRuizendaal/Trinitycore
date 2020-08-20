#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "WorldSession.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Random.h"
#include "DatabaseEnv.h"
#include <iostream>
#include "Chat.h"

#define A_THOUSAND_GOLD 10000000



class character_management_npc : public CreatureScript
{
public:
	character_management_npc() : CreatureScript("character_management_npc") { }

	struct test_npc_AI : public ScriptedAI
	{
		test_npc_AI(Creature* creature) : ScriptedAI(creature) { }

		bool GossipHello(Player* player) override
		{
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to change my race", GOSSIP_SENDER_MAIN, 0, "Are you sure you want to buy the race change feature for 1000 gold?", 0, false);
			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to change my faction", GOSSIP_SENDER_MAIN, 1, "Are you sure you want to buy the faction change for 1000 gold?", 0, false);
			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to customize my character", GOSSIP_SENDER_MAIN, 2, "Are you sure you want to customize your character for 1000 gold?", 0, false);
			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I would like to rename my character", GOSSIP_SENDER_MAIN, 3, "Are you sure you want to rename your character for 1000 gold?", 0, false);
			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Log me out (Instantly)", GOSSIP_SENDER_MAIN, 4, "Are you sure you want to logout?", 0, false);
			SendGossipMenuFor(player, 907, me->GetGUID());
			return true;

		}

		bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
		{
			uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
			switch (action)
			{

			case 0:
            {
                if (player->GetMoney()< A_THOUSAND_GOLD) {
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00You don't have enough gold to buy the race change feature.";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    CloseGossipMenuFor(player);
                    return false;
                }
                else {
                    player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00Relog to change your race";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    player->ModifyMoney(-A_THOUSAND_GOLD);
                    CloseGossipMenuFor(player);
                    return true;
                }
            }

            case 1:
            {
                if (player->GetMoney()< A_THOUSAND_GOLD) {
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00You don't have enough gold to buy the faction change feature.";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    CloseGossipMenuFor(player);
                    return false;
                }
                else {
                    player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00Relog to change your faction";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    player->ModifyMoney(-A_THOUSAND_GOLD);
                    CloseGossipMenuFor(player);
                    return true;
                }
            }

            case 2:
            {
                if (player->GetMoney()< A_THOUSAND_GOLD) {
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00You don't have enough gold to buy the customization feature.";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    CloseGossipMenuFor(player);
                    return false;
                }
                else {
                    player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00Relog to customize your character";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    player->ModifyMoney(-A_THOUSAND_GOLD);
                    CloseGossipMenuFor(player);
                    return true;
                }
            }

            case 3:
            {
                if (player->GetMoney()< A_THOUSAND_GOLD) {
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00You don't have enough gold to buy the rename feature.";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    CloseGossipMenuFor(player);
                    return false;
                }
                else {
                    player->SetAtLoginFlag(AT_LOGIN_RENAME);
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00Relog to change your name";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    player->ModifyMoney(-A_THOUSAND_GOLD);
                    CloseGossipMenuFor(player);
                    return true;
                }
            }

            case 4:
            {
                if (player->IsInCombat()) {
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00You cant use this feature while you are in combat";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    CloseGossipMenuFor(player);
                    return false;
                }
                else {
                    player->GetSession()->LogoutPlayer(1);
                    CloseGossipMenuFor(player);
                    return true;
                }
            }

			}
			return true;
		}
	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new test_npc_AI(creature);
	}

};

void AddSC_character_management_npc()
{
	new character_management_npc();
}