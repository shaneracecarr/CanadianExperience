/**
 * @file Pulley.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H

#include "Component.h"
#include "Cylinder.h"
#include "RotationSink.h"
#include "RotationSource.h"
/**
 * Class that represents a Pulley component in the machine.
 *
 * The Pulley class handles rotation, belt connections to other pulleys, and rendering of the pulley and belt.
 * It functions as both a rotation sink and a rotation source for other machine components.
 */
class Pulley : public Component, public RotationSink
{
private:
    /// Radius of the pulley
    double mRadius = 20;

    /// Top hub cylinder of the pulley
    cse335::Cylinder mLeftHub;

    /// Bottom hub cylinder of the pulley
    cse335::Cylinder mRightHub;

    /// Main body cylinder of the pulley
    cse335::Cylinder mBody;

    /// Current rotation of the pulley in turns
    double mRotation = 0;

    /// Rotation source for transmitting rotation to other components
    RotationSource mSource;

    /// Pulley connected to this pulley via a belt
    Pulley* mBeltConnectedPulley = nullptr;

    /// The belt cylinder that visually connects two pulleys
    cse335::Cylinder mBelt;

public:
    /**
     * Constructor for a pulley component.
     * @param radius Radius of the pulley, defaults to 20.
     */
    explicit Pulley(double radius = 20);

    /**
     * Get a pointer to the rotation source of the pulley.
     * @return Pointer to the RotationSource object.
     */
    RotationSource* GetSource() { return &mSource; }

    /**
     * Get the radius of the pulley.
     * @return Pulley's radius as a double.
     */
    double GetRadius() const { return mRadius; }

    /// Copy constructor (disabled)
    Pulley(const Pulley &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Pulley &) = delete;

    /**
     * Draw the pulley component.
     * @param graphics Graphics context for rendering the pulley.
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Draw the foreground elements of the pulley.
     * @param graphics Graphics context for rendering.
     */
    void DrawForeground(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Update the pulley state over time.
     * @param elapsed Time elapsed since the last update, in seconds.
     */
    void Update(double elapsed) override;

    /**
     * Drive another pulley by connecting them.
     * @param pulley Pulley to drive.
     */
    void DrivePulley(Pulley* pulley);

    /// Update the rotation of this pulley and connected pulleys.
    void UpdateRotations();

    /**
     * Draw the belt between this pulley and a connected pulley.
     * @param graphics Graphics context for rendering the belt.
     */
    void DrawBelt(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Set the rotation of the pulley.
     * @param rotation New rotation value in turns.
     */
    void SetRotation(double rotation)override;

    /**
     * Connect this pulley to another pulley using a belt.
     * @param pulley Pulley to connect to.
     */
    void BeltTo(Pulley* pulley) { mBeltConnectedPulley = pulley; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
