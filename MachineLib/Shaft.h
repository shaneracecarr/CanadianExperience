/**
 * @file Shaft.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_SHAFT_H
#define CANADIANEXPERIENCE_MACHINELIB_SHAFT_H

#include "Component.h"
#include "Cylinder.h"
#include "RotationSink.h"
#include "RotationSource.h"

/**
 * Class that represents a rotating shaft in the machine.
 *
 * The Shaft class is a component that gets its rotation from a Crank and transmits this rotation to other components.
 * It is rendered as a cylinder and provides the necessary interfaces to update and manage its rotation.
 */
class Shaft : public Component, public RotationSink
{
private:
    /// The cylinder used to render the shaft visually
    cse335::Cylinder mRod;

    /// Current rotation of the shaft in turns (set by Crank)
    double mRotation = 0;

    /// Rotation source to propagate rotation to connected components
    RotationSource mSource;

public:

    /// Copy constructor (disabled)
    Shaft(const Shaft &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Shaft &) = delete;

    /**
     * Constructor to create a Shaft component.
     */
    explicit Shaft(double length);

    /**
     * Draw the shaft component.
     * @param graphics Graphics context for rendering.
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Draw the foreground elements of the shaft.
     * @param graphics Graphics context for rendering.
     */
    void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Update the shaft state over time.
     * @param elapsed time past
     */
    void Update(double elapsed) override;

    /**
     * Get the source of rotation for the shaft.
     * @return Pointer to the RotationSource object.
     */
    RotationSource* GetSource() { return &mSource; }

    /**
     * Set the rotation of the shaft.
     * @param rotation The new rotation value in turns.
     */
    void SetRotation(double rotation) override
    {
        mRotation = rotation;
        mSource.SetRotation(rotation);  // Pass rotation to any connected components
    }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_SHAFT_H
