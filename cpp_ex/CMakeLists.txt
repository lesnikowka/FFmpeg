set(target advanced_audio_info)

project(${target})

file(GLOB srcs "*.cpp*")
file(GLOB hdrs "*.hpp*")

add_executable(${target} ${srcs} ${hdrs})