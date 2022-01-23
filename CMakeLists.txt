cmake_minimum_required(VERSION 3.17)
project(gym)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH D:/QT5/5.15.2/msvc2015_64)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Widgets Core Gui Sql LinguistTools REQUIRED)

set(QM qtbase_ru.qm)

file(GLOB_RECURSE CODE_FILES *.cpp)
file(GLOB_RECURSE HEADERS *.h)

qt5_add_resources (QRC_SOURCES resources.qrc)

add_executable(gym WIN32
    ${CODE_FILES}
    ${HEADERS}
    ${QRC_SOURCES}
    ${QM}
    )

option(BUILD_DOC "Build documentation" ON)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
    # build the docs
endif()

target_link_libraries(gym PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Sql)

install(FILES ${QM} DESTINATION bin)

install(TARGETS gym DESTINATION bin)

install(FILES ${PROJECT_SOURCE_DIR}/database.db DESTINATION bin)


install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc_doxygen/ DESTINATION bin/docs/)

install(FILES $<TARGET_FILE:Qt5::Core> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Gui> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Widgets> DESTINATION bin)
install(FILES $<TARGET_FILE:Qt5::Sql> DESTINATION bin)


install(FILES $<TARGET_FILE:Qt5::QSQLiteDriverPlugin> DESTINATION bin/sqldrivers)

install(FILES $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> DESTINATION bin/platforms)
install(FILES $<TARGET_FILE:Qt5::QWindowsDirect2DIntegrationPlugin> DESTINATION bin/platforms)
