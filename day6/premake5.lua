workspace("AoC Day 6")
configurations({ "Release" })

project("Day6")
kind("ConsoleApp")
language("C++")
targetdir("out")

files({ "**.h", "**.cpp" })

filter("configurations:Release")
defines({ "NDEBUG" })
symbols("On")
