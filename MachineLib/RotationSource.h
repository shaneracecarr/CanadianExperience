/**
 * @file RotationSource.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#include <vector>
#include "RotationSink.h"
/**
 *  Class that allows a component to give rotation to another component
 */
class RotationSource {
private:
    /// The current rotation in turns
    double mRotation = 0;

    /// Collection of rotation sinks that receive our rotation
    std::vector<RotationSink*> mSinks;

public:
    /// Default constructor
    RotationSource() = default;

    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSource &) = delete;

    /// Add a sink to be rotated by this source
    /// @param sink The sink to add
    void AddSink(RotationSink* sink) { mSinks.push_back(sink); }

    /// Set the rotation and update all sinks
    /// @param rotation Rotation in turns
    void SetRotation(double rotation)
    {
        mRotation = rotation;
        // Update all connected sinks
        for (auto sink : mSinks)
        {
            sink->SetRotation(rotation);
        }
    }

    /// Get the current rotation
    /// @return Rotation in turns
    double GetRotation() const { return mRotation; }
};
#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
