# CMake 최소 버전 설정
cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

# 프로젝트 선언
project(MML)

# 출력 디렉토리 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# include 폴더 설정
include_directories(include)

# 실행 파일 정의
add_executable(mml utils.c song.c main.c)
