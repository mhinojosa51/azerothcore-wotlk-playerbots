//importing header files needed
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellMgr.h"
#include "Log.h"
#include "Config.h"
#include <algorithm>

enum PallySpells
{
    PALADIN_HOLY_CHARGE = 200001,
    PALADIN_CONSECRATION_R1 = 26573,
};

//Custom WoW Spell script for Fist of Heaven custom spell, does extra damage for every stack of Crusaders Mark.
class spell_paladin_argent_crusader_strike_bonus_dmg : SpellScriptLoader
{
public:
    //constructor to initialize the parent class
    spell_paladin_argent_crusader_strike_bonus_dmg() : SpellScriptLoader("spell_paladin_argent_crusader_strike_bonus_dmg") {}

    //nested spell class to handle the actual spell logic
    class spell_paladin_argent_crusader_strike_bonus_dmg_SpellScript : public SpellScript
    {
        // Prepare the script for customization
        PrepareSpellScript(spell_paladin_argent_crusader_strike_bonus_dmg_SpellScript);

        // Function to handle on hit effect of the spell
        void HandleOnHit()
        {
            // Check if the spell hit a unit
            if (Unit* target = GetHitUnit())
            {
                // Increase damage by how many stacks of Crusaders Mark are on the target
                // Removes all stacks of Crusaders Mark from the target after damage is applied
                if (target->HasAura(200004))
                {
                    int32 auraCount = target->GetAuraCount(200004);
                    int32 damage = GetHitDamage();
                    if (auraCount < 4)
                    {
                        float dmgMultiplier = .20f * auraCount;
                        SetHitDamage(int32(damage + (damage * dmgMultiplier)));
                    }
                    // If target has 4 stacks of Crusaders Mark do 300% damage
                    if (auraCount == 4)
                    {
                        SetHitDamage(int32(damage * 4.0f));
                    }
                    target->RemoveAura(200004);
                }
            }
        }

        // Register the function to be called when the spell hits a target
        void Register() override
        {
            OnHit += SpellHitFn(spell_paladin_argent_crusader_strike_bonus_dmg_SpellScript::HandleOnHit);
        }
    };

    // Create a new object of the nested class and return it

    SpellScript* GetSpellScript() const override
    {
        return new spell_paladin_argent_crusader_strike_bonus_dmg_SpellScript();
    }
};

// Function to add the custom spell to the Azerothcore systerm
void AddSC_spell_paladin_argent_crusader_strike_bonus_dmg()
{
    //create a new object of the main class to activate the custom spell
    new spell_paladin_argent_crusader_strike_bonus_dmg();
}

//Custom WoW Spell script, drops a Consecration spell on end of Charge spell
class spell_paladin_charged_consecration : SpellScriptLoader
{
public:
    //constructor to initialize the parent class
    spell_paladin_charged_consecration() : SpellScriptLoader("spell_paladin_charged_consecration") {}

    //nested spell class to handle the actual spell logic
    class spell_paladin_charged_consecration_SpellScript : public AuraScript
    {
        // Prepare the script for customization
        PrepareAuraScript(spell_paladin_charged_consecration_SpellScript);
        
        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            // GetCaster()->CastSpell(GetCaster(), 20924);
            Unit* caster = GetCaster();
            if (caster->HasSpell(PALADIN_CONSECRATION_R1))
            {
                /*LOG_INFO("module", "Spell Info Name: [{}]", GetSpellInfo()->SpellName);
                LOG_INFO("module", "Spell Info Name: [{}]", GetSpellInfo()->GetRank());*/
                caster->CastSpell(caster, sSpellMgr->GetSpellWithRank(PALADIN_CONSECRATION_R1, GetSpellInfo()->GetRank()));
            }
        }
        // Register the function to be called when the spell hits a target
        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_paladin_charged_consecration_SpellScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    // Create a new object of the nested class and return it

    AuraScript* GetAuraScript() const override
    {
        return new spell_paladin_charged_consecration_SpellScript();
    }
};

// Function to add the custom spell to the Azerothcore systerm
void AddSC_spell_paladin_charged_consecration()
{
    //create a new object of the main class to activate the custom spell
    new spell_paladin_charged_consecration();
}

//Custom WoW Spell script, adds damage buff when paladin is fighting on consecrated ground (has cast the spell Consecration)
class spell_paladin_consecrated_fighting : SpellScriptLoader
{
public:
    //constructor to initialize the parent class
    spell_paladin_consecrated_fighting() : SpellScriptLoader("spell_paladin_consecrated_fighting") {}

    //nested spell class to handle the actual spell logic
    class spell_paladin_consecrated_fighting_SpellScript : public SpellScript
    {
        // Prepare the script for customization
        PrepareSpellScript(spell_paladin_consecrated_fighting_SpellScript);

        void HandleOnHit()
        {
            Unit* caster = GetCaster();
            caster->CastSpell(caster, 200014, true);
        }
        // Register the function to be called when the spell hits a target
        void Register() override
        {
            OnHit += SpellHitFn(spell_paladin_consecrated_fighting_SpellScript::HandleOnHit);
        }
    };

    // Create a new object of the nested class and return it

    SpellScript* GetSpellScript() const override
    {
        return new spell_paladin_consecrated_fighting_SpellScript();
    }
};

// Function to add the custom spell to the Azerothcore systerm
void AddSC_spell_paladin_consecrated_fighting()
{
    //create a new object of the main class to activate the custom spell
    new spell_paladin_consecrated_fighting();
}

// sets the scale of the player on load/map change
class spell_general_grow_player : SpellScriptLoader
{
public:
    //constructor to initialize the parent class
    spell_general_grow_player() : SpellScriptLoader("spell_general_grow_player") {}

    //nested spell class to handle the actual spell logic
    class spell_general_grow_player_AuraScript : public AuraScript
    {
        // Prepare the script for customization
        PrepareAuraScript(spell_general_grow_player_AuraScript);

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            GetCaster()->SetObjectScale(1.25f);
        }
        // Register the function to be called when the spell hits a target
        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_general_grow_player_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    // Create a new object of the nested class and return it

    AuraScript* GetAuraScript() const override
    {
        return new spell_general_grow_player_AuraScript();
    }
};

// Function to add the custom spell to the Azerothcore systerm
void AddSC_spell_general_grow_player()
{
    //create a new object of the main class to activate the custom spell
    new spell_general_grow_player();
}

// shrink the player when a certain aura is removed
class spell_general_shrink_player : SpellScriptLoader
{
public:
    //constructor to initialize the parent class
    spell_general_shrink_player() : SpellScriptLoader("spell_general_shrink_player") {}

    //nested spell class to handle the actual spell logic
    class spell_general_shrink_player_AuraScript : public AuraScript
    {
        // Prepare the script for customization
        PrepareAuraScript(spell_general_shrink_player_AuraScript);

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            GetCaster()->SetObjectScale(0.68f);
        }
        // Register the function to be called when the spell hits a target
        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_general_shrink_player_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    // Create a new object of the nested class and return it

    AuraScript* GetAuraScript() const override
    {
        return new spell_general_shrink_player_AuraScript();
    }
};

// Function to add the custom spell to the Azerothcore systerm
void AddSC_spell_general_shrink_player()
{
    //create a new object of the main class to activate the custom spell
    new spell_general_shrink_player();
}

// set the players displayid based on the config file
class spell_general_morph_character_displayid : SpellScriptLoader
{
public:
    //constructor to initialize the parent class
    spell_general_morph_character_displayid() : SpellScriptLoader("spell_general_morph_character_displayid") {}

    //nested spell class to handle the actual spell logic
    class spell_general_morph_character_displayid_AuraScript : public AuraScript
    {
        // Prepare the script for customization
        PrepareAuraScript(spell_general_morph_character_displayid_AuraScript);

        std::vector<std::string> parseCSVToVector(const std::string& str, const std::string& delim)
        {
            std::vector<std::string> csv;
            for (std::size_t last_pos = 0; last_pos < str.size(); )
            {
                std::size_t pos = str.find(delim, last_pos);
                if (pos == str.npos) pos = str.size();
                csv.push_back(str.substr(last_pos, pos - last_pos));
                last_pos = pos + delim.size();
            }
            return csv;
        }

        std::vector<uint32> parseCSVToUINT32Vector(const std::string& str, const std::string& delim)
        {
            std::vector<uint32> csv;
            for (std::size_t last_pos = 0; last_pos < str.size(); )
            {
                std::size_t pos = str.find(delim, last_pos);
                if (pos == str.npos) pos = str.size();
                csv.push_back(static_cast<uint32_t>(std::stoul(str.substr(last_pos, pos - last_pos))));
                last_pos = pos + delim.size();
            }
            return csv;
        }

        std::vector<std::string> characterNamesToApplyMorphsTo = parseCSVToVector(sConfigMgr->GetOption<std::string>("CustomSpells.CharacterNamesToApplyMorphsTo", ""), ",");
        std::vector<uint32> displayIdsToApplyToCharacters = parseCSVToUINT32Vector(sConfigMgr->GetOption<std::string>("CustomSpells.DisplayIdsToApplyToCharacters", ""), ",");

        void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            std::string characterName = GetCaster()->GetName();
            auto characterNameIndex = std::find(characterNamesToApplyMorphsTo.begin(), characterNamesToApplyMorphsTo.end(), characterName) - characterNamesToApplyMorphsTo.begin();

            if (characterNameIndex != characterNamesToApplyMorphsTo.size())
            {
                GetCaster()->SetDisplayId(displayIdsToApplyToCharacters[characterNameIndex]);
            }
        }
        // Register the function to be called when the spell hits a target
        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_general_morph_character_displayid_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    // Create a new object of the nested class and return it

    AuraScript* GetAuraScript() const override
    {
        return new spell_general_morph_character_displayid_AuraScript();
    }
};

// Function to add the custom spell to the Azerothcore systerm
void AddSC_spell_general_morph_character_displayid()
{
    //create a new object of the main class to activate the custom spell
    new spell_general_morph_character_displayid();
}

