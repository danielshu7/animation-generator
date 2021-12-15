#include "Dispatcher.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Move_Command.h"
#include "Draw_Command.h"
#include "Color_Command.h"
#include "Read_Command.h"
#include "TiffStat_Command.h"
#include "TiffRead_Command.h"
#include "TiffWrite_Command.h"
#include "Resize_Command.h"
#include "Zoom_Command.h"
#include "Push_Command.h"
#include "Pop_Command.h"
#include "Translate_Command.h"
#include "Scale_Command.h"
#include "Rotate_Command.h"
#include "Ortho_Command.h"
#include "Perspective_Command.h"
#include "LookAt_Command.h"
#include "Vertex_Command.h"
#include "Reset_Command.h"
#include "Screen_Command.h"
#include "Background_Command.h"
#include "Orthocamera_Command.h"
#include "Camera_Command.h"
#include "Sphere_Command.h"
#include "Triangle_Command.h"
#include "Box_Command.h"
#include "Ilight_Command.h"
#include "Trace_Command.h"
#include "Clear_Command.h"


// Ctor
Dispatcher::Dispatcher(char* line)
{
    // used to check for comma syntax error
    char* lineCpy = (char*) malloc(strlen(line) + 1);
    strcpy(lineCpy, line);

    // parses the line of input into the command and parameters
    char* tmp = strtok(line, " \t");
    if(tmp != NULL) {
        // enters when line isn't only whitespace
        // set the command and remove case sensitivity
        cmd += tmp;
        for(int i = 0; i < cmd.length(); ++i) {
            cmd[i] = std::toupper(cmd[i]);
        }

        for(tmp = strtok(NULL, ", \t"); tmp != NULL; tmp = strtok(NULL, ", \t")) {
            parameters.push_back(tmp);
        }
    }

    // syntax error if there's a comma in the command
    if(cmd.find(',') != std::string::npos) {
        cmd = "comma syntax error";
    }
    else {
        // otherwise we still need to check if there's a comma between the command the the 1st param
        char* commaChecker = strtok(lineCpy, " \t");
        commaChecker = strtok(NULL, " \t");
        if(commaChecker != NULL && commaChecker[0] == ',') {
            cmd = "comma syntax error";
        }
    }
    free(lineCpy);
}

// dispatch
void Dispatcher::dispatch() const
{
    if(cmd == "MOVE") {
        Move_Command mCmd(parameters);
        mCmd.run();
        return;
    }
    else if(cmd == "DRAW") {
        Draw_Command dCmd(parameters);
        dCmd.run();
        return;
    }
    else if(cmd == "COLOR") {
        Color_Command cCmd(parameters);
        cCmd.run();
        return;
    }
    else if(cmd == "READ") {
        if(depth >= MAX_DEPTH) {
            // skips read commands when at max depth
            std::cout << "ERROR: MAX DEPTH (" << MAX_DEPTH << ") reached - \"READ " <<
            parameters[0] << "\" skipped." << std::endl;
        }
        else {
            Read_Command rCmd(parameters);
            rCmd.run();
        }
        return;
    }
    else if(cmd == "TIFFSTAT") {
        TiffStat_Command tsCmd(parameters);
        tsCmd.run();
        return;
    }
    else if(cmd == "TIFFREAD") {
        TiffRead_Command trCmd(parameters);
        trCmd.run();
        return;
    }
    else if(cmd == "TIFFWRITE") {
        TiffWrite_Command twCmd(parameters);
        twCmd.run();
        return;
    }
    else if(cmd == "RESIZE") {
        Resize_Command rsCmd(parameters);
        rsCmd.run();
        return;
    }
    else if(cmd == "ZOOM") {
        Zoom_Command zCmd(parameters);
        zCmd.run();
        return;
    }
    else if(cmd == "PUSH") {
        Push_Command pCmd(parameters);
        pCmd.run();
        return;
    }
    else if(cmd == "POP") {
        Pop_Command pCmd(parameters);
        pCmd.run();
        return;
    }
    else if(cmd == "TRANSLATE") {
        Translate_Command tCmd(parameters);
        tCmd.run();
        return;
    }
    else if(cmd == "SCALE") {
        Scale_Command sCmd(parameters);
        sCmd.run();
        return;
    }
    else if(cmd == "ROTATE") {
        Rotate_Command rCmd(parameters);
        rCmd.run();
        return;
    }
    else if(cmd == "ORTHO") {
        Ortho_Command oCmd(parameters);
        oCmd.run();
        return;
    }
    else if(cmd == "PERSPECTIVE") {
        Perspective_Command pCmd(parameters);
        pCmd.run();
        return;
    }
    else if(cmd == "LOOKAT") {
        LookAt_Command laCmd(parameters);
        laCmd.run();
        return;
    }
    else if(cmd == "VERTEX") {
        Vertex_Command vCmd(parameters);
        vCmd.run();
        return;
    }
    else if(cmd == "RESET") {
        Reset_Command rCmd(parameters);
        rCmd.run();
        return;
    }
    else if(cmd == "SCREEN") {
        Screen_Command sCmd(parameters);
        sCmd.run();
        return;
    }
    else if(cmd == "BACKGROUND") {
        Background_Command bgCmd(parameters);
        bgCmd.run();
        return;
    }
    else if(cmd == "ORTHOCAMERA") {
        Orthocamera_Command ocCmd(parameters);
        ocCmd.run();
        return;
    }
    else if(cmd == "CAMERA") {
        Camera_Command cCmd(parameters);
        cCmd.run();
        return;
    }
    else if(cmd == "SPHERE") {
        Sphere_Command sCmd(parameters);
        sCmd.run();
        return;
    }
    else if(cmd == "TRIANGLE") {
        Triangle_Command tCmd(parameters);
        tCmd.run();
        return;
    }
    else if(cmd == "BOX") {
        Box_Command bCmd(parameters);
        bCmd.run();
        return;
    }
    else if(cmd == "ILIGHT") {
        Ilight_Command iCmd(parameters);
        iCmd.run();
        return;
    }
    else if(cmd == "TRACE") {
        Trace_Command tCmd(parameters);
        tCmd.run();
        return;
    }
    else if(cmd == "CLEAR") {
        Clear_Command cCmd(parameters);
        cCmd.run();
        return;
    }
    else if(cmd == "comma syntax error") {
        std::cout << "ERROR: The command should not include, be preceded by, or be followed by a "
                     "comma." << std::endl;
        return;
    }
    else if(cmd.empty()) {
        // does nothing when line of input was just whitespace
        return;
    }
    else {
        std::cout << "ERROR: \"" << cmd << '"' << " is not a valid command." << std::endl;
    }
}


