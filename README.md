OpenGL Engine

Welcome to my OpenGL Engine project! This is a custom C++ engine built using OpenGL, featuring a 3D camera, a lighting system, and texture rendering.
Features

    3D Camera: Navigate and view scenes in a 3D space.
    Lighting System: Implements basic light sources to enhance visual realism.
    Texture Rendering: Adds detailed textures to objects for a more immersive visual experience.
    Core Rendering Pipeline: Set up for rendering 3D objects and environments.

Getting Started
Prerequisites

Ensure the following are available on your system:

    Microsoft Visual Studio 2019 or later
    OpenGL 4.5 or higher

External Libraries

This project relies on GLFW and GLM, which can be found in my GitHub repository:
External Libs Repository

    download the External Libs repository.
    Place the External Libs folder as showed in down place .

Project Structure

The project assumes the following layout:

c++/  
├── External Libs/       # Contains GLFW and GLM libraries  
├── OpenGLengine/        # Project folder  

Building and Running

    Open the OpenGLengine.sln file in Visual Studio.

    Configure the project:
        Set the appropriate build configuration (Debug or Release).
        Verify that the library paths for GLFW and GLM in the External Libs folder are correctly set in the project properties.

    Build and run the project directly from Visual Studio.

Future Enhancements

    Advanced lighting features, such as shadows and specular highlights
    Interaction mechanics for a dynamic 3D environment

Notes

This project is a personal learning endeavor in OpenGL and C++ programming. Feedback and suggestions are welcome!
