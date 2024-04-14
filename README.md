# Simple OpenGL Scene

Simple OpenGL Scene is a C++ project demonstrating a simple OpenGL scene with directional, point and spot light. This project is built using CMake.

## Prerequisites

This project has the following dependencies:

- C++ Compiler (GCC, Clang, MSVC, etc.)
- CMake (version 3.15 or higher)

Dependencies already included on the repository:

- GLEW
- GLFW
- GLM

## Building the Project

1. **Clone the Repository**

    First, clone the repository to your local machine:

    ```sh
    git clone https://github.com/yourusername/Simple_OpenGL_Scene.git
    cd Simple_OpenGL_Scene
    ```

2. **Generate Build System**

    Next, create a build directory and navigate into it:

    ```sh
    mkdir build && cd build
    ```

    Then, generate the build system with CMake:

    ```sh
    cmake ..
    ```

    Note: On Windows, you might need to specify the generator and architecture, for example:

    ```sh
    cmake .. -G "Visual Studio 16 2019" -A x64
    ```

3. **Build the Project**

    Once the build system is generated, compile the project:

    ```sh
    cmake --build build --config Release --target ALL_BUILD -j 14 --
    ```

## Running the Application

After building, you can find the executable in the `build` directory. Run it directly from the command line or through your file explorer.

On Linux or macOS:

```sh
./Simple_OpenGL_Scene
```

On Windows:

```sh
Simple_OpenGL_Scene.exe
```

## License

[Apache License](LICENSE)
