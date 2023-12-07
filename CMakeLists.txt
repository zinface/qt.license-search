
cmake_minimum_required(VERSION 3.5.1)

project(license-search LANGUAGES CXX VERSION 0.2)

include(cmake/SparkEnvConfig.cmake)
include(cmake/SparkMacrosConfig.cmake)
include(cmake/SparkFindLibraries.cmake)
include(cmake/SparkFindQt5Config.cmake)
# include(cmake/SparkFindQt6Config.cmake)
# include(cmake/SparkMacrosExtendConfig.cmake)

# 资源文件路径
set(QRC_SOURCES "")

spark_add_executable_path(${PROJECT_NAME} src
    ${QRC_SOURCES}

    src/utils/NetworkRequest
    src/utils/LicenceInfoObject
    src/utils/LicenceInfoManage
)
target_link_qt5(${PROJECT_NAME})

include(cmake/SparkBuildGraphviz.cmake)


# 设置安装路径的前缀(默认为"/usr/local")
set(CMAKE_INSTALL_PREFIX "/opt")

# 设置执行 make install 时哪个目标应该被 install 到哪个位置
install(TARGETS ${PROJECT_NAME} 
    DESTINATION share/youwant/license-search) 

install(FILES assets/open_source_license.png
    DESTINATION share/youwant/license-search/icon) 

install(FILES assets/license-search.desktop
    DESTINATION share/applications)

# 注释行(使用方式)
find_package(SparkDebPackage PATHS ${CMAKE_SOURCE_DIR})
add_package_descript(cmake/spark-deb-package.descript)