cmake_minimum_required(VERSION 3.0.0)

set(MODULE_NAME "LicenceInfoObject")
set(${MODULE_NAME}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(${MODULE_NAME}_LIBRARIES ${MODULE_NAME} PARENT_SCOPE)


find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Network)


add_library(${MODULE_NAME}
    LicenceInfoObject.cpp LicenceInfoObject.h
)

target_link_libraries(${MODULE_NAME} Qt5::Core Qt5::Network)

# add_subdirectory(LicenceInfoObject)
# target_include_directories(${MODULE_NAME} PRIVATE
#     ${LicenceInfoObject_INCLUDE_DIRS}
# )
# target_link_libraries(${MODULE_NAME} Qt5::Core Qt5::Network
#     ${LicenceInfoObject_LIBRARIES}
# )
