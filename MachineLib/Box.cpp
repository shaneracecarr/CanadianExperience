/**
 * @file Box.cpp
 * @author Shane Carr
 */

#include "pch.h"
#include "Box.h"

/// The background image to use
const std::wstring BoxBackgroundImage = L"/box-background.png";

/// The foreground image to use
const std::wstring BoxForegroundImage = L"/box-foreground.png";

/// The lid image to use
const std::wstring BoxLidImage = L"/box-lid.png";

/// The horizontal scale for the lid when the angle is zero

double LidZeroAngleScale = .02;


/// How long it takes to up the lid in seconds
const double LidOpeningTime = 0.25;



Box::Box(const std::wstring& imagesDir, int boxSize, int lidSize)
   :  mImagesDir(imagesDir), mBoxSize(boxSize), mLidSize(lidSize)
{
    mBox.Rectangle(-boxSize / 2, 0, boxSize, boxSize);
    mBox.SetImage(imagesDir + BoxBackgroundImage);




    mFront.Rectangle(-boxSize / 2, 0, boxSize, boxSize);
    mFront.SetImage(imagesDir + BoxForegroundImage);

    mLid.Rectangle(-lidSize / 2, 0, boxSize, lidSize);
    mLid.SetImage(imagesDir + BoxLidImage);


}

void Box::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{


graphics->PushState();

mBox.DrawPolygon(graphics, GetX(), GetY());

double s = sin(mLidAngle);
double lidScale = LidZeroAngleScale + s * (1.0-LidZeroAngleScale);


graphics->PushState();
graphics->Translate(GetX(), GetY() - mBoxSize);
graphics->Scale(1, lidScale);
mLid.DrawPolygon(graphics, 0, 0);
graphics->PopState();
}

void Box::KeyFall()
{
 mOpen = true;
}
void Box::OpenBox(bool open)
{

}
void Box::Update(double elapsed)
{
    // Detect when time goes backwards (reset)


//    SetTime(GetTime() + elapsed);
//
//    // Start opening after a certain time
//    if(GetTime() > 1.0 && mLidAngle < M_PI/2)
//    {
//        mLidAngle += elapsed * 2;  // Speed of opening
//        if(mLidAngle > M_PI/2)
//            mLidAngle = M_PI/2;
//    }
}
void Box::DrawForeground(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    graphics->Translate(GetX(), GetY());
    // Draw the front of the box last, so it appears on top
    mFront.DrawPolygon(graphics, 0, 0);

    graphics->PopState();
}

/**
 * Advance the animation in time
 * @param delta Amount of time to advance in seconds
 */
void Box::Advance(double delta)
{


    Component::Advance(delta);	// Upcall

    double openAngle = M_PI / 2;

    if(mOpen && mLidAngle < openAngle)
    {
        mLidAngle += openAngle * delta / LidOpeningTime;

        if(mLidAngle > openAngle)
        {
            mLidAngle = openAngle;
        }
    }
}


void Box::Reset()
{
    Component::Reset();  // Call base to reset time
    mLidAngle = 0;
    mOpen = false;
}
