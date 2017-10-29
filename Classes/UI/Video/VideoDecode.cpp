#include "VideoDecode.h"
#include "VideoTextureCache.h"

VideoPic::VideoPic()
{
    FUNCLOG;
    _image = NULL;
}

VideoPic::~VideoPic()
{
    FUNCLOG;
    if(_image) {
        delete _image;
    }
}

bool VideoPic::init(const string& path, int frame)
{
    
    Image* image = new Image();
    image->initWithImageFile(path);
    _width = image->getWidth();
    _height = image->getHeight();
    _frame = frame;
    _image = image;

    return true;
}

VideoDecode::VideoDecode()
{
    FUNCLOG;
	_fileDir = NULL;
    _frameCount = 0;
}

VideoDecode::~VideoDecode() { FUNCLOG; }

bool VideoDecode::init(const char *dir)
{
    _fileDir = dir;
    _frameRate = 1.0/30;
    
    _frames = 1;
    FileUtils *fileutils = FileUtils::getInstance();
    while (fileutils->isFileExist(getFilePath(_frames))) {
        _frames++;
    }
    _frames--;

    string filePath = getFilePath(_frames);
    
    Image* image = new Image();
    bool initResult = image->initWithImageFile(filePath);
    if(!initResult) {
        CCLOG("読み込み失敗 ファイル：%s", filePath.c_str());
        return false;
    }

    _width = image->getWidth();
    _height = image->getHeight();
    
    CC_SAFE_RELEASE(image);

    return true;
}

unsigned int VideoDecode::getWidth()
{
    return _width;
}

unsigned int VideoDecode::getHeight()
{
    return _height;
}

double VideoDecode::getFrameRate()
{
    return _frameRate;
}

unsigned int VideoDecode::getFrames()
{
    return _frames;
}

string VideoDecode::getFilePath(int frame)
{
    string fileDir = _fileDir;

    string fileName = to_string(frame);
    while(fileName.length() < 5) {
        fileName = "0" + fileName;
    }
    
    return fileDir + fileName + ".png";
}

// 1ファイルづつ読み込んでキャッシュにセットする
bool VideoDecode::decode()
{
    if(_frameCount == -1) {
        return false;
    }
    CCLOG("decode");
    _frameCount++;
    
    string filePath = getFilePath(_frameCount);
    
    // 画像をセット
    VideoPic *pVideoPic = new VideoPic();
    pVideoPic->init(filePath, _frameCount);
    VideoTextureCache::sharedTextureCache()->addPicData(pVideoPic);

    if (_frameCount == _frames) {
        _frameCount = -1;
    }

    return true;
}

