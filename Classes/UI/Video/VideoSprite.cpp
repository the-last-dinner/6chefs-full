
#include "VideoSprite.h"
#include "VideoTextureCache.h"
#include "VideoDecode.h"

VideoSprite* VideoSprite::create(const char* dir)
{
    VideoSprite* video = new VideoSprite();

    if (video && video->init(dir)) {
         video->autorelease();
         return video;
    }
    CC_SAFE_DELETE(video);
    return NULL;  
}  

VideoSprite::VideoSprite()
{
    FUNCLOG;
    _frameRate = 1.0 / 30;
    _frameCount = 1;
    _width = 100;
    _height = 100;
}  

VideoSprite::~VideoSprite()
{  
    FUNCLOG;
    VideoTextureCache* video = VideoTextureCache::sharedTextureCache();
    video->removeVideo(_fileDir.c_str());
    CC_SAFE_RELEASE_NULL(video);
}

bool VideoSprite::init(const char* dir)
{  
    _fileDir = dir;

    VideoDecode *videoDecode = VideoTextureCache::sharedTextureCache()->addVideo(dir);
    if(!videoDecode) {
        CCLOGERROR("videoDecode get error in %s", "VideoSprite");
        return false;
    }

    _width = videoDecode->getWidth();
    _height = videoDecode->getHeight();
    _frames = videoDecode->getFrames();
    _frameRate = videoDecode->getFrameRate();

    Texture2D *texture = new Texture2D();
    unsigned int length = _width * _height * 4;
    unsigned char* tempData = new unsigned char[length];
    for(unsigned int i = 0; i < length; ++i) {
        tempData[i] = 0;
    }

    texture->initWithData(tempData, length, Texture2D::PixelFormat::RGB565, _width, _height, Size(_width, _height));
    initWithTexture(texture);
    this->setContentSize(Size(_width, _height));

    delete [] tempData;
    CC_SAFE_RELEASE(texture);
    return true;
}

void VideoSprite::playVideo()
{  
    update(0);
    this->schedule(schedule_selector(VideoSprite::update), _frameRate);
}  

void VideoSprite::stopVideo(void)
{
    this->unscheduleAllCallbacks();
    VideoTextureCache::sharedTextureCache()->removeAllTextures();
}

void VideoSprite::update(float dt)
{
    Texture2D *texture = NULL;
    texture = VideoTextureCache::sharedTextureCache()->getTexture(_frameCount);
    _frameCount++;
    if(texture) {
        setTexture(texture);
    } else {
        CCLOG("表示失敗 VideoSprite::update filename = %s , now_frame = %d, total_frame = %d", _fileDir.c_str(), _frameCount, _frames);
    }
    if(_frameCount >= _frames) {
        _frameCount = 1;
        if (_videoEndCallback)
            _videoEndCallback();
    }
}

void VideoSprite::setVideoEndCallback(function<void()> func)
{  
    _videoEndCallback = func;
}
