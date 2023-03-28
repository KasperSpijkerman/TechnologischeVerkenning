# Install script for directory: /Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/build/JUCE/modules/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/build/JUCE/extras/Build/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/JUCE-7.0.5" TYPE FILE FILES
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/build/JUCE/JUCEConfigVersion.cmake"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/build/JUCE/JUCEConfig.cmake"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/JUCECheckAtomic.cmake"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/JUCEHelperTargets.cmake"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/JUCEModuleSupport.cmake"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/JUCEUtils.cmake"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/JuceLV2Defines.h.in"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/LaunchScreen.storyboard"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/PIPAudioProcessor.cpp.in"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/PIPAudioProcessorWithARA.cpp.in"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/PIPComponent.cpp.in"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/PIPConsole.cpp.in"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/RecentFilesMenuTemplate.nib"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/UnityPluginGUIScript.cs.in"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/checkBundleSigning.cmake"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/copyDir.cmake"
    "/Volumes/SSD_Kasper/HKU/Jaar_2/CSD2/Juce_Projects/JUCE/extras/Build/CMake/juce_runtime_arch_detection.cpp"
    )
endif()

