/**
 * @file RotationSink.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
/**
 *  Interface class to handle updating the rotation of components being rotated.
 */
class RotationSink {
public:
    /// Default constructor
    RotationSink() = default;

    /// Copy constructor (disabled)
    RotationSink(const RotationSink &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSink &) = delete;

    /// Set the rotation of this sink
    /// @param rotation Rotation in turns
    virtual void SetRotation(double rotation) = 0;

    virtual ~RotationSink() = default;
};
#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
