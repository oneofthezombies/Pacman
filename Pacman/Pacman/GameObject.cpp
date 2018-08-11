#include "stdafx.h"
#include "GameObject.h"
#include "Constants.h"
#include "Random.h"

GameObject::GameObject() :
    _position(Vector2()),
    _velocity(Vector2()),
    _tag(Kind::kIdle),
    _color(Constant::kBlack),
    _nextDirection(Direction::kIdle),
    _rect(RECT()),
    enemyDirectionCoolDown(1.0f)
{
}

GameObject::~GameObject()
{
}

void GameObject::Position(int x, int y)
{
    _position.x = x;
    _position.y = y;
}

void GameObject::Position(Vector2 vec2)
{
    _position = vec2;
}

Vector2 GameObject::Position()
{
    return _position;
}

void GameObject::Velocity(int x, int y)
{
    _velocity.x = x;
    _velocity.y = y;
}

void GameObject::Velocity(Vector2 vec2)
{
    _velocity = vec2;
}

Vector2 GameObject::Velocity()
{
    return _velocity;
}

void GameObject::Tag(Kind kind)
{
    _tag = kind;
}

Kind GameObject::Tag()
{
    return _tag;
}

void GameObject::Color(COLORREF color)
{
    _color = color;
}

COLORREF GameObject::Color()
{
    return _color;
}

void GameObject::NextDirection(Direction direction)
{
    _nextDirection = direction;
}

Direction GameObject::NextDirection()
{
    return _nextDirection;
}

void GameObject::Rect(int x, int y, int width, int height)
{
    _rect.left = x - width / 2;
    _rect.top = y - height / 2;
    _rect.right = x + width / 2;
    _rect.bottom = y + height / 2;
}

void GameObject::Rect(RECT rect)
{
    _rect = rect;
}

RECT GameObject::Rect()
{
    return _rect;
}

void GameObject::Move(vector<RoadAtX>& roadAtXs, vector<RoadAtY>& roadAtYs)
{
    for (auto& roadAtX : roadAtXs)
    {
        if (_position.x == roadAtX.x)
        {
            for (auto& road : roadAtX.road)
            {
                if (_position.y >= road.minimum &&
                    _position.y <= road.maximum)
                {
                    switch (_nextDirection)
                    {
                        case Direction::kUp:
                            if (Tag() == Kind::kEnemy)
                            {
                                Velocity(0, -Constant::kEnemySpeed);
                            }
                            else
                            {
                                Velocity(0, -Constant::kMovableGameObjectSpeed);
                            }
                            break;
                        case Direction::kDown:
                            if (Tag() == Kind::kEnemy)
                            {
                                Velocity(0, Constant::kEnemySpeed);
                            }
                            else
                            {
                                Velocity(0, Constant::kMovableGameObjectSpeed);
                            }
                            break;
                    }

                    _position.y += _velocity.y;

                    if (_position.y < road.minimum)
                    {
                        _position.y = road.minimum;
                    }

                    if (_position.y > road.maximum)
                    {
                        _position.y = road.maximum;
                    }

                    if (_position.y == road.minimum ||
                        _position.y == road.maximum)
                    {
                        switch (_nextDirection)
                        {
                            case Direction::kToLeft:
                                if (Tag() == Kind::kEnemy)
                                {
                                    Velocity(-Constant::kEnemySpeed, 0);
                                }
                                else
                                {
                                    Velocity(-Constant::kMovableGameObjectSpeed, 0);
                                }
                                break;
                            case Direction::kToRight:
                                if (Tag() == Kind::kEnemy)
                                {
                                    Velocity(Constant::kEnemySpeed, 0);
                                }
                                else
                                {
                                    Velocity(Constant::kMovableGameObjectSpeed, 0);
                                }
                                break;
                        }

                        if (Tag() == Kind::kEnemy)
                        {
                            NextDirection(static_cast<Direction>(RANDOM->GetIntFromTo(1,5)));
                        }
                    }
                }
            }
        }
    }

    for (auto& roadAtY : roadAtYs)
    {
        if (_position.y == roadAtY.y)
        {
            for (auto& road : roadAtY.road)
            {
                if (_position.x >= road.minimum &&
                    _position.x <= road.maximum)
                {
                    switch (_nextDirection)
                    {
                        case Direction::kToLeft:
                            if (Tag() == Kind::kEnemy)
                            {
                                Velocity(-Constant::kEnemySpeed, 0);
                            }
                            else
                            {
                                Velocity(-Constant::kMovableGameObjectSpeed, 0);
                            }
                            break;
                        case Direction::kToRight:
                            if (Tag() == Kind::kEnemy)
                            {
                                Velocity(Constant::kEnemySpeed, 0);
                            }
                            else
                            {
                                Velocity(Constant::kMovableGameObjectSpeed, 0);
                            }
                            break;
                    }

                    _position.x += _velocity.x;

                    if (_position.x < road.minimum)
                    {
                        _position.x = road.minimum;
                    }

                    if (_position.x > road.maximum)
                    {
                        _position.x = road.maximum;
                    }

                    if (_position.x == road.minimum ||
                        _position.x == road.maximum)
                    {
                        switch (_nextDirection)
                        {
                            case Direction::kUp:
                                if (Tag() == Kind::kEnemy)
                                {
                                    Velocity(0, -Constant::kEnemySpeed);
                                }
                                else
                                {
                                    Velocity(0, -Constant::kMovableGameObjectSpeed);
                                }
                                break;
                            case Direction::kDown:
                                if (Tag() == Kind::kEnemy)
                                {
                                    Velocity(0, Constant::kEnemySpeed);
                                }
                                else
                                {
                                    Velocity(0, Constant::kMovableGameObjectSpeed);
                                }
                                break;
                        }

                        if (Tag() == Kind::kEnemy)
                        {
                            NextDirection(static_cast<Direction>(RANDOM->GetIntFromTo(1, 5)));
                        }
                    }

                    if (_position.y == 176 && _position.x == 0)
                    {
                        _position.x = 1168;
                    }
                    else if (_position.y == 176 && _position.x == 1168)
                    {
                        _position.x = 0;
                    }
                }
            }
        }
    }

    _rect.left = _position.x - Constant::kMovableGameObjectWidth / 2;
    _rect.top = _position.y - Constant::kMovableGameObjectHeight / 2;
    _rect.right = _position.x + Constant::kMovableGameObjectWidth / 2;
    _rect.bottom = _position.y + Constant::kMovableGameObjectHeight / 2;
}
