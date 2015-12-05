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
        static const std::string base_path = "fonts/";
        static const std::string system = base_path + "aoyagireisyosimo_ttf_2_01.ttf";
        static const std::string message = base_path + "cinecaption2.28.ttf";
    };
    
    namespace SE
    {
        static const std::string get_item = "mystery5.mp3";
        static const std::string trophy_notification = "receipt05.mp3";
    };
};

#endif /* resources_h */
