
cmake_minimum_required(VERSION 2.4)  
project( Display )  
find_package( OpenCV REQUIRED )  
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( Display Display.cpp )  
target_link_libraries( Display ${OpenCV_LIBS} ) 
¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª
°æÈ¨ÉùÃ÷£º±¾ÎÄÎªCSDN²©Ö÷¡¸Merle314¡¹µÄÔ­´´ÎÄÕÂ£¬×ñÑ­ CC 4.0 BY-SA °æÈ¨Ð­Òé£¬×ªÔØÇë¸½ÉÏÔ­ÎÄ³ö´¦Á´½Ó¼°±¾ÉùÃ÷¡£
Ô­ÎÄÁ´½Ó£ºhttps://blog.csdn.net/ustczhang/article/details/79027655
PROJECT(BACKGROUND_SPLIT)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

FIND_PACKAGE(OpenCV REQUIRED)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)

INCLUDE_DIRECTORIES(./)
INCLUDE_DIRECTORIES(./src)

# BGDifferenceï¼Œé«˜æ–¯èƒŒæ™¯å·®åˆ†æ³•åŠ¨æ€é“¾æŽ¥åº“ç”Ÿæˆ
SET(LIB_BGDIFF_SOURCE
	./src/BGDifference/BGDifference.h
	./src/BGDifference/BGDifference.cpp)
ADD_LIBRARY(BGDiff SHARED ${LIB_BGDIFF_SOURCE})
TARGET_LINK_LIBRARIES(BGDiff
	${OpenCV_LIBS})

# ViBeåŠ¨æ€é“¾æŽ¥åº“ç”Ÿæˆ
SET(LIB_VIBE_SOURCE
	./src/ViBe/Vibe.h
	./src/ViBe/Vibe.cpp)
ADD_LIBRARY(vibe SHARED ${LIB_VIBE_SOURCE})
TARGET_LINK_LIBRARIES(vibe
	${OpenCV_LIBS})

# ViBe+åŠ¨æ€é“¾æŽ¥åº“ç”Ÿæˆ
SET(LIB_VIBEPLUS_SOURCE
	./src/ViBe+/ViBePlus.h
	./src/ViBe+/ViBePlusMacro.h
	./src/ViBe+/ViBePlus.cpp)
ADD_LIBRARY(vibe+ SHARED ${LIB_VIBEPLUS_SOURCE})
TARGET_LINK_LIBRARIES(vibe+
	${OpenCV_LIBS})

# ç”ŸæˆFrameDifferenceæµ‹è¯•ç¨‹åº
ADD_EXECUTABLE(FrameDifference_test ./src/FramesDifference/main.cpp)
TARGET_LINK_LIBRARIES(FrameDifference_test
	${OpenCV_LIBS})


# ç”ŸæˆBGDifferenceæµ‹è¯•ç¨‹åº
SET(LIB_BGDIFF BGDiff)
ADD_EXECUTABLE(BGDiff_test ./src/BGDifference/main.cpp)
TARGET_LINK_LIBRARIES(BGDiff_test
	${LIB_BGDIFF})

# ç”ŸæˆViBeæµ‹è¯•ç¨‹åº
SET(LIB_VIBE vibe)
ADD_EXECUTABLE(vibe_test ./src/ViBe/main.cpp)
TARGET_LINK_LIBRARIES(vibe_test
	${LIB_VIBE})

# ç”ŸæˆViBe+æµ‹è¯•ç¨‹åº
SET(LIB_VIBEPLUS vibe+)
ADD_EXECUTABLE(vibe+_test ./src/ViBe+/main.cpp)
TARGET_LINK_LIBRARIES(vibe+_test
	${LIB_VIBEPLUS})
