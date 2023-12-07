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
                        if (i == 0) {
                            std::string msg = "死亡位置：\n" + name + "\n[map]：" + std::to_string(conf.map) + "\n[x]：" + std::to_string(conf.x) + "\n[y]：" + std::to_string(conf.y) + "\n[z]：" + std::to_string(conf.z);
                            AddGossipItemFor(player, GossipOptionNpc(0), name, GOSSIP_SENDER_MAIN, i, msg, 0, false);
                        }
                        else {
                            std::string msg = "记忆位置：\n" + name + "\n[map]：" + std::to_string(conf.map) + "\n[x]：" + std::to_string(conf.x) + "\n[y]：" + std::to_string(conf.y) + "\n[z]：" + std::to_string(conf.z);
                            AddGossipItemFor(player, GossipOptionNpc(0), name, GOSSIP_SENDER_MAIN, i, msg, 0, false);
                        }
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
                    if (menuid == 0) {
                        if (aaCenter.aa_world_confs[109].value1 > 0) {
                            uint32 need = aaCenter.aa_world_confs[109].value1;
                            if (need > 0) {
                                if (aaCenter.M_CanNeed(player, need)) {
                                    aaCenter.M_Need(player, need);
                                }
                                else {
                                    return;
                                }
                            }
                        }
                    }
                    else {
                        if (aaCenter.aa_world_confs[109].value2 != "" && aaCenter.aa_world_confs[109].value2 != "0") {
                            uint32 need = aaCenter.AA_StringInt32(aaCenter.aa_world_confs[109].value2);
                            if (need > 0) {
                                if (aaCenter.M_CanNeed(player, need)) {
                                    aaCenter.M_Need(player, need);
                                }
                                else {
                                    return;
                                }
                            }
                        }
                    }
                    std::string gm = ".组合 *.传送 " + std::to_string(conf.x) + " " + std::to_string(conf.y) + " " + std::to_string(conf.z) + " " + std::to_string(conf.map) + " " + std::to_string(conf.o) + " " + std::to_string(conf.nanduid) + "<$自身>";
                    aaCenter.AA_DoCommand(player, gm.c_str());
                    return;
                }
            }
        }

        aaCenter.AA_ItemZuobiao_Save(player, pProto->GetId(), item->GetGUIDLow(), menuid);

        ShowMenu(player, item);
    }
};

void AddAA_Item_Zuobiao()
{
    new aa_item_zuobiao();
}
