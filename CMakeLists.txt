cmake_minimum_required(VERSION 3.9)
project(minishell)

set(CMAKE_CXX_STANDARD 11)

include_directories(libft/includes includes) # header directories
link_directories(libft) # library directories

add_executable(minishell
        src/main.c
        src/bi_cd.c
        src/bi_echo.c
        src/bi_set_unset_env.c
        src/builtins.c
        src/entered_commands_check.c
        src/env.c
        src/env_commands.c
        src/prompt.c)

target_link_libraries(minishell -lft)

