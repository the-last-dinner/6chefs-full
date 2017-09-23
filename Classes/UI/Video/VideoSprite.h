
#ifndef VideoSprite_h
#define VideoSprite_h

#include "define.h"

class VideoSprite : public Sprite
{  
public:
    static VideoSprite* create(const char* path);
    VideoSprite();
    virtual ~VideoSprite();
      
    bool init(const char* path);  
    void playVideo(void);  
    void stopVideo(void); 
    void update(float dt);  
      
    void setVideoEndCallback(function<void()> func);
    
private:
    unsigned int m_width;  
    unsigned int m_height;
    unsigned int m_frames;
    double m_frameRate;

    unsigned int m_frame_count;
    string m_strFileName;
    function<void()> m_videoEndCallback;
};  

#endif /* VideoSprite_h */
