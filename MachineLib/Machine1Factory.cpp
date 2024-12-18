/**
 * @file Machine1Factory.cpp
 * @author Shane Carr
 */


#include "pch.h"
#include "Machine1Factory.h"
#include "Machine.h"
#include "Box.h"
#include "Sparty.h"
#include "Crank.h"
#include "Shaft.h"
#include "Pulley.h"
#include "Cam.h"


/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";


/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
Machine1Factory::Machine1Factory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}



/**
 * Factory method to create machine #1
 * @return
 */
std::shared_ptr<Machine> Machine1Factory::Create()
{
    // The machine itself
    auto machine = std::make_shared<Machine>();

    /*
     * The Box class constructor parameters are:
     * @param imagesDir Directory containing the images
     * @param boxSize Size of the box in pixels (just the box, not the lid)
     * @param lidSize Size of the lid in pixels
     */
    auto box = std::make_shared<Box>(mImagesDir, 250, 240);
    //box->SetPosition(500,500); //I am putting the box at 500, 500 but i do not know if that is the right approach to gettign the box in the correct location

    // This simulates the cam key drop so the box will immediately open
    //box->KeyDrop();
    machine->AddComponent(box);



    /*
     * The Sparty class constructor parameters are:
     * @param image Image file to load
     * @param size Size to draw Sparty (width and height)
     * @param springLength How long the spring is when fully extended in pixels
     * @param springWidth How wide the spring is in pixels
     * @param numLinks How many links (loops) there are in the spring
     */
    auto sparty = std::make_shared<Sparty>(mImagesDir + L"/sparty.png", 212, 260, 80, 15);

    // This simulates the cam key drop so Sparty will immediately pop up
    //sparty->KeyDrop();
    machine->AddComponent(sparty);

    auto shaft1 = std::make_shared<Shaft>(80);
    shaft1->SetPosition(80, -175);
    machine->AddComponent(shaft1);

    auto crank = std::make_shared<Crank>();
    crank->SetPosition(150, -100);
    machine->AddComponent(crank);

    auto shaft2 = std::make_shared<Shaft>(230);
    shaft2->SetPosition(-115, -75);
    machine->AddComponent(shaft2);

    auto shaft3 = std::make_shared<Shaft>(60);
    shaft3->SetPosition(-115, -175);
    machine->AddComponent(shaft3);


    auto pulley1 = std::make_shared<Pulley>(20);
    pulley1->SetPosition(95, -175);
    machine->AddComponent(pulley1);

    auto pulley2 = std::make_shared<Pulley>(40);
    pulley2->SetPosition(95, -75);
    machine->AddComponent(pulley2);

    auto pulley3 = std::make_shared<Pulley>(10);
    pulley3->SetPosition(-105, -75);
    machine->AddComponent(pulley3);

    auto pulley4 = std::make_shared<Pulley>(40);
    pulley4->SetPosition(-105, -175);
    machine->AddComponent(pulley4);


    auto cam = std::make_shared<Cam>(mImagesDir);
    cam->SetPosition(-70, -175);
    machine->AddComponent(cam);

    shaft1->GetSource()->AddSink(pulley1.get());

    pulley1->BeltTo(pulley2.get());

    crank->GetSource()->AddSink(shaft1.get());

    pulley2->GetSource()->AddSink(shaft2.get());

    shaft2->GetSource()->AddSink(pulley3.get());

    pulley3->BeltTo(pulley4.get());

    pulley4->GetSource()->AddSink(shaft3.get());

    shaft3->GetSource()->AddSink(cam.get());



    cam->AddKeyFallListener(box.get());  // or sparty.get()
    cam->AddKeyFallListener(sparty.get());


    return machine;
}