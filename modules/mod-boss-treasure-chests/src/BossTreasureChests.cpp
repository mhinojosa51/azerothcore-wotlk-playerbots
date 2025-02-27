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

        void OnPlayerCreatureKill(Player* player, Creature* boss) override
        {
            if (ShouldSkipDungeonOrRaidMap(boss->GetMapId()))
            {
                return;
            }

            if (boss->IsDungeonBoss())
            {
                uint8 playerRoundedLevel = std::ceil(player->GetLevel() / 5.0) * 5;
                switch (playerRoundedLevel)
                {
                    case 15:
                        AddTreasureChestToGameOnDungeonBossKill(player, boss, CHEST_OF_THE_CONQUEROR_20, 300);
                        break;

                    case 20:
                        AddTreasureChestToGameOnDungeonBossKill(player, boss, CHEST_OF_THE_CONQUEROR_20, 300);
                        break;

                    case 25:
                        AddTreasureChestToGameOnDungeonBossKill(player, boss, CHEST_OF_THE_CONQUEROR_25, 300);
                        break;

                    case 30:
                        AddTreasureChestToGameOnDungeonBossKill(player, boss, CHEST_OF_THE_CONQUEROR_30, 300);
                        break;

                    case 35:
                        AddTreasureChestToGameOnDungeonBossKill(player, boss, CHEST_OF_THE_CONQUEROR_35, 300);
                        break;

                    case 40:
                        AddTreasureChestToGameOnDungeonBossKill(player, boss, CHEST_OF_THE_CONQUEROR_40, 300);
                        break;

                    case 45:
                        AddTreasureChestToGameOnDungeonBossKill(player, boss, CHEST_OF_THE_CONQUEROR_45, 300);
                        break;

                    case 50:
                        AddTreasureChestToGameOnDungeonBossKill(player, boss, CHEST_OF_THE_CONQUEROR_50, 300);
                        break;

                    case 55:
                        AddTreasureChestToGameOnDungeonBossKill(player, boss, CHEST_OF_THE_CONQUEROR_55, 300);
                        break;

                    case 60:
                        AddTreasureChestToGameOnDungeonBossKill(player, boss, CHEST_OF_THE_CONQUEROR_60, 300);
                        break;
                }
            }
        }

        bool AddTreasureChestToGameOnDungeonBossKill(Player* player, Creature* boss, uint32 objectId, Optional<uint64> spawntime)
        {
            uint64 spawntm(spawntime.value_or(300));

            if (!sObjectMgr->GetGameObjectTemplate(objectId))
            {
                return false;
            }
            Position bossHomePosition = boss->GetHomePosition();

            float x = float(bossHomePosition.GetPositionX());
            float y = float(bossHomePosition.GetPositionY());
            float z = float(bossHomePosition.GetPositionZ());
            float ang = float(bossHomePosition.GetOrientation());

            AddTempTreaureChestToGame(player, objectId, x, y, z, ang, 300);

            return true;
        }

    private:
        enum ChestIDs
        {
            CHEST_OF_THE_CONQUEROR_20 = 500020,
            CHEST_OF_THE_CONQUEROR_25 = 500025,
            CHEST_OF_THE_CONQUEROR_30 = 500030,
            CHEST_OF_THE_CONQUEROR_35 = 500035,
            CHEST_OF_THE_CONQUEROR_40 = 500040,
            CHEST_OF_THE_CONQUEROR_45 = 500045,
            CHEST_OF_THE_CONQUEROR_50 = 500050,
            CHEST_OF_THE_CONQUEROR_55 = 500055,
            CHEST_OF_THE_CONQUEROR_60 = 500060,
        };

        enum MapIDs
        {
            ONYXIAS_LAIR = 249,
            MOLTEN_CORE = 409,
            BLACK_WING_LAIR = 469,
            AHN_QIRAJ_RUINS = 509,
            AHN_QIRAJ_TEMPLE = 531,
            KARAZHAN = 532,
            NAXXRAMAS = 533,
            HYJAL_SUMMIT = 534,
        };

        enum AreaIDs
        {
            FARGODEEP_MINE = 57,
        };

        uint32 excludedMapIds[8] = { 249,409,469,509,531,532,533,534 };

        bool ShouldSkipDungeonOrRaidMap(uint32 mapId)
        {
            if (std::find(std::begin(excludedMapIds), std::end(excludedMapIds), mapId) != std::end(excludedMapIds))
            {
                return true;
            }
            return false;
        }

        void AddTempTreaureChestToGame(Player* player, uint32 treasureChestObjectId, float posX, float posY, float posZ, float orientation, Optional<uint64> spawntime)
        {
            uint64 spawntm(spawntime.value_or(300));

            if (!sObjectMgr->GetGameObjectTemplate(treasureChestObjectId))
            {
                return;
            }

            float rot2 = std::sin(orientation / 2);
            float rot3 = cos(orientation / 2);

            player->SummonGameObject(treasureChestObjectId, posX, posY, posZ, orientation, 0, 0, rot2, rot3, spawntm);
        }
};

void AddBossTreasureChestScripts()
{
    new boss_treasure_chests();
}
