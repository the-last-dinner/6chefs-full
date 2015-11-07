//
//  SpriteUtils.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/07.
//
//

#include "Utils/SpriteUtils.h"

// 四角形のスプライトを生成
Sprite* SpriteUtils::getSquareSprite(SpriteUtils::Square &range, SpriteUtils::Margin &margin)
{
    Sprite* square = Sprite::create();
    float rate_width = WINDOW_WIDTH / 100;
    float rate_height = WINDOW_HEIGHT / 100;
    float width = range.getWidth() * rate_width - margin.getLeft() - margin.getRight();
    float height = range.getHeight() * rate_height - margin.getTop() - margin.getBottom();
    square->setTextureRect(Rect(0, 0, width, height));
    square->setPosition((width / 2) + range.getMinX() * rate_width + margin.getLeft(), (height / 2) + range.getMinY() * rate_height + margin.getBottom());
    return square;
}

// 四角形のスプライトをマージン一括していで生成
Sprite* SpriteUtils::getSquareSprite(SpriteUtils::Square &range, const float margin)
{
    Margin strc = Margin(margin);
    return SpriteUtils::getSquareSprite(range, strc);
}