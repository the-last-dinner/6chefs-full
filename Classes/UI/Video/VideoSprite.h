
#ifndef VideoSprite_h
#define VideoSprite_h

#include "define.h"

class VideoSprite : public Sprite
{  
public:
    static VideoSprite* create(const char* dir);
    VideoSprite();
    virtual ~VideoSprite();
    bool init(const char* path);  
    void playVideo(void);  
    void stopVideo(void); 
    void update(float dt);
    void setVideoEndCallback(function<void()> func);
    
private:
    unsigned int _width;
    unsigned int _height;
    unsigned int _frames;
    double _frameRate;
    unsigned int _frameCount;
    string _fileDir;
    function<void()> _videoEndCallback;
};  

#endif /* VideoSprite_h */
