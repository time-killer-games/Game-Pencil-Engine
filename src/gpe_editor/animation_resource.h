/*
animation_resource.h
This file is part of:
GAME PENCIL ENGINE
https://www.pawbyte.com/gamepencilengine
Copyright (c) 2014-2020 Nathan Hurde, Chase Lee.

Copyright (c) 2014-2020 PawByte LLC.
Copyright (c) 2014-2020 Game Pencil Engine contributors ( Contributors Page )

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the “Software”), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-Game Pencil Engine <https://www.pawbyte.com/gamepencilengine>


*/

#ifndef animaton2d_RESOURCES_H
#define animaton2d_RESOURCES_H

#include "gpe_basic_resource_page.h"

const float ZOOM_LEVEL_MIN = 0.0625;
const float ZOOM_LEVEL_MAX = 16;

const int ANIMATION_DATA_FIELD_COUNT = 7;

extern std::string animaton2d_LABELS[ANIMATION_DATA_FIELD_COUNT];


const float GPE_ANIM_FCOUNT_VERSION = 1.04;

class animationResource: public standardEditableGameResource
{
public:
    bool areaIsScrollable;
    float animationSpeed;
    bool isPreloaded;
    float editorZoomValue;
    float minZoomValue;
    float maxZoomValue;
    int autoAnimationPos;
    GPE_Slider_XAxis * animationTrackBar;
    gpe::animaton2d * animInEditor;

    //
    gpe::shape_rect animCameraRect;
    gpe::shape_rect animRect;

    GPE_ScrollBar_XAxis * animXScroll;
    GPE_ScrollBar_YAxis * animYScroll;

    //Right pane
    gpe::shape_rect  * animatonPreviewRect;
    gpe::shape_rect  * animationPreviewCam;
    GPE_Label_Text * animationSpeedLabel;
    GPE_CheckBoxBasic * previewZoomLevel;
    GPE_CheckBoxBasic * previewSubImageNumbers;

    //Editor panel elements
    GPE_Label_Text * labelanimationDimensions;
    GPE_Label_Text * labelFrameInfo;
    GPE_Label_Text * labelanimationMessage;
    GPE_ToolIconButton * editResourceButton;
    GPE_ToolIconButton * transformResourceButton;
    GPE_ToolIconButton * playPauseResourceButton;
    GPE_ToolIconButton * openExternalEditorButton;
    GPE_ToolIconButton * refreshResourceDataButton;
    GPE_CheckBoxBasic * preloadCheckBox;
    GPE_CheckBoxBasic * showCollisionShapeCheckBox;
    GPE_CheckBoxBasic * showAnimationCheckBox;

    gpe_text_widget_number * animationDataFields[ANIMATION_DATA_FIELD_COUNT];

    gpe_text_widget_number * animationCollisionRectX;
    gpe_text_widget_number * animationCollisionRectY;
    gpe_text_widget_number * animationCollisionRectW;
    gpe_text_widget_number * animationCollisionRectH;

    gpe_text_widget_number * animationCollisionCircleX;
    gpe_text_widget_number * animationCollisionCircleY;
    gpe_text_widget_number * animationCollisionCircleR;

    GPE_ToolLabelButton * animationCenterCollisionButton;

    GPE_DropDown_Menu * animationCollisionShapeMenu;

    GPE_ToolIconButton * previousSubImageButton;
    GPE_ToolIconButton * nextSubImageButton;
    gpe_text_widget_number * subImageNumberField;
    gpe_text_widget_number * subImageEditorPreviewId;
    int subImagePreviewNumber;
    float subImageMiniAnimationNumber;
    GPE_Label_Text * labelInfoMaxTextureSize;

    animationResource(GPE_GeneralResourceContainer * pFolder = NULL);
    ~animationResource();

    bool build_intohtml5_file(std::ofstream * fileTarget, int leftTabAmount = 0);
    bool build_intocpp_file(std::ofstream * fileTarget, int leftTabAmount = 0);
    void compile_cpp();
    bool get_mouse_coords( gpe::shape_rect * viewedSpace = NULL, gpe::shape_rect * cam = NULL);
    int get_preview_frame();
    gpe::animaton2d * get_resource_animation();
    void handle_scrolling();
    bool include_local_files( std::string pBuildDir , int buildType );
    bool is_build_ready();
    void load_image(std::string new_file_name, bool autoProcess = false);
    void load_resource(std::string file_path = "");
    void prerender_self( );
    void process_collision_box();
    void process_data_fields(float versionToProcess = -1);
    void process_self( gpe::shape_rect * viewedSpace = NULL, gpe::shape_rect * cam = NULL);
    void render_self( gpe::shape_rect * viewedSpace = NULL, gpe::shape_rect * cam = NULL);
    void revert_data_fields();
    void save_resource(std::string file_path = "", int backupId = -1);
    void update_box(int newX=-1, int newY=-1, int newW=-1, int newH=-1);
    bool write_data_into_projectfile(std::ofstream * fileTarget, int nestedFoldersIn = 0);
};


#endif // animaton2d_RESOURCES_H
