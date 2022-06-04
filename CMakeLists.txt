cmake_minimum_required(VERSION 3.22)
set(PROJECT_NAME main)			# Установка переменной со списком исходников
project(${PROJECT_NAME})				# Название проекта
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

set(SOURCE_EXE main.cpp 
    
        build/Resource.rc
        headers/mics/exception.hpp sourse/mics/exception.cpp 
        headers/gui/windows/window.hpp sourse/gui/windows/window.cpp
        headers/gui/windows/infoBox.hpp sourse/gui/windows/infoBox.cpp
        headers/gui/windows/input.hpp sourse/gui/windows/input.cpp
        headers/mics/helper.hpp sourse/mics/helper.cpp
        headers/mics/Mouse.hpp sourse/mics/Mouse.cpp
        headers/mics/Keyboard.hpp sourse/mics/Keyboard.cpp
        headers/GDI/GDIPlusManager.hpp sourse/GDI/GDIPlusManager.cpp
        headers/mics/BitmapHelper.hpp sourse/mics/BitmapHelper.cpp
        headers/gui/buttons.hpp sourse/gui/buttons.cpp
        headers/gui/mics/rectCorner.hpp sourse/gui/mics/rectCorner.cpp
        headers/mics/query.hpp  sourse/mics/query.cpp
        headers/gui/ProgressBar.hpp  sourse/gui/ProgressBar.cpp
        App.hpp App.cpp
        
)	
find_package(libpqxx CONFIG COMPONENTS) # find_package(PostgreSQL REQUIRED)
find_package(gdiplus COMPONENTS)
add_executable(${PROJECT_NAME} WIN32 ${SOURCE_EXE})	# Создает исполняемый файл с именем main
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

