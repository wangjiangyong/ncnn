
find_package(OpenCV QUIET COMPONENTS core highgui imgproc imgcodecs tracking)
if(NOT OpenCV_FOUND)
    find_package(OpenCV REQUIRED COMPONENTS core highgui imgproc tracking )
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../src)

add_executable(squeezenet squeezenet.cpp)
target_link_libraries(squeezenet ncnn ${OpenCV_LIBS})

add_executable(fasterrcnn fasterrcnn.cpp)
target_link_libraries(fasterrcnn ncnn ${OpenCV_LIBS})

add_executable(rfcn rfcn.cpp)
target_link_libraries(rfcn ncnn ${OpenCV_LIBS})

add_executable(yolov2 yolov2.cpp)
target_link_libraries(yolov2 ncnn ${OpenCV_LIBS})

add_executable(yolov3 yolov3.cpp)
target_link_libraries(yolov3 ncnn ${OpenCV_LIBS})

add_executable(mobilenetv2ssdlite mobilenetv2ssdlite.cpp)
target_link_libraries(mobilenetv2ssdlite ncnn ${OpenCV_LIBS})

add_executable(mobilenetssd mobilenetssd.cpp)
target_link_libraries(mobilenetssd ncnn ${OpenCV_LIBS})

add_executable(mobilenetssd_camera mobilenetssd_camera.cpp)
target_link_libraries(mobilenetssd_camera ncnn ${OpenCV_LIBS})

add_executable(mobilenetssd_tracking_camera mobilenetssd_tracking_camera.cpp)
target_link_libraries(mobilenetssd_tracking_camera ncnn ${OpenCV_LIBS})

add_executable(squeezenetssd squeezenetssd.cpp)
target_link_libraries(squeezenetssd ncnn ${OpenCV_LIBS})

add_executable(shufflenetv2 shufflenetv2.cpp)
target_link_libraries(shufflenetv2 ncnn ${OpenCV_LIBS})
