#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "WorldSession.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "Random.h"
#include "DatabaseEnv.h"
#include <iostream>
#include "Chat.h"


class account_npc : public CreatureScript
{
public:
	account_npc() : CreatureScript("account_npc") { }

	struct test_npc_AI : public ScriptedAI
	{
		test_npc_AI(Creature* creature) : ScriptedAI(creature) { }

		bool GossipHello(Player* player) override
		{
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "How many auctions are available?", GOSSIP_SENDER_MAIN, 0);
			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "How many characters have been made?", GOSSIP_SENDER_MAIN, 1);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "What is the highest buyout price of the auctionhouse? ", GOSSIP_SENDER_MAIN, 2);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "What is the highest 2s rating? ", GOSSIP_SENDER_MAIN, 3);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "What is the highest 3s rating? ", GOSSIP_SENDER_MAIN, 4);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "How many players are online? ", GOSSIP_SENDER_MAIN, 5);
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

                QueryResult result = CharacterDatabase.PQuery("Select count(*) from auctionhouse"); // do the query
                if (result) // check if query returned a result
                {
                    int32 x = result->Fetch()[0].GetInt32(); // Get the first row's first column's value.
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00There are in total " << x << " auction(s) available";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    CloseGossipMenuFor(player);
                    return true;
                }
            }
			case 1:
			{

                QueryResult result = CharacterDatabase.PQuery("select count(*) from characters"); // do the query
                if (result) // check if query returned a result
                {
                    int32 x = result->Fetch()[0].GetInt32(); // Get the first row's first column's value.
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00There are " << x << " character(s) made in total";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    CloseGossipMenuFor(player);
                    return true;
                    }
			}

            case 2:
            {

                QueryResult result = CharacterDatabase.PQuery("select max(buyoutprice) from auctionhouse"); // do the query
                if (result) // check if query returned a result
                {
                    int32 x = result->Fetch()[0].GetInt32(); // Get the first row's first column's value.
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00The highest buyout price is: " << x << "";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    CloseGossipMenuFor(player);
                    return true;
                }
            }

            case 3:
            {

                QueryResult result = CharacterDatabase.PQuery("Select name, max(rating) from arena_team where type = 2"); // do the query
                if (result) // check if query returned a result
                {
                    int32 y = result->Fetch()[1].GetInt32(); // Get the second row's first column's value.
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00The highest 2s rating is: " << y <<" ";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    CloseGossipMenuFor(player);
                    return true;
                }
            }

            case 4:
            {

                QueryResult result = CharacterDatabase.PQuery("Select name, max(rating) from arena_team where type = 3"); // do the query
                if (result) // check if query returned a result
                {
                    int32 y = result->Fetch()[1].GetInt32(); // Get the second row's first column's value.
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00The highest 3s rating is: " << y << " ";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
                    CloseGossipMenuFor(player);
                    return true;
                }
            }

            case 5:
            {
                QueryResult result = CharacterDatabase.PQuery("select count(*) online from characters where online = 1"); // do the query
                if (result) // check if query returned a result
                {
                    int32 y = result->Fetch()[0].GetInt32(); // Get the second row's first column's value.
                    std::stringstream ss;
                    ss << "|cffE68318[Server info]:|r |cff00ff00There are currently: " << y << " character(s) online!";
                    std::string account = ss.str();
                    player->GetSession()->SendAreaTriggerMessage(account.c_str());
                    ChatHandler(player->GetSession()).PSendSysMessage(account.c_str());
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

void AddSC_account_npc()
{
	new account_npc();
}