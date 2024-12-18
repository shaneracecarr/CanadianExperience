/**
 * @file MachineStartDlg.h
 * @author Shane Carr
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTDLG_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTDLG_H

class Timeline;

/**
 * Dialog box for setting machine start times
 */
class MachineStartDlg final : public wxDialog
{
private:
    /// The timeline we are editing
    Timeline* mTimeline;

    /// Start frame for machine 1
    int mMachine1Start;

    /// Start frame for machine 2
    int mMachine2Start;

    void OnOK(wxCommandEvent& event);

public:
    MachineStartDlg(wxWindow* parent, Timeline* timeline);
};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINESTARTDLG_H
