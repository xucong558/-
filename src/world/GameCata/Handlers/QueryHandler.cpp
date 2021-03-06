/*
Copyright (c) 2014-2017 AscEmu Team <http://www.ascemu.org/>
This file is released under the MIT license. See README-MIT for more information.
*/

#include "StdAfx.h"
#include "Storage/MySQLDataStore.hpp"
#include "Management/LocalizationMgr.h"
#include "Map/WorldCreatorDefines.hpp"


void WorldSession::HandleCorpseQueryOpcode(WorldPacket& recv_data)
{
    Corpse* pCorpse = objmgr.GetCorpseByOwner(GetPlayer()->GetLowGUID());
    if (pCorpse == nullptr)
    {
        WorldPacket data(MSG_CORPSE_QUERY, 1);
        data << uint8_t(0);                         // no coprse for player
        SendPacket(&data);
    }
    else
    {
        WorldPacket data(MSG_CORPSE_QUERY, 25);
        data << uint8_t(1);                         // corpse found

        uint32_t corpsemap;
        uint32_t repopmap;
        float x, y, z;

        MapInfo const* pMapinfo = sMySQLStore.getWorldMapInfo(pCorpse->GetMapId());
        if (pMapinfo)
        {
            if (pMapinfo->type == INSTANCE_NULL || pMapinfo->type == INSTANCE_BATTLEGROUND)
            {
                repopmap = pCorpse->GetMapId();     // mapid (that tombstones shown on)
                x = pCorpse->GetPositionX();
                y = pCorpse->GetPositionY();
                z = pCorpse->GetPositionZ();
                corpsemap = pCorpse->GetMapId();    // instance mapid (needs to be same as mapid to be able to recover corpse)
            }
            else
            {
                repopmap = pMapinfo->repopmapid;    // mapid (that tombstones shown on)
                x = pMapinfo->repopx;
                y = pMapinfo->repopy;
                z = pMapinfo->repopz;
                corpsemap = pCorpse->GetMapId();    // instance mapid (needs to be same as mapid to be able to recover corpse)
            }
        }
        else
        {
            repopmap = pCorpse->GetMapId();         // mapid (that tombstones shown on)
            x = pCorpse->GetPositionX();
            y = pCorpse->GetPositionY();
            z = pCorpse->GetPositionZ();
            corpsemap = pCorpse->GetMapId();        // instance mapid (needs to be same as mapid to be able to recover corpse)
        }

        data << uint32_t(repopmap);
        data << float(x);
        data << float(y);
        data << float(z);
        data << uint32_t(corpsemap);
        data << uint32_t(0);                        // unk
        SendPacket(&data);
    }
}

void WorldSession::HandleInrangeQuestgiverQuery(WorldPacket& recv_data)
{
    uint32_t count = 0;

    WorldPacket data(SMSG_QUESTGIVER_STATUS_MULTIPLE, 4 + 8 + 4);
    data << uint32_t(count);

    Object::InRangeSet::iterator itr;
    for (itr = _player->m_objectsInRange.begin(); itr != _player->m_objectsInRange.end(); ++itr)
    {
        if (!(*itr)->IsCreature())
            continue;

        Creature* pCreature = static_cast<Creature*>(*itr);

        if (pCreature->isQuestGiver())
        {
            data << uint64_t(pCreature->GetGUID());
            data << uint32_t(sQuestMgr.CalcStatus(pCreature, _player));
            ++count;
        }
    }

    data.put<uint32_t>(0, count);
    SendPacket(&data);
}
