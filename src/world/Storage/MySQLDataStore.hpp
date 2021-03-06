/*
Copyright (c) 2014-2017 AscEmu Team <http://www.ascemu.org/>
This file is released under the MIT license. See README-MIT for more information.
*/

#pragma once

#include "Singleton.h"
#include "Server/Packets/Handlers/MiscHandler.h"
#include "Server/Packets/Handlers/NPCHandler.h"
#include "../../scripts/Battlegrounds/IsleOfConquest.h"
#include "Objects/ObjectMgr.h"
#include "Spell/Definitions/SpellClickSpell.h"
#include "Spell/Definitions/TeleportCoords.h"
#include "MySQLStructures.h"

extern SERVER_DECL std::set<std::string> CreatureSpawnsTables;
extern SERVER_DECL std::set<std::string> GameObjectSpawnsTables;
extern SERVER_DECL std::set<std::string> GameObjectPropertiesTables;
extern SERVER_DECL std::set<std::string> CreaturePropertiesTables;
extern SERVER_DECL std::set<std::string> ItemPropertiesTables;
extern SERVER_DECL std::set<std::string> QuestPropertiesTables;


class SERVER_DECL MySQLDataStore : public Singleton <MySQLDataStore>
{
public:

    MySQLDataStore();
    ~MySQLDataStore();

    //maps
    typedef std::unordered_map<uint32_t, MySQLStructure::ItemPage> ItemPageContainer;
    typedef std::unordered_map<uint32_t, ItemProperties> ItemPropertiesContainer;
    typedef std::unordered_map<uint32_t, CreatureProperties> CreaturePropertiesContainer;
    typedef std::unordered_map<uint32_t, GameObjectProperties> GameObjectPropertiesContainer;
    typedef std::unordered_map<uint32_t, QuestProperties> QuestPropertiesContainer;

    typedef std::unordered_map<uint32_t, MySQLStructure::CreatureDifficulty> CreatureDifficultyContainer;
    typedef std::unordered_map<uint32_t, DisplayBounding> DisplayBoundingBoxesContainer;
    typedef std::unordered_map<uint32_t, MySQLStructure::VendorRestrictions> VendorRestrictionContainer;
    typedef std::unordered_map<uint32_t, NpcText> NpcTextContainer;
    typedef std::unordered_map<uint32_t, NpcScriptText> NpcScriptTextContainer;
    typedef std::unordered_map<uint32_t, MySQLStructure::GossipMenuOption> GossipMenuOptionContainer;
    typedef std::unordered_map<uint32_t, GraveyardTeleport> GraveyardsContainer;
    typedef std::unordered_map<uint32_t, TeleportCoords> TeleportCoordsContainer;
    typedef std::unordered_map<uint32_t, MySQLStructure::FishingZones> FishingZonesContainer;
    typedef std::unordered_map<uint32_t, MapInfo> WorldMapInfoContainer;
    typedef std::unordered_map<uint32_t, MySQLStructure::ZoneGuards> ZoneGuardsContainer;
    typedef std::unordered_map<uint32_t, BGMaster> BattleMastersContainer;
    typedef std::unordered_map<uint32_t, MySQLStructure::TotemDisplayIds> TotemDisplayIdContainer;
    typedef std::unordered_map<uint32_t, SpellClickSpell> SpellClickSpellContainer;
    typedef std::unordered_map<uint32_t, MySQLStructure::WorldStringTable> WorldStringContainer;
    typedef std::unordered_map<uint32_t, MySQLStructure::PointsOfInterest> PointsOfInterestContainer;

    typedef std::unordered_map<int32, ItemSetLinkedItemSetBonus> ItemSetDefinedSetBonusContainer;

    typedef std::unordered_map<uint32_t, PlayerCreateInfo> PlayerCreateInfoContainer;
    typedef std::vector<uint32_t> PlayerXPperLevel;

    typedef std::map<uint32_t, std::list<SpellInfo*>*> SpellOverrideIdMap;

    typedef std::map<uint32_t, uint32_t> NpcGossipTextIdMap;

    typedef std::unordered_map<uint32_t, MySQLStructure::PetLevelAbilities> PetLevelAbilitiesContainer;

    typedef std::unordered_map<uint32_t, MySQLStructure::WorldBroadCast> WorldBroadcastContainer;

    typedef std::unordered_map<uint32_t, MySQLStructure::AreaTrigger> AreaTriggerContainer;

    typedef std::list<MySQLStructure::WordFilterCharacterNames> WordFilterCharacterNamesSet;
    typedef std::list<MySQLStructure::WordFilterChat> WordFilterChatSet;

    //helper
    MySQLStructure::ItemPage const* getItemPage(uint32_t entry);
    ItemPageContainer const* getItemPagesStore() { return &_itemPagesStore; }
    ItemProperties const* getItemProperties(uint32_t entry);
    ItemPropertiesContainer const* getItemPropertiesStore() { return &_itemPropertiesStore; }

    CreatureProperties const* getCreatureProperties(uint32_t entry);
    CreaturePropertiesContainer const* getCreaturePropertiesStore() { return &_creaturePropertiesStore; }

    GameObjectProperties const* getGameObjectProperties(uint32_t entry);
    GameObjectPropertiesContainer const* getGameObjectPropertiesStore() { return &_gameobjectPropertiesStore; }

    QuestProperties const* getQuestProperties(uint32_t entry);
    QuestPropertiesContainer const* getQuestPropertiesStore() { return &_questPropertiesStore; }

    uint32_t getCreatureDifficulty(uint32_t entry, uint8_t difficulty_type);
    CreatureDifficultyContainer const* getCreatureDifficultyStore() { return &_creatureDifficultyStore; }

    DisplayBounding const* getDisplayBounding(uint32_t entry);
    DisplayBoundingBoxesContainer const* getDisplayBoundingBoxesStore() { return &_displayBoundingBoxesStore; }

    MySQLStructure::VendorRestrictions const* getVendorRestriction(uint32_t entry);
    VendorRestrictionContainer const* getVendorRestrictionsStore() { return &_vendorRestrictionsStore; }

    NpcText const* getNpcText(uint32_t entry);
    NpcTextContainer const* getNpcTextStore() { return &_npcTextStore; }

    NpcScriptText const* getNpcScriptText(uint32_t entry);
    NpcScriptTextContainer const* getNpcScriptTextStore() { return &_npcScriptTextStore; }

    MySQLStructure::GossipMenuOption const* getGossipMenuOption(uint32_t entry);
    GossipMenuOptionContainer const* getGossipMenuOptionStore() { return &_gossipMenuOptionStore; }

    GraveyardTeleport const* getGraveyard(uint32_t entry);
    GraveyardsContainer const* getGraveyardsStore() { return &_graveyardsStore; }

    TeleportCoords const* getTeleportCoord(uint32_t entry);
    TeleportCoordsContainer const* getTeleportCoordsStore() { return &_teleportCoordsStore; }

    MySQLStructure::FishingZones const* getFishingZone(uint32_t entry);
    FishingZonesContainer const* getFischingZonesStore() { return &_fishingZonesStore; }

    MapInfo const* getWorldMapInfo(uint32_t entry);
    WorldMapInfoContainer const* getWorldMapInfoStore() { return &_worldMapInfoStore; }

    MySQLStructure::ZoneGuards const* getZoneGuard(uint32_t entry);
    ZoneGuardsContainer const* getZoneGuardsStore() { return &_zoneGuardsStore; }

    BGMaster const* getBattleMaster(uint32_t entry);
    BattleMastersContainer const* getBattleMastersStore() { return &_battleMastersStore; }

    MySQLStructure::TotemDisplayIds const* getTotemDisplayId(uint32_t entry);
    TotemDisplayIdContainer const* getTotemDisplayIdsStore() { return &_totemDisplayIdsStore; }

    SpellClickSpell const* getSpellClickSpell(uint32_t entry);
    SpellClickSpellContainer const* getSpellClickSpellsStore() { return &_spellClickSpellsStore; }

    MySQLStructure::WorldStringTable const* getWorldString(uint32_t entry);
    WorldStringContainer const* getWorldStringsStore() { return &_worldStringsStore; }

    MySQLStructure::PointsOfInterest const* getPointOfInterest(uint32_t entry);
    PointsOfInterestContainer const* getPointOfInterestStore() { return &_pointsOfInterestStore; }

    uint32_t getItemSetLinkedBonus(int32 itemset);

    PlayerCreateInfo const* getPlayerCreateInfo(uint8_t player_race, uint8_t player_class);
    uint32_t getPlayerXPForLevel(uint32_t level);

    uint32_t getGossipTextIdForNpc(uint32_t entry);

    MySQLStructure::PetLevelAbilities const* getPetLevelAbilities(uint32_t level);
    PetLevelAbilitiesContainer const* getPetAbilitiesStore() { return &_petLevelAbilitiesStore; }

    MySQLStructure::WorldBroadCast const* getWorldBroadcastById(uint32_t level);
    WorldBroadcastContainer* getWorldBroadcastStore() { return &_worldBroadcastStore; }

    MySQLStructure::AreaTrigger const* getAreaTrigger(uint32_t entry);
    AreaTriggerContainer const* getAreaTriggersStore() { return &_areaTriggerStore; }
    MySQLStructure::AreaTrigger const* getMapEntranceTrigger(uint32_t mapId);

    bool isCharacterNameAllowed(std::string charName);

    //Config
    void loadAdditionalTableConfig();

    //Loads
    void loadItemPagesTable();
    void loadItemPropertiesTable();

    void loadCreaturePropertiesTable();

    void loadGameObjectPropertiesTable();

    void loadQuestPropertiesTable();
    void loadGameObjectQuestItemBindingTable();
    void loadGameObjectQuestPickupBindingTable();

    void loadCreatureDifficultyTable();
    void loadDisplayBoundingBoxesTable();
    void loadVendorRestrictionsTable();

    void loadNpcTextTable();
    void loadNpcScriptTextTable();
    void loadGossipMenuOptionTable();
    void loadGraveyardsTable();
    void loadTeleportCoordsTable();
    void loadFishingTable();
    void loadWorldMapInfoTable();
    void loadZoneGuardsTable();
    void loadBattleMastersTable();
    void loadTotemDisplayIdsTable();
    void loadSpellClickSpellsTable();

    void loadWorldStringsTable();

    void loadPointsOfInterestTable();

    void loadItemSetLinkedSetBonusTable();
    void loadCreatureInitialEquipmentTable();

    //player create info
    void loadPlayerCreateInfoTable();
    void loadPlayerCreateInfoSkillsTable();
    void loadPlayerCreateInfoSpellsTable();
    void loadPlayerCreateInfoItemsTable();
    void loadPlayerCreateInfoBarsTable(uint32_t player_info_index);
    void loadPlayerXpToLevelTable();

    void loadSpellOverrideTable();

    void loadNpcGossipTextIdTable();
    void loadPetLevelAbilitiesTable();

    void loadBroadcastTable();

    void loadAreaTriggerTable();

    void loadWordFilterCharacterNames();
    void loadWordFilterChat();

    ItemPageContainer _itemPagesStore;
    ItemPropertiesContainer _itemPropertiesStore;
    CreaturePropertiesContainer _creaturePropertiesStore;
    GameObjectPropertiesContainer _gameobjectPropertiesStore;
    QuestPropertiesContainer _questPropertiesStore;

    CreatureDifficultyContainer _creatureDifficultyStore;
    DisplayBoundingBoxesContainer _displayBoundingBoxesStore;
    VendorRestrictionContainer _vendorRestrictionsStore;
    NpcTextContainer _npcTextStore;
    NpcScriptTextContainer _npcScriptTextStore;
    GossipMenuOptionContainer _gossipMenuOptionStore;
    GraveyardsContainer _graveyardsStore;
    TeleportCoordsContainer _teleportCoordsStore;
    FishingZonesContainer _fishingZonesStore;
    WorldMapInfoContainer _worldMapInfoStore;
    ZoneGuardsContainer _zoneGuardsStore;
    BattleMastersContainer _battleMastersStore;
    TotemDisplayIdContainer _totemDisplayIdsStore;
    SpellClickSpellContainer _spellClickSpellsStore;

    WorldStringContainer _worldStringsStore;

    PointsOfInterestContainer _pointsOfInterestStore;

    ItemSetDefinedSetBonusContainer _definedItemSetBonusStore;

    PlayerCreateInfoContainer _playerCreateInfoStore;
    PlayerXPperLevel _playerXPperLevelStore;

    SpellOverrideIdMap _spellOverrideIdStore;

    NpcGossipTextIdMap _npcGossipTextIdStore;

    PetLevelAbilitiesContainer _petLevelAbilitiesStore;

    WorldBroadcastContainer _worldBroadcastStore;

    AreaTriggerContainer _areaTriggerStore;

    WordFilterCharacterNamesSet _wordFilterCharacterNamesStore;
    WordFilterChatSet _wordFilterChatStore;
};

#define sMySQLStore MySQLDataStore::getSingleton()
