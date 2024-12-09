OpenGL Engine

Welcome to my OpenGL Engine project! This is a custom C++ engine built using OpenGL, featuring a 3D camera and a lighting system.
Features

    3D Camera: Navigate and view scenes in a 3D space.
    Lighting System: Implements basic light sources to enhance visual realism.
    Core Rendering Pipeline: Set up for rendering 3D objects and environments.

Getting Started

Follow these steps to set up and run the project on a Windows environment.
Prerequisites

Ensure the following are installed on your system:

    Microsoft Visual Studio 2019 or later
    OpenGL 4.5 or higher
    GLFW, GLM AND GLEW libraries (included in the External Libs folder)

Project Structure

The project assumes the following directory layout:

c++/  
├── External Libs/       # Contains GLFW, GLM AND GLEW libraries  
├── OpenGLengine/        # Project folder  
    ├── src/             # Source code files  
    ├── shaders/         # GLSL shader files  
    ├── include/         # Header files  
    ├── OpenGLengine.sln # Visual Studio solution file  
    └── README.md        # Project documentation  

Building and Running

    Clone the repository:

    git clone https://github.com/YigitHamza47/OpenGLengine.git  

    Place the External Libs folder one level above the OpenGLengine project directory.

    Open the OpenGLengine.sln file in Visual Studio.

    Configure the project:
        Set the appropriate build configuration (Debug or Release).
        Ensure the library paths for GLFW and GLM in the External Libs folder are correctly configured in the project settings.

    Build and run the project directly from Visual Studio.


Notes

This project is a personal learning endeavor in OpenGL and C++ programming. Feedback and suggestions are welcome!
