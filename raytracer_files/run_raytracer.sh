#!/bin/sh
g++ main.cpp 3D.c Background_Command.cpp Box.cpp Box_Command.cpp Camera_Command.cpp Clear_Command.cpp Color_Command.cpp Command.cpp Dispatcher.cpp Draw_Command.cpp Ilight_Command.cpp LookAt_Command.cpp Matrix_3x3.cpp Move_Command.cpp Object_Model.cpp Ortho_Command.cpp Orthocamera_Command.cpp Perspective_Command.cpp Pop_Command.cpp Push_Command.cpp Read_Command.cpp Reset_Command.cpp Resize_Command.cpp Rotate_Command.cpp Scale_Command.cpp Screen_Command.cpp Sphere.cpp Sphere_Command.cpp Tiff_Input_Command.cpp TiffRead_Command.cpp TiffStat_Command.cpp TiffWrite_Command.cpp Trace_Command.cpp Translate_Command.cpp Triangle.cpp Triangle_Command.cpp Vector3.cpp Vertex_Command.cpp Zoom_Command.cpp -o raytraceApp -lglut -lGLU -lGL
while true
do
    python3 consumerS.py
    ./raytraceApp
    python3 producerI.py
done
