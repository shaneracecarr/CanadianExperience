/**
 * @file Box.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BOX_H
#define CANADIANEXPERIENCE_MACHINELIB_BOX_H
#include "Component.h"

#include "Polygon.h"
#include "IKeyFall.h"
/**
 * The box of the machine, has a lid and 2 squares to create it.
 */
class Box : public Component, public IKeyFall
{
private:
    /// The box background image
    cse335::Polygon mBox;

    /// Image directory for pictures
    std::wstring mImagesDir;

    /// Size of the box
    int mBoxSize;

    /// Size of the lid
    int mLidSize;

    /// Boolean to know if the lid is open
    bool mOpen = false;

    /// Back plate of the box
    std::unique_ptr<cse335::Polygon> mBack;

    /// Front plate of the box
    cse335::Polygon mFront;

    /// Lid of the box
    cse335::Polygon mLid;

    /// Angle the lid is shown
    double mLidAngle = 0;

public:
    /**
     * Constructor for the Box class.
     * @param imagesDir Directory containing the images.
     * @param boxSize Size of the box.
     * @param lidSize Size of the lid.
     */
    Box(const std::wstring& imagesDir, int boxSize, int lidSize);

    /// Copy constructor (disabled)
    Box(const Box &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Box &) = delete;

    /**
     * Draw the foreground elements of the box.
     * @param graphics Graphics context used to draw the box foreground.
     */
    void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Draw the box and its components.
     * @param graphics Graphics context used to draw the box.
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Handle the key fall event.
     */
    void KeyFall() override;

    /**
     * Open or close the box lid.
     * @param open True to open the lid, false to close it.
     */
    void OpenBox(bool open);

    /**
     * Update the state of the box over time.
     * @param time The current time to update the box state.
     */
    void Update(double time) override;

    /**
     * Advance the state of the box by a time increment.
     */
    void Advance(double delta) override;

    /**
     * Reset the box to its initial state.
     */
    void Reset() override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_BOX_H
