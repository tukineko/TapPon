#ifndef __Config_H__
#define __Config_H__

#include "cocos2d.h"

#define PI 3.14159265358979323846

#define VisibleSize Director::getInstance()->getVisibleSize()
#define winSizeW VisibleSize.width
#define winSizeH VisibleSize.height
#define winSizeCenterW winSizeW / 2
#define winSizeCenterH winSizeH / 2

#define BOX_START_POS_X 300
#define BOX_START_POS_Y winSizeCenterH
#define BOX_END_POS_X 1100
#define BOX_END_POS_Y winSizeCenterH
#define BOX_NEXT_POS_X 1500
#define BOX_NEXT_POS_Y winSizeCenterH



#endif // __Config_H__