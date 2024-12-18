/**
 * @file MachineAdapter.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H

#include "Drawable.h"

// Only allowed to include the API
#include <machine-api.h>

/**
 * Class that adapts the machine system to work as a Drawable
 *
 * This class adapts the machine system to work with
 * the Canadian Experience architecture as a Drawable object
 */

class MachineAdapter : public Drawable
{
private:
    /// The adapted machine system
    std::shared_ptr<IMachineSystem> mMachineSystem;

    /// The machine number
    int mMachineNumber = 1;

    /// The frame the machine starts running at
    int mStartFrame = 0;

    /// Directory containing resources for the machine
    std::wstring mResourcesDir;

public:
    /// Constructor
    MachineAdapter(const std::wstring& name, const std::wstring& resourcesDir);

    /// Default constructor (disabled)
    MachineAdapter() = delete;

    /// Copy constructor (disabled)
    MachineAdapter(const MachineAdapter&) = delete;

    /// Assignment operator (disabled)
    void operator=(const MachineAdapter&) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    bool HitTest(wxPoint pos) override;
    /**
 * Checks whether the machine is movable.
 * @return Returns true if the machine can be moved, false otherwise.
 */
    bool IsMovable() override { return true; }

    /**
     * Sets the machine number
     */
    void SetMachineNumber(int machine);

    /**
     * Gets the current machine number
     * @return Current machine number
     */
    int GetMachineNumber() const { return mMachineNumber; }

    /**
     * Set the starting frame for machine animation
     * @param frame Frame number machine starts at
     */
    void SetStartFrame(int frame) { mStartFrame = frame; }

    /**
     * Get the starting frame for machine animation
     * @return Starting frame number
     */
    int GetStartFrame() const { return mStartFrame; }

    void SetFrame(int frame);
    void XmlSave(wxXmlNode* node);
    void XmlLoad(wxXmlNode* node);

    /**
     * Show the dialog box for this machine
     * @param parent Parent window for the dialog box
     */
    void ShowDialogBox(wxWindow* parent);

    /**
 * Set the frame rate for the machine
 * @param rate New frame rate in frames per second
 */
    void SetFrameRate(double rate) { mMachineSystem->SetFrameRate(rate); }
};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEADAPTER_H
