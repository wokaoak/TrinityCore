#include "AAData.h"
#include "Player.h"


AAData* AAData::instance()
{
    static AAData instance;
    return &instance;
}
void AAData::AA_UPD_Character_Paihang(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans)
{
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_UPD_Character_Paihang_Jisha);
        stmt->setUInt32(0, aaCenter.aa_jishas[guidlow]);
        stmt->setUInt64(1, guidlow);
        trans->Append(stmt);
    }
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_UPD_Character_Paihang_Renwu);
        stmt->setUInt32(0, aaCenter.aa_renwus[guidlow]);
        stmt->setUInt64(1, guidlow);
        trans->Append(stmt);
    }
    {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_UPD_Character_Paihang_Hongbao);
        stmt->setUInt32(0, aaCenter.aa_hongbaos[guidlow]);
        stmt->setUInt64(1, guidlow);
        trans->Append(stmt);
    }
}
void AAData::AA_REP_Character_Instance(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans)
{
    AA_Character_Instance conf = aaCenter.aa_character_instances[guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Character_Instance);
    uint32 i = 0;
    stmt->setUInt64(i++, guidlow);
    stmt->setUInt32(i++, conf.itemEntry);
    stmt->setUInt64(i++, conf.owner_guid);
    stmt->setString(i++, conf.name);
    stmt->setUInt32(i++, conf.fugai_zu);
    stmt->setString(i++, conf.fugai);
    stmt->setUInt32(i++, conf.jd_zu);
    stmt->setUInt32(i++, conf.jd_id);
    stmt->setUInt32(i++, conf.jd_level);
    stmt->setString(i++, conf.jd_values);
    stmt->setUInt32(i++, conf.qh_zu);
    stmt->setUInt32(i++, conf.qh_id);
    stmt->setUInt32(i++, conf.qh_level);
    stmt->setString(i++, conf.qh_values);
    stmt->setUInt32(i++, conf.qh_reward_value);
    stmt->setUInt32(i++, conf.qh_reward_point);
    stmt->setString(i++, conf.qh_reward_spell);
    stmt->setUInt32(i++, conf.cz_zu);
    stmt->setUInt32(i++, conf.cz_id);
    stmt->setUInt32(i++, conf.cz_level);
    stmt->setUInt32(i++, conf.cz_exp);
    stmt->setString(i++, conf.cz_values);
    stmt->setUInt32(i++, conf.cz_reward_value);
    stmt->setUInt32(i++, conf.cz_reward_point);
    stmt->setString(i++, conf.cz_reward_spell);
    stmt->setUInt32(i++, conf.fm_spell_count);
    stmt->setString(i++, conf.fm_spells);
    stmt->setString(i++, conf.fm_spell_suodings);
    stmt->setUInt32(i++, conf.fm_value_count);
    stmt->setString(i++, conf.fm_values);
    stmt->setString(i++, conf.fm_value_suodings);
    stmt->setUInt32(i++, conf.chongzhu_count);
    stmt->setUInt32(i++, conf.chongzhu_value);
    stmt->setUInt32(i++, conf.chongzhu_spell);
    stmt->setUInt32(i++, conf.fw_count);
    stmt->setString(i++, conf.fw_values);
    stmt->setString(i++, conf.fwzh_values);
    stmt->setInt32(i++, conf.cuiqu_pos);
    stmt->setUInt32(i++, conf.baoshi_entry);
    stmt->setUInt32(i++, conf.item_set);
    stmt->setUInt64(i++, conf.zulin_time);
    stmt->setUInt32(i++, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Character_ZhanPet(uint32 id, CharacterDatabaseTransaction& trans)
{
    //ObjectGuid::LowType guidlow = player->GetGUIDLow();
    //for (auto iter : aaCenter.aa_character_petzhans) {
    //    AA_Character_ZhanPet conf = iter.second;
    //    if (!conf.isUpdate || guidlow != conf.owner_guid) {
    //        continue;
    //    }
    //    aaCenter.aa_character_zhanpets[iter.first].isUpdate = false;
    //    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Character_ZhanPet);
    //    int i = 0;
    //    stmt->SetData(i++, iter.first);//`guid` int unsigned NOT NULL DEFAULT '0',
    //    stmt->SetData(i++, conf.itemEntry);//`itemEntry` int unsigned NOT NULL DEFAULT '0',
    //    stmt->SetData(i++, conf.owner_guid);//
    //    stmt->SetData(i++, conf.displayid);//模型生物id
    //    stmt->SetData(i++, conf.level);//等级
    //    stmt->SetData(i++, conf.exp);//经验
    //    stmt->SetData(i++, conf.dianshu_all);//总点数
    //    stmt->SetData(i++, conf.dianshu);//消耗点数
    //    stmt->SetData(i++, conf.value);//属性值
    //    stmt->SetData(i++, conf.nonsuch_id);//鉴定id
    //    stmt->SetData(i++, conf.gongji);
    //    stmt->SetData(i++, conf.fali);
    //    stmt->SetData(i++, conf.tili);
    //    stmt->SetData(i++, conf.fangyu);
    //    stmt->SetData(i++, conf.update_time);//`update_time` int NOT NULL DEFAULT '1',
    //    trans->Append(stmt);
    //}
    AA_Character_PetZhan conf = aaCenter.aa_character_petzhans[id];
    if (conf.owner_guid > 0) {
        CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Character_ZhanPet);
        int i = 0;
        stmt->setUInt32(i++, conf.id);// = 0;//id
        stmt->setUInt32(i++, conf.owner_guid);// = 0;//owner_guid
        stmt->setUInt32(i++, conf.pet_id);// = 0;//宠物id
        stmt->setUInt32(i++, conf.level);// = 0;//宠物等级
        stmt->setUInt32(i++, conf.exp);// = 0;//宠物经验
        stmt->setUInt32(i++, conf.pet_level_zu);// = 0;//等级组
        stmt->setFloat(i++, conf.chengzhang);// = 0;//成长
        stmt->setFloat(i++, conf.qihe);// = 0;//契合
        stmt->setFloat(i++, conf.jicheng);// = 0;//继承
        stmt->setUInt32(i++, conf.health);// = 0;//生命
        stmt->setUInt32(i++, conf.shanghai);// = 0;//伤害
        stmt->setUInt32(i++, conf.fashu);// = 0;//法术
        stmt->setUInt32(i++, conf.zhiliao);// = 0;//治疗
        stmt->setUInt32(i++, conf.hujia);// = 0;//护甲
        stmt->setString(i++, conf.spell_pet);// = "";//宠物技能
        stmt->setString(i++, conf.spell_owner);// = "";//主人技能
        stmt->setUInt32(i++, conf.is_chuzhan);// = 0;//已出战
        stmt->setUInt32(i++, conf.is_heti);// = 0;//已出战
        stmt->setUInt32(i++, conf.update_time);// = 0;
        trans->Append(stmt);
    }
}
void AAData::AA_DEL_Character_ZhanPet(uint32 id, CharacterDatabaseTransaction& trans)
{
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_DEL_Character_ZhanPet);
    stmt->setUInt32(0, id);// = 0;//id
    trans->Append(stmt);
}
void AAData::AA_REP_Characters(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans)
{
    AA_Characters conf = aaCenter.aa_characterss[guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Characters);
    stmt->setUInt64(0, guidlow);
    stmt->setUInt32(1, conf.playtime);
    stmt->setString(2, conf.shengji);
    stmt->setUInt32(3, conf.tianfu);
    stmt->setUInt32(4, conf.choujiang);
    stmt->setUInt32(5, conf.choujianglq);
    stmt->setString(6, conf.buy_time);
    stmt->setString(7, conf.buy_time_yj);
    stmt->setString(8, conf.zhaomu);
    stmt->setString(9, conf.diy_guid);
    stmt->setString(10, conf.name_pre);
    stmt->setString(11, conf.name_suf);
    stmt->setUInt32(12, conf.duel_diy);
    stmt->setUInt32(13, conf.yiming);
    stmt->setUInt32(14, conf.is_yiming);
    stmt->setString(15, conf.huoyues);
    stmt->setString(16, conf.huoyue_jindus);
    stmt->setString(17, conf.huoyue_jindu_status);
    stmt->setUInt32(18, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Character_Juanxian(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans)
{
    AA_Character_Juanxian conf = aaCenter.aa_character_juanxians[guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Character_Juanxian);
    stmt->setUInt64(0, guidlow);
    stmt->setString(1, conf.name);
    stmt->setUInt32(2, conf.juanxian);
    stmt->setUInt32(3, conf.juanxian_zhou);
    stmt->setUInt32(4, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Systems(CharacterDatabaseTransaction& trans)
{
    AA_System conf = aaCenter.aa_system_conf;
    if (!conf.isUpdate) {
        return;
    }
    aaCenter.aa_system_conf.isUpdate = false;
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Systems);
    stmt->setUInt32(0, 0);
    stmt->setString(1, conf.diy_system);
    stmt->setUInt32(2, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Characters_Dianfeng(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans)
{
    AA_Characters_Dianfeng conf = aaCenter.aa_characters_dianfengs[guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Characters_Dianfeng);
    stmt->setUInt64(0, guidlow);
    stmt->setUInt32(1, conf.level);
    stmt->setUInt32(2, conf.exp);
    stmt->setUInt32(3, conf.dianshu_all);
    stmt->setInt32(4, conf.dianshu);
    stmt->setUInt32(5, conf.tianfu);
    stmt->setString(6, conf.value);
    stmt->setUInt32(7, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Characters_Douqi(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans)
{
    AA_Characters_Douqi conf = aaCenter.aa_characters_douqis[guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Characters_Douqi);
    stmt->setUInt64(0, guidlow);
    stmt->setUInt32(1, conf.level);
    stmt->setUInt32(2, conf.exp);
    stmt->setUInt32(3, conf.dianshu_all);
    stmt->setInt32(4, conf.dianshu);
    stmt->setUInt32(5, conf.tianfu);
    stmt->setString(6, conf.value);
    stmt->setUInt32(7, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Characters_Junxian(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans)
{
    AA_Characters_Junxian conf = aaCenter.aa_characters_junxians[guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Characters_Junxian);
    stmt->setUInt64(0, guidlow);
    stmt->setUInt32(1, conf.level);
    stmt->setUInt32(2, conf.exp);
    stmt->setUInt32(3, conf.dianshu_all);
    stmt->setInt32(4, conf.dianshu);
    stmt->setUInt32(5, conf.tianfu);
    stmt->setString(6, conf.value);
    stmt->setUInt32(7, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Account(uint32 accountid, LoginDatabaseTransaction& trans)
{
    AA_Account conf = aaCenter.aa_accounts[accountid];
    LoginDatabasePreparedStatement* stmt = LoginDatabase.GetPreparedStatement(_AA_REP_Account);
    int i = 0;
    stmt->setUInt64(i++, accountid);
    stmt->setUInt32(i++, conf.vip);
    stmt->setUInt32(i++, conf.jifen);
    stmt->setUInt32(i++, conf.jifen_cz);
    stmt->setUInt32(i++, conf.jifen_all);
    stmt->setUInt32(i++, conf.paodian);
    stmt->setUInt32(i++, conf.mobi);
    stmt->setUInt32(i++, conf.battlecore);
    stmt->setUInt32(i++, conf.jifen_day);
    stmt->setUInt32(i++, conf.shouchong_day);
    stmt->setUInt32(i++, conf.shouchong);
    stmt->setString(i++, conf.leichong);
    stmt->setUInt32(i++, conf.denglu_day);
    stmt->setString(i++, conf.denglu);
    stmt->setUInt32(i++, conf.denglu_qiandao);
    stmt->setUInt32(i++, conf.licai_day);
    stmt->setUInt32(i++, conf.licai);
    stmt->setString(i++, conf.buy_time);
    stmt->setString(i++, conf.buy_time_yj);
    stmt->setString(i++, conf.diy_account);
    stmt->setUInt32(i++, conf.dianka);
    stmt->setUInt32(i++, conf.update_time);

    stmt->setUInt32(i++, conf.vip);
    stmt->setUInt32(i++, conf.jifen);
    stmt->setUInt32(i++, conf.jifen_all);
    stmt->setUInt32(i++, conf.paodian);
    stmt->setUInt32(i++, conf.mobi);
    stmt->setUInt32(i++, conf.battlecore);
    stmt->setUInt32(i++, conf.jifen_day);
    stmt->setUInt32(i++, conf.shouchong_day);
    stmt->setUInt32(i++, conf.shouchong);
    stmt->setString(i++, conf.leichong);
    stmt->setUInt32(i++, conf.denglu_day);
    stmt->setString(i++, conf.denglu);
    stmt->setUInt32(i++, conf.denglu_qiandao);
    stmt->setUInt32(i++, conf.licai_day);
    stmt->setUInt32(i++, conf.licai);
    stmt->setString(i++, conf.buy_time);
    stmt->setString(i++, conf.buy_time_yj);
    stmt->setString(i++, conf.diy_account);
    stmt->setUInt32(i++, conf.dianka);
    stmt->setUInt32(i++, conf.update_time);
    trans->Append(stmt);
}

void AAData::AA_REP_Player_Map_Value(ObjectGuid::LowType guidlow, int32 mapid, CharacterDatabaseTransaction& trans)
{
    AA_Player_Map_Value conf = aaCenter.aa_player_map_values[mapid][guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Player_Map_Value);
    stmt->setUInt64(0, guidlow);
    stmt->setInt32(1, mapid);
    stmt->setString(2, conf.valueb);
    stmt->setString(3, conf.valuev);
    stmt->setUInt32(4, conf.update_time);
    stmt->setString(5, conf.valueb);
    stmt->setString(6, conf.valuev);
    stmt->setUInt32(7, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Player_Zone_Value(ObjectGuid::LowType guidlow, int32 mapid, CharacterDatabaseTransaction& trans)
{
    AA_Player_Zone_Value conf = aaCenter.aa_player_zone_values[mapid][guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Player_Zone_Value);
    stmt->setUInt64(0, guidlow);
    stmt->setInt32(1, mapid);
    stmt->setString(2, conf.valueb);
    stmt->setString(3, conf.valuev);
    stmt->setUInt32(4, conf.update_time);
    stmt->setString(5, conf.valueb);
    stmt->setString(6, conf.valuev);
    stmt->setUInt32(7, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Player_Area_Value(ObjectGuid::LowType guidlow, int32 mapid, CharacterDatabaseTransaction& trans)
{
    AA_Player_Area_Value conf = aaCenter.aa_player_area_values[mapid][guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Player_Area_Value);
    stmt->setUInt64(0, guidlow);
    stmt->setInt32(1, mapid);
    stmt->setString(2, conf.valueb);
    stmt->setString(3, conf.valuev);
    stmt->setUInt32(4, conf.update_time);
    stmt->setString(5, conf.valueb);
    stmt->setString(6, conf.valuev);
    stmt->setUInt32(7, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Player_Instance_Value(ObjectGuid::LowType guidlow, int32 mapid, CharacterDatabaseTransaction& trans)
{
    AA_Player_Instance_Value conf = aaCenter.aa_player_instance_values[mapid][guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Player_Instance_Value);
    stmt->setUInt64(0, guidlow);
    stmt->setInt32(1, mapid);
    stmt->setString(2, conf.valueb);
    stmt->setString(3, conf.valuev);
    stmt->setUInt32(4, conf.update_time);
    stmt->setString(5, conf.valueb);
    stmt->setString(6, conf.valuev);
    stmt->setUInt32(7, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Map_Map_Value(int32 mapid, CharacterDatabaseTransaction& trans)
{
    AA_Map_Map_Value conf = aaCenter.aa_map_map_values[mapid];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Map_Map_Value);
    stmt->setUInt64(0, mapid);
    stmt->setString(1, conf.valueb);
    stmt->setString(2, conf.valuev);
    stmt->setUInt32(3, conf.update_time);
    stmt->setString(4, conf.valueb);
    stmt->setString(5, conf.valuev);
    stmt->setUInt32(6, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Map_Zone_Value(int32 mapid, CharacterDatabaseTransaction& trans)
{
    AA_Map_Zone_Value conf = aaCenter.aa_map_zone_values[mapid];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Map_Zone_Value);
    stmt->setUInt64(0, mapid);
    stmt->setString(1, conf.valueb);
    stmt->setString(2, conf.valuev);
    stmt->setUInt32(3, conf.update_time);
    stmt->setString(4, conf.valueb);
    stmt->setString(5, conf.valuev);
    stmt->setUInt32(6, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Map_Area_Value(int32 mapid, CharacterDatabaseTransaction& trans)
{
    AA_Map_Area_Value conf = aaCenter.aa_map_area_values[mapid];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Map_Area_Value);
    stmt->setUInt64(0, mapid);
    stmt->setString(1, conf.valueb);
    stmt->setString(2, conf.valuev);
    stmt->setUInt32(3, conf.update_time);
    stmt->setString(4, conf.valueb);
    stmt->setString(5, conf.valuev);
    stmt->setUInt32(6, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Map_Instance_Value(int32 mapid, CharacterDatabaseTransaction& trans)
{
    //for (auto iter : aaCenter.aa_map_instance_values) {
    //    AA_Map_Instance_Value conf = iter.second;
    //    if (!conf.isUpdate) {
    //        continue;
    //    }
    //    aaCenter.aa_map_instance_values[iter.first].isUpdate = false;
    //    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Map_Instance_Value);
    //    stmt->SetData(0, iter.first);
    //    stmt->SetData(1, conf.valueb);
    //    stmt->SetData(2, conf.valuev);
    //    stmt->SetData(3, conf.update_time);
    //    stmt->SetData(4, conf.valueb);
    //    stmt->SetData(5, conf.valuev);
    //    stmt->SetData(6, conf.update_time);
    //    trans->Append(stmt);
    //}

    AA_Map_Instance_Value conf = aaCenter.aa_map_instance_values[mapid];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Map_Instance_Value);
    stmt->setUInt64(0, mapid);
    stmt->setString(1, conf.valueb);
    stmt->setString(2, conf.valuev);
    stmt->setUInt32(3, conf.update_time);
    stmt->setString(4, conf.valueb);
    stmt->setString(5, conf.valuev);
    stmt->setUInt32(6, conf.update_time);
    trans->Append(stmt);
}
void AAData::AA_REP_Item_Instance(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans)
{
    AA_Item_Instance conf = aaCenter.aa_item_instances[guidlow];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Item_Instance);
    stmt->setUInt64(0, conf.guid);
    stmt->setUInt32(1, conf.itemEntry);
    stmt->setUInt64(2, conf.owner_guid);
    stmt->setUInt64(3, conf.creatorGuid);
    stmt->setUInt64(4, conf.giftCreatorGuid);
    stmt->setUInt32(5, conf.count);
    stmt->setUInt32(6, conf.duration);
    stmt->setString(7, conf.charges);
    stmt->setUInt32(8, conf.flags);
    stmt->setString(9, conf.enchantments);
    stmt->setUInt32(10, conf.randomBonusListId);
    stmt->setUInt32(11, conf.durability);
    stmt->setUInt32(12, conf.playedTime);
    stmt->setString(13, conf.text);
    stmt->setUInt32(14, conf.transmogrification);
    stmt->setUInt32(15, conf.enchantIllusion);
    stmt->setUInt32(16, conf.battlePetSpeciesId);
    stmt->setUInt32(17, conf.battlePetBreedData);
    stmt->setUInt16(18, conf.battlePetLevel);
    stmt->setUInt32(19, conf.battlePetDisplayId);
    stmt->setUInt8(20, conf.context);
    stmt->setString(21, conf.bonusListIDs);
    stmt->setString(22, conf.weizhi);
    stmt->setUInt32(23, conf.update_time);
    trans->Append(stmt);
}

void AAData::AA_REP_Item_Zuobiao(ObjectGuid::LowType guidlow, uint32 index, CharacterDatabaseTransaction& trans)
{
    AA_Item_Zuobiao conf = aaCenter.aa_item_zuobiaos[guidlow][index];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Item_Zuobiao);
    stmt->setUInt32(0, conf.guid);//= 0;//` int(10) unsigned NOT NULL DEFAULT '0',
    stmt->setUInt32(1, conf.index);//= 0;//` int(10) unsigned NOT NULL DEFAULT '0',
    stmt->setUInt32(2, conf.itemEntry);//= 0;//` int(10) unsigned NOT NULL DEFAULT '0',
    stmt->setString(3, conf.map_name);//= "";//` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
    stmt->setString(4, conf.area_name);//= "";//` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '',
    stmt->setInt32(5, conf.map);//= 0;//` int(10) unsigned NOT NULL DEFAULT '0',
    stmt->setInt32(6, conf.zone);//= 0;//` int(10) unsigned NOT NULL DEFAULT '0',
    stmt->setInt32(7, conf.area);//= 0;//` int(10) unsigned NOT NULL DEFAULT '0',
    stmt->setFloat(8, conf.x);//= 0;//` float NOT NULL DEFAULT '0',
    stmt->setFloat(9, conf.y);//= 0;//` float NOT NULL DEFAULT '0',
    stmt->setFloat(10, conf.z);//= 0;//` float NOT NULL DEFAULT '0' COMMENT '品质id',
    stmt->setFloat(11, conf.o);//= 0;//` float NOT NULL DEFAULT '0',
    stmt->setUInt32(12, conf.nanduid);//= 0;
    stmt->setUInt32(13, conf.update_time);//= 0;//` int(11) unsigned NOT NULL DEFAULT '0',
    trans->Append(stmt);
}
void AAData::AA_REP_Character_Hongbao(uint32 id, CharacterDatabaseTransaction& trans)
{
    AA_Character_Hongbao conf = aaCenter.aa_character_hongbaos[id];
    CharacterDatabasePreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(_AA_REP_Character_Hongbao);
    int i = 0;
    stmt->setUInt32(i++, conf.id);// = 0;//id
    stmt->setUInt32(i++, conf.account);// = 0;//account
    stmt->setUInt32(i++, conf.guid);// = 0;//guid
    stmt->setString(i++, conf.name);// = "";//玩家姓名
    stmt->setUInt32(i++, conf.fangshi);// = 0;//发放方式
    stmt->setUInt32(i++, conf.type);// = 0;//红包类型
    stmt->setUInt32(i++, conf.money_all);// = 0;//红包金额
    stmt->setUInt32(i++, conf.money);// = 0;//红包剩余金额
    stmt->setUInt32(i++, conf.count_all);// = 0;//红包总数量
    stmt->setUInt32(i++, conf.count);// = 0;//红包剩余数量
    stmt->setString(i++, conf.text);// = "";//红包描述
    stmt->setString(i++, conf.lq_count);// = "";//红包领取数量
    stmt->setString(i++, conf.lq_guids);// = "";//红包领取玩家
    stmt->setUInt32(i++, conf.update_time);// = 0;
    trans->Append(stmt);
}

void AAData::AA_SaveData()
{
    {
        CharacterDatabaseTransaction trans = CharacterDatabase.BeginTransaction();
        if (AA_REP_Character_Juanxians.size() > 0) {
            for (auto itr : AA_REP_Character_Juanxians) {
                AA_REP_Character_Juanxian(itr, trans);
            }
            AA_REP_Character_Juanxians.clear();
        }
        if (AA_UPD_Character_Paihangs.size() > 0) {
            for (auto itr : AA_UPD_Character_Paihangs) {
                AA_UPD_Character_Paihang(itr, trans);
            }
            AA_UPD_Character_Paihangs.clear();
        }
        if (AA_REP_Character_Instances.size() > 0) {
            for (auto itr : AA_REP_Character_Instances) {
                AA_REP_Character_Instance(itr, trans);
            }
            AA_REP_Character_Instances.clear();
        }
        if (AA_REP_Characterss.size() > 0) {
            for (auto itr : AA_REP_Characterss) {
                AA_REP_Characters(itr, trans);
            }
            AA_REP_Characterss.clear();
        }
        if (AA_REP_Characters_Dianfengs.size() > 0) {
            for (auto itr : AA_REP_Characters_Dianfengs) {
                AA_REP_Characters_Dianfeng(itr, trans);
            }
            AA_REP_Characters_Dianfengs.clear();
        }
        if (AA_REP_Characters_Douqis.size() > 0) {
            for (auto itr : AA_REP_Characters_Douqis) {
                AA_REP_Characters_Douqi(itr, trans);
            }
            AA_REP_Characters_Douqis.clear();
        }
        if (AA_REP_Characters_Junxians.size() > 0) {
            for (auto itr : AA_REP_Characters_Junxians) {
                AA_REP_Characters_Junxian(itr, trans);
            }
            AA_REP_Characters_Junxians.clear();
        }
        if (AA_REP_Character_ZhanPets.size() > 0) {
            for (auto itr : AA_REP_Character_ZhanPets) {
                AA_REP_Character_ZhanPet(itr, trans);
            }
            AA_REP_Character_ZhanPets.clear();
        }


        if (AA_REP_Player_Map_Values.size() > 0) {
            for (auto itr : AA_REP_Player_Map_Values) {
                ObjectGuid::LowType guidlow = itr.first;
                for (auto mapid : itr.second) {
                    AA_REP_Player_Map_Value(guidlow, mapid, trans);
                }
            }
            AA_REP_Player_Map_Values.clear();
        }
        if (AA_REP_Player_Zone_Values.size() > 0) {
            for (auto itr : AA_REP_Player_Zone_Values) {
                ObjectGuid::LowType guidlow = itr.first;
                for (auto mapid : itr.second) {
                    AA_REP_Player_Zone_Value(guidlow, mapid, trans);
                }
            }
            AA_REP_Player_Zone_Values.clear();
        }
        if (AA_REP_Player_Area_Values.size() > 0) {
            for (auto itr : AA_REP_Player_Area_Values) {
                ObjectGuid::LowType guidlow = itr.first;
                for (auto mapid : itr.second) {
                    AA_REP_Player_Area_Value(guidlow, mapid, trans);
                }
            }
            AA_REP_Player_Area_Values.clear();
        }
        if (AA_REP_Player_Instance_Values.size() > 0) {
            for (auto itr : AA_REP_Player_Instance_Values) {
                ObjectGuid::LowType guidlow = itr.first;
                for (auto mapid : itr.second) {
                    AA_REP_Player_Instance_Value(guidlow, mapid, trans);
                }
            }
            AA_REP_Player_Instance_Values.clear();
        }

        if (AA_REP_Map_Map_Values.size() > 0) {
            for (auto itr : AA_REP_Map_Map_Values) {
                AA_REP_Map_Map_Value(itr, trans);
            }
            AA_REP_Map_Map_Values.clear();
        }
        if (AA_REP_Map_Zone_Values.size() > 0) {
            for (auto itr : AA_REP_Map_Zone_Values) {
                AA_REP_Map_Zone_Value(itr, trans);
            }
            AA_REP_Map_Zone_Values.clear();
        }
        if (AA_REP_Map_Area_Values.size() > 0) {
            for (auto itr : AA_REP_Map_Area_Values) {
                AA_REP_Map_Area_Value(itr, trans);
            }
            AA_REP_Map_Area_Values.clear();
        }
        if (AA_REP_Map_Instance_Values.size() > 0) {
            for (auto itr : AA_REP_Map_Instance_Values) {
                AA_REP_Map_Instance_Value(itr, trans);
            }
            AA_REP_Map_Instance_Values.clear();
        }

        if (AA_REP_Item_Instances.size() > 0) {
            for (auto itr : AA_REP_Item_Instances) {
                AA_REP_Item_Instance(itr, trans);
            }
            AA_REP_Item_Instances.clear();
        }

        if (AA_REP_Character_Hongbaos.size() > 0) {
            for (auto itr : AA_REP_Character_Hongbaos) {
                AA_REP_Character_Hongbao(itr, trans);
            }
            AA_REP_Character_Hongbaos.clear();
        }

        AA_REP_Systems(trans);
        CharacterDatabase.CommitTransaction(trans);
    }

    {
        LoginDatabaseTransaction trans = LoginDatabase.BeginTransaction();
        if (AA_REP_Accounts.size() > 0) {
            for (auto itr : AA_REP_Accounts) {
                AA_REP_Account(itr, trans);
            }
            AA_REP_Accounts.clear();
        }
        LoginDatabase.CommitTransaction(trans);
    }
}
