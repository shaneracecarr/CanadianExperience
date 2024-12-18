/**
 * @file Shaft.cpp
 * @author Shane Carr
 */

#include "pch.h"
#include "Shaft.h"

/// The color to draw the shaft
const wxColour ShaftColor = wxColour(220, 220, 220);

/// The color to draw the lines on the shaft
const wxColour ShaftLineColor = wxColour(100, 100, 100);

/// The width to draw the lines on the shaft
const int ShaftLinesWidth = 1;

/// The number of lines to draw on the shaft
const int ShaftNumLines = 4;

/**
 * Constructor
 * @param length Length of the shaft
 */
Shaft::Shaft(double length)
{
    // Configure the rod (cylinder)
    mRod.SetColour(ShaftColor);
    mRod.SetLines(ShaftLineColor, ShaftLinesWidth, ShaftNumLines);
    mRod.SetSize(7, length);
}

void Shaft::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(GetX(), GetY());

    mRod.Draw(graphics, 0, 0, mRotation);


    graphics->PopState();
}

void Shaft::DrawForeground(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Nothing to draw in foreground
}

void Shaft::Update(double elapsed)
{
    // Nothing to update - rotation comes from Crank
}
