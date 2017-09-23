#include "VideoDecode.h"
#include "VideoTextureCache.h"

#include <sys/types.h>
#include <dirent.h>

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "swresample.lib")

VideoPic::VideoPic()
{
    FUNCLOG;
    m_image = NULL;
}

VideoPic::~VideoPic()
{
    FUNCLOG;
    if(m_image) {
        delete m_image;
    }
}


bool VideoPic::init(const string& path, int frame)
{
    
    Image* image = new Image();
    image->initWithImageFile(path);
    m_width = image->getWidth();
    m_height = image->getHeight();
    m_frame = frame;
    m_image = image;

    return true;
}

VideoDecode::VideoDecode()
{
    FUNCLOG;
	m_filepath = NULL;
    m_frameCount = 0;
}

bool VideoDecode::init(const char *path)
{
    m_filepath = path;
    m_frameRate = 1.0/30;
    
    std::vector<std::string> list;
    DIR* dp;
    struct dirent* ent;
    
    if ((dp = opendir(m_filepath), "r") == NULL) {
        CCLOG("ディレクトリが開けません。：%s", m_filepath);
        perror(m_filepath);
    }
    
    while ((ent = readdir(dp)) != NULL) {
        if(ent->d_namlen != 9) continue;
        CCLOG("ファイル：%s", ent->d_name);
        list.push_back(ent->d_name);
    };
    closedir(dp);
    
    m_frames = list.size();
    
    string filePath = getFullFilePath(m_frames);
    
    Image* image = new Image();
    
    bool initResult = image->initWithImageFile(filePath);
    if(!initResult) {
        CCLOG("読み込み失敗 ファイル：%s", filePath.c_str());
        return false;
    }
    m_width = image->getWidth();
    m_height = image->getHeight();
    
    return true;
}

unsigned int VideoDecode::getWidth()
{
    return m_width;
}

unsigned int VideoDecode::getHeight()
{
    return m_height;
}

double VideoDecode::getFrameRate()
{
    return m_frameRate;
}

unsigned int VideoDecode::getFrames()
{
    return m_frames;
}

const char* VideoDecode::getFilePath()
{
    return m_filepath;
}

VideoDecode::~VideoDecode()
{
    FUNCLOG;
}

string VideoDecode::getFullFilePath(int frame)
{
    string filePath = m_filepath;
    string fileName = to_string(frame);
    
    while(fileName.length() < 5) {
        fileName = "0" + fileName;
    }
    
    return filePath + "/" + fileName + ".png";
}

// デコードしてcocosで表示できる形式の画像に分解する
bool VideoDecode::decode()
{
    if(m_frameCount == -1)
        return false;
    CCLOG("decode");
    m_frameCount++;
    
    string filePath = getFullFilePath(m_frameCount);
    
    // 変換した画像をセット
    VideoPic *pVideoPic = new VideoPic();
    pVideoPic->init(filePath, m_frameCount);
    VideoTextureCache::sharedTextureCache()->addPicData(pVideoPic);

    if (m_frameCount == m_frames) {
        m_frameCount = -1;
    }

    return true;
}

