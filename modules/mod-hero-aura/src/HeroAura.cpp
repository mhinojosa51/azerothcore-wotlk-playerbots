/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "ObjectMgr.h"
#include "Log.h"

// Add player script
class hero_aura : PlayerScript
{
    public:
        hero_aura() : PlayerScript("hero_aura")
        {
            killCount = 0;
        }

        void OnPlayerCreatureKill(Player* player, Creature* creature) override
        {
            if (player->HasAura(heroAuraSpellId))
            {
                killCount++;
                LOG_INFO("module", "Hero has killed [{}] creatures!", killCount);
            }
        }

    private:
        uint32 killCount;
        uint32 heroAuraSpellId = 200046;
};

void AddHeroAuraScripts()
{
    new hero_aura();
}
