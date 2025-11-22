cmake_minimum_required(VERSION 3.10)
project(puzzle VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

add_executable(puzzle src/main.cpp)

target_link_libraries(puzzle PRIVATE
  ftxui::component
  ftxui::dom
  ftxui::screen
)
