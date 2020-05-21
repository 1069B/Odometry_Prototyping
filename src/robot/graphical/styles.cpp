#include "robot/graphical/styles.hpp"

lv_style_t redBtnRel;
lv_style_t redBtnPress;
lv_style_t blueBtnRel;
lv_style_t blueBtnPress;
lv_style_t greenBtnRel;
lv_style_t greenBtnPress;
lv_style_t defaultBtnRel;
lv_style_t defaultBtnPress;

lv_style_t redText;
lv_style_t blueText;
lv_style_t greenText;
lv_style_t blackText;
lv_style_t whiteText;

lv_style_t defaultBackground;
lv_style_t popupBackground;

lv_style_t meterStyle;

lv_style_t toggleBackground;
lv_style_t toggleInactive;
lv_style_t toggleOn;
lv_style_t toggleOff;

lv_point_t HORZ_20[] = {{0, 20},{480, 20}};
lv_point_t HORZ_40[] = {{0, 40},{480, 40}};
lv_point_t HORZ_60[] = {{0, 60},{480, 60}};
lv_point_t HORZ_80[] = {{0, 80},{480, 80}};
lv_point_t HORZ_100[] = {{0, 100},{480, 100}};
lv_point_t HORZ_120[] = {{0, 120},{480, 120}};
lv_point_t HORZ_140[] = {{0, 140},{480, 140}};
lv_point_t HORZ_160[] = {{0, 160},{480, 160}};
lv_point_t HORZ_180[] = {{0, 180},{480, 180}};
lv_point_t HORZ_200[] = {{0, 200},{480, 200}};
lv_point_t HORZ_220[] = {{0, 220},{480, 220}};
lv_point_t HORZ_240[] = {{0, 240},{480, 240}};

void defineStyles(){
  //Default relesed style
  lv_style_copy(&defaultBtnRel, &lv_style_plain);
  defaultBtnRel.body.radius = 8;
  defaultBtnRel.body.main_color = LV_COLOR_WHITE;
  defaultBtnRel.body.grad_color = LV_COLOR_WHITE;
  defaultBtnRel.text.color = LV_COLOR_RED;

  //Default relesed style
  lv_style_copy(&defaultBtnPress, &defaultBtnRel);
  defaultBtnPress.body.main_color = LV_COLOR_SILVER;
  defaultBtnPress.body.grad_color = LV_COLOR_SILVER;

  //Red Rel style
  lv_style_copy(&redBtnRel, &defaultBtnRel);
  redBtnRel.body.main_color = LV_COLOR_RED;
  redBtnRel.body.grad_color = LV_COLOR_RED;
  redBtnRel.text.color = LV_COLOR_MAKE(255, 255, 255);

  //Red pressed style
  lv_style_copy(&redBtnPress, &redBtnRel);
  redBtnPress.body.main_color = LV_COLOR_MAROON;
  redBtnPress.body.grad_color = LV_COLOR_MAROON;

  //Blue Rel style
  lv_style_copy(&blueBtnRel, &defaultBtnRel);
  blueBtnRel.body.main_color = LV_COLOR_BLUE;
  blueBtnRel.body.grad_color = LV_COLOR_BLUE;
  blueBtnRel.text.color = LV_COLOR_MAKE(255, 255, 255);

  //Blue pressed style
  lv_style_copy(&blueBtnPress, &blueBtnRel);
  blueBtnPress.body.main_color = LV_COLOR_NAVY;
  blueBtnPress.body.grad_color = LV_COLOR_NAVY;

  //Green Rel style
  lv_style_copy(&greenBtnRel, &defaultBtnRel);
  greenBtnRel.body.radius = 8;
  greenBtnRel.body.main_color = LV_COLOR_GREEN;
  greenBtnRel.body.grad_color = LV_COLOR_GREEN;
  greenBtnRel.text.color = LV_COLOR_MAKE(255, 255, 255);

  //Green Pressed style
  lv_style_copy(&greenBtnPress, &greenBtnRel);
  greenBtnPress.body.main_color = LV_COLOR_HEX(0x10690C);
  greenBtnPress.body.grad_color = LV_COLOR_HEX(0x10690C);

  lv_style_copy(&redText, &lv_style_plain);
  redText.text.color = LV_COLOR_RED;
  redText.line.color = LV_COLOR_RED;
  redText.line.width = 3;
  lv_style_copy(&blueText, &lv_style_plain);
  blueText.text.color = LV_COLOR_BLUE;
  blueText.line.color = LV_COLOR_BLUE;
  blueText.line.width = 3;
  lv_style_copy(&greenText, &lv_style_plain);
  greenText.text.color = LV_COLOR_GREEN;
  greenText.line.color = LV_COLOR_GREEN;
  greenText.line.width = 3;
  lv_style_copy(&blackText, &lv_style_plain);
  blackText.text.color = LV_COLOR_BLACK;
  blackText.line.color = LV_COLOR_BLACK;
  blackText.line.width = 3;
  lv_style_copy(&whiteText, &lv_style_plain);
  whiteText.text.color = LV_COLOR_WHITE;
  whiteText.line.color = LV_COLOR_WHITE;
  whiteText.line.width = 3;

  lv_style_copy(&defaultBackground, &lv_style_plain);
  defaultBackground.body.main_color = LV_COLOR_MAKE(0, 0, 0);
  defaultBackground.body.grad_color = LV_COLOR_MAKE(0, 0, 0);

  lv_style_copy(&popupBackground, &lv_style_plain);
  popupBackground.body.main_color = LV_COLOR_MAKE(126, 126, 126);
  popupBackground.body.grad_color = LV_COLOR_MAKE(126, 126, 126);
  popupBackground.body.radius = 8;
  popupBackground.body.border.color = LV_COLOR_MAROON;
  popupBackground.body.border.width = 2;


  lv_style_copy(&meterStyle, &lv_style_pretty_color);
  meterStyle.line.width = 2;
  meterStyle.line.color = LV_COLOR_WHITE;
  meterStyle.body.padding.hor = 16;            /*Line length*/
  meterStyle.body.main_color = LV_COLOR_LIME;
  meterStyle.body.grad_color = LV_COLOR_RED;

  /* Toggle Styles*/
  lv_style_copy(&toggleBackground, &lv_style_pretty);
  toggleBackground.body.radius = LV_RADIUS_CIRCLE;

  lv_style_copy(&toggleInactive, &lv_style_pretty_color);
  toggleInactive.body.radius = LV_RADIUS_CIRCLE;
  toggleInactive.body.main_color = LV_COLOR_HEX(0x9fc8ef);
  toggleInactive.body.grad_color = LV_COLOR_HEX(0x9fc8ef);
  toggleInactive.body.padding.hor = 0;
  toggleInactive.body.padding.ver = 0;

  lv_style_copy(&toggleOff, &lv_style_pretty);
  toggleOff.body.radius = LV_RADIUS_CIRCLE;
  toggleOff.body.shadow.width = 4;
  toggleOff.body.shadow.type = LV_SHADOW_BOTTOM;

  lv_style_copy(&toggleOn, &lv_style_pretty_color);
  toggleOn.body.radius = LV_RADIUS_CIRCLE;
  toggleOn.body.shadow.width = 4;
  toggleOn.body.shadow.type = LV_SHADOW_BOTTOM;
}
