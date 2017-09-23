
#include "VideoTextureCache.h"
#include "VideoDecode.h"

static queue<VideoPic*>* s_pAsyncVideoPicQueue = NULL;

static VideoTextureCache *g_sharedTextureCache = NULL;

static mutex mtx;

VideoTextureCache * VideoTextureCache::sharedTextureCache()
{
    if (!g_sharedTextureCache) {
        g_sharedTextureCache = new VideoTextureCache();
    }
    return g_sharedTextureCache;
}

void VideoTextureCache::purgeSharedTextureCache()
{
    CC_SAFE_RELEASE_NULL(g_sharedTextureCache);
}

VideoTextureCache::VideoTextureCache()
{
    FUNCLOG;
    CCAssert(g_sharedTextureCache == NULL, "Attempted to allocate a second instance of a singleton.");
    m_pTextures = new Map<std::string, Ref *>();
    m_pVideoDecodes = new Map<std::string, Ref *>();
}

VideoTextureCache::~VideoTextureCache()
{
    FUNCLOG;
}

VideoDecode* VideoTextureCache::addVideo(const char *path)
{

    VideoDecode* pVideoDecode = (VideoDecode*)m_pVideoDecodes->at(path);
    
    pVideoDecode = new VideoDecode();
    if(pVideoDecode->init(path)) {
        m_pVideoDecodes->insert(path, pVideoDecode);
        
        _threadEnd = false;
        std::thread thread = std::thread([this](void *data){
            VideoDecode *p = (VideoDecode *) data;
            if(p) {
                while(!_threadEnd && p->decode()) {
                    //sleep ?
                    if(_threadEnd)
                        break;
                    
                    mtx.lock();
                    int size = (int)m_pTextures->size();
                    mtx.unlock();
                    while (size > 60) {
                        mtx.lock();
                        size = (int)m_pTextures->size();
                        mtx.unlock();
                    }
                }
            }
            CC_SAFE_RELEASE_NULL(p);
        },pVideoDecode);
        thread.detach();
        pVideoDecode->release();

        s_pAsyncVideoPicQueue = new queue<VideoPic*>();
                
        Director::getInstance()->getScheduler()->schedule(schedule_selector(VideoTextureCache::picToTexture), this, 0, false);
    
        } else {
            CCLOGERROR("CCVideoDecode init error in CCVideoTextureCache");
            return NULL;
        }
    
    pVideoDecode->retain();

    return pVideoDecode;
}

void VideoTextureCache::addPicData(VideoPic *pVideoPic)
{
    mtx.lock();
    s_pAsyncVideoPicQueue->push(pVideoPic);
    mtx.unlock();
}

void VideoTextureCache::picToTexture(float fd)
{
    VideoPic *pVideoPic = NULL;
    int length = m_pVideoDecodes->size();
    m_pTextures->erase(_delKey);

    for(int i = 0; i < length; i++) {
        mtx.lock();
        if (!s_pAsyncVideoPicQueue->empty()) {
            pVideoPic = s_pAsyncVideoPicQueue->front();
            s_pAsyncVideoPicQueue->pop();
            mtx.unlock();
            if(pVideoPic) {
                addImageWidthData(pVideoPic);
                pVideoPic->release();
            }
        } else {
            mtx.unlock();
            break;
        }
    }
}

void VideoTextureCache::removeVideo(const char *path)
{
    _threadEnd = true;
    VideoDecode* pVideoDecode = (VideoDecode*)m_pVideoDecodes->at(path);
    if(pVideoDecode) {
        unsigned int rcount =  pVideoDecode->getReferenceCount();
        if(rcount == 1) {
            unsigned int frames = pVideoDecode->getFrames();
            for(; frames > 0; frames--) {
                m_pTextures->erase(to_string(frames));
            }
            m_pVideoDecodes->erase(path);
        } else {
            pVideoDecode->release();
        }
    }
}

Texture2D* VideoTextureCache::getTexture(int frame)
{
    Texture2D * texture = NULL;
    texture = (Texture2D*)m_pTextures->at(to_string(frame));
    _delKey = to_string(frame - 5);
	return texture;
}

Texture2D* VideoTextureCache::addImageWidthData(VideoPic *pic)
{

    string key = to_string(pic->m_frame);
    
    Texture2D * texture = NULL;
    texture = (Texture2D*)m_pTextures->at(key);
	if(!texture) {
        texture = new Texture2D();
        if( texture && 
        	texture->initWithImage(pic->m_image) ) {
            
            m_pTextures->insert(key, texture);
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
    m_pTextures->clear();
}
