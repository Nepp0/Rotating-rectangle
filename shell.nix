{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  # List of packages to include in environment
  buildInputs = [
    # Compiler and build tools
    pkgs.gcc      # C/C++ compiler
    pkgs.cmake    # Build system
    pkgs.pkg-config # Dependency resolver

    # OpenGL libraries
    pkgs.glfw-wayland
    pkgs.mesa     # OpenGL implementation
    pkgs.glew     # OpenGL extension loader
    pkgs.glm      # Math library for OpenGL
    pkgs.vulkan-headers # Optional: For Vulkan support
    # Optional: Debugging tools
    pkgs.gdb      # Debugger
    pkgs.renderdoc # Graphics debugger
    pkgs.libGL
  ];
  # Environment variables (optional)
  shellHook = ''
    export XDG_SESSION_TYPE=wayland
    export WAYLAND_DISPLAY=wayland-1
    # Help CMake find libraries
    export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath [ pkgs.mesa pkgs.glfw pkgs.glew ]}:$LD_LIBRARY_PATH
  '';
}
