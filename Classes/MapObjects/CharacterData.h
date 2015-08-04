//
//  CharacterData.h
//  LastSupper
//
//  Created by Kohei on 2015/08/03.
//
//

#ifndef __CHARACTER_DATA_H__
#define __CHARACTER_DATA_H__

#include "define.h"

namespace CharacterData {
	// 列挙型
	enum struct DataType
	{
		TexturePrefix,
		Name,
		SIZE,
	};
	
	// 変数
	map<int, vector<string>> datas =
	{
		{0, {"magoichi", "孫一"}},
		{1, {"nadeshiko", "撫子"}},
	};
}

#endif // __CHARACTER_DATA_H__
