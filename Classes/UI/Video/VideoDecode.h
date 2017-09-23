#ifndef VideoDecode_h
#define VideoDecode_h

#include "define.h"

extern "C" { 
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"  
    #include "libswscale/swscale.h"
    #include "libavutil/imgutils.h"
}

struct AVFormatContext;  
struct AVCodecContext;  
struct AVFrame;  
struct AVPicture;  
struct SwsContext; 

// 動画の１枚毎の画像
class VideoPic : public Ref
{
	public:
        VideoPic();
		bool init(const string& path, int frame);
        virtual ~VideoPic();
		int m_frame;
		int m_width;
		int m_height;
        Image *m_image;
};

// 動画を画像に変換
class VideoDecode : public Ref
{
	private:

	    int m_frameCount;
	    const char *m_filepath;
	    double m_frameRate;
	    unsigned int m_frames;
	    unsigned int m_width;  
    	unsigned int m_height;
        string getFullFilePath(int frame);
	public:
        VideoDecode();
        virtual ~VideoDecode();
		bool decode();
		bool init(const char *path);
		unsigned int getWidth();
		unsigned int getHeight();
		double getFrameRate();
		unsigned int getFrames();
		const char* getFilePath(); 
};

#endif /* VideoDecode_h */
