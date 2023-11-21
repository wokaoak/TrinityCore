#include "ObjectMgr.h"
#include "WorldSession.h"
#include "Configuration/Config.h"


#include "Define.h"
#include "GossipDef.h"
#include "Item.h"
#include "Spell.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Map.h"
#include "DB2Store.h"
#include <CharacterDatabase.h>
#include "World.h"

class aa_item_zuobiao: public ItemScript
{
private:
    std::vector<int32> type_ids;
    uint32 vcount = 0;
    uint32 scount = 0;
public:
    aa_item_zuobiao() : ItemScript("aa_item_zuobiao") { }

    bool ShowMenu(Player* player, Item* item) {
        if (!player || !player->IsInWorld() || !item || !item->IsInWorld()) {
            return true;
        }
        ItemTemplate const* pProto = item->GetTemplate();
        if (!pProto)
        {
            return true;
        }
        if (aaCenter.aa_item_zuobiao_confs.find(pProto->GetId()) == aaCenter.aa_item_zuobiao_confs.end()) {
            return true;
        }
        AA_Item_Zuobiao_Conf conf = aaCenter.aa_item_zuobiao_confs[pProto->GetId()];
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GossipOptionNpc(0), "记录当前位置或传送记录位置。", GOSSIP_SENDER_MAIN, 999);
        if (conf.count <= 0 || conf.count > 20) {
            return true;
        }
        for (size_t i = 0; i < conf.count; i++)
        {
            bool isOk = true;
            if (aaCenter.aa_item_zuobiaos.find(item->GetGUIDLow()) != aaCenter.aa_item_zuobiaos.end()) {
                if (aaCenter.aa_item_zuobiaos[item->GetGUIDLow()].find(i) != aaCenter.aa_item_zuobiaos[item->GetGUIDLow()].end()) {
                    AA_Item_Zuobiao conf = aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][i];
                    if (conf.x || conf.y || conf.z || conf.o) {
                        std::string name = conf.area_name;
                        if (name == "") {
                            name = conf.map_name;
                        }
                        std::string msg = "传送坐标：\n" + name + "\n[map]：" + std::to_string(conf.map) + "\n[x]：" + std::to_string(conf.x) + "\n[y]：" + std::to_string(conf.y) + "\n[z]：" + std::to_string(conf.z);
                        AddGossipItemFor(player, GossipOptionNpc(0), name, GOSSIP_SENDER_MAIN, i, msg, 0, false);
                        isOk = false;
                    }
                }
            }
            if (isOk) {
                AddGossipItemFor(player, GossipOptionNpc(0), "[空]", GOSSIP_SENDER_MAIN, i, "点接受确认当前坐标。", 0, false);
            }
        }
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
        return true;
    }

    // Called when a player uses the item.
    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets, ObjectGuid /*castId*/) override {
        
        return ShowMenu(player, item); // Cast the spell on use normally
    }
    
    void OnGossipSelect(Player* player, Item* item, uint32 action, uint32 menuid) override
    {
        if (menuid == 999) {
            ShowMenu(player, item);
            return;
        }
        ItemTemplate const* pProto = item->GetTemplate();
        if (!pProto)
        {
            return;
        }
        if (aaCenter.aa_item_zuobiao_confs.find(pProto->GetId()) == aaCenter.aa_item_zuobiao_confs.end()) {
            return;
        }
        AA_Item_Zuobiao_Conf conf = aaCenter.aa_item_zuobiao_confs[pProto->GetId()];
        if (conf.count <= 0 || conf.count > 20) {
            return;
        }
        if (aaCenter.aa_item_zuobiaos.find(item->GetGUIDLow()) != aaCenter.aa_item_zuobiaos.end()) {
            if (aaCenter.aa_item_zuobiaos[item->GetGUIDLow()].find(menuid) != aaCenter.aa_item_zuobiaos[item->GetGUIDLow()].end()) {
                AA_Item_Zuobiao conf = aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid];
                if (conf.x || conf.y || conf.z || conf.o) {
                    std::string gm = ".组合 *.传送 " + std::to_string(conf.x) + " " + std::to_string(conf.y) + " " + std::to_string(conf.z) + " " + std::to_string(conf.map) + " " + std::to_string(conf.o) + " " + std::to_string(conf.nanduid) + "<$自身>";
                    aaCenter.AA_DoCommand(player, gm.c_str());
                    return;
                }
            }
        }
        if (conf.maps != "") {
            std::vector<int32> v; v.clear();
            aaCenter.AA_StringToVectorInt(conf.maps, v, ",");
            if (std::find(v.begin(), v.end(), player->GetMapId()) != v.end()) {
                aaCenter.AA_SendMessage(player, 1, "|cFF00FFFF[记|r|cFF00D9FF忆|r|cFF00B3FF传|r|cFF008DFF送|r|cFF00FFFF]|r|cffFFFF00当前地图禁止记忆传送!");
                ShowMenu(player, item);
                return;
            }
        }
        if (conf.zones != "") {
            std::vector<int32> v; v.clear();
            aaCenter.AA_StringToVectorInt(conf.zones, v, ",");
            if (std::find(v.begin(), v.end(), player->GetZoneId()) != v.end()) {
                aaCenter.AA_SendMessage(player, 1, "|cFF00FFFF[记|r|cFF00D9FF忆|r|cFF00B3FF传|r|cFF008DFF送|r|cFF00FFFF]|r|cffFFFF00当前区域Zone禁止记忆传送!");
                ShowMenu(player, item);
                return;
            }
        }
        if (conf.areas != "") {
            std::vector<int32> v; v.clear();
            aaCenter.AA_StringToVectorInt(conf.areas, v, ",");
            if (std::find(v.begin(), v.end(), player->GetAreaId()) != v.end()) {
                aaCenter.AA_SendMessage(player, 1, "|cFF00FFFF[记|r|cFF00D9FF忆|r|cFF00B3FF传|r|cFF008DFF送|r|cFF00FFFF]|r|cffFFFF00当前区域Area禁止记忆传送!");
                ShowMenu(player, item);
                return;
            }
        }

        Position pos = player->GetPosition();
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].guid = item->GetGUIDLow();
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].index = menuid;
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].itemEntry = pProto->GetId();
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].map = player->GetMapId();
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].zone = player->GetZoneId();
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].area = player->GetAreaId();
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].x = pos.m_positionX;
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].y = pos.m_positionY;
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].z = pos.m_positionZ;
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].o = pos.GetOrientation();
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].map_name = player->GetMap()->GetMapName();
        LocaleConstant locale = LOCALE_zhCN;
        AreaTableEntry const* areaEntry = sAreaTableStore.LookupEntry(player->GetAreaId());
        if (areaEntry)
        {
            aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].area_name = areaEntry->AreaName[locale];
        }
        if (player->GetMap() && player->GetMap()->IsDungeon()) {
            aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].nanduid = aaCenter.aa_minstancevalues[player->GetMap()->GetInstanceId()][3];
        }
        time_t timep;
        time(&timep); /*当前time_t类型UTC时间*/
        aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].update_time = timep;

        CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
        sAAData->AA_REP_Item_Zuobiao(item->GetGUIDLow(), menuid, trans);
        CharacterDatabase.CommitTransaction(trans);
        std::string msg = "";
        if (aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].area_name != "") {
            msg = "|cFF00FFFF[记|r|cFF00D9FF忆|r|cFF00B3FF传|r|cFF008DFF送|r|cFF00FFFF]|r坐标已记录：" + aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].area_name + "[map]：" + std::to_string(aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].map) + "[x]：" + std::to_string(aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].x) + "\n[y]：" + std::to_string(aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].y) + "[z]：" + std::to_string(aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].z);
        }
        else if (aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].map_name != "") {
            msg = "|cFF00FFFF[记|r|cFF00D9FF忆|r|cFF00B3FF传|r|cFF008DFF送|r|cFF00FFFF]|r坐标已记录：" + aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].map_name + "[map]：" + std::to_string(aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].map) + "[x]：" + std::to_string(aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].x) + "\n[y]：" + std::to_string(aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].y) + "[z]：" + std::to_string(aaCenter.aa_item_zuobiaos[item->GetGUIDLow()][menuid].z);
        }
        aaCenter.AA_SendMessage(player, 1, msg.c_str());

        ShowMenu(player, item);
    }
};

void AddAA_Item_Zuobiao()
{
    new aa_item_zuobiao();
}
