
cmake_minimum_required(VERSION 2.4)  
project( Display )  
find_package( OpenCV REQUIRED )  
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( Display Display.cpp )  
target_link_libraries( Display ${OpenCV_LIBS} ) 
————————————————
版权声明：本文为CSDN博主「Merle314」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/ustczhang/article/details/79027655
PROJECT(BACKGROUND_SPLIT)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

FIND_PACKAGE(OpenCV REQUIRED)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)

INCLUDE_DIRECTORIES(./)
INCLUDE_DIRECTORIES(./src)

# BGDifference锛岄珮鏂儗鏅樊鍒嗘硶鍔ㄦ�侀摼鎺ュ簱鐢熸垚
SET(LIB_BGDIFF_SOURCE
	./src/BGDifference/BGDifference.h
	./src/BGDifference/BGDifference.cpp)
ADD_LIBRARY(BGDiff SHARED ${LIB_BGDIFF_SOURCE})
TARGET_LINK_LIBRARIES(BGDiff
	${OpenCV_LIBS})

# ViBe鍔ㄦ�侀摼鎺ュ簱鐢熸垚
SET(LIB_VIBE_SOURCE
	./src/ViBe/Vibe.h
	./src/ViBe/Vibe.cpp)
ADD_LIBRARY(vibe SHARED ${LIB_VIBE_SOURCE})
TARGET_LINK_LIBRARIES(vibe
	${OpenCV_LIBS})

# ViBe+鍔ㄦ�侀摼鎺ュ簱鐢熸垚
SET(LIB_VIBEPLUS_SOURCE
	./src/ViBe+/ViBePlus.h
	./src/ViBe+/ViBePlusMacro.h
	./src/ViBe+/ViBePlus.cpp)
ADD_LIBRARY(vibe+ SHARED ${LIB_VIBEPLUS_SOURCE})
TARGET_LINK_LIBRARIES(vibe+
	${OpenCV_LIBS})

# 鐢熸垚FrameDifference娴嬭瘯绋嬪簭
ADD_EXECUTABLE(FrameDifference_test ./src/FramesDifference/main.cpp)
TARGET_LINK_LIBRARIES(FrameDifference_test
	${OpenCV_LIBS})


# 鐢熸垚BGDifference娴嬭瘯绋嬪簭
SET(LIB_BGDIFF BGDiff)
ADD_EXECUTABLE(BGDiff_test ./src/BGDifference/main.cpp)
TARGET_LINK_LIBRARIES(BGDiff_test
	${LIB_BGDIFF})

# 鐢熸垚ViBe娴嬭瘯绋嬪簭
SET(LIB_VIBE vibe)
ADD_EXECUTABLE(vibe_test ./src/ViBe/main.cpp)
TARGET_LINK_LIBRARIES(vibe_test
	${LIB_VIBE})

# 鐢熸垚ViBe+娴嬭瘯绋嬪簭
SET(LIB_VIBEPLUS vibe+)
ADD_EXECUTABLE(vibe+_test ./src/ViBe+/main.cpp)
TARGET_LINK_LIBRARIES(vibe+_test
	${LIB_VIBEPLUS})
