cmake_minimum_required(VERSION 3.22)

# Définition du projet pour STM32
project(STM32H7A3_Project C CXX ASM)

# Spécifier l'utilisation de la toolchain ARM Cross-Compiler
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Indiquer où se trouvent vos fichiers sources
add_executable(${PROJECT_NAME}
    Core/Src/main.c
    # Ajoutez ici les fichiers HAL stm32h7xx_hal.c si vous les utilisez
)

# Indiquer au compilateur où chercher les fichiers d'en-tête (.h)
target_include_directories(${PROJECT_NAME} PRIVATE
    Core/Inc
)