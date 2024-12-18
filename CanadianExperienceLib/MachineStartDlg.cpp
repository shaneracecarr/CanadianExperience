/**
 * @file MachineStartDlg.cpp
 * @author Shane Carr
 */

#include "pch.h"
#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>
#include <wx/spinctrl.h>

#include "MachineStartDlg.h"
#include "Timeline.h"

/**
 * Constructor
 * @param parent The parent window
 * @param timeline Timeline we are editing
 */
MachineStartDlg::MachineStartDlg(wxWindow* parent, Timeline* timeline) : mTimeline(timeline)
{
    wxXmlResource::Get()->LoadDialog(this, parent, L"MachineStartDlg");

    // Get the current values
    mMachine1Start = timeline->GetMachine1StartFrame();
    mMachine2Start = timeline->GetMachine2StartFrame();

    Bind(wxEVT_BUTTON, &MachineStartDlg::OnOK, this, wxID_OK);

    // Set up spin control for machine 1
    auto machine1Ctrl = XRCCTRL(*this, "Machine1StartTime", wxSpinCtrl);
    machine1Ctrl->SetRange(0, timeline->GetNumFrames());
    machine1Ctrl->SetValue(mMachine1Start);

    // Set up spin control for machine 2
    auto machine2Ctrl = XRCCTRL(*this, "Machine2StartTime", wxSpinCtrl);
    machine2Ctrl->SetRange(0, timeline->GetNumFrames());
    machine2Ctrl->SetValue(mMachine2Start);
}

/**
 * Handle an OK button press
 * @param event Button event
 */
void MachineStartDlg::OnOK(wxCommandEvent& event)
{
    auto machine1Ctrl = XRCCTRL(*this, "Machine1StartTime", wxSpinCtrl);
    auto machine2Ctrl = XRCCTRL(*this, "Machine2StartTime", wxSpinCtrl);

    // Get the values from the controls
    mMachine1Start = machine1Ctrl->GetValue();
    mMachine2Start = machine2Ctrl->GetValue();



    mTimeline->SetMachine1StartFrame(mMachine1Start);
    mTimeline->SetMachine2StartFrame(mMachine2Start);

    EndModal(wxID_OK);
}
