/**
 * @file Machine.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

#include <wx/graphics.h>
#include "Component.h"
/**
 * Class that represents a machine composed of multiple components.
 *
 * The Machine class manages all components, updates their states over time,
 * and handles rendering of the machine as a whole.
 */
class Machine
{
private:
    /// Flags used for testing purposes
    int mFlag = 0;

    /// Unique identifier for this machine
    int mMachineNumber = 0;

    /// List of components that make up the machine
    std::vector<std::shared_ptr<Component>> mComponents;

    /// Current time of the machine's animation
    double mTime = 0;

public:
    /// Default constructor
    Machine();

    /// Copy constructor (disabled)
    Machine(const Machine &) = delete;

    /// Assignment operator (disabled)
    void operator=(const Machine &) = delete;

    /**
     * Draw the machine and all its components.
     * @param graphics Graphics context used for rendering the machine.
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Update the state of the machine and its components.
     * @param elapsedTime Time elapsed since the last update, in seconds.
     */
    void Update(double elapsedTime);

    /**
     * Add a component to the machine.
     * @param component Shared pointer to the component to be added.
     */
    void AddComponent(std::shared_ptr<Component> component);

    /**
     * Set the current time of the machine's animation.
     * @param time New time to set, in seconds.
     */
    void SetTime(double time) { mTime = time; }

    /// Reset the machine and all its components to their initial state.
    void Reset();

    /**
     * Advance the machine's animation time.
     * @param delta Amount of time to advance, in seconds.
     */
    void Advance(double delta);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
