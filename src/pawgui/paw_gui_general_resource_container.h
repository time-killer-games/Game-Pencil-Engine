/*
paw_gui_general_resource_container.h
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

#ifndef PAW_GUI_GRC_H
#define PAW_GUI_GRC_H

#include "paw_gui_base.h"
#include "paw_gui_general_resource.h"

const int RESOURCE_AREA_HEIGHT = 14;
const int restype_regular = -1;
const int restype_superfolder = 0;
const int restype_projfolder = 1;

class GPE_GeneralResourceContainer: public GPE_GeneralGuiElement
{
protected:
    int globalResouceId;
    int resourceId;
    int resourceType;
    bool isFolder, isSuperFolder, isSuperProjectFolder;
    bool subMenuIsOpen;
    gpe::animaton2d * containeranimation;
    gpe::texture_base * containerTexture;
    int animationFrameNumber;
    generalGameResource * heldResource;
    std::vector <GPE_GeneralResourceContainer *> subOptions;
    bool resouceNameChanged;
    bool subContentsModified;
    int strTexWidth, strTexHeight;
public:
    int foundX2Pos;
    int exportBuildGlobalId;
    std::string parentProjectDirectory;
    std::string projectParentFileName;
    std::string projectParentName;
    gpe::shape_rect element_box;
    GPE_GeneralResourceContainer * parentResource;
    //GPE_GeneralResourceContainer(std::string projFolderName, int  rezPropValue = -1);
    GPE_GeneralResourceContainer(std::string projFolderName = "", std::string new_name =  "", int rType = -1, int rId = -1,bool folder = true, int globalIdVal = -1,int  rezPropValue = -1);
    virtual ~GPE_GeneralResourceContainer();
    void add_resource_container( GPE_GeneralResourceContainer * newResource, bool changeGlobalId = false, GPE_GeneralResourceContainer * referenceObject = NULL );
    GPE_GeneralResourceContainer * add_resource_folder( std::string resourceTypeName, int gResId = -1, int rezPropValue = -1);
    GPE_GeneralResourceContainer * add_newtype_folder( int rType,std::string resourceTypeName, int gResId = -1,int rezPropValue = -1);
    void delete_resource(GPE_GeneralResourceContainer * otherContainer);
    bool detect_name_change(bool autoChange = true);
    int get_global_id();
    generalGameResource * get_held_resource();
    std::string get_name();
    int get_resource_id();
    int get_resource_type();
    GPE_GeneralResourceContainer * find_resource_from_id(int resourceIdToFind, bool nestDown = true, bool includeSelf = true);
    GPE_GeneralResourceContainer * find_resource_from_name(std::string rNameToFind, bool nestDown = true);
    GPE_GeneralResourceContainer * find_resource_target(std::string rNameToFind, bool nestDown = true);
    GPE_GeneralResourceContainer * get_usable_resource();
    void grab_useable_resources(std::vector <GPE_GeneralResourceContainer * > &rVector);
    GPE_GeneralResourceContainer * get_resource_at(int resourcePos, bool nestDown = false);
    std::string get_project_name();
    int get_resource_count();
    int get_resource_image_frame();
    virtual gpe::animaton2d * get_resource_animation();
    virtual gpe::texture_base * get_resource_texture();
    int get_size();
    int get_options_width();
    bool include_local_files( std::string pBuildDir , int buildType );
    void integrate_into_syntax();
    bool is_folder();
    bool is_super_folder();
    bool is_super_project_folder();
    bool is_child_of(GPE_GeneralResourceContainer * otherContainer);
    bool can_obtain(GPE_GeneralResourceContainer * otherContainer);
    int matches(GPE_GeneralResourceContainer * otherContainer);
    void open_folder();
    void preprocess_container(std::string file_path = "", int backupId = -1);
    void prerender_self( );
    int process_container(int xPos, int yPos, int selectedId = -1, gpe::shape_rect * viewedSpace = NULL, gpe::shape_rect * cam = NULL, bool mouseInRange = false);
    bool read_data_from_projectfile(std::ofstream * fileTarget);
    void remove_resource(GPE_GeneralResourceContainer * otherContainer, bool deleteResource = true);
    //Render options
    void render_contained_object( gpe::shape_rect * viewedSpace = NULL, gpe::shape_rect * cam = NULL);
    void render_option( int xPos, int yPos, int selectedIdNumber=-1, gpe::shape_rect * viewedSpace = NULL, gpe::shape_rect * cam = NULL, bool renderSubOptions = true, bool renderAutomatically = false);
    void render_image( int xPos, int yPos, int rWidth = -1, int rHeight = -1, gpe::shape_rect * viewedSpace = NULL, gpe::shape_rect * cam = NULL, gpe::color * renderColor = NULL);
    void render_image_scaled( int xPos, int yPos, float xScale = 1, float yScale = -1, gpe::shape_rect * viewedSpace = NULL, gpe::shape_rect * cam = NULL, gpe::color * renderColor = NULL);

    void save_container(std::string file_path = "", int backupId = -1);
    int search_for_string(std::string needle);
    int search_and_replace_string(std::string needle, std::string newStr = "");
    void set_basic_image_value();
    void set_global_id(int new_id);
    void set_container_gameid(int new_id);
    void set_held_resource(generalGameResource * newGenResource);
    void set_name(std::string new_name);
    void set_project_parent_name(std::string newParentName);
    bool write_data_into_projectfile(std::ofstream * fileTarget, int nestedFoldersIn = 0);
};

extern GPE_GeneralResourceContainer * RESOURCE_TO_DRAG;
extern GPE_GeneralResourceContainer * LAST_CLICKED_RESOURCE;
extern bool RESOURCEMENU_WAS_RIGHTCLICKED;
extern GPE_GeneralResourceContainer * RESOURCE_BEINGRENAMED;
extern int LAST_CLICKED_RESTYPE;
extern int DRAGGED_RESTYPE;

extern std::string project_current_name;
extern std::string seeked_project_name;
extern int lastResTypeRendered;

#endif // PAW_GUI_GRC_H
