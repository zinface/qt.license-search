
cmake_minimum_required(VERSION 3.5.1)

project(template LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Widgets Network)

# 头文件目录
include_directories()

# 资源文件路径
set(QRC_SOURCES "")

add_subdirectory(LicenceInfoObject)
add_subdirectory(NetworkRequest)
add_subdirectory(LicenceInfoManage)

add_executable(${PROJECT_NAME} "main.cpp"
    "mainwindow.cpp" "mainwindow.h" 
    ${QRC_SOURCES}
)
# target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Network)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${LicenceInfoObject_INCLUDE_DIRS}
    ${NetworkRequest_INCLUDE_DIRS}
    ${LicenceInfoManage_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Network
    ${LicenceInfoObject_LIBRARIES}
    ${NetworkRequest_LIBRARIES}
    ${LicenceInfoManage_LIBRARIES}
)
