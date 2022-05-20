workspace "main"
    configurations {"Release"}

project "main"
    kind "WindowedApp"
    language "C++"
    files {"src/**.cpp", "include/**.h"}
    includedirs {"include"}
    libdirs {"lib"}
    links {"blue", "glfw3", "Cocoa.framework", "IOKit.framework", "CoreVideo.framework", "OpenGL.framework"}