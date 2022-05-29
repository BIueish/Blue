workspace "main"
    configurations {"Release"}

project "main"
    kind "ConsoleApp"
    language "C++"
    files {"src/**.cpp", "include/**.h"}
    includedirs {"include" }
    libdirs {"lib"}
    links {"blue", "glfw3", "msdfgl", "Cocoa.framework", "IOKit.framework", "CoreVideo.framework", "OpenGL.framework"}