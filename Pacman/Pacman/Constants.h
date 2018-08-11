#pragma once

static class Constant
{
public:
    static const int kScaleFactor = 2;

    static const int kWindowOriginX = 100;
    static const int kWindowOriginY = 100;
    static const int kWindowWidth = 585 * kScaleFactor;
    static const int kGameSceneHeight = 174 * kScaleFactor;
    static const int kStatusHeight = 80;
    static const int kWindowHeight = kGameSceneHeight + kStatusHeight;

    static const COLORREF kBlack = RGB(0, 0, 0);
    static const COLORREF kWhite = RGB(255, 255, 255);
    static const COLORREF kRed = RGB(255, 0, 0);
    static const COLORREF kGreen = RGB(0, 255, 0);
    static const COLORREF kBlue = RGB(0, 0, 255);

    static const int kMovableGameObjectSpeed = 4;
    static const int kMovableGameObjectWidth = 30;
    static const int kMovableGameObjectHeight = kMovableGameObjectWidth;

    static const int kEnemySpeed = 3;

    static const int kCoinWidth = 7;
    static const int kCoinHeight = kCoinWidth;
};
