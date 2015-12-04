//
//  GlobalPlayerData.h
//  LastSupper
//
//  Created by Ryoya Ino on 2015/12/04.
//
//

#ifndef GlobalPlayerData_h
#define GlobalPlayerData_h

#include "define.h"

class GlobalPlayerData : public Ref
{
    // path
    static const string GLOBAL_DATA_PATH;
    static const string GLOBAL_TEMPLATE_PATH;
    
    // Save data member
    static const char* STATUS;
    static const char* GLOBAL_ID;
    static const char* CLEAR_COUNT;
    static const char* BEST_SAVE_COUNT;
    static const char* BEST_CLEAR_TIME;
    static const char* TROPHY;
    static const char* TOKENS;
    
    // Record
    static const int CHIKEN_SAVE_COUNT;
    static const int FAST_CLEAR_TIME;
    
public:
    CREATE_FUNC(GlobalPlayerData)
private:
    GlobalPlayerData(){FUNCLOG}
    ~GlobalPlayerData(){FUNCLOG}
// Instance valiables
private:
    rapidjson::Document globalData {nullptr};

// Instance methods
private:
    bool init();
    
public:
    // Global data file
    bool loadGlobalData();
    bool initGlobalData();
    void saveGlobalData();
    
    // Clear count
    void setClearCount(const string& token);
    int getClearCount();
    bool isCleared();
    
    // Minimum save count
    void setBestSaveCount(const int save_count);
    int getBestSaveCount();
    
    // Best clear time
    void setBestClearTime(const int play_time);
    int getBestClearTimeSecound();
    
    // Trophy data
    void setTrophy(const int trophy_id);
    bool hasTrophy(const int trophy_id);
    
    // Clear token
    bool isClearedToken(const string& token);
    void setClearToken(const string& token);
    
};

#endif /* GlobalPlayerData_h */
