#pragma once

#include "Tags.h"

struct Vector2
{
    Vector2() : x(0), y(0) {}
    virtual ~Vector2() {}

    int x;
    int y;
};

struct Range
{
    Range() : minimum(0), maximum(0) {}
    Range(int min, int max) : minimum(min), maximum(max) {}
    virtual ~Range() {}

    int minimum;
    int maximum;
};

struct RoadAtX
{
    RoadAtX() : x(0) {}
    RoadAtX(int x) : x(x) {}
    virtual ~RoadAtX() {}

    int x;
    vector<Range> road;
};

struct RoadAtY
{
    RoadAtY() : y(0) {}
    RoadAtY(int y) : y(y) {}
    virtual ~RoadAtY() {}

    int y;
    vector<Range> road;
};

enum Direction
{
    kIdle,
    kToLeft,
    kUp,
    kToRight,
    kDown
};

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    void Position(int x, int y);
    void Position(Vector2 vec2);
    Vector2 Position();

    void Velocity(int x, int y);
    void Velocity(Vector2 vec2);
    Vector2 Velocity();

    void Tag(Kind kind);
    Kind Tag();

    void Color(COLORREF color);
    COLORREF Color();

    void NextDirection(Direction direction);
    Direction NextDirection();

    void Rect(int x, int y, int width, int height);
    void Rect(RECT rect);
    RECT Rect();

    void Move(vector<RoadAtX>& roadAtXs, vector<RoadAtY>& roadAtYs);

private:
    Vector2 _position;
    Vector2 _velocity;
    Kind _tag;
    COLORREF _color;
    Direction _nextDirection;
    RECT _rect;

    float enemyDirectionCoolDown;
};
