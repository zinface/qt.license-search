
cmake_minimum_required(VERSION 3.5.1)

project(license-search LANGUAGES CXX VERSION 0.2)

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
    "mainwindow.cpp" "mainwindow.h" "mainwindow.ui" 
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


# 设置安装路径的前缀(默认为"/usr/local")
set(CMAKE_INSTALL_PREFIX "/opt")

# 设置执行 make install 时哪个目标应该被 install 到哪个位置
install(TARGETS ${PROJECT_NAME} 
    DESTINATION share/youwant/license-search) 

install(FILES open_source_license.png
    DESTINATION share/youwant/license-search/icon) 

install(FILES license-search.desktop
    DESTINATION share/applications)

# package deb
find_package(DebPackage PATHS ${CMAKE_SOURCE_DIR})
add_package_descript(cmake/package-deb.descript)