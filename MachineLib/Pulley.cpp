/**
 * @file Pulley.cpp
 * @author Shane Carr
 */

#include "pch.h"
#include "Pulley.h"

///width of the pulley
const double PulleyHubWidth = 3;

/// How deep the belt is into the pulley
const double PulleyBeltDepth = 3;

/// The color to use for pulleys
const wxColour PulleyColor = wxColour(205, 250, 5);

/// The line color to use for the hub
const wxColour PulleyHubLineColor = wxColour(139, 168, 7);

/// The width to draw the lines on the hub
const int PulleyHubLineWidth = 4;

/// The number of lines to draw on a pulley is the int(diameter / 6.0)
const double PulleyHubLineCountDiviser = 6.0;

// In Pulley.cpp
Pulley::Pulley(double radius)
{
    mRadius = radius;
    // Calculate number of lines based on diameter
    int numLines = int((mRadius * 2) / PulleyHubLineCountDiviser);

    // Configure the side hub cylinders
    mLeftHub.SetColour(PulleyColor);
    mLeftHub.SetSize(mRadius * 2, PulleyHubWidth);
    mLeftHub.SetLines(PulleyHubLineColor, PulleyHubLineWidth, numLines);

    mRightHub.SetColour(PulleyColor);
    mRightHub.SetSize(mRadius * 2, PulleyHubWidth);
    mRightHub.SetLines(PulleyHubLineColor, PulleyHubLineWidth, numLines);

    // Configure the main body cylinder
    mBody.SetColour(PulleyColor);
    mBody.SetSize(mRadius * 1.5 - PulleyBeltDepth, PulleyHubWidth*3);

    mBelt.SetColour(*wxBLACK);
    mBelt.SetSize(PulleyBeltDepth, 0);
}

void Pulley::SetRotation(double rotation)
{
    mRotation = rotation;
    mSource.SetRotation(rotation);

    if (mBeltConnectedPulley != nullptr)
    {

        double scaledRotation = rotation;

        double speedRatio = double(mRadius) / double(mBeltConnectedPulley->GetRadius());
        mBeltConnectedPulley->SetRotation(scaledRotation * speedRatio);
    }
}

void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    graphics->PushState();

    graphics->Translate(GetX(), GetY());

    mBody.Draw(graphics, -2.75, 0, mRotation);

    // Draw the left hub
    mLeftHub.Draw(graphics, -PulleyHubWidth * 2, 0, mRotation);

    // Draw the right hub
    mRightHub.Draw(graphics, PulleyHubWidth * 2, 0, mRotation);

    graphics->PopState();

}

void Pulley::DrawForeground(std::shared_ptr<wxGraphicsContext> graphics)
{
    DrawBelt(graphics);
}

void Pulley::Update(double elapsed)
{
    // Nothing to update - rotation comes from source
}

void Pulley::DrawBelt(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mBeltConnectedPulley != nullptr)
    {
        graphics->PushState();

        double y1 = GetY();  // First pulley location
        double y2 = mBeltConnectedPulley->GetY();  // Second pulley location

        // Base center-to-center distance
        double diff = mRadius + mBeltConnectedPulley->GetRadius()-10;
        double beltHeight = abs(y2 - y1) + diff;
        mBelt.SetSize(beltHeight, PulleyHubWidth*3);

        // Draw from midpoint between the two pulleys
        double midpointY = (y1 + y2) / 2;
        double offset = (mRadius - mBeltConnectedPulley->GetRadius())/2;

        mBelt.SetLines(*wxWHITE, 2, 5);


        if (y1 > y2){
            mBelt.Draw(graphics, GetX() - 2.75, midpointY + offset, mRotation);
        }
        else{
            mBelt.Draw(graphics, GetX() - 2.75, midpointY - offset, mRotation);
        }


        graphics->PopState();
    }
}