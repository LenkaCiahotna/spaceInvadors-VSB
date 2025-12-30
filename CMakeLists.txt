cmake_minimum_required(VERSION 3.12)

project(catventure C)

# Přidání přepínačů překladače
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")

# Najdi SDL2 a SDL2_image
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Vytvoření spustitelného souboru
add_executable(catventure  catventure.c sdl.c defs.h sprites.c menu.c guide.c player.c enemy.c game.c bullet.c leaderboard.c)

# Include directories pro SDL2 i SDL2_image
target_include_directories(catventure PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Linkování knihoven
target_link_libraries(catventure
    ${SDL2_LIBRARIES}
    SDL2_image
    SDL2_ttf
)