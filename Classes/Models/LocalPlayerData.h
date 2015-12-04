//
//  LocalPlayerData.h
//  LastSupper
//
//  Created by Ryoya Ino on 2015/12/04.
//
//

#ifndef LocalPlayerData_h
#define LocalPlayerData_h

#include "define.h"

class LocalPlayerData : public Ref
{
public:
    CREATE_FUNC(LocalPlayerData)
private:
    LocalPlayerData(){FUNCLOG};
    ~LocalPlayerData(){FUNCLOG};
    
private:
    bool init();
};

#endif /* LocalPlayerData_h */
