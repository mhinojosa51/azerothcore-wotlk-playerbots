/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "Log.h"

// Add player script
class boss_treasure_chests : PlayerScript
{
    public:
        boss_treasure_chests() : PlayerScript("boss_treasure_chests") { }

        void OnCreatureKill(Player* player, Creature* boss) override
        {
            
        }    
};

void AddBossTreasureChestScripts()
{
    new boss_treasure_chests();
}
