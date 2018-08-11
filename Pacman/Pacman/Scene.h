#pragma once

#include "Tags.h"
#include "GameObject.h"

class Block;

class Scene
{
public:
    Scene();
    virtual ~Scene();

    HRESULT Init();
    void Release();
    void Reset();
    void Update();
    void Render(HDC hdc);

    LRESULT MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void RenderProc(HWND hWnd, UINT message, UINT idEvent, DWORD time);

    void DrawBitmap(HDC hdc, HBITMAP hBitmap, int x, int y, int width, int height);

    GameObject* CreateCoin(int x, int y);

private:
    HBITMAP hBit;
    HBITMAP hBackground;
    array<HBITMAP, 5> hPacmans;
    HBITMAP hEnemy;

    chrono::time_point<chrono::system_clock> startTime;
    chrono::time_point<chrono::system_clock> previousTime;
    chrono::duration<float> deltaTime;

    float pacmanBiteCoolDown;
    bool pacmanBiting;
    int pacmanLife;
    
    bool isFinished;
    float finishCoolDown;

    map<Kind, vector<GameObject*>> gameObjects;
    vector<RoadAtX> roadAtXs;
    vector<RoadAtY> roadAtYs;

    int score;
};

