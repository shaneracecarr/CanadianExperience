/**
 * @file IKeyFall.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_IKEYFALL_H
#define CANADIANEXPERIENCE_MACHINELIB_IKEYFALL_H
/**
 *  Class to handle when the key drops into the cam
 */
class IKeyFall {
public:
    /**
     * Pure virtual function to handle the key fall.
     * Derived classes must provide an implementation for this function.
     */
    virtual void KeyFall() = 0;

    /**
     * Virtual destructor for IKeyFall.
     */
    virtual ~IKeyFall() = default;
};



#endif //CANADIANEXPERIENCE_MACHINELIB_IKEYFALL_H
