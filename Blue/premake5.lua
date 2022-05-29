workspace "Blue"
    configurations {"Release"}

project "blue"
    kind "StaticLib"
    language "C++"
    files {"src/**.cpp", "include/**.h", "src/**.c"}
    includedirs {"include"}
    libdirs {"lib"}
    links {"glfw3", "msdfgl", "Cocoa.framework", "IOKit.framework", "CoreVideo.framework", "OpenGL.framework", "freetype"}