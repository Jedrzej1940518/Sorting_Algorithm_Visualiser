#pragma once

#include <Fl/Fl_Color_Chooser.H>

#include <vector>
#include <utility>

using namespace std;

typedef std::vector<pair<pair<int, int>, bool>> SoC; // swap or Comparsion-> bool = 0 -> swap, bool = 1, comp

constexpr int WIN_W = 1000;
constexpr int WIN_H = 700;

constexpr int MNU_W = 300;
constexpr int MNU_H = 300;

constexpr int CH_W = 120;
constexpr int CH_H = 30;

constexpr int BTN_W = 60;
constexpr int BTN_H = 20;

constexpr int MRG = 80; //margines

constexpr int MX_LEN = 10;//max number lenght

constexpr int DELTA = 20;
constexpr double RATE = 0.03;
constexpr double COMP_T = 0.3;

constexpr Fl_Color COMP_C = FL_YELLOW;
constexpr Fl_Color SWP_C = FL_RED;

///////////////////////////
///// CHOICE MENU ////////

extern const char* rn10;// = "Random 10";
extern const char* rn20;// = "Random 20";
extern const char* rnUI;// = "User Input";

extern const char* QS;// = "QuickSort";
extern const char* IS;// = "InsertionSort";
extern const char* UA;// = "User's algorithm";

extern const char* FLU;// = "Fluid";
extern const char* SBS;// = "Step by step";

