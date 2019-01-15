if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++11 -g  ${CMAKE_CXX_FLAGS}")
    message(STATUS "optional:-std=c++11")   
endif(CMAKE_COMPILER_IS_GNUCXX)

find_package(OpenCV QUIET COMPONENTS core highgui imgproc imgcodecs tracking)
if(NOT OpenCV_FOUND)
    find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc tracking)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../../src)


add_executable(main main.cpp object.cpp tracking.cpp )
target_link_libraries(main ncnn ${OpenCV_LIBS})

add_executable(mobilenetssd_camera1 mobilenetssd_camera.cpp)
target_link_libraries(mobilenetssd_camera1 ncnn ${OpenCV_LIBS})
