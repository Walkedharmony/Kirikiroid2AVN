cmake_minimum_required(VERSION 3.19)
project(layerExDraw)

set(LAYEREX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
    set(LAYEREX_CORE_SOURCES
            ${LAYEREX_SOURCE_DIR}/windows/LayerExDraw.cpp
    )
else()
    set(LAYEREX_CORE_SOURCES
            ${LAYEREX_SOURCE_DIR}/general/LayerExDraw.cpp
            ${LAYEREX_SOURCE_DIR}/general/DrawPath.cpp
    )
endif()

add_library(${PROJECT_NAME} STATIC ${LAYEREX_CORE_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
        "${PORTBUILD_PATH}/include/libgdiplus"
        "${PORTBUILD_PATH}/include/"
        "${PORTBUILD_PATH}/include/glib-2.0"
        "${PORTBUILD_PATH}/lib/glib-2.0/include"
        "${KRKR2PLUGIN_PATH}"
        "${COCOS2DX_PATH}/cocos/"
        ${KRKR2CORE_PATH}
        ${KRKR2CORE_PATH}/tjs2
        ${KRKR2PLUGIN_PATH}/ncbind
        ${PORTBUILD_PATH}/include
        ${KRKR2CORE_PATH}
        ${KRKR2CORE_PATH}/tjs2
        ${KRKR2CORE_PATH}/environ
        ${KRKR2CORE_PATH}/msg
        ${KRKR2CORE_PATH}/msg/win32
        ${KRKR2CORE_PATH}/utils
        ${KRKR2CORE_PATH}/utils/win32
        ${KRKR2CORE_PATH}/base
        ${KRKR2CORE_PATH}/base/win32
        ${KRKR2CORE_PATH}/sound
        ${KRKR2CORE_PATH}/sound/win32
        ${KRKR2CORE_PATH}/visual
        ${KRKR2CORE_PATH}/visual/win32
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        krkr2plugin
        "${PORTBUILD_PATH}/lib/libgdiplus.a"
        "${PORTBUILD_PATH}/lib/libglib-2.0.a"
        "${PORTBUILD_PATH}/lib/libtiff.a"
        "${PORTBUILD_PATH}/lib/libfreetype.a"
        "${PORTBUILD_PATH}/lib/libbz2.a"
        "${PORTBUILD_PATH}/lib/liblzma.a"
        "${PORTBUILD_PATH}/lib/libbrotlidec.a"
        "${PORTBUILD_PATH}/lib/libbrotlicommon.a"
        "${PORTBUILD_PATH}/lib/libbrotlienc.a"
)

if(WIN32)
    add_executable(${PROJECT_NAME}_main
            ${LAYEREX_SOURCE_DIR}/windows/main.cpp
    )
else()
    add_executable(${PROJECT_NAME}_main
            ${LAYEREX_SOURCE_DIR}/general/main.cpp
    )
endif()

target_link_libraries(${PROJECT_NAME}_main PRIVATE ${PROJECT_NAME})
