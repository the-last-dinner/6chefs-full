
#ifndef VideoTextureCache_h
#define VideoTextureCache_h

#include "define.h"
#include "VideoDecode.h"

class VideoTextureCache : public Ref
{
public:
    VideoTextureCache();
    virtual ~VideoTextureCache();
    static VideoTextureCache * sharedTextureCache();
    Texture2D* addImageWidthData(VideoPic *pic);
    Texture2D* getTexture(int frame);
    void removeAllTextures();
    VideoDecode* addVideo(const char *dir);
    void removeVideo(const char *dir);
    void addPicData(VideoPic *videoPic);
    void picToTexture(float fd);

private:
    Map<string, Ref *>* _textures;
    Map<string, Ref *>* _videoDecodes;
    bool _threadEnd = false;
    string _delKey = "";
};

#endif /* VideoTextureCache_h */
