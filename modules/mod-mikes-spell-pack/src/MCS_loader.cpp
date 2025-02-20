/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

// From SC
void AddSC_spell_paladin_argent_crusader_strike_bonus_dmg();
void AddSC_spell_paladin_charged_consecration();
void AddSC_spell_paladin_consecrated_fighting();
void AddSC_spell_general_grow_player();
void AddSC_spell_general_shrink_player();
void AddSC_spell_general_player_model_becomes_alexstraza();
void AddSC_spell_general_player_model_becomes_sylvana();
void AddSC_spell_general_player_model_becomes_veeresa();
void AddSC_spell_general_player_model_becomes_blood_elf_male();
void AddSC_spell_general_player_model_becomes_draenei_female();

// Add all
// cf. the naming convention https://github.com/azerothcore/azerothcore-wotlk/blob/master/doc/changelog/master.md#how-to-upgrade-4
// additionally replace all '-' in the module folder name with '_' here
void Addmod_mikes_spell_packScripts()
{
    AddSC_spell_paladin_argent_crusader_strike_bonus_dmg();
    AddSC_spell_paladin_charged_consecration();
    AddSC_spell_paladin_consecrated_fighting();
    AddSC_spell_general_grow_player();
    AddSC_spell_general_shrink_player();
    AddSC_spell_general_player_model_becomes_alexstraza();
    AddSC_spell_general_player_model_becomes_sylvana();
    AddSC_spell_general_player_model_becomes_veeresa();
    AddSC_spell_general_player_model_becomes_blood_elf_male();
    AddSC_spell_general_player_model_becomes_draenei_female();
}

