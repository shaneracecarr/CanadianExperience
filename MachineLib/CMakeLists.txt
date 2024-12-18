project(MachineLib)
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.14)

set(SOURCE_FILES
        pch.h
        IMachineSystem.h
        MachineSystemFactory.cpp MachineSystemFactory.h
        MachineDialog.cpp MachineDialog.h include/machine-api.h
        Const.cpp
        Const.h
        MachineSystemStandin.h
        MachineSystemStandin.cpp
        MachineStandin.cpp
        MachineStandin.h
        Polygon.cpp
        Polygon.h
        Cylinder.cpp
        Cylinder.h
        MachineSystem.h
        MachineSystem.cpp
        Machine.h
        Machine.cpp
        MachineCFactory.h
        MachineCFactory.cpp
        Component.h
        Component.cpp
        Box.h
        Box.cpp
        IKeyDrop.cpp
        Sparty.h
        Sparty.cpp
        Crank.h
        Crank.cpp
        Shaft.h
        Shaft.cpp
        RotationSource.h
        RotationSink.h
        Pulley.h
        Pulley.cpp
        Cam.h
        Cam.cpp
        IKeyFall.h
        Machine1Factory.h
        Machine1Factory.cpp
        Machine2Factory.h
        Machine2Factory.cpp
)

find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
