#pragma once
#include "raylib.h"

class RenderComponent
{
public:
    //Virtual destructor to ensure proper destruction of derived class objects
    virtual ~RenderComponent();

    //Pure virtual functions, any class inheriting from this class must provide its own implementations
    virtual void Draw(int x, int y) const = 0;
    virtual void DrawTint(int x, int y, const Color& col) const = 0;
    virtual void Release() = 0;
 
    //Simple shapes rendering methods
    void DrawBox(int x, int y, int w, int h, const Color& col) const;
    void DrawCorners(int x, int y, int w, int h) const;

 private:
    void DrawPlus(int x, int y, int radius, const Color& col) const;
};

