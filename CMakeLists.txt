cmake_minimum_required(VERSION 3.16)
project(gamebook)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra -Wno-long-long")

add_executable(gamebook
                src/CApplication.cpp src/CApplication.h
                src/CCreature.h
                src/CEntity.h
                src/CGame.cpp src/CGame.h
                src/CInventory.cpp src/CInventory.h
                src/CItem.cpp src/CItem.h
                src/CLocation.cpp src/CLocation.h
                src/CMonster.cpp src/CMonster.h
                src/COption.cpp src/COption.h
                src/CPlayer.cpp src/CPlayer.h
                src/CWizard.cpp src/CWizard.h
                src/EAction.cpp src/EAction.h
                src/EGameStatus.cpp src/EGameStatus.h
                src/interface.cpp src/interface.h
                src/main.cpp
                src/tools.cpp src/tools.h
                )
