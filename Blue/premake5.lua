workspace "Blue"
    configurations {"Release"}

project "Blue"
    kind "StaticLib"
    language "C++"
    location "bin"
    files {"src/**.cpp", "include/**.h"}