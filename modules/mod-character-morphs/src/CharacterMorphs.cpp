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

    void OnMapChanged(Player* player) override
    {
        if (sConfigMgr->GetOption<bool>("CharacterMorphs.Enable", false))
        {
     
            std::string playerName = player->GetName();

            std::vector<std::string> characterNamesToGrowVector = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.CharacterNamesToScaleUp", ""), ",");
            std::vector<std::string> characterNamesToUseAlexstrazaModelId = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.AlexstrazaMorphNames", ""), ",");
            std::vector<std::string> characterNamesToUseSylvanasModelId = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.SylvanasMorphNames", ""), ",");
            std::vector<std::string> characterNamesToUseVeeresaModelId = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.VeeresaMorphNames", ""), ",");
            std::vector<std::string> characterNamesToUseBEMaleModelId = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.BEMaleMorphNames", ""), ",");
            std::vector<std::string> characterNamesToUseDraeneiFemaleModelId = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.DraeneiFemaleMorphNames", ""), ",");

            // add scale aura to characters listed in config
            for (const std::string& characterName : characterNamesToGrowVector)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200017, player);
                }
            }

            // add alexstraza model id aura to characters listed in config
            for (const std::string& characterName : characterNamesToUseAlexstrazaModelId)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200019, player);
                }
            }

            // add sylvanas model id aura to characters listed in config
            for (const std::string& characterName : characterNamesToUseSylvanasModelId)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200020, player);
                }
            }

            // add veeresa model id aura to characters listed in config
            for (const std::string& characterName : characterNamesToUseVeeresaModelId)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200021, player);
                }
            }

            // add BE Male model id aura to characters listed in config
            for (const std::string& characterName : characterNamesToUseBEMaleModelId)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200022, player);
                    player->AddAura(200046, player);
                }
            }

            // add Draenei Female model id aura to characters listed in config
            for (const std::string& characterName : characterNamesToUseDraeneiFemaleModelId)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200023, player);
                }
            }
        }
    }

    void OnPlayerResurrect(Player* player, float someFloat, bool someBool) override
    {
        if (sConfigMgr->GetOption<bool>("CharacterMorphs.Enable", false))
        {

            std::string playerName = player->GetName();

            std::vector<std::string> characterNamesToGrowVector = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.CharacterNamesToScaleUp", ""), ",");
            std::vector<std::string> characterNamesToUseAlexstrazaModelId = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.AlexstrazaMorphNames", ""), ",");
            std::vector<std::string> characterNamesToUseSylvanasModelId = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.SylvanasMorphNames", ""), ",");
            std::vector<std::string> characterNamesToUseVeeresaModelId = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.VeeresaMorphNames", ""), ",");
            std::vector<std::string> characterNamesToUseBEMaleModelId = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.BEMaleMorphNames", ""), ",");
            std::vector<std::string> characterNamesToUseDraeneiFemaleModelId = parseNamesStringToVector(sConfigMgr->GetOption<std::string>("CharacterMorphs.DraeneiFemaleMorphNames", ""), ",");

            // add scale aura to characters listed in config
            for (const std::string& characterName : characterNamesToGrowVector)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200017, player);
                }
            }

            // add alexstraza model id aura to characters listed in config
            for (const std::string& characterName : characterNamesToUseAlexstrazaModelId)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200019, player);
                }
            }

            // add sylvanas model id aura to characters listed in config
            for (const std::string& characterName : characterNamesToUseSylvanasModelId)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200020, player);
                }
            }

            // add veeresa model id aura to characters listed in config
            for (const std::string& characterName : characterNamesToUseVeeresaModelId)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200021, player);
                }
            }

            // add BE Male model id aura to characters listed in config
            for (const std::string& characterName : characterNamesToUseBEMaleModelId)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200022, player);
                    player->AddAura(200046, player);
                }
            }

            // add Draenei Female model id aura to characters listed in config
            for (const std::string& characterName : characterNamesToUseDraeneiFemaleModelId)
            {
                if (characterName == playerName)
                {
                    player->AddAura(200023, player);
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
