/**
 * @file MachineSystem.cpp
 * @author Shane Carr
 */

#include "pch.h"
#include "MachineSystem.h"
#include "Machine.h"
#include "MachineCFactory.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"

MachineSystem::MachineSystem(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
    ChooseMachine(1);
}
void MachineSystem::SetLocation(wxPoint location)
{
 mLocation = location;
}
wxPoint MachineSystem::GetLocation()
{
    return mLocation;
}
void MachineSystem::SetFlag(int flag)
{

}
double MachineSystem::GetMachineTime()
{
    return mFrame / static_cast<double>(mFrameRate);
}
int MachineSystem::GetMachineNumber()
{
    return mMachineNumber;
}


/**
 * Set the machine number, creating the appropriate machine
 * @param machine Machine number
 */
void MachineSystem::ChooseMachine(int machine)
{

    mMachineNumber = machine;

    if(machine == 1)
    {
        Machine1Factory factory(mResourcesDir);
        mMachine = factory.Create();
    }
    else if(machine == 2)
    {
        Machine2Factory factory(mResourcesDir);
        mMachine = factory.Create();
    }
}


void MachineSystem::SetFrameRate(double rate)
{
    mFrameRate = rate;
}
/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystem::SetMachineFrame(int frame)
{
    if (frame < mFrame)
    {
        mFrame = 0;
        Reset();
    }

    while (mFrame < frame) {
        mFrame++;
        mTime = mFrame / mFrameRate;
        mMachine->Advance(1.0 / mFrameRate);
        mMachine->SetTime(mTime);
    }

}
/**
 * Draw the machine
 * @param graphics Graphics context to draw on.
 */
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    // This will put the machine where it is supposed to be drawn
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);


    mMachine->Draw(graphics);

    graphics->PopState();
}






void MachineSystem::Reset()
{
    mTime = 0;
    mFrame = 0;
    if(mMachine != nullptr)
    {
        mMachine->Reset();
    }
}