/********* CONTENTS **********/
//(A) Initialize Colors Main

//(B) Initialize Colors Limited
void colors_limited();

//(C) Initialize Colors Full
void colors_full();

/********* CONTENTS **********/

#include <ncurses.h>
#include "colors.h"


//(A) Initialize Colors Main
void initialize_colors()
{
  //Changes default colors
  //RGB values multiplied by as ncurses goes from 0-1000 instead of 0-255
  init_color(COLOR_RED, (255*200)/51, (20*200)/51, (28*200)/51);
  init_color(COLOR_GREEN, (81*200)/51, (161*200)/51, (72*200)/51);
  init_color(COLOR_YELLOW, (248*200)/51, (248*200)/51, (46*200)/51);
  init_color(COLOR_BLUE, (44*200)/51, (66*200)/51, (177*200)/51);
  init_color(COLOR_MAGENTA, (128*200)/51, (45*200)/51, (206*200)/51);
  init_color(COLOR_CYAN, (66*200)/51, (155*200)/51, (255*200)/51);

  //Chooses to initialize colors depending on terminal capabilities
  if(COLORS>8) { colors_full(); }
  else { colors_limited(); }
}

//(B) Initialize Colors Limited
//Limited terminal colors enabled, less options for color
void colors_limited()
{
  //Default Printing Color
  init_pair(253, COLOR_WHITE, COLOR_BLACK);
  init_pair(254, COLOR_WHITE, COLOR_BLACK);
  init_pair(255, COLOR_WHITE, COLOR_BLACK);

  //Color Pairs - Default
  init_pair(10, COLOR_RED, COLOR_GREEN);
  init_pair(11, COLOR_RED, COLOR_GREEN);
  init_pair(12, COLOR_YELLOW, COLOR_GREEN);
  init_pair(13, COLOR_YELLOW, COLOR_GREEN);
  init_pair(14, COLOR_WHITE, COLOR_GREEN);
  init_pair(15, COLOR_WHITE, COLOR_GREEN);
  init_pair(16, COLOR_CYAN, COLOR_GREEN);
  init_pair(17, COLOR_BLUE, COLOR_GREEN);
  init_pair(18, COLOR_MAGENTA, COLOR_GREEN);
  init_pair(19, COLOR_BLACK, COLOR_GREEN);
  init_pair(20, COLOR_BLACK, COLOR_GREEN);
  init_pair(21, COLOR_BLACK, COLOR_GREEN);

  //Color Pairs - Forest
  init_pair(22, COLOR_RED, COLOR_BLACK);
  init_pair(23, COLOR_RED, COLOR_BLACK);
  init_pair(24, COLOR_YELLOW, COLOR_BLACK);
  init_pair(25, COLOR_YELLOW, COLOR_BLACK);
  init_pair(26, COLOR_GREEN, COLOR_BLACK);
  init_pair(27, COLOR_GREEN, COLOR_BLACK);
  init_pair(28, COLOR_CYAN, COLOR_BLACK);
  init_pair(29, COLOR_BLUE, COLOR_BLACK);
  init_pair(30, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(31, COLOR_WHITE, COLOR_BLACK);
  init_pair(32, COLOR_WHITE, COLOR_BLACK);
  init_pair(33, COLOR_WHITE, COLOR_BLACK);

  //Color Pairs - Stone
  init_pair(34, COLOR_RED, COLOR_WHITE);
  init_pair(35, COLOR_RED, COLOR_WHITE);
  init_pair(36, COLOR_YELLOW, COLOR_WHITE);
  init_pair(37, COLOR_YELLOW, COLOR_WHITE);
  init_pair(38, COLOR_GREEN, COLOR_WHITE);
  init_pair(39, COLOR_GREEN, COLOR_WHITE);
  init_pair(40, COLOR_CYAN, COLOR_WHITE);
  init_pair(41, COLOR_BLUE, COLOR_WHITE);
  init_pair(42, COLOR_MAGENTA, COLOR_WHITE);
  init_pair(43, COLOR_BLACK, COLOR_WHITE);
  init_pair(44, COLOR_BLACK, COLOR_WHITE);
  init_pair(45, COLOR_BLACK, COLOR_WHITE);

  //Color Pairs - Gold
  init_pair(46, COLOR_RED, COLOR_YELLOW);
  init_pair(47, COLOR_RED, COLOR_YELLOW);
  init_pair(48, COLOR_WHITE, COLOR_YELLOW);
  init_pair(49, COLOR_WHITE, COLOR_YELLOW);
  init_pair(50, COLOR_GREEN, COLOR_YELLOW);
  init_pair(51, COLOR_GREEN, COLOR_YELLOW);
  init_pair(52, COLOR_CYAN, COLOR_YELLOW);
  init_pair(53, COLOR_BLUE, COLOR_YELLOW);
  init_pair(54, COLOR_MAGENTA, COLOR_YELLOW);
  init_pair(55, COLOR_BLACK, COLOR_YELLOW);
  init_pair(56, COLOR_BLACK, COLOR_YELLOW);
  init_pair(57, COLOR_BLACK, COLOR_YELLOW);

  //Color Pairs - Water
  init_pair(58, COLOR_RED, COLOR_BLUE);
  init_pair(59, COLOR_RED, COLOR_BLUE);
  init_pair(60, COLOR_YELLOW, COLOR_BLUE);
  init_pair(61, COLOR_YELLOW, COLOR_BLUE);
  init_pair(62, COLOR_GREEN, COLOR_BLUE);
  init_pair(63, COLOR_GREEN, COLOR_BLUE);
  init_pair(64, COLOR_CYAN, COLOR_BLUE);
  init_pair(65, COLOR_WHITE, COLOR_BLUE);
  init_pair(66, COLOR_MAGENTA, COLOR_BLUE);
  init_pair(67, COLOR_BLACK, COLOR_BLUE);
  init_pair(68, COLOR_BLACK, COLOR_BLUE);
  init_pair(69, COLOR_BLACK, COLOR_BLUE);

  //Color Pairs - Water Shallow
  init_pair(70, COLOR_RED, COLOR_CYAN);
  init_pair(71, COLOR_RED, COLOR_CYAN);
  init_pair(72, COLOR_YELLOW, COLOR_CYAN);
  init_pair(73, COLOR_YELLOW, COLOR_CYAN);
  init_pair(74, COLOR_GREEN, COLOR_CYAN);
  init_pair(75, COLOR_GREEN, COLOR_CYAN);
  init_pair(76, COLOR_WHITE, COLOR_CYAN);
  init_pair(77, COLOR_BLUE, COLOR_CYAN);
  init_pair(78, COLOR_MAGENTA, COLOR_CYAN);
  init_pair(79, COLOR_BLACK, COLOR_CYAN);
  init_pair(80, COLOR_BLACK, COLOR_CYAN);
  init_pair(81, COLOR_BLACK, COLOR_CYAN);

  //Color Pairs - Coast
  init_pair(82, COLOR_RED, COLOR_YELLOW);
  init_pair(83, COLOR_RED, COLOR_YELLOW);
  init_pair(84, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(85, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(86, COLOR_GREEN, COLOR_YELLOW);
  init_pair(87, COLOR_GREEN, COLOR_YELLOW);
  init_pair(88, COLOR_WHITE, COLOR_YELLOW);
  init_pair(89, COLOR_BLUE, COLOR_YELLOW);
  init_pair(90, COLOR_MAGENTA, COLOR_YELLOW);
  init_pair(91, COLOR_BLACK, COLOR_YELLOW);
  init_pair(92, COLOR_BLACK, COLOR_YELLOW);
  init_pair(93, COLOR_BLACK, COLOR_YELLOW);


  //Color Pairs - Target
  init_pair(190, COLOR_WHITE, COLOR_RED);
  init_pair(191, COLOR_WHITE, COLOR_RED);
  init_pair(192, COLOR_YELLOW, COLOR_RED);
  init_pair(193, COLOR_YELLOW, COLOR_RED);
  init_pair(194, COLOR_GREEN, COLOR_RED);
  init_pair(195, COLOR_GREEN, COLOR_RED);
  init_pair(196, COLOR_CYAN, COLOR_RED);
  init_pair(197, COLOR_BLUE, COLOR_RED);
  init_pair(198, COLOR_MAGENTA, COLOR_RED);
  init_pair(199, COLOR_BLACK, COLOR_RED);
  init_pair(200, COLOR_BLACK, COLOR_RED);
  init_pair(201, COLOR_BLACK, COLOR_RED);

  //Color Pairs - Text
  init_pair(210, COLOR_RED, COLOR_BLACK);
  init_pair(211, COLOR_RED, COLOR_BLACK);
  init_pair(212, COLOR_YELLOW, COLOR_BLACK);
  init_pair(213, COLOR_YELLOW, COLOR_BLACK);
  init_pair(214, COLOR_GREEN, COLOR_BLACK);
  init_pair(215, COLOR_GREEN, COLOR_BLACK);
  init_pair(216, COLOR_CYAN, COLOR_BLACK);
  init_pair(217, COLOR_BLUE, COLOR_BLACK);
  init_pair(218, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(219, COLOR_BLACK, COLOR_BLACK);
  init_pair(220, COLOR_BLACK, COLOR_BLACK);
  init_pair(221, COLOR_BLACK, COLOR_WHITE);

  //Color Pairs - Background
  init_pair(230, COLOR_RED, COLOR_RED);
  init_pair(231, COLOR_RED, COLOR_RED);
  init_pair(232, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(233, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(234, COLOR_GREEN, COLOR_GREEN);
  init_pair(235, COLOR_GREEN, COLOR_GREEN);
  init_pair(236, COLOR_CYAN, COLOR_CYAN);
  init_pair(237, COLOR_BLUE, COLOR_BLUE);
  init_pair(238, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(239, COLOR_BLACK, COLOR_BLACK);
  init_pair(240, COLOR_BLACK, COLOR_BLACK);
  init_pair(241, COLOR_BLACK, COLOR_BLACK);
}

//(C) Initialize Colors Full
//Full terminal color usage enabled, more options
void colors_full()
{
  //New Colors
  //RGB values multiplied by as ncurses goes from 0-1000 instead of 0-255

  //Interface Colors
  //252 - Target Red
  init_color(252, (193*200)/51, (67*200)/51, (67*200)/51);
  //253 - Background Blue
  init_color(253, (40*200)/51, (40*200)/51, (91*200)/51);
  //254 - Dark Background
  init_color(254, (102*200)/51, (86*200)/51, (61*200)/51);
  //255 - Light Background
  init_color(255, (204*200)/51, (171*200)/51, (128*200)/51);

  //Player Colors
  //8 - Pink
  init_color(8, (255*200)/51, (102*200)/51, (242*200)/51);
  //9 - Orange
  init_color(9, (255*200)/51, (114*200)/51, (0*200)/51);
  //10 - Brown
  init_color(10, (135*200)/51, (54*200)/51, (0*200)/51);
  //11 - Grey
  init_color(11, (128*200)/51, (128*200)/51, (128*200)/51);

  //Tile Colors
  //12 - Default
  init_color(12, (132*200)/51, (183*200)/51, (75*200)/51);
  //13 - Forest
  init_color(13, (69*200)/51, (96*200)/51, (0*200)/51);
  //14 - Stone
  init_color(14, (65*200)/51, (65*200)/51, (65*200)/51);
  //15 - Gold
  init_color(15, (173*200)/51, (144*200)/51, (0*200)/51);
  //16 - Water
  init_color(16, (0*200)/51, (25*200)/51, (168*200)/51);
  //17 - Shallow Water
  init_color(17, (0*200)/51, (136*200)/51, (234*200)/51);
  //18 - Coast
  init_color(18, (187*200)/51, (153*200)/51, (126*200)/51);

  //Tile FOW Colors
  //32 - Default
  init_color(32, (92*200)/51, (127*200)/51, (52*200)/51);
  //33 - Forest
  init_color(33, (46*200)/51, (63*200)/51, (0*200)/51);
  //34 - Stone
  init_color(34, (35*200)/51, (35*200)/51, (35*200)/51);
  //35 - Gold
  init_color(35, (137*200)/51, (112*200)/51, (0*200)/51);
  //36 - Water
  init_color(36, (0*200)/51, (20*200)/51, (135*200)/51);
  //37 - Shallow Water
  init_color(37, (0*200)/51, (113*200)/51, (193*200)/51);
  //38 - Coast
  init_color(38, (150*200)/51, (123*200)/51, (102*200)/51);

  //Default Printing Colors
  init_pair(253, COLOR_WHITE, 253);
  init_pair(254, COLOR_WHITE, 254);
  init_pair(255, COLOR_BLACK, 255);

  //Color Pairs - Default
  init_pair(10, COLOR_RED, 12);
  init_pair(11, 8, 12);
  init_pair(12, 9, 12);
  init_pair(13, COLOR_YELLOW, 12);
  init_pair(14, 10, 12);
  init_pair(15, COLOR_GREEN, 12);
  init_pair(16, COLOR_CYAN, 12);
  init_pair(17, COLOR_BLUE, 12);
  init_pair(18, COLOR_MAGENTA, 12);
  init_pair(19, COLOR_WHITE, 12);
  init_pair(20, 11, 12);
  init_pair(21, COLOR_BLACK, 12);

  //Color Pairs - Forest
  init_pair(22, COLOR_RED, 13);
  init_pair(23, 8, 13);
  init_pair(24, 9, 13);
  init_pair(25, COLOR_YELLOW, 13);
  init_pair(26, 10, 13);
  init_pair(27, COLOR_GREEN, 13);
  init_pair(28, COLOR_CYAN, 13);
  init_pair(29, COLOR_BLUE, 13);
  init_pair(30, COLOR_MAGENTA, 13);
  init_pair(31, COLOR_WHITE, 13);
  init_pair(32, 11, 13);
  init_pair(33, COLOR_BLACK, 13);

  //Color Pairs - Stone
  init_pair(34, COLOR_RED, 14);
  init_pair(35, 8, 14);
  init_pair(36, 9, 14);
  init_pair(37, COLOR_YELLOW, 14);
  init_pair(38, 10, 14);
  init_pair(39, COLOR_GREEN, 14);
  init_pair(40, COLOR_CYAN, 14);
  init_pair(41, COLOR_BLUE, 14);
  init_pair(42, COLOR_MAGENTA, 14);
  init_pair(43, COLOR_WHITE, 14);
  init_pair(44, 11, 14);
  init_pair(45, COLOR_BLACK, 14);

  //Color Pairs - Gold
  init_pair(46, COLOR_RED, 15);
  init_pair(47, 8, 15);
  init_pair(48, 9, 15);
  init_pair(49, COLOR_YELLOW, 15);
  init_pair(50, 10, 15);
  init_pair(51, COLOR_GREEN, 15);
  init_pair(52, COLOR_CYAN, 15);
  init_pair(53, COLOR_BLUE, 15);
  init_pair(54, COLOR_MAGENTA, 15);
  init_pair(55, COLOR_WHITE, 15);
  init_pair(56, 11, 15);
  init_pair(57, COLOR_BLACK, 15);

  //Color Pairs - Water
  init_pair(58, COLOR_RED, 16);
  init_pair(59, 8, 16);
  init_pair(60, 9, 16);
  init_pair(61, COLOR_YELLOW, 16);
  init_pair(62, 10, 16);
  init_pair(63, COLOR_GREEN, 16);
  init_pair(64, COLOR_CYAN, 16);
  init_pair(65, COLOR_BLUE, 16);
  init_pair(66, COLOR_MAGENTA, 16);
  init_pair(67, COLOR_WHITE, 16);
  init_pair(68, 11, 16);
  init_pair(69, COLOR_BLACK, 16);

  //Color Pairs - Water Shallow
  init_pair(70, COLOR_RED, 17);
  init_pair(71, 8, 17);
  init_pair(72, 9, 17);
  init_pair(73, COLOR_YELLOW, 17);
  init_pair(74, 10, 17);
  init_pair(75, COLOR_GREEN, 17);
  init_pair(76, COLOR_WHITE, 17);
  init_pair(77, COLOR_BLUE, 17);
  init_pair(78, COLOR_MAGENTA, 17);
  init_pair(79, COLOR_WHITE, 17);
  init_pair(80, 11, 17);
  init_pair(81, COLOR_BLACK, 17);

  //Color Pairs - Coast
  init_pair(82, COLOR_RED, 18);
  init_pair(83, 8, 18);
  init_pair(84, 9, 18);
  init_pair(85, COLOR_YELLOW, 18);
  init_pair(86, 10, 18);
  init_pair(87, COLOR_GREEN, 18);
  init_pair(88, COLOR_WHITE, 18);
  init_pair(89, COLOR_BLUE, 18);
  init_pair(90, COLOR_MAGENTA, 18);
  init_pair(91, COLOR_WHITE, 18);
  init_pair(92, 11, 18);
  init_pair(93, COLOR_BLACK, 18);

  //Color Pairs - FOW
  init_pair(170, 32, 32);
  init_pair(171, 33, 33);
  init_pair(172, 34, 34);
  init_pair(173, 35, 35);
  init_pair(174, 36, 36);
  init_pair(175, 37, 37);
  init_pair(176, 38, 38);

  //Color Pairs - Target
  init_pair(190, COLOR_RED, 252);
  init_pair(191, 8, 252);
  init_pair(192, 9, 252);
  init_pair(193, COLOR_YELLOW, 252);
  init_pair(194, 10, 252);
  init_pair(195, COLOR_GREEN, 252);
  init_pair(196, COLOR_CYAN, 252);
  init_pair(197, COLOR_BLUE, 252);
  init_pair(198, COLOR_MAGENTA, 252);
  init_pair(199, COLOR_WHITE, 252);
  init_pair(200, 11, 252);
  init_pair(201, COLOR_BLACK, 252);

  //Color Pairs - Text
  init_pair(210, COLOR_RED, 255);
  init_pair(211, 8, 255);
  init_pair(212, 9, 255);
  init_pair(213, COLOR_YELLOW, 255);
  init_pair(214, 10, 255);
  init_pair(215, COLOR_GREEN, 255);
  init_pair(216, COLOR_CYAN, 255);
  init_pair(217, COLOR_BLUE, 255);
  init_pair(218, COLOR_MAGENTA, 255);
  init_pair(219, COLOR_WHITE, 255);
  init_pair(220, 11, 255);
  init_pair(221, COLOR_BLACK, 255);

  //Color Pairs - Background
  init_pair(230, COLOR_RED, COLOR_RED);
  init_pair(231, 8, 8);
  init_pair(232, 9, 9);
  init_pair(233, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(234, 10, 10);
  init_pair(235, COLOR_GREEN, COLOR_GREEN);
  init_pair(236, COLOR_CYAN, COLOR_CYAN);
  init_pair(237, COLOR_BLUE, COLOR_BLUE);
  init_pair(238, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(239, COLOR_WHITE, COLOR_WHITE);
  init_pair(240, 11, 11);
  init_pair(241, COLOR_BLACK, COLOR_BLACK);
}
