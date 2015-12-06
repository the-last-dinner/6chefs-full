//
//  resources.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/04.
//
//

#ifndef resources_h
#define resources_h

namespace Resource
{
    namespace Font
    {
        static const std::string BASE_PATH = "fonts/";
        static const std::string SYSTEM = BASE_PATH + "aoyagireisyosimo_ttf_2_01.ttf";
        static const std::string MESSAGE = BASE_PATH + "cinecaption2.28.ttf";
    };
    
    namespace SE
    {
        static const std::string BASE_PATH = "se/";
        static const std::string GET_ITEM = "mystery5.mp3";
        static const std::string TROPHY_NOTIFICATION = "receipt05.mp3";
    };
    
    namespace BGM
    {
        static const std::string BASE_PATH = "bgm/";
    };
};

#endif /* resources_h */
