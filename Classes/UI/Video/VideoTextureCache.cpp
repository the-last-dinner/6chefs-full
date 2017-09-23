
#include "VideoTextureCache.h"
#include "VideoDecode.h"

static queue<VideoPic*>* _asyncVideoPicQueue = NULL;

static VideoTextureCache *_sharedTextureCache = NULL;

static mutex mtx;

VideoTextureCache * VideoTextureCache::sharedTextureCache()
{
    if (!_sharedTextureCache) {
        _sharedTextureCache = new VideoTextureCache();
    }
    return _sharedTextureCache;
}

VideoTextureCache::VideoTextureCache()
{
    FUNCLOG;
    CCAssert(_sharedTextureCache == NULL, "Attempted to allocate a second instance of a singleton.");
    _textures = new Map<std::string, Ref *>();
    _videoDecodes = new Map<std::string, Ref *>();
}

VideoTextureCache::~VideoTextureCache() { FUNCLOG; }

VideoDecode* VideoTextureCache::addVideo(const char *dir)
{

    VideoDecode* videoDecode = (VideoDecode*)_videoDecodes->at(dir);
    
    videoDecode = new VideoDecode();
    if(videoDecode->init(dir)) {
        _videoDecodes->insert(dir, videoDecode);
        
        _threadEnd = false;
        std::thread thread = std::thread([this](void *data){
            VideoDecode *p = (VideoDecode *) data;
            if(p) {
                while(!_threadEnd && p->decode()) {
                    if(_threadEnd) {
                        break;
                    }
                    
                    mtx.lock();
                    int size = (int)_textures->size();
                    mtx.unlock();
                    while (size > 60) {
                        mtx.lock();
                        size = (int)_textures->size();
                        mtx.unlock();
                    }
                }
            }
            CC_SAFE_RELEASE_NULL(p);
        },videoDecode);
        thread.detach();
        videoDecode->release();

        _asyncVideoPicQueue = new queue<VideoPic*>();
                
        Director::getInstance()->getScheduler()->schedule(schedule_selector(VideoTextureCache::picToTexture), this, 0, false);
    
    } else {
        CCLOGERROR("CCVideoDecode init error in CCVideoTextureCache");
        return NULL;
    }
    
    videoDecode->retain();

    return videoDecode;
}

void VideoTextureCache::addPicData(VideoPic *videoPic)
{
    mtx.lock();
    _asyncVideoPicQueue->push(videoPic);
    mtx.unlock();
}

void VideoTextureCache::picToTexture(float fd)
{
    VideoPic *videoPic = NULL;
    int length = _videoDecodes->size();
    _textures->erase(_delKey);

    for(int i = 0; i < length; i++) {
        mtx.lock();
        if (!_asyncVideoPicQueue->empty()) {
            videoPic = _asyncVideoPicQueue->front();
            _asyncVideoPicQueue->pop();
            mtx.unlock();
            if(videoPic) {
                addImageWidthData(videoPic);
                videoPic->release();
            }
        } else {
            mtx.unlock();
            break;
        }
    }
}

void VideoTextureCache::removeVideo(const char *dir)
{
    _threadEnd = true;
    VideoDecode* videoDecode = (VideoDecode*)_videoDecodes->at(dir);
    if(videoDecode) {
        unsigned int rcount =  videoDecode->getReferenceCount();
        if(rcount == 1) {
            unsigned int frames = videoDecode->getFrames();
            for(; frames > 0; frames--) {
                _textures->erase(to_string(frames));
            }
            _videoDecodes->erase(dir);
        } else {
            videoDecode->release();
        }
    }
}

Texture2D* VideoTextureCache::getTexture(int frame)
{
    Texture2D * texture = NULL;
    texture = (Texture2D*)_textures->at(to_string(frame));
    _delKey = to_string(frame - 5);
	return texture;
}

Texture2D* VideoTextureCache::addImageWidthData(VideoPic *pic)
{
    string key = to_string(pic->_frame);
    
    Texture2D * texture = NULL;
    texture = (Texture2D*)_textures->at(key);
	if(!texture) {
        texture = new Texture2D();
        if( texture && 
        	texture->initWithImage(pic->_image) ) {
            
            _textures->insert(key, texture);
            texture->release();
		} else {
            CCLOG("cocos2d: Couldn't create texture for file:%s in CCVideoTextureCache", key.c_str());
        }
	} else {
        CCLOG("追加画像データ - %s", key.c_str());
    }

	return texture;
}

void VideoTextureCache::removeAllTextures()
{
    _threadEnd = true;
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(VideoTextureCache::picToTexture), this);
    _textures->clear();
}
