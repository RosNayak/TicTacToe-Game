cmake_minimum_required(VERSION 3.0)
project(tic_tac_toe)
add_subdirectory(pybind11)
pybind11_add_module(tictactoe tictactoe_backend.cpp)