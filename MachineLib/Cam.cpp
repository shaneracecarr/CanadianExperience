/**
 * @file Cam.cpp
 * @author Shane Carr
 */
#include "pch.h"
#include "Cam.h"


Cam::Cam(const std::wstring& imagesDir)
{
    // Configure the key
    mKey.SetImage(imagesDir + KeyImage);
    mKey.Rectangle(-KeyImageSize/2, 0, KeyImageSize, KeyImageSize);
}

void Cam::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(GetX(), GetY());

    // Draw the key
    double baseKeyY =  -CamDiameter/2;  // This puts bottom of key at cam's top
    double dropDistance = mKeyDropped ? KeyDrop : 0;  // Drop by KeyDrop when triggered

    mKey.DrawPolygon(graphics, 0, baseKeyY + dropDistance);

    // Draw the cam body
    wxBrush brush(*wxWHITE);
    wxPen pen(*wxBLACK);
    graphics->SetBrush(brush);
    graphics->SetPen(pen);
    graphics->DrawRectangle(-CamWidth/2, -CamDiameter/2, CamWidth, CamDiameter);

    if (mRotation <= 1.0)
    {
        // Start at bottom inside the rectangle and adjust travel distance
        double startY = (CamDiameter/2) - 10;  // Start 10 pixels in from bottom
        double endY = (-CamDiameter/2);        // End at top
        double totalDistance = startY - endY;   // Total distance to travel

        // Calculate current position
        double holeY = startY - (mRotation * totalDistance);

        double holeHeight = HoleSize;
        if (mRotation > 0.9)
        {
            double scaleProgress = (mRotation - 0.9) * 10;
            holeHeight = HoleSize * (1.0 - scaleProgress);
            holeHeight = std::max(holeHeight, 2.0);
        }
        graphics->SetBrush(*wxBLACK_BRUSH);
        graphics->DrawEllipse(-HoleSize/2, holeY, HoleSize, holeHeight);
    }



    graphics->PopState();

}

void Cam::SetRotation(double rotation)
{
    mRotation = rotation;

    // When dot reaches top (rotation = 1.0), trigger key fall
    if (mRotation >= 1.0 && !mKeyDropped)
    {
        mKeyDropped = true;
        for(auto listener : mKeyFallListeners)
        {
            listener->KeyFall();
        }
    }
}

void Cam::DrawForeground(std::shared_ptr<wxGraphicsContext> graphics)
{
}

void Cam::Update(double elapsed)
{
    // Nothing to update - rotation comes from source
}

void Cam::Reset()
{
    Component::Reset();  // Call base class reset

    // Reset cam-specific values
    mRotation = 0;
    mKeyDropped = false;
}