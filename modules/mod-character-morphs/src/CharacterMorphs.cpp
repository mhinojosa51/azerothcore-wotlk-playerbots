/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "Log.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

// Add player scripts
class PlayerBotMorphs : public PlayerScript
{
public:
    PlayerBotMorphs() : PlayerScript("PlayerBotMorphs") { }

    void OnPlayerMapChanged(Player* player) override
    {
        if (sConfigMgr->GetOption<bool>("CharacterMorphs.Enable", false))
        {
     
            std::string playerName = player->GetName();

            uint32 genericMorphSpellId = sConfigMgr->GetOption<uint32>("CharacterMorphs.GenericMorphSpellId", 0);
            uint32 heroAuraSpellId = sConfigMgr->GetOption<uint32>("CharacterMorphs.HeroAuraSpellId", 0);
            uint32 shrinkAuraSpellId = sConfigMgr->GetOption<uint32>("CharacterMorphs.ShrinkAuraSpellId", 0);
            uint32 growAuraSpellId = sConfigMgr->GetOption<uint32>("CharacterMorphs.GrowAuraSpellId", 0);

            std::vector<std::string> characterNamesToApplyGenericMorphAuraTo = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.CharactersToApplyGenericMorphAuraTo", ""), ",");
            std::vector<std::string> characterNamesToApplyHeroAuraTo = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.CharacterNamesToApplyHeroAuraTo", ""), ",");
            std::vector<std::string> characterNamesToApplyShrinkAuraTo = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.CharacterNamesToApplyShrinkAuraTo", ""), ",");
            std::vector<std::string> characterNamesToApplyGrowAuraTo = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.CharacterNamesToApplyGrowAuraTo", ""), ",");

            for (const std::string& characterName : characterNamesToApplyGenericMorphAuraTo)
            {
                if (characterName == playerName)
                {
                    player->AddAura(genericMorphSpellId, player);
                }
            }

            for (const std::string& characterName : characterNamesToApplyHeroAuraTo)
            {
                if (characterName == playerName)
                {
                    player->AddAura(heroAuraSpellId, player);
                }
            }

            for (const std::string& characterName : characterNamesToApplyGrowAuraTo)
            {
                if (characterName == playerName)
                {
                    player->AddAura(growAuraSpellId, player);
                }
            }

            for (const std::string& characterName : characterNamesToApplyShrinkAuraTo)
            {
                if (characterName == playerName)
                {
                    player->AddAura(shrinkAuraSpellId, player);
                }
            }
        }
    }

    void OnPlayerResurrect(Player* player, float someFloat, bool someBool) override
    {
        if (sConfigMgr->GetOption<bool>("CharacterMorphs.Enable", false))
        {

            std::string playerName = player->GetName();

            uint32 genericMorphSpellId = sConfigMgr->GetOption<uint32>("CharacterMorphs.GenericMorphSpellId", 0);
            uint32 heroAuraSpellId = sConfigMgr->GetOption<uint32>("CharacterMorphs.HeroAuraSpellId", 0);
            uint32 shrinkAuraSpellId = sConfigMgr->GetOption<uint32>("CharacterMorphs.ShrinkAuraSpellId", 0);
            uint32 growAuraSpellId = sConfigMgr->GetOption<uint32>("CharacterMorphs.GrowAuraSpellId", 0);

            std::vector<std::string> characterNamesToApplyGenericMorphAuraTo = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.CharactersToApplyGenericMorphAuraTo", ""), ",");
            std::vector<std::string> characterNamesToApplyHeroAuraTo = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.CharacterNamesToApplyHeroAuraTo", ""), ",");
            std::vector<std::string> characterNamesToApplyShrinkAuraTo = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.CharacterNamesToApplyShrinkAuraTo", ""), ",");
            std::vector<std::string> characterNamesToApplyGrowAuraTo = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.CharacterNamesToApplyGrowAuraTo", ""), ",");

            for (const std::string& characterName : characterNamesToApplyGenericMorphAuraTo)
            {
                if (characterName == playerName)
                {
                    player->AddAura(genericMorphSpellId, player);
                }
            }

            for (const std::string& characterName : characterNamesToApplyHeroAuraTo)
            {
                if (characterName == playerName)
                {
                    player->AddAura(heroAuraSpellId, player);
                }
            }

            for (const std::string& characterName : characterNamesToApplyGrowAuraTo)
            {
                if (characterName == playerName)
                {
                    player->AddAura(growAuraSpellId, player);
                }
            }

            for (const std::string& characterName : characterNamesToApplyShrinkAuraTo)
            {
                if (characterName == playerName)
                {
                    player->AddAura(shrinkAuraSpellId, player);
                }
            }
        }
    }

private:

    uint32 sylvanasDisplayId = 28213;
    uint32 alexstrazaDisplayId = 28227;
    uint32 veeresaDisplayId = 28222;

    std::vector<std::string> parseNamesStringToVector(const std::string& str, const std::string& delim)
    {
        std::vector<std::string> namesToMorph;
        for (std::size_t last_pos = 0; last_pos < str.size(); )
        {
            std::size_t pos = str.find(delim, last_pos);
            if (pos == str.npos) pos = str.size();
            namesToMorph.push_back(str.substr(last_pos, pos - last_pos));
            last_pos = pos + delim.size();
        }
        return namesToMorph;
    }
};

// Add all scripts in one
void AddPlayerBotMorphsScripts()
{
    new PlayerBotMorphs();
}
