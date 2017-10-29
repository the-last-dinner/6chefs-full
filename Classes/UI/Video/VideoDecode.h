#ifndef VideoDecode_h
#define VideoDecode_h

#include "define.h"

// 動画の１枚毎の画像
class VideoPic : public Ref
{
public:
    VideoPic();
    virtual ~VideoPic();
    bool init(const string& path, int frame);
    int _frame;
    int _width;
    int _height;
    Image *_image;
};

// 連番画像の読み込み
class VideoDecode : public Ref
{
public:
    VideoDecode();
    virtual ~VideoDecode();
    bool decode();
    bool init(const char *dir);
    unsigned int getWidth();
    unsigned int getHeight();
    double getFrameRate();
    unsigned int getFrames();

private:
    int _frameCount;
    const char *_fileDir;
    double _frameRate;
    unsigned int _frames;
    unsigned int _width;
    unsigned int _height;
    string getFilePath(int frame);
};

#endif /* VideoDecode_h */
