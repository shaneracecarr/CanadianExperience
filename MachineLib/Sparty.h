/**
 * @file Sparty.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_SPARTY_H
#define CANADIANEXPERIENCE_MACHINELIB_SPARTY_H

#include "Component.h"

#include "Polygon.h"
#include "IKeyFall.h"

/**
 * Class that implements Sparty, a spring-loaded component in the machine.
 *
 * The Sparty class simulates a character that pops up when activated, represented by a polygon
 * and animated using a spring mechanism. It handles both the drawing and updating of Sparty's
 * state over time, including its spring and pop-up animation.
 */
class Sparty : public Component, public IKeyFall
{
private:
    /// The Sparty polygon used to draw the character
    cse335::Polygon mSparty;

    /// Path to the image used for the character
    std::wstring mImagePath;

    /// Size to draw Sparty
    int mSize = 0;

    /// Spring wire size
    const double SpringWireSize = 2;

    /// Minimum spacing between spring wire
    const double SpringWireMinSpacing = 1;

    /// Spring color
    const wxColour SpringColor = wxColour(220, 220, 220);

    /// Time for Sparty to pop up
    const double SpartyPopupTime = 0.25;

    /// Spring parameters
    double mSpringLength = 0;      ///< Current spring length
    double mSpringWidth = 0;       ///< Spring width
    int mNumLinks = 0;            ///< Number of spring links
    double mCompressedLength = 0;  ///< Length when compressed

    /// Current angle (for animation)
    double mPopupAngle = 0;

    /// Flag for whether Sparty is popped or not
    bool mPopped = false;

    /// Bounce parameters
    double mHorizontalBounce = 0;    /// Current horizontal offset
    double mVerticalBounce = 0;      /// Additional vertical bounce
    double mBounceDecay = 0.95;      /// How quickly bounce dies out
    double mBounceFrequency = 15;    /// Speed of bounce

public:
    /**
     * Constructor to create a Sparty component.
     */
    Sparty(const std::wstring &imagePath, int size, double springLength, double springWidth, int numLinks);

    /**
     * Draw the Sparty character.
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Draw the spring attached to Sparty.
     */
    void DrawSpring(std::shared_ptr<wxGraphicsContext> graphics, int x, int y,
                    double length, double width, int numLinks);

    /**
     * Update the Sparty component over time
     */
    void Update(double elapsed) override;

    /**
     * Activate the key fall action for Sparty (pop-up animation).
     */
    void KeyFall()override;

    /**
     * Draw the foreground elements of Sparty (no additional foreground for Sparty).
     * @param graphics Graphics context for rendering.
     */
    void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) override { }

    /**
     * Advance Sparty's state over time.
     */
    void Advance(double delta)override;

    /**
     * Reset Sparty to its initial state.
     */
    void Reset() override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_SPARTY_H
