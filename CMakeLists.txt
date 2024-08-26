cmake_minimum_required(VERSION 3.16)

project(aplikacija VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (ANDROID)
    include(FetchContent)
    FetchContent_Declare(
        android_openssl
        DOWNLOAD_EXTRACT_TIMESTAMP true
        URL https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip
    )
    FetchContent_MakeAvailable(android_openssl)
    include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)
endif()
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Core Network)

qt_standard_project_setup()

qt_add_executable(appaplikacija
    main.cpp
)

qt_add_qml_module(appaplikacija
    URI aplikacija
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES smtpmanager.h smtpmanager.cpp
)

include_directories(.)

# Add your custom library
add_library(MyLibrary SHARED
    emailaddress.cpp
    mimeattachment.cpp
    mimebytearrayattachment.cpp
    mimefile.cpp
    mimehtml.cpp
    mimeinlinefile.cpp
    mimemessage.cpp
    mimepart.cpp
    mimetext.cpp
    smtpclient.cpp
    quotedprintable.cpp
    mimemultipart.cpp
    mimecontentencoder.cpp
    mimebase64encoder.cpp
    mimeqpencoder.cpp
    mimeqpformatter.cpp
    mimebase64formatter.cpp
    mimecontentformatter.cpp

)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appaplikacija PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appaplikacija
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
# Link Qt Core to MyLibrary
target_link_libraries(MyLibrary
    PRIVATE Qt6::Core
    PRIVATE Qt6::Network
)
target_link_libraries(appaplikacija
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Core
    MyLibrary
)

include(GNUInstallDirs)
install(TARGETS appaplikacija
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
if (ANDROID)
    add_android_openssl_libraries(appaplikacija MyLibrary)
endif()



