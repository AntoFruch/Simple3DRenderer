add_library(lib_core
        App.cpp
        App.hpp
        polygons/Cube.cpp
        polygons/Cube.hpp
        polygons/Pyramid.cpp
        polygons/Pyramid.hpp
        polygons/Object3D.cpp
        polygons/Object3D.hpp

)

target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC sfml-graphics)
