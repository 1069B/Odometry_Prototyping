#include "main.h"

#ifndef STYLES_H
#define STYLES_H

extern int color_Red;
extern int color_Blue;
extern int color_Green;
extern int color_Defualt;

extern lv_style_t redBtnRel;
extern lv_style_t redBtnPress;
extern lv_style_t blueBtnRel;
extern lv_style_t blueBtnPress;
extern lv_style_t greenBtnRel;
extern lv_style_t greenBtnPress;
extern lv_style_t defaultBtnRel;
extern lv_style_t defaultBtnPress;

extern lv_style_t redText;
extern lv_style_t blueText;
extern lv_style_t greenText;
extern lv_style_t blackText;
extern lv_style_t whiteText;

extern lv_style_t defaultBackground;
extern lv_style_t popupBackground;

extern lv_style_t meterStyle;

extern lv_style_t toggleBackground;
extern lv_style_t toggleInactive;
extern lv_style_t toggleOn;
extern lv_style_t toggleOff;

extern lv_point_t HORZ_20[];
extern lv_point_t HORZ_40[];
extern lv_point_t HORZ_60[];
extern lv_point_t HORZ_80[];
extern lv_point_t HORZ_100[];
extern lv_point_t HORZ_120[];
extern lv_point_t HORZ_140[];
extern lv_point_t HORZ_160[];
extern lv_point_t HORZ_180[];
extern lv_point_t HORZ_200[];
extern lv_point_t HORZ_220[];
extern lv_point_t HORZ_240[];

void defineStyles(void);

#endif // STYLES_H
