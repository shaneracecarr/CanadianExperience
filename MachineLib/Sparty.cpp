/**
 * @file Sparty.cpp
 * @author Shane Carr
 */

#include "pch.h"
#include "Sparty.h"
#include "Component.h"

/**
 * Constructor for Sparty.
 *
 * Initializes the Sparty component with the given parameters, including the image path, size,
 * spring properties, and the polygon for Sparty. Sets the initial state as compressed.
 *
 * @param imagePath Path to the image file for Sparty.
 * @param size Size to draw Sparty.
 * @param springLength Full length of the spring when fully extended.
 * @param springWidth Width of the spring.
 * @param numLinks Number of links in the spring.
 */
Sparty::Sparty(const std::wstring& imagePath, int size, double springLength,
               double springWidth, int numLinks) :
    mImagePath(imagePath), mSize(size), mSpringWidth(springWidth),
    mNumLinks(numLinks)
{
    // Initially compressed
    mCompressedLength = springLength * 0.2;  // 20% of full length
    mSpringLength = springLength;  // Store the full spring length

    // Create the polygon for Sparty
    mSparty.Rectangle(-size/2, mCompressedLength / 2, size, size);
    mSparty.SetImage(imagePath);

    // Initialize at compressed state
    mPopupAngle = 0;
    mSpringLength = mCompressedLength;
}

/**
 * Draw Sparty at the current position with the spring attached.
 *
 * This method uses the provided graphics context to draw both Sparty's image and the spring.
 * It calculates Sparty's height based on the current spring length and animation angle.
 *
 * @param graphics The graphics context used to render Sparty and the spring.
 */
void Sparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Set up spring drawing
    wxPen springPen(SpringColor, SpringWireSize);
    graphics->SetPen(springPen);

    // Draw spring at base position
    DrawSpring(graphics, GetX(), GetY(), mSpringLength, mSpringWidth, mNumLinks);

    // Draw Sparty with bounce
    double s = sin(mPopupAngle);
    double height = mCompressedLength + s * (mSpringLength - mCompressedLength);

    // Add bouncing motion
    double bounceX = mHorizontalBounce * sin(GetTime() * mBounceFrequency);
    double bounceY = mVerticalBounce * cos(GetTime() * mBounceFrequency);

    graphics->PushState();
    graphics->Translate(GetX() + bounceX, GetY() - height + bounceY);
    mSparty.DrawPolygon(graphics, 0, 0);
    graphics->PopState();

    graphics->PopState();
}

/**
 * Update the Sparty animation based on elapsed time.
 *
 * This method updates the state of Sparty's spring animation. The logic for the popup effect
 * is currently handled in the `Advance` method, which governs the transition of the spring
 * and animation.
 *
 * @param elapsed Time elapsed since the last update.
 */
void Sparty::Update(double elapsed)
{
    // Animation logic could go here if needed, but it's handled in Advance()
}

/**
 * Trigger the key fall event to initiate Sparty's pop-up animation.
 *
 * This method sets a flag to indicate that the Sparty component should pop up.
 */
void Sparty::KeyFall()
{
    mPopped = true;  // Set flag to trigger animation
}

/**
 * Draw the spring attached to Sparty.
 *
 * This method renders a spring as a series of curves. The spring is drawn by alternating
 * between right and left side curves for each spring link.
 *
 * @param graphics Graphics context to draw the spring on.
 * @param x X-coordinate for the starting point of the spring.
 * @param y Y-coordinate for the starting point of the spring.
 * @param length Length of the spring.
 * @param width Width of the spring.
 * @param numLinks Number of links in the spring.
 */
void Sparty::DrawSpring(std::shared_ptr<wxGraphicsContext> graphics,
                        int x, int y, double length, double width, int numLinks)
{
    auto path = graphics->CreatePath();

    // Calculate bounce offsets
    double bounceX = mHorizontalBounce * sin(GetTime() * mBounceFrequency);
    double bounceY = mVerticalBounce * cos(GetTime() * mBounceFrequency);

    // Start at bottom (fixed point)
    double y1 = y;
    double linkLength = length / numLinks;

    // Left and right X values for the spring
    double xR = x + width / 2;
    double xL = x - width / 2;

    path.MoveToPoint(x, y1);

    // Draw each link with progressively more bounce effect
    for(int i = 0; i < numLinks; i++)
    {
        // Calculate how much this link should bounce (more effect near top)
        double bounceRatio = (double)i / numLinks;  // 0 at bottom, 1 at top
        double currentBounceX = bounceX * bounceRatio;
        double currentBounceY = bounceY * bounceRatio;

        auto y2 = y1 - linkLength;
        auto y3 = y2 - linkLength / 2;

        // Add bounce to control points
        path.AddCurveToPoint(xR + currentBounceX, y1,
                             xR + currentBounceX, y3 + currentBounceY,
                             x + currentBounceX, y3 + currentBounceY);

        path.AddCurveToPoint(xL + currentBounceX, y3 + currentBounceY,
                             xL + currentBounceX, y2 + currentBounceY,
                             x + currentBounceX, y2 + currentBounceY);

        y1 = y2;
    }

    graphics->StrokePath(path);
}


/**
 * Advance Sparty's animation state based on elapsed time.
 *
 * This method is responsible for advancing the pop-up effect, including adjusting the spring's
 * length and Sparty's angle based on the elapsed time.
 *
 * @param delta Time increment to advance the animation.
 */
void Sparty::Advance(double delta)
{
        Component::Advance(delta);

        double openAngle = M_PI / 2;

        if(mPopped && mPopupAngle < openAngle)
        {
            mPopupAngle += openAngle * delta / SpartyPopupTime;

            if(mPopupAngle > openAngle)
            {
                mPopupAngle = openAngle;
                // Start bounce when fully extended
                mHorizontalBounce = 20;  // Initial horizontal amplitude
                mVerticalBounce = 30;    // Initial vertical amplitude
            }

            double s = sin(mPopupAngle);
            mSpringLength = mCompressedLength + s * (260 - mCompressedLength);
        }

        // Apply bounce if popped up
        if(mPopupAngle >= openAngle)
        {

            // Decay the bounce amplitudes
            mHorizontalBounce *= mBounceDecay;
            mVerticalBounce *= mBounceDecay;
        }
}

/**
 * Reset Sparty to its initial state.
 *
 * This method resets the Sparty component to its initial compressed state, stopping any
 * ongoing animations.
 */
void Sparty::Reset()
{
    Component::Reset();
    mPopupAngle = 0;
    mPopped = false;
    mSpringLength = mCompressedLength;
    mHorizontalBounce = 0;
    mVerticalBounce = 0;
}