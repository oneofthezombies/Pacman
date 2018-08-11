#include "stdafx.h"
#include "Scene.h"
#include "CommonMacroFunction.h"
#include "Constants.h"
#include "Input.h"

Scene::Scene() :
    hBit(nullptr),
    hBackground(nullptr),
    isFinished(false),
    startTime(chrono::time_point<chrono::system_clock>()),
    previousTime(chrono::time_point<chrono::system_clock>()),
    deltaTime(chrono::duration<float>()),
    pacmanBiteCoolDown(0.1f),
    pacmanBiting(false),
    score(0),
    finishCoolDown(0.2f),
    pacmanLife(1),
    hEnemy(nullptr)
{
}

Scene::~Scene()
{
}

HRESULT Scene::Init()
{
    hBackground = (HBITMAP)LoadImage(hInst, "Assets/background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hPacmans[0] = (HBITMAP)LoadImage(hInst, "Assets/pacman_idle.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hPacmans[1] = (HBITMAP)LoadImage(hInst, "Assets/pacman_left.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hPacmans[2] = (HBITMAP)LoadImage(hInst, "Assets/pacman_up.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hPacmans[3] = (HBITMAP)LoadImage(hInst, "Assets/pacman_right.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hPacmans[4] = (HBITMAP)LoadImage(hInst, "Assets/pacman_down.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hEnemy = (HBITMAP)LoadImage(hInst, "Assets/enemy.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    auto player = new GameObject;
    player->Tag(Kind::kPlayer);
    gameObjects[Kind::kPlayer].push_back(player);

    auto enemy1 = new GameObject;
    enemy1->Tag(Kind::kEnemy);
    gameObjects[Kind::kEnemy].push_back(enemy1);

    auto enemy2 = new GameObject;
    enemy2->Tag(Kind::kEnemy);
    gameObjects[Kind::kEnemy].push_back(enemy2);

    auto enemy3 = new GameObject;
    enemy3->Tag(Kind::kEnemy);
    gameObjects[Kind::kEnemy].push_back(enemy3);

    RoadAtY y18(18 * Constant::kScaleFactor);
    y18.road.push_back(Range(18 * Constant::kScaleFactor, 58 * Constant::kScaleFactor));
    y18.road.push_back(Range(58 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    y18.road.push_back(Range(158 * Constant::kScaleFactor, 318 * Constant::kScaleFactor));
    y18.road.push_back(Range(318 * Constant::kScaleFactor, 408 * Constant::kScaleFactor));
    y18.road.push_back(Range(408 * Constant::kScaleFactor, 448 * Constant::kScaleFactor));
    y18.road.push_back(Range(448 * Constant::kScaleFactor, 508 * Constant::kScaleFactor));
    y18.road.push_back(Range(508 * Constant::kScaleFactor, 568 * Constant::kScaleFactor));
    roadAtYs.push_back(y18);

    RoadAtY y48(48 * Constant::kScaleFactor);
    y48.road.push_back(Range(18 * Constant::kScaleFactor, 58 * Constant::kScaleFactor));
    y48.road.push_back(Range(158 * Constant::kScaleFactor, 238 * Constant::kScaleFactor));
    y48.road.push_back(Range(238 * Constant::kScaleFactor, 318 * Constant::kScaleFactor));
    y48.road.push_back(Range(318 * Constant::kScaleFactor, 408 * Constant::kScaleFactor));
    y48.road.push_back(Range(448 * Constant::kScaleFactor, 508 * Constant::kScaleFactor));
    y48.road.push_back(Range(508 * Constant::kScaleFactor, 526 * Constant::kScaleFactor));
    y48.road.push_back(Range(526 * Constant::kScaleFactor, 568 * Constant::kScaleFactor));
    roadAtYs.push_back(y48);

    RoadAtY y58(58 * Constant::kScaleFactor);
    y58.road.push_back(Range(98 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtYs.push_back(y58);

    RoadAtY y88(88 * Constant::kScaleFactor);
    y88.road.push_back(Range(0 * Constant::kScaleFactor, 58 * Constant::kScaleFactor));
    y88.road.push_back(Range(98 * Constant::kScaleFactor, 116 * Constant::kScaleFactor));
    y88.road.push_back(Range(526 * Constant::kScaleFactor, 584 * Constant::kScaleFactor));
    roadAtYs.push_back(y88);

    RoadAtY y98(98 * Constant::kScaleFactor);
    y98.road.push_back(Range(488 * Constant::kScaleFactor, 526 * Constant::kScaleFactor));
    roadAtYs.push_back(y98);

    RoadAtY y108(108 * Constant::kScaleFactor);
    y108.road.push_back(Range(318 * Constant::kScaleFactor, 408 * Constant::kScaleFactor));
    roadAtYs.push_back(y108);

    RoadAtY y128(128 * Constant::kScaleFactor);
    y128.road.push_back(Range(18 * Constant::kScaleFactor, 58 * Constant::kScaleFactor));
    y128.road.push_back(Range(58 * Constant::kScaleFactor, 68 * Constant::kScaleFactor));
    y128.road.push_back(Range(68 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    y128.road.push_back(Range(158 * Constant::kScaleFactor, 178 * Constant::kScaleFactor));
    y128.road.push_back(Range(178 * Constant::kScaleFactor, 208 * Constant::kScaleFactor));
    y128.road.push_back(Range(208 * Constant::kScaleFactor, 238 * Constant::kScaleFactor));
    y128.road.push_back(Range(238 * Constant::kScaleFactor, 318 * Constant::kScaleFactor));
    y128.road.push_back(Range(408 * Constant::kScaleFactor, 448 * Constant::kScaleFactor));
    y128.road.push_back(Range(448 * Constant::kScaleFactor, 508 * Constant::kScaleFactor));
    y128.road.push_back(Range(508 * Constant::kScaleFactor, 526 * Constant::kScaleFactor));
    y128.road.push_back(Range(526 * Constant::kScaleFactor, 568 * Constant::kScaleFactor));
    roadAtYs.push_back(y128);

    RoadAtY y138(138 * Constant::kScaleFactor);
    y138.road.push_back(Range(318 * Constant::kScaleFactor, 348 * Constant::kScaleFactor));
    y138.road.push_back(Range(378 * Constant::kScaleFactor, 408 * Constant::kScaleFactor));
    roadAtYs.push_back(y138);

    RoadAtY y158(158 * Constant::kScaleFactor);
    y158.road.push_back(Range(18 * Constant::kScaleFactor, 68 * Constant::kScaleFactor));
    y158.road.push_back(Range(68 * Constant::kScaleFactor, 178 * Constant::kScaleFactor));
    y158.road.push_back(Range(208 * Constant::kScaleFactor, 318 * Constant::kScaleFactor));
    y158.road.push_back(Range(348 * Constant::kScaleFactor, 378 * Constant::kScaleFactor));
    y158.road.push_back(Range(408 * Constant::kScaleFactor, 508 * Constant::kScaleFactor));
    y158.road.push_back(Range(508 * Constant::kScaleFactor, 568 * Constant::kScaleFactor));
    roadAtYs.push_back(y158);

    RoadAtX x18(18 * Constant::kScaleFactor);
    x18.road.push_back(Range(18 * Constant::kScaleFactor, 48 * Constant::kScaleFactor));
    x18.road.push_back(Range(128 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtXs.push_back(x18);

    RoadAtX x58(58 * Constant::kScaleFactor);
    x58.road.push_back(Range(18 * Constant::kScaleFactor, 48 * Constant::kScaleFactor));
    x58.road.push_back(Range(48 * Constant::kScaleFactor, 88 * Constant::kScaleFactor));
    x58.road.push_back(Range(88 * Constant::kScaleFactor, 128 * Constant::kScaleFactor));
    roadAtXs.push_back(x58);

    RoadAtX x68(68 * Constant::kScaleFactor);
    x68.road.push_back(Range(128 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtXs.push_back(x68);

    RoadAtX x98(98 * Constant::kScaleFactor);
    x98.road.push_back(Range(58 * Constant::kScaleFactor, 88 * Constant::kScaleFactor));
    roadAtXs.push_back(x98);

    RoadAtX x158(158 * Constant::kScaleFactor);
    x158.road.push_back(Range(18 * Constant::kScaleFactor, 48 * Constant::kScaleFactor));
    x158.road.push_back(Range(48 * Constant::kScaleFactor, 58 * Constant::kScaleFactor));
    x158.road.push_back(Range(58 * Constant::kScaleFactor, 128 * Constant::kScaleFactor));
    roadAtXs.push_back(x158);

    RoadAtX x178(178 * Constant::kScaleFactor);
    x178.road.push_back(Range(128 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtXs.push_back(x178);

    RoadAtX x208(208 * Constant::kScaleFactor);
    x208.road.push_back(Range(128 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtXs.push_back(x208);

    RoadAtX x238(238 * Constant::kScaleFactor);
    x238.road.push_back(Range(48 * Constant::kScaleFactor, 128 * Constant::kScaleFactor));
    roadAtXs.push_back(x238);

    RoadAtX x318(318 * Constant::kScaleFactor);
    x318.road.push_back(Range(18 * Constant::kScaleFactor, 48 * Constant::kScaleFactor));
    x318.road.push_back(Range(48 * Constant::kScaleFactor, 108 * Constant::kScaleFactor));
    x318.road.push_back(Range(108 * Constant::kScaleFactor, 128 * Constant::kScaleFactor));
    x318.road.push_back(Range(128 * Constant::kScaleFactor, 138 * Constant::kScaleFactor));
    x318.road.push_back(Range(138 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtXs.push_back(x318);

    RoadAtX x348(348 * Constant::kScaleFactor);
    x348.road.push_back(Range(138 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtXs.push_back(x348);

    RoadAtX x378(378 * Constant::kScaleFactor);
    x378.road.push_back(Range(138 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtXs.push_back(x378);

    RoadAtX x408(408 * Constant::kScaleFactor);
    x408.road.push_back(Range(18 * Constant::kScaleFactor, 48 * Constant::kScaleFactor));
    x408.road.push_back(Range(48 * Constant::kScaleFactor, 108 * Constant::kScaleFactor));
    x408.road.push_back(Range(108 * Constant::kScaleFactor, 128 * Constant::kScaleFactor));
    x408.road.push_back(Range(128 * Constant::kScaleFactor, 138 * Constant::kScaleFactor));
    x408.road.push_back(Range(138 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtXs.push_back(x408);

    RoadAtX x448(448 * Constant::kScaleFactor);
    x448.road.push_back(Range(18 * Constant::kScaleFactor, 48 * Constant::kScaleFactor));
    x448.road.push_back(Range(48 * Constant::kScaleFactor, 128 * Constant::kScaleFactor));
    roadAtXs.push_back(x448);

    RoadAtX x508(508 * Constant::kScaleFactor);
    x508.road.push_back(Range(18 * Constant::kScaleFactor, 48 * Constant::kScaleFactor));
    x508.road.push_back(Range(128 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtXs.push_back(x508);

    RoadAtX x526(526 * Constant::kScaleFactor);
    x526.road.push_back(Range(48 * Constant::kScaleFactor, 88 * Constant::kScaleFactor));
    x526.road.push_back(Range(88 * Constant::kScaleFactor, 98 * Constant::kScaleFactor));
    x526.road.push_back(Range(98 * Constant::kScaleFactor, 128 * Constant::kScaleFactor));
    roadAtXs.push_back(x526);

    RoadAtX x568(568 * Constant::kScaleFactor);
    x568.road.push_back(Range(18 * Constant::kScaleFactor, 48 * Constant::kScaleFactor));
    x568.road.push_back(Range(128 * Constant::kScaleFactor, 158 * Constant::kScaleFactor));
    roadAtXs.push_back(x568);

    Reset();

    return S_OK;
}

void Scene::Release()
{
    if (hBit)
    {
        DeleteObject(hBit);
    }

    if (hBackground)
    {
        DeleteObject(hBackground);
    }

    for (auto& hPacman : hPacmans)
    {
        if (hPacman)
        {
            DeleteObject(hPacman);
        }
    }

    if (hEnemy)
    {
        DeleteObject(hEnemy);
    }
}

void Scene::Reset()
{
    startTime = chrono::system_clock::now();

    auto currentTime = chrono::system_clock::now();
    previousTime = currentTime;

    isFinished = false;
    finishCoolDown = 0.2f;

    score = 0;

    pacmanBiting = false;
    pacmanBiteCoolDown = 0.1f;
    pacmanLife = 1;

    for (auto& go : gameObjects[Kind::kPlayer])
    {
        go->Position(363 * Constant::kScaleFactor, 158 * Constant::kScaleFactor);
    }

    gameObjects[Kind::kEnemy][0]->Position(343 * Constant::kScaleFactor, 108 * Constant::kScaleFactor);
    gameObjects[Kind::kEnemy][0]->NextDirection(Direction::kToLeft);
    gameObjects[Kind::kEnemy][1]->Position(363 * Constant::kScaleFactor, 108 * Constant::kScaleFactor);
    gameObjects[Kind::kEnemy][1]->NextDirection(Direction::kToLeft);
    gameObjects[Kind::kEnemy][2]->Position(383 * Constant::kScaleFactor, 108 * Constant::kScaleFactor);
    gameObjects[Kind::kEnemy][2]->NextDirection(Direction::kToLeft);

    gameObjects[Kind::kCoin].resize(0);

    for (int x = 18; x <= 318; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 18));
    }

    for (int x = 348; x <= 568; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 18));
    }

    for (int x = 18; x <= 58; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 48));
    }

    for (int x = 158; x <= 318; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 48));
    }

    for (int x = 348; x <= 408; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 48));
    }

    for (int x = 448; x <= 568; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 48));
    }

    for (int x = 18; x <= 318; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 128));
    }

    for (int x = 408; x <= 568; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 128));
    }

    for (int x = 18; x <= 178; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 158));
    }

    for (int x = 218; x <= 318; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 158));
    }

    for (int x = 408; x <= 568; x += 20)
    {
        gameObjects[Kind::kCoin].push_back(CreateCoin(x, 158));
    }
}

void Scene::Update()
{
    auto currentTime = chrono::system_clock::now();
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    chrono::duration<float> elapsedTime = currentTime - startTime;

    pacmanBiteCoolDown -= deltaTime.count();
    if (pacmanBiteCoolDown <= 0.0f)
    {
        pacmanBiting = !pacmanBiting;

        pacmanBiteCoolDown = 0.1f;
    }

    if (INPUT->IsStayKeyDown(VK_UP))
    {
        for (auto& go : gameObjects[Kind::kPlayer])
        {
            go->NextDirection(Direction::kUp);
        }
    }

    if (INPUT->IsStayKeyDown(VK_LEFT))
    {
        for (auto& go : gameObjects[Kind::kPlayer])
        {
            go->NextDirection(Direction::kToLeft);
        }
    }

    if (INPUT->IsStayKeyDown(VK_RIGHT))
    {
        for (auto& go : gameObjects[Kind::kPlayer])
        {
            go->NextDirection(Direction::kToRight);
        }
    }

    if (INPUT->IsStayKeyDown(VK_DOWN))
    {
        for (auto& go : gameObjects[Kind::kPlayer])
        {
            go->NextDirection(Direction::kDown);
        }
    }

    for (auto& go : gameObjects[Kind::kPlayer])
    {
        go->Move(roadAtXs, roadAtYs);
    }

    for (auto& go : gameObjects[Kind::kEnemy])
    {
        go->Move(roadAtXs, roadAtYs);
    }

    for (auto& player : gameObjects[Kind::kPlayer])
    {
        for (auto coin = gameObjects[Kind::kCoin].begin(); coin != gameObjects[Kind::kCoin].end();)
        {
            RECT rc;
            if (IntersectRect(&rc, &(player->Rect()), &((*coin)->Rect())))
            {
                score += 1;

                coin = gameObjects[Kind::kCoin].erase(coin);
            }
            else
            {
                ++coin;
            }
        }
    }

    for (auto& player : gameObjects[Kind::kPlayer])
    {
        for (auto& enemy : gameObjects[Kind::kEnemy])
        {
            RECT rc;
            if (IntersectRect(&rc, &(player->Rect()), &(enemy->Rect())))
            {
                pacmanLife--;
            }

            int distanceX = abs(player->Position().x - enemy->Position().x);
            int distanceY = abs(player->Position().y - enemy->Position().y);
            if (distanceX <= 65 &&
                distanceY <= 65)
            {
                if (distanceX < distanceY)
                {
                    if (player->Position().y < enemy->Position().y)
                    {
                        enemy->NextDirection(Direction::kUp);
                    }
                    else
                    {
                        enemy->NextDirection(Direction::kDown);
                    }
                }
                else
                {
                    if (player->Position().x < enemy->Position().x)
                    {
                        enemy->NextDirection(Direction::kToLeft);
                    }
                    else
                    {
                        enemy->NextDirection(Direction::kToRight);
                    }
                }
            }
        }
    }

    if (pacmanLife <= 0)
    {
        finishCoolDown -= deltaTime.count();
    }

    if (gameObjects[Kind::kCoin].empty())
    {
        finishCoolDown -= deltaTime.count();
    }

    if (finishCoolDown <= 0.0f)
    {
        isFinished = true;
    }
}

void Scene::Render(HDC hdc)
{
    DrawBitmap(hdc, hBackground, 0, 0, Constant::kWindowWidth, Constant::kGameSceneHeight);

    HPEN myPen = CreatePen(PS_SOLID, 1, Constant::kWhite);
    HPEN oldPen = (HPEN)SelectObject(hdc, myPen);
    HBRUSH myBrush = CreateSolidBrush(Constant::kWhite);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    for (auto& coin : gameObjects[Kind::kCoin])
    {
        DrawRectangleCenter(hdc, coin->Position().x, coin->Position().y, Constant::kCoinWidth, Constant::kCoinHeight);
    }
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);

    myPen = CreatePen(PS_SOLID, 1, Constant::kRed);
    oldPen = (HPEN)SelectObject(hdc, myPen);
    myBrush = CreateSolidBrush(Constant::kRed);
    oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
    for (auto& enemy : gameObjects[Kind::kEnemy])
    {
        DrawBitmap(hdc, hEnemy,
                   enemy->Position().x - Constant::kMovableGameObjectWidth / 2, enemy->Position().y - Constant::kMovableGameObjectHeight / 2,
                   Constant::kMovableGameObjectWidth, Constant::kMovableGameObjectHeight);
    }
    SelectObject(hdc, oldPen);
    SelectObject(hdc, oldBrush);
    DeleteObject(myPen);
    DeleteObject(myBrush);

    for (auto& go : gameObjects[Kind::kPlayer])
    {
        int halfWidth = Constant::kMovableGameObjectWidth / 2;
        int halfHeight = Constant::kMovableGameObjectHeight / 2;

        if (pacmanBiting)
        {
            if (go->Velocity().x < 0)
            {
                DrawBitmap(hdc, hPacmans[1],
                           go->Position().x - halfWidth, go->Position().y - halfHeight,
                           Constant::kMovableGameObjectWidth, Constant::kMovableGameObjectHeight);
            }
            else if (go->Velocity().x >= 0)
            {
                DrawBitmap(hdc, hPacmans[3],
                           go->Position().x - halfWidth, go->Position().y - halfHeight,
                           Constant::kMovableGameObjectWidth, Constant::kMovableGameObjectHeight);
            }

            if (go->Velocity().y < 0)
            {
                DrawBitmap(hdc, hPacmans[2],
                           go->Position().x - halfWidth, go->Position().y - halfHeight,
                           Constant::kMovableGameObjectWidth, Constant::kMovableGameObjectHeight);
            }
            else if (go->Velocity().y > 0)
            {
                DrawBitmap(hdc, hPacmans[4],
                           go->Position().x - halfWidth, go->Position().y - halfHeight,
                           Constant::kMovableGameObjectWidth, Constant::kMovableGameObjectHeight);
            }
        }
        else
        {
            DrawBitmap(hdc, hPacmans[0],
                       go->Position().x - halfWidth, go->Position().y - halfHeight,
                       Constant::kMovableGameObjectWidth, Constant::kMovableGameObjectHeight);
        }
    }

    SetTextColor(hdc, Constant::kWhite);
    HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "Malgun Gothic");
    HFONT oldfont = (HFONT)SelectObject(hdc, myFont);
    string scoreText = "점수 : " + to_string(score);
    TextOut(hdc, 10, Constant::kGameSceneHeight + 10, scoreText.c_str(), scoreText.size());
    SelectObject(hdc, oldfont);
    DeleteObject(myFont);

    if (isFinished)
    {
        KillTimer(hWnd, 0);

        if (MessageBox(hWnd, "", "게임 오버", MB_RETRYCANCEL) == IDRETRY)
        {
            Reset();
            SendMessage(hWnd, WM_CREATE, 0, 0);
        }
        else
        {
            SendMessage(hWnd, WM_DESTROY, 0, 0);
        }
    }
}

LRESULT Scene::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void Scene::RenderProc(HWND hWnd, UINT message, UINT idEvent, DWORD time)
{
    Update();

    RECT crt;
    GetClientRect(hWnd, &crt);
    HDC hDC = GetDC(hWnd);
    if (hBit == nullptr)
    {
        hBit = CreateCompatibleBitmap(hDC, crt.right, crt.bottom);
    }

    HDC hMemDC = CreateCompatibleDC(hDC);
    HBITMAP oldBit = (HBITMAP)SelectObject(hMemDC, hBit);

    HBRUSH myBrush = CreateSolidBrush(Constant::kBlack);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hMemDC, myBrush);
    FillRect(hMemDC, &crt, myBrush);
    SelectObject(hMemDC, oldBrush);
    DeleteObject(myBrush);
    SetBkMode(hMemDC, TRANSPARENT);

    Render(hMemDC);

    BitBlt(hDC, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);
    SelectObject(hMemDC, oldBit);
    DeleteDC(hMemDC);
    ReleaseDC(hWnd, hDC);
}

void Scene::DrawBitmap(HDC hdc, HBITMAP hBitmap, int x, int y, int width, int height)
{
    BITMAP bm;
    GetObject(hBitmap, sizeof(BITMAP), &bm);

    HDC hMemDC = CreateCompatibleDC(hdc);
    HBITMAP oldBit = (HBITMAP)SelectObject(hMemDC, hBitmap);

    StretchBlt(hdc, x, y, width, height, 
               hMemDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

    SelectObject(hMemDC, oldBit);
    DeleteDC(hMemDC);
}

GameObject* Scene::CreateCoin(int x, int y)
{
    auto coin = new GameObject;
    coin->Tag(Kind::kCoin);
    coin->Position(x * Constant::kScaleFactor, y * Constant::kScaleFactor);
    coin->Rect(coin->Position().x, coin->Position().y, Constant::kCoinWidth, Constant::kCoinHeight);
    return coin;
}
