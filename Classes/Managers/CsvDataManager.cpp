//
//  CsvDataManager.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/09/13.
//
//

#include "Managers/CsvDataManager.h"

// 唯一のインスタンスを初期化
static CsvDataManager* _instance = nullptr;

const map<CsvDataManager::DataType, string> CsvDataManager::file_type = {
    {CsvDataManager::DataType::MAP, "map"},
    {CsvDataManager::DataType::ITEM, "item"},
    {CsvDataManager::DataType::CHARACTER, "character"},
    {CsvDataManager::DataType::CHAPTER, "chapter"}
};

// インスタンスの生成&取得
CsvDataManager* CsvDataManager::getInstance()
{
    if(!_instance) _instance = new CsvDataManager();
    return _instance;
}

// インスタンスの消去
void CsvDataManager::destroy()
{
    delete _instance;
}

// デストラクタ
CsvDataManager::~CsvDataManager()
{FUNCLOG}

// コンストラクタ
CsvDataManager::CsvDataManager():fu(FileUtils::getInstance())
{
    FUNCLOG
    //各CSVデータの取得
    for(auto itr:this->file_type)
    {
        this->csv_data[itr.first] = this->readCsvFile(itr.second);
    }
}

//CSV読み取り
map<int, vector<string>> CsvDataManager::readCsvFile(string file_name)
{
    //ファイル読み込み
    ifstream file(this->fu->fullPathForFilename("csv/" + file_name + ".csv"));
    map<int, vector<string>> values;
    string str;
    int p, i, data_id;
    //ファイル読み込み失敗時
    if(file.fail()){
        CCLOG("Reading csv file of %s is failed.", file_name.c_str());
        return values;
    }
    //csvデータ格納
    while(getline(file, str)){
        //コメント箇所は除く
        if( (p = str.find("//")) != str.npos ) continue;
        vector<string> inner;
        i = 0;
        //カンマがあるかを探し、そこまでをvaluesに格納
        while( (p = str.find(",")) != str.npos ){
            if (i == 0)
            {
                data_id = stoi(str.substr(0, p));
            }
            inner.push_back(str.substr(0, p));
            //strの中身は","の1文字を飛ばす
            str = str.substr(p+1);
            i++;
        }
        inner.push_back(str);
        //values.push_back(inner);
        values[data_id] = inner;
    }
#ifdef DEBUG
    // デバッグ用出力
    cout << "Read csv file >> " << file_name << ".csv" << endl;
    string line;
    for (auto itr: values)
    {
        line = "";
        for(string str: itr.second)
        {
            line += str + ",";
        }
        //CCLOG(line.c_str());
    }
#endif
    return values;
}

#pragma mark -
#pragma mark Map

// マップ名を取得
string CsvDataManager::getMapName(const int map_id)
{
    return this->csv_data[DataType::MAP][map_id][1];
}

// マップのファイル名を取得
string CsvDataManager::getMapFileName(const int map_id)
{
    return this->csv_data[DataType::MAP][map_id][2];
}

// アイテム名を取得
string CsvDataManager::getItemName(const int item_id)
{
    return (item_id >= 0) ? this->csv_data[DataType::ITEM][item_id][1] : "アイテムがありません";
}

// アイテムの説明を取得
string CsvDataManager::getItemDiscription(const int item_id)
{
    return (item_id >= 0) ? this->csv_data[DataType::ITEM][item_id][2] : "アイテムがありません";
}

#pragma mark -
#pragma mark Chapter

// チャプター名を取得
string CsvDataManager::getChapterName(const int chapter_id)
{
    return this->csv_data[DataType::CHAPTER][chapter_id][1];
}

// チャプターのタイトルを取得
string CsvDataManager::getChapterTitle(const int chapter_id)
{
    return this->csv_data[DataType::CHAPTER][chapter_id][2];
}

#pragma mark -
#pragma mark Character

// キャラクター名の取得
string CsvDataManager::getCharaName(const int chara_id)
{
    return this->csv_data[DataType::CHARACTER][chara_id][1];
}

// キャラクターのファイル名を取得
string CsvDataManager::getCharaFileName(const int chara_id)
{
    return this->csv_data[DataType::CHARACTER][chara_id][2];
}

// キャラクターの表情差分IDを取得
int CsvDataManager::getCharaFaceDiff(const int chara_id)
{
    return stoi(this->csv_data[DataType::CHARACTER][chara_id][3]);
}

// キャラクターの説明をレベルごとに取得
// @param int level 0 ~ 2
string CsvDataManager::getCharaDiscription(const int chara_id, const int level)
{
    return this->csv_data[DataType::CHARACTER][chara_id][level+4];
}
// キャラクターをメニューに表示するかどうか
bool CsvDataManager::isDisplayChara(const int chara_id)
{
    return this->csv_data[DataType::CHARACTER][chara_id][7] == "1" ? true : false;
}

// 表示するキャラクターリスト
vector<int> CsvDataManager::getDisplayCharacters()
{
    vector<int> charas;
    for (auto itr:this->csv_data[DataType::CHARACTER])
    {
        if(this->isDisplayChara(itr.first))
        {
            charas.push_back(itr.first);
        }
    }
    return charas;
}