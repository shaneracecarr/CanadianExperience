/**
 * @file Cam.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CAM_H
#define CANADIANEXPERIENCE_MACHINELIB_CAM_H

#include "Component.h"
#include "RotationSink.h"
#include "Polygon.h"
#include "IKeyFall.h"

/// Width of the cam on the screen in pixels
const double CamWidth = 17;

/// Cam diameter
const double CamDiameter = 60;

/// How big is the hole in the cam?
const double HoleSize = 8;

/// The key image
const std::wstring KeyImage = L"/key.png";

/// The key image size
const int KeyImageSize = 20;

/// The amount the key drops into the hole
const int KeyDrop = 10;

/**
 * Class that represents the cam component.
 *
 * The cam manages rotation and detects when a key drops into its hole.
 */
class Cam : public Component, public RotationSink
{
private:
    /// Current rotation of the cam
    double mRotation = 0;

    /// The key image
    cse335::Polygon mKey;

    /// Has the key dropped into the cam hole?
    bool mKeyDropped = false;

    /// List of components that listen for the key fall event
    std::vector<IKeyFall*> mKeyFallListeners;

public:
    /**
     * Constructor
     * @param imagesDir Directory containing the key image
     */
    Cam(const std::wstring& imagesDir);

    /**
     * Draw the cam component.
     * @param graphics Graphics context used to draw the cam.
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Draw the cam's foreground.
     * @param graphics Graphics context used to draw the cam's foreground.
     */
    void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Update the cam's state based on elapsed time.
     * @param elapsed Elapsed time in seconds since last update.
     */
    void Update(double elapsed) override;

    /**
     * Set the cam's rotation angle.
     * @param rotation New rotation angle.
     */
    void SetRotation(double rotation) override;

    /**
     * Add a listener for the key fall event.
     * @param listener Pointer to the key fall listener.
     */
    void AddKeyFallListener(IKeyFall* listener) { mKeyFallListeners.push_back(listener); }

    /// Reset the cam to its initial state.
    void Reset() override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CAM_H
