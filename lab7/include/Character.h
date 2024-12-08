#pragma once

#include <memory>
#include <string>
#include <cmath>

struct Vec2 {
public:
    Vec2() = default;
    Vec2(double x, double y) : x(x), y(y) {}
    void Normalize() {
        x /= GetLenght();
        y /= GetLenght();
    }
    double GetLenght() const {
        return std::sqrt(x * x + y * y);
    }
    Vec2& operator+=(const Vec2& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Vec2& operator-=(const Vec2& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    Vec2& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vec2& operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }
    Vec2 operator*(double scalar) {
        Vec2 result = *this;
        result.x *= scalar;
        result.y *= scalar;
        return result;
    }
    Vec2 operator/(double scalar) {
        Vec2 result = *this;
        result.x /= scalar;
        result.y /= scalar;
        return result;
    }
    Vec2 operator+(double scalar) {
        Vec2 result = *this;
        result.x += scalar;
        result.y += scalar;
        return result;
    }
    Vec2 operator-(double scalar) {
        Vec2 result = *this;
        result.x -= scalar;
        result.y -= scalar;
        return result;
    }
public:
    double x;
    double y;
};

class Character {
public:
    Character(const std::string& name, double x, double y, float stepSize, float attackRange) 
        :
        name(name),
        pos({x, y}),
        stepSize(stepSize),
        attackRange(attackRange)
    {}
    const std::string& GetName() const noexcept { return name; }
    double GetPosX() const noexcept { return pos.x; }
    double GetPosY() const noexcept { return pos.y; }
    virtual std::string GetType() const = 0;
    bool IsAlive() const { return isAlive; }
    void Kill() { isAlive = false; }
    void Move(Vec2 dir) {
        dir.Normalize();
        pos += dir * stepSize;
    }
    float GetAttackRange() const {
        return attackRange;
    }
    void SetPosition(const Vec2& p) {
        pos.x = p.x;
        pos.y = p.y;
    }
    virtual bool Beats(const Character& other) const = 0;
    virtual ~Character() = default;
protected:
    std::string name;
    Vec2 pos;
    bool isAlive = true;
    float stepSize;
    float attackRange;
};

class Dragon : public Character {
public:
    Dragon(const std::string& name, double x, double y)
        :
        Character(name, x, y, 50, 30)
    {}
    virtual std::string GetType() const override {
        return "Dragon";
    }
    virtual bool Beats(const Character& other) const override {
        return other.GetType() == "Bull";
    }
};

class Bull : public Character {
public:
    Bull(const std::string& name, double x, double y)
        :
        Character(name, x, y, 30, 10)
    {}
    virtual std::string GetType() const override {
        return "Bull";
    }
    virtual bool Beats(const Character& other) const override {
        return other.GetType() == "Frog";
    }
};

class Frog : public Character {
public:
    Frog(const std::string& name, double x, double y)
        :
        Character(name, x, y, 1, 10)
    {}
    virtual std::string GetType() const override {
        return "Frog";
    }
    virtual bool Beats(const Character&) const override {
        return false;
    }
};