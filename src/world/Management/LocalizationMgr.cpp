/*
 * AscEmu Framework based on ArcEmu MMORPG Server
 * String Localization Manager
 * Copyright (C) 2007-2012 Burlex <burlex@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StdAfx.h"
#include "Management/LocalizationMgr.h"
#include "Server/MainServerDefines.h"
#include "Server/World.h"
#include "Server/World.Legacy.h"
#include "Config/Config.h"
#include "Log.hpp"
#include "Database/Database.h"
#include "Server/WUtil.h"
#include "../shared/Util.hpp"

LocalizationMgr sLocalizationMgr;

void LocalizationMgr::Shutdown()
{
    if (m_disabled)
        return;

#define SAFE_FREE_PTR(x) if (deletedPointers.find((x)) == deletedPointers.end()) { deletedPointers.insert((x)); free((x)); }

    std::set<void*> deletedPointers;
    uint32 maxid = 0;
    uint32 i, j;
    std::vector<std::pair<uint32, uint32> >::iterator xtr = m_languages.begin();
    for (; xtr != m_languages.end(); ++xtr)
        if (xtr->second > maxid)
            maxid = xtr->second;

    maxid++;
    LogNotice("LocalizationMgr : Beginning pointer cleanup...");
    uint32 t = getMSTime();

    for (i = 0; i < maxid; ++i)
    {
        for (std::unordered_map<uint32, LocalizedQuest>::iterator itr = m_Quests[i].begin(); itr != m_Quests[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.Title);
            SAFE_FREE_PTR(itr->second.Details);
            SAFE_FREE_PTR(itr->second.Objectives);
            SAFE_FREE_PTR(itr->second.CompletionText);
            SAFE_FREE_PTR(itr->second.IncompleteText);
            SAFE_FREE_PTR(itr->second.EndText);
            SAFE_FREE_PTR(itr->second.ObjectiveText[0]);
            SAFE_FREE_PTR(itr->second.ObjectiveText[1]);
            SAFE_FREE_PTR(itr->second.ObjectiveText[2]);
            SAFE_FREE_PTR(itr->second.ObjectiveText[3]);
        }

        for (std::unordered_map<uint32, LocalizedItem>::iterator itr = m_Items[i].begin(); itr != m_Items[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.Name);
            SAFE_FREE_PTR(itr->second.Description);
        }

        for (std::unordered_map<uint32, LocalizedNpcText>::iterator itr = m_NpcTexts[i].begin(); itr != m_NpcTexts[i].end(); ++itr)
        {
            for (j = 0; j < 8; ++j)
            {
                SAFE_FREE_PTR(itr->second.Texts[j][0]);
                SAFE_FREE_PTR(itr->second.Texts[j][1]);
            }
        }

        for (std::unordered_map<uint32, LocalizedCreatureName>::iterator itr = m_CreatureNames[i].begin(); itr != m_CreatureNames[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.Name);
            SAFE_FREE_PTR(itr->second.SubName);
        }

        for (std::unordered_map<uint32, LocalizedGameObjectName>::iterator itr = m_GameObjectNames[i].begin(); itr != m_GameObjectNames[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.Name);
        }

        for (std::unordered_map<uint32, LocalizedItemPage>::iterator itr = m_ItemPages[i].begin(); itr != m_ItemPages[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.Text);
        }

        for (std::unordered_map<uint32, LocalizedCreatureText>::iterator itr = m_CreatureText[i].begin(); itr != m_CreatureText[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.Text);
        }

        for (std::unordered_map<uint32, LocalizedGossipMenuOption>::iterator itr = m_GossipMenuOption[i].begin(); itr != m_GossipMenuOption[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.Text);
        }

        for (std::unordered_map<uint32, LocalizedWorldStringTable>::iterator itr = m_WorldStrings[i].begin(); itr != m_WorldStrings[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.Text);
        }

        for (std::unordered_map<uint32, LocalizedWorldBroadCast>::iterator itr = m_WorldBroadCast[i].begin(); itr != m_WorldBroadCast[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.Text);
        }

        for (std::unordered_map<uint32, LocalizedWorldMapInfo>::iterator itr = m_WorldMapInfo[i].begin(); itr != m_WorldMapInfo[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.Text);
        }

        for (std::unordered_map<uint32, LocalizedMonstersay>::iterator itr = m_MonsterSay[i].begin(); itr != m_MonsterSay[i].end(); ++itr)
        {
            SAFE_FREE_PTR(itr->second.monstername);
            SAFE_FREE_PTR(itr->second.text0);
            SAFE_FREE_PTR(itr->second.text1);
            SAFE_FREE_PTR(itr->second.text2);
            SAFE_FREE_PTR(itr->second.text3);
            SAFE_FREE_PTR(itr->second.text4);
        }


    }

    deletedPointers.clear();
    delete[] m_ItemPages;
    delete[] m_CreatureNames;
    delete[] m_GameObjectNames;
    delete[] m_Items;
    delete[] m_NpcTexts;
    delete[] m_Quests;
    delete[] m_CreatureText;
    delete[] m_GossipMenuOption;
    delete[] m_WorldStrings;
    delete[] m_WorldBroadCast;
    delete[] m_WorldMapInfo;
    delete[] m_MonsterSay;
    m_languages.clear();

    LogNotice("LocalizationMgr : Pointer cleanup completed in %.4f seconds.", (getMSTime() - t) / 1000.0f);

#undef SAFE_FREE_PTR
}

void LocalizationMgr::Lower(std::string & conv)
{
    for (size_t i = 0; i < conv.length(); ++i)
        conv[i] = static_cast<char>(tolower(conv[i]));
}

void LocalizationMgr::GetDistinctLanguages(std::set<std::string>& dest, const char* table)
{
    QueryResult* result = WorldDatabase.Query("SELECT DISTINCT language_code FROM %s", table);
    if (result == NULL)
        return;

    std::string lc;
    do
    {
        lc = result->Fetch()[0].GetString();
        sLocalizationMgr.Lower(lc);
        if (dest.find(lc) == dest.end())
            dest.insert(lc);

    }
    while (result->NextRow());
    delete result;
}

uint32 LocalizationMgr::GetLanguageId(uint32 full)
{
    if (m_disabled)
    {
        return 0;
    }

    for (std::vector<std::pair<uint32, uint32> >::iterator itr = m_languages.begin(); itr != m_languages.end(); ++itr)
    {
        if (itr->first == full)
        {
            return itr->second;
        }
    }

    return 0;
}

#define MAX_LOCALIZED_CHAR 200
void LocalizationMgr::Reload(bool first)
{
    if (first)
    {
        return;
    }

    QueryResult* result;
    std::set<std::string> languages;
    std::map<std::string, std::string> bound_languages;
    GetDistinctLanguages(languages, "locales_creature");
    GetDistinctLanguages(languages, "locales_gameobject");
    GetDistinctLanguages(languages, "locales_item");
    GetDistinctLanguages(languages, "locales_quest");
    GetDistinctLanguages(languages, "locales_npc_text");
    GetDistinctLanguages(languages, "locales_npc_script_text");
    GetDistinctLanguages(languages, "locales_item_pages");
    GetDistinctLanguages(languages, "locales_gossip_menu_option");
    GetDistinctLanguages(languages, "locales_worldstring_table");
    GetDistinctLanguages(languages, "locales_worldbroadcast");
    GetDistinctLanguages(languages, "locales_worldmap_info");
    GetDistinctLanguages(languages, "locales_npc_monstersay");

    /// Read Language Bindings From Config
    std::string ls = worldConfig.localization.localizedBindings;
    std::vector<std::string> tbindings = Util::SplitStringBySeperator(ls, " ");
    for (std::vector<std::string>::iterator ztr = tbindings.begin(); ztr != tbindings.end(); ++ztr)
    {
        char lb[MAX_LOCALIZED_CHAR];
        std::string ll1, ll2;
        strncpy(lb, (*ztr).c_str(), MAX_LOCALIZED_CHAR);
        lb[MAX_LOCALIZED_CHAR - 1] = '\0';

        char* lbp = strchr(lb, '=');
        if (lbp == NULL)
        {
            continue;
        }

        *lbp = 0;
        lbp++;

        ll1 = std::string(lb);
        ll2 = std::string(lbp);
        Lower(ll1);
        Lower(ll2);

        if (languages.find(ll1) == languages.end())
        {
            bound_languages[ll1] = ll2;
            languages.insert(ll1);
        }
    }

    /// Generate Language IDs
    uint32 langid = 1;
    std::pair<uint32, uint32> dpr;
    for (std::set<std::string>::iterator sitr = languages.begin(); sitr != languages.end(); ++sitr)
    {
        if ((*sitr) == "enus")        // Default
        {
            dpr.first = *(uint32*)sitr->c_str();
            dpr.second = 0;
        }
        else
        {
            dpr.first = *(uint32*)sitr->c_str();
            dpr.second = langid++;
        }

        m_languages.push_back(dpr);
    }

    if (m_languages.size() == 0)
    {
        m_disabled = true;
        return;                 // No localizations
    }
    else
    {
        m_disabled = false;
    }

    m_CreatureNames = new std::unordered_map<uint32, LocalizedCreatureName>[langid];
    m_GameObjectNames = new std::unordered_map<uint32, LocalizedGameObjectName>[langid];
    m_Quests = new std::unordered_map<uint32, LocalizedQuest>[langid];
    m_NpcTexts = new std::unordered_map<uint32, LocalizedNpcText>[langid];
    m_Items = new std::unordered_map<uint32, LocalizedItem>[langid];
    m_ItemPages = new std::unordered_map<uint32, LocalizedItemPage>[langid];
    m_CreatureText = new std::unordered_map<uint32, LocalizedCreatureText>[langid];
    m_GossipMenuOption = new std::unordered_map<uint32, LocalizedGossipMenuOption>[langid];
    m_WorldStrings = new std::unordered_map<uint32, LocalizedWorldStringTable>[langid];
    m_WorldBroadCast = new std::unordered_map<uint32, LocalizedWorldBroadCast>[langid];
    m_WorldMapInfo = new std::unordered_map<uint32, LocalizedWorldMapInfo>[langid];
    m_MonsterSay = new std::unordered_map<uint32, LocalizedMonstersay>[langid];

    //////////////////////////////////////////////////////////////////////////////////////////
    // Creature Names
    {
        LocalizedCreatureName cn;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        result = WorldDatabase.Query("SELECT * FROM locales_creature");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;        // no loading enUS stuff.. lawl
                }

                cn.Name = strdup(f[2].GetString());
                cn.SubName = strdup(f[3].GetString());
                m_CreatureNames[lid].insert(std::make_pair(entry, cn));
            }
            while (result->NextRow());
            delete result;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // GameObject Names
    {
        LocalizedGameObjectName gn;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        result = WorldDatabase.Query("SELECT * FROM locales_gameobject");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;        // no loading enUS stuff.. lawl
                }

                gn.Name = strdup(f[2].GetString());
                m_GameObjectNames[lid].insert(std::make_pair(entry, gn));
            }
            while (result->NextRow());
            delete result;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // Items
    {
        LocalizedItem it;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        result = WorldDatabase.Query("SELECT * FROM locales_item");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;        // no loading enUS stuff.. lawl
                }

                if (m_Items[lid].find(entry) != m_Items[lid].end())
                {
                    continue;
                }

                it.Name = strdup(f[2].GetString());
                it.Description = strdup(f[3].GetString());
                m_Items[lid].insert(std::make_pair(entry, it));
            }
            while (result->NextRow());
            delete result;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // Quests
    {
        LocalizedQuest q;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        result = WorldDatabase.Query("SELECT * FROM locales_quest");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;        // no loading enUS stuff.. lawl
                }

                q.Title = strdup(f[2].GetString());
                q.Details = strdup(f[3].GetString());
                q.Objectives = strdup(f[4].GetString());
                q.CompletionText = strdup(f[5].GetString());
                q.IncompleteText = strdup(f[6].GetString());
                q.EndText = strdup(f[7].GetString());
                q.ObjectiveText[0] = strdup(f[8].GetString());
                q.ObjectiveText[1] = strdup(f[9].GetString());
                q.ObjectiveText[2] = strdup(f[10].GetString());
                q.ObjectiveText[3] = strdup(f[11].GetString());

                m_Quests[lid].insert(std::make_pair(entry, q));
            }
            while (result->NextRow());
            delete result;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // NPC Texts
    {
        LocalizedNpcText nt;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;
        uint32 counter;

        result = WorldDatabase.Query("SELECT * FROM locales_npc_text");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;        // no loading enUS stuff.. lawl
                }

                counter = 2;
                for (uint8 i = 0; i < 8; ++i)
                {
                    nt.Texts[i][0] = strdup(f[counter++].GetString());
                    nt.Texts[i][1] = strdup(f[counter++].GetString());
                }

                m_NpcTexts[lid].insert(std::make_pair(entry, nt));
            }
            while (result->NextRow());
            delete result;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////////////
    // Item Pages
    {
        LocalizedItemPage nt;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        result = WorldDatabase.Query("SELECT * FROM locales_item_pages");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;        // no loading enUS stuff.. lawl
                }

                nt.Text = strdup(f[2].GetString());
                m_ItemPages[lid].insert(std::make_pair(entry, nt));
            }
            while (result->NextRow());
            delete result;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // Creature Text
    {
        LocalizedCreatureText nt;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        result = WorldDatabase.Query("SELECT * FROM locales_npc_script_text");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;
                }

                nt.Text = strdup(f[2].GetString());
                m_CreatureText[lid].insert(std::make_pair(entry, nt));
            }
            while (result->NextRow());
            delete result;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // Gossip Menu Option
    {
        LocalizedGossipMenuOption nt;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        result = WorldDatabase.Query("SELECT * FROM locales_gossip_menu_option");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;
                }

                nt.Text = strdup(f[2].GetString());
                m_GossipMenuOption[lid].insert(std::make_pair(entry, nt));
            }
            while (result->NextRow());
            delete result;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // World Common Message
    {
        LocalizedWorldStringTable nt;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        result = WorldDatabase.Query("SELECT * FROM locales_worldstring_table");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;
                }

                nt.Text = strdup(f[2].GetString());
                m_WorldStrings[lid].insert(std::make_pair(entry, nt));
            }
            while (result->NextRow());
            delete result;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // World BroadCast Messages
    {
        LocalizedWorldBroadCast nt;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        result = WorldDatabase.Query("SELECT * FROM locales_worldbroadcast");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;
                }

                nt.Text = strdup(f[2].GetString());
                m_WorldBroadCast[lid].insert(std::make_pair(entry, nt));
            }
            while (result->NextRow());
            delete result;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // World MapInfo Entry Name
    {
        LocalizedWorldMapInfo nt;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        result = WorldDatabase.Query("SELECT * FROM locales_worldmap_info");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;
                }

                nt.Text = strdup(f[2].GetString());
                m_WorldMapInfo[lid].insert(std::make_pair(entry, nt));
            }
            while (result->NextRow());
            delete result;
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    // NPC Monstersay
    {
        LocalizedMonstersay ms;
        std::string str;
        uint32 entry;
        Field* f;
        uint32 lid;

        LogDefault("Loading locales_npc_monstersay rows...");
        result = WorldDatabase.Query("SELECT * FROM locales_npc_monstersay");
        if (result)
        {
            do
            {
                f = result->Fetch();
                str = std::string(f[1].GetString());
                entry = f[0].GetUInt32();

                lid = GetLanguageId(str);
                if (lid == 0)
                {
                    continue;        // no loading enUS stuff.. lawl
                }

                ms.monstername = strdup(f[2].GetString());
                ms.text0 = strdup(f[3].GetString());
                ms.text1 = strdup(f[4].GetString());
                ms.text2 = strdup(f[5].GetString());
                ms.text3 = strdup(f[6].GetString());
                ms.text4 = strdup(f[7].GetString());

                m_MonsterSay[lid].insert(std::make_pair(entry, ms));
            }
            while (result->NextRow());
            delete result;
        }
    }


    //////////////////////////////////////////////////////////////////////////////////////////
    // Apply all the language bindings.
    for (std::map<std::string, std::string>::iterator itr = bound_languages.begin(); itr != bound_languages.end(); ++itr)
    {
        uint32 source_language_id = GetLanguageId(itr->second);
        uint32 dest_language_id = GetLanguageId(itr->first);
        if (source_language_id == 0 || dest_language_id == 0)
        {
            LOG_ERROR("Invalid locale conversion string specified: %u->%u (%s->%s)", source_language_id, dest_language_id, itr->second.c_str(), itr->first.c_str());
            continue;
        }

        // duplicate the hashmaps (we can save the pointers here)
        CopyHashMap<LocalizedItem>(&m_Items[source_language_id], &m_Items[dest_language_id]);
        CopyHashMap<LocalizedCreatureName>(&m_CreatureNames[source_language_id], &m_CreatureNames[dest_language_id]);
        CopyHashMap<LocalizedGameObjectName>(&m_GameObjectNames[source_language_id], &m_GameObjectNames[dest_language_id]);
        CopyHashMap<LocalizedItemPage>(&m_ItemPages[source_language_id], &m_ItemPages[dest_language_id]);
        CopyHashMap<LocalizedQuest>(&m_Quests[source_language_id], &m_Quests[dest_language_id]);
        CopyHashMap<LocalizedNpcText>(&m_NpcTexts[source_language_id], &m_NpcTexts[dest_language_id]);
        CopyHashMap<LocalizedCreatureText>(&m_CreatureText[source_language_id], &m_CreatureText[dest_language_id]);
        CopyHashMap<LocalizedGossipMenuOption>(&m_GossipMenuOption[source_language_id], &m_GossipMenuOption[dest_language_id]);
        CopyHashMap<LocalizedWorldStringTable>(&m_WorldStrings[source_language_id], &m_WorldStrings[dest_language_id]);
        CopyHashMap<LocalizedWorldBroadCast>(&m_WorldBroadCast[source_language_id], &m_WorldBroadCast[dest_language_id]);
        CopyHashMap<LocalizedWorldMapInfo>(&m_WorldMapInfo[source_language_id], &m_WorldMapInfo[dest_language_id]);
        CopyHashMap<LocalizedMonstersay>(&m_MonsterSay[source_language_id], &m_MonsterSay[dest_language_id]);
    }
}

#define MAKE_LOOKUP_FUNCTION(t, hm, fn) t * LocalizationMgr::fn(uint32 id, uint32 language) { \
    if (m_disabled) { return NULL; } \
    std::unordered_map<uint32, t>::iterator itr = hm[language].find(id); \
    return (itr == hm[language].end()) ? NULL : &itr->second; }

MAKE_LOOKUP_FUNCTION(LocalizedCreatureName, m_CreatureNames, GetLocalizedCreatureName);
MAKE_LOOKUP_FUNCTION(LocalizedGameObjectName, m_GameObjectNames, GetLocalizedGameObjectName);
MAKE_LOOKUP_FUNCTION(LocalizedQuest, m_Quests, GetLocalizedQuest);
MAKE_LOOKUP_FUNCTION(LocalizedItem, m_Items, GetLocalizedItem);
MAKE_LOOKUP_FUNCTION(LocalizedNpcText, m_NpcTexts, GetLocalizedNpcText);
MAKE_LOOKUP_FUNCTION(LocalizedItemPage, m_ItemPages, GetLocalizedItemPage);
MAKE_LOOKUP_FUNCTION(LocalizedCreatureText, m_CreatureText, GetLocalizedCreatureText);
MAKE_LOOKUP_FUNCTION(LocalizedGossipMenuOption, m_GossipMenuOption, GetLocalizedGossipMenuOption);
MAKE_LOOKUP_FUNCTION(LocalizedWorldStringTable, m_WorldStrings, GetLocalizedWorldStringTable);
MAKE_LOOKUP_FUNCTION(LocalizedWorldBroadCast, m_WorldBroadCast, GetLocalizedWorldBroadCast);
MAKE_LOOKUP_FUNCTION(LocalizedWorldMapInfo, m_WorldMapInfo, GetLocalizedWorldMapInfo);
MAKE_LOOKUP_FUNCTION(LocalizedMonstersay, m_MonsterSay, GetLocalizedMonstersay);
