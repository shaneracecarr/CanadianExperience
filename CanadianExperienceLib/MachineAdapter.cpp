/**
 * @file MachineAdapter.cpp
 * @author Shane Carr
 */

#include "pch.h"
#include "MachineAdapter.h"

/**
 * Constructor
 * @param name The drawable name to use
 * @param resourcesDir Directory containing the machine resources
 */
MachineAdapter::MachineAdapter(const std::wstring& name, const std::wstring& resourcesDir)
    : Drawable(name), mResourcesDir(resourcesDir)
{
    MachineSystemFactory factory(resourcesDir);
    mMachineSystem = factory.CreateMachineSystem();

}


/**
 * Draw the machine at the current location
 * @param graphics Graphics object to render to
 */
void MachineAdapter::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    wxPoint location;
    if(GetName() == L"Machine1")
    {
        location = wxPoint(400, 600);  // Center
    }
    else
    {
        location = wxPoint(600, 10);  // Right of center
    }


    mMachineSystem->SetLocation(location);
    mMachineSystem->DrawMachine(graphics);
}

/**
 * Test if we hit the machine
 * @param pos Position to test
 * @return True if we hit the machine
 */
bool MachineAdapter::HitTest(wxPoint pos)
{

    wxPoint machinePos = mMachineSystem->GetLocation();
    int dx = abs(pos.x - machinePos.x);
    int dy = abs(pos.y - machinePos.y);

    return dx < 50 && dy < 50;
}

/**
 * Handle updates for animation
 * @param frame The current frame being drawn
 */
void MachineAdapter::SetFrame(int frame)
{


    if (frame >= mStartFrame)
    {
        int runningFrame = frame - mStartFrame;
        mMachineSystem->SetMachineFrame(runningFrame);
    }
    else
    {
        mMachineSystem->SetMachineFrame(0);
    }
}

/**
 * Change the machine number
 * @param machine New machine number
 */
void MachineAdapter::SetMachineNumber(int machine)
{
    mMachineNumber = machine;
    mMachineSystem->ChooseMachine(machine);
}

/**
 * Save this drawable to XML
 * @param node Node to save to
 */
void MachineAdapter::XmlSave(wxXmlNode* node)
{
    node->AddAttribute(L"type", L"machine");
    node->AddAttribute(L"name", GetName());
    node->AddAttribute(L"machine", wxString::Format(wxT("%i"), mMachineNumber));
    node->AddAttribute(L"start", wxString::Format(wxT("%i"), mStartFrame));
}

/**
 * Load this drawable from XML
 * @param node Node to load from
 */
void MachineAdapter::XmlLoad(wxXmlNode* node)
{
    mMachineNumber = wxAtoi(node->GetAttribute(L"machine", L"1"));
    mStartFrame = wxAtoi(node->GetAttribute(L"start", L"0"));
    SetMachineNumber(mMachineNumber);
}

/**
 * Show the dialog box for this machine
 * @param parent Parent window for the dialog box
 */
void MachineAdapter::ShowDialogBox(wxWindow* parent)
{
    MachineDialog dialog(parent, mMachineSystem);
    if(dialog.ShowModal() == wxID_OK)
    {
        // The machine number updates automatically
        mMachineNumber = mMachineSystem->GetMachineNumber();
    }
}
