#ifndef __CLY_AADATA_H__
#define __CLY_AADATA_H__

#include <iostream>
#include <stdint.h>
#include "World.h"
#include "DatabaseEnv.h"

using namespace std;

class Player;

class AAData
{
private:
    AAData(){};
    ~AAData(){};
public:
    void AA_SaveData();
    /*Character*/
    void AA_REP_Character_Juanxian(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans);
    void AA_UPD_Character_Paihang(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans);
    void AA_REP_Character_Instance(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans);
    void AA_REP_Characters(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans);
    void AA_REP_Characters_Dianfeng(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans);
    void AA_REP_Characters_Douqi(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans);
    void AA_REP_Characters_Junxian(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans);
    std::set<ObjectGuid::LowType> AA_REP_Character_Juanxians;
    std::set<ObjectGuid::LowType> AA_UPD_Character_Paihangs;
    std::set<ObjectGuid::LowType> AA_REP_Character_Instances;
    std::set<ObjectGuid::LowType> AA_REP_Characterss;
    std::set<ObjectGuid::LowType> AA_REP_Characters_Dianfengs;
    std::set<ObjectGuid::LowType> AA_REP_Characters_Douqis;
    std::set<ObjectGuid::LowType> AA_REP_Characters_Junxians;

    void AA_REP_Character_ZhanPet(uint32 id, CharacterDatabaseTransaction& trans);
    void AA_DEL_Character_ZhanPet(uint32 id, CharacterDatabaseTransaction& trans);
    std::set<ObjectGuid::LowType> AA_REP_Character_ZhanPets;
    
    void AA_REP_Player_Map_Value(ObjectGuid::LowType guidlow, int32 mapid, CharacterDatabaseTransaction& trans);
    void AA_REP_Player_Zone_Value(ObjectGuid::LowType guidlow, int32 mapid, CharacterDatabaseTransaction& trans);
    void AA_REP_Player_Area_Value(ObjectGuid::LowType guidlow, int32 mapid, CharacterDatabaseTransaction& trans);
    void AA_REP_Player_Instance_Value(ObjectGuid::LowType guidlow, int32 mapid, CharacterDatabaseTransaction& trans);
    std::map<ObjectGuid::LowType, std::set<int32>> AA_REP_Player_Map_Values;
    std::map<ObjectGuid::LowType, std::set<int32>> AA_REP_Player_Zone_Values;
    std::map<ObjectGuid::LowType, std::set<int32>> AA_REP_Player_Area_Values;
    std::map<ObjectGuid::LowType, std::set<int32>> AA_REP_Player_Instance_Values;
    
    void AA_REP_Map_Map_Value(int32 mapid, CharacterDatabaseTransaction& trans);
    void AA_REP_Map_Zone_Value(int32 mapid, CharacterDatabaseTransaction& trans);
    void AA_REP_Map_Area_Value(int32 mapid, CharacterDatabaseTransaction& trans);
    void AA_REP_Map_Instance_Value(int32 mapid, CharacterDatabaseTransaction& trans);
    std::set<int32> AA_REP_Map_Map_Values;
    std::set<int32> AA_REP_Map_Zone_Values;
    std::set<int32> AA_REP_Map_Area_Values;
    std::set<int32> AA_REP_Map_Instance_Values;

    void AA_REP_Item_Instance(ObjectGuid::LowType guidlow, CharacterDatabaseTransaction& trans);
    std::set<ObjectGuid::LowType> AA_REP_Item_Instances;

    void AA_REP_Item_Zuobiao(ObjectGuid::LowType guidlow, uint32 index, CharacterDatabaseTransaction& trans);

    void AA_REP_Character_Hongbao(uint32 id, CharacterDatabaseTransaction& trans);
    std::set<int32> AA_REP_Character_Hongbaos;

    void AA_REP_Systems(CharacterDatabaseTransaction& trans);
    
    /*Account*/
    void AA_REP_Account(uint32 accountid, LoginDatabaseTransaction& trans);
    std::set<uint32> AA_REP_Accounts;

    
    static AAData* instance();
};

#define sAAData AAData::instance()

#endif
