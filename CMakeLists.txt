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

target_sources(puzzle PRIVATE
  src/app/app_manager.cpp
  src/app/app_manager.hpp
  src/app/puzzle.cpp
  src/app/puzzle.hpp

  src/ui/screens/base_screen.cpp
  src/ui/screens/base_screen.hpp
  src/ui/screens/start_screen.cpp
  src/ui/screens/start_screen.hpp
  src/ui/screens/game_screen.cpp
  src/ui/screens/game_screen.hpp
  src/ui/screens/completed_screen.cpp
  src/ui/screens/completed_screen.hpp
)
