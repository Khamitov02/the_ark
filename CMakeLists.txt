# cmake_minimum_required(VERSION <specify CMake version here>)
project(the_ark)

set(CMAKE_CXX_STANDARD 17)

add_executable(the_ark main.cpp TheArk.cpp Service.cpp TechnicalService.cpp TechnicalService.h BiologicalService.cpp BiologicalService.h MedicalService.cpp MedicalService.h NavigationService.cpp NavigationService.h EmergencyService.cpp EmergencyService.h SocialService.cpp SocialService.h Population.cpp Population.h Resources.cpp Resources.h)