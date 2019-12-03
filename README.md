# catch_the_princess
This is visualisation of generalized puzzle from video: https://www.youtube.com/watch?v=nv0Onj3wXCE

## usage
The program takes 3 or 0 parameters from command line: heigth and width of table and then number of allowed checks in night. If there is no parameters it is just defaults to 3 3 2.

## rules
You start with table full of crosses. Your goal is to get rid of crosses by removing some of them. When you removed allowed number of crosses each cross replaced with four crosses aroud its location in up, down, left and right directions.

## explanation
Each cross corresponds to possible location of the princess. Removing crosses corresponds to checking rooms.

## compilation

checked on vs2019

https://github.com/OneLoneCoder/olcPixelGameEngine
