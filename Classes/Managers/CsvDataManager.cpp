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
    return;
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
    FUNCLOG
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
        CCLOG(line.c_str());
    }
#endif
    return values;
}

//idから表示名を取得
string CsvDataManager::getDisplayName(const CsvDataManager::DataType& data_type, int data_id)
{
    FUNCLOG
    return this->csv_data[data_type][data_id][1];
}

//idからファイル名を取得
string CsvDataManager::getFileName(const CsvDataManager::DataType& data_type, int data_id)
{
    FUNCLOG
    return this->csv_data[data_type][data_id][2];
}

//表情の個数を取得
int CsvDataManager::existsFaceDiff(const CsvDataManager::DataType& data_type, int data_id)
{
    FUNCLOG
    return stoi(this->csv_data[data_type][data_id][3]);
}


