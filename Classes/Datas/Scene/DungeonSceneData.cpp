//
//  DungeonSceneData.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/23.
//
//

#include "Datas/Scene/DungeonSceneData.h"

// コンストラクタ
DungeonSceneData::DungeonSceneData(){FUNCLOG}

// デストラクタ
DungeonSceneData::~DungeonSceneData(){FUNCLOG}

// 初期化
bool DungeonSceneData::init(const string& mapName)
{
	FUNCLOG
	
	this->mapName = mapName;
	this->fu = FileUtils::getInstance();
	
	FILE* fp;
	char buf[512];
	
	//ファイルパス
	string path = this->fu->fullPathForFilename("event/" + mapName + ".json");
	const char* cstr = path.c_str();
	
	//JSONファイルを読み込んでインスタンス変数jsonに格納
	fp = fopen(cstr, "rb");
	FileReadStream rs(fp, buf, sizeof(buf));
	this->json.ParseStream(rs);
	fclose(fp);
	
	//JSONの文法エラーチェック
	bool error = this->json.HasParseError();
	
	if(error){
		//エラーがあった場合
		size_t offset = this->json.GetErrorOffset();
		ParseErrorCode code = this->json.GetParseError();
		const char* msg = GetParseError_En(code);
		printf("JSON Parse Error : %d:%d(%s)\n", static_cast<int>(offset), code, msg);
		return false;
	} else {
		//エラーがなかった場合
#ifdef DEBUG
		//テスト出力
		ifstream filein(path);
		for (string line; getline(filein, line);)
		{
			cout << line << endl;
		}
#endif
	}
	
	// プリロード用リストを取得
	this->soundFilePaths = this->getPreLoadList("sound");
	this->textureFilePaths = this->getPreLoadList("texture");
	
	this->textureFilePaths.push_back("frame");
	
	return true;
}

//リソースのプリロード関数
vector<string> DungeonSceneData::getPreLoadList(const string& type){
	vector<string> list;
	const char* typec = type.c_str();
	rapidjson::Value& obj = this->json[typec];
	SizeType len = obj.Size();
	for(int i=0;i<len;i++){
		list.push_back(obj[i].GetString());
	}
	return list;
}