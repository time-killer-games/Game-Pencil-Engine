/*
pawgui_labels.cpp
This file is part of:
PawByte Ambitious Working GUI(PAWGUI)
https://www.pawbyte.com/pawgui
Copyright (c) 2014-2020 Nathan Hurde, Chase Lee.

Copyright (c) 2014-2020 PawByte LLC.
Copyright (c) 2014-2020 PawByte Ambitious Working GUI(PAWGUI) contributors ( Contributors Page )

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

-PawByte Ambitious Working GUI(PAWGUI) <https://www.pawbyte.com/pawgui>


*/

#include "pawgui_labels.h"
namespace pawgui
{
    widget_label_image::widget_label_image(std::string name_param, std::string file_name, std::string description, std::string urlIn)
    {
        allowOverSize = true;
        resizeAspect = 1;
        guiListTypeName = "labelimage";
        opName = name_param;
        descriptionText = description;
        wasClicked = false;
        isHoldingCustomTexture = false;
        webUrl = urlIn;
        imgSrc = rsm_gui->texture_add_filename( file_name );
        if( imgSrc!=NULL )
        {
            widget_box.w = imgSrc->get_width();
            widget_box.h = imgSrc->get_height();
        }
        else
        {
            widget_box.w = 32;
            widget_box.h = 32;
            imgSrc = NULL;
        }
    }

    widget_label_image::~widget_label_image()
    {

    }

    void widget_label_image::load_label_image(std::string new_file_name)
    {
        imgSrc = rsm_gui->texture_add_filename( new_file_name );
        if( imgSrc!=NULL )
        {
            widget_box.w = imgSrc->get_width();
            widget_box.h = imgSrc->get_height();
        }
    }

    void widget_label_image::process_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam)
    {
        viewedSpace = gpe::camera_find( viewedSpace );
        cam = gpe::camera_find( cam );
        widget_basic::process_self(viewedSpace,cam);
        if( viewedSpace!=NULL && cam!=NULL )
        {
            if( isHovered && (int)webUrl.size() > 3)
            {
                gpe::cursor_main_controller->cursor_change("hand");
            }
            if( isInUse &&( gpe::input->check_kb_down( kb_enter ) || gpe::input->check_kb_down( kb_space )  ) )
            {
                isClicked = true;
            }
            if( isClicked )
            {
                wasClicked = true;
                if( (int)webUrl.size() > 3)
                {
                    gpe::external_open_url(webUrl);
                }
            }
        }
    }

    void widget_label_image::render_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam)
    {
        viewedSpace = gpe::camera_find(viewedSpace);
        cam = gpe::camera_find(cam);
        if( cam!=NULL )
        {
            if( imgSrc!=NULL )
            {
                imgSrc->render_tex_resized( widget_box.x-cam->x,widget_box.y-cam->y,widget_box.w,widget_box.h,NULL );
            }
            else
            {
                gpe::gcanvas->render_rectangle( widget_box.x-cam->x,widget_box.y-cam->y,widget_box.x+widget_box.w-cam->x,widget_box.y+widget_box.h-cam->y,pawgui::theme_main->main_box_font_color,true);
            }
            if( isInUse)
            {
                gpe::gcanvas->render_rectangle( widget_box.x-cam->x,widget_box.y-cam->y,widget_box.x+widget_box.w-cam->x,widget_box.y+widget_box.h-cam->y,pawgui::theme_main->main_box_font_url_color,true);
            }
            if( isHovered)
            {
                gpe::gcanvas->render_rectangle( widget_box.x-cam->x,widget_box.y-cam->y,widget_box.x+widget_box.w-cam->x,widget_box.y+widget_box.h-cam->y,pawgui::theme_main->main_box_font_url_hovered_color,true);
            }
        }
    }

    void widget_label_image::change_texture( gpe::texture_base * imgIn )
    {
        imgSrc = imgIn;
        if( imgSrc!=NULL )
        {
            widget_box.w = imgSrc->get_width();
            widget_box.h = imgSrc->get_height();
        }
    }

    void widget_label_image::set_width( int newW )
    {
        //if( newW!=widget_box.w)
        {
            if( newW > 0)
            {
                float newH = 0;
                if( imgSrc!=NULL && imgSrc->get_width() > 0)
                {
                    if( !allowOverSize && !isFullWidth )
                    {
                        if( newW > imgSrc->get_width() )
                        {
                            newW = imgSrc->get_width();
                        }
                    }

                    widget_box.w = newW*resizeAspect;
                    if( imgSrc!=NULL && imgSrc->get_width()!=0 )
                    {
                        widget_box.h =  ( widget_box.w ) *  ( (float) imgSrc->get_height() / (float)imgSrc->get_width() );
                    }
                }
            }
            else if( imgSrc!=NULL && imgSrc->get_width() > 0)
            {
                widget_box.w = imgSrc->get_width() ;
                widget_box.h = imgSrc->get_height() ;
            }
            else
            {
                widget_box.w = 0;
                widget_box.h = 0;
            }
        }
    }

    void widget_label_image::set_height( int newH)
    {
        if( newH > 0)
        {
            if( imgSrc!=NULL && !allowOverSize)
            {
                if( newH > imgSrc->get_height() )
                {
                    newH = imgSrc->get_height();
                }
            }
            widget_box.h = newH*resizeAspect;
            if( imgSrc!=NULL )
            {
                widget_box.w = resizeAspect * ceil( (float)newH * (float)imgSrc->get_width()/(float)imgSrc->get_height() );
            }
        }
        else
        {
            widget_box.w = 0;
            widget_box.h = 0;
        }
    }

    void widget_label_image::set_size( float newW, float newH)
    {
        widget_box.w = newW;
        widget_box.h = newH;
    }

    void widget_label_image::set_name(std::string name_param)
    {
        opName = name_param;
    }

    //

    //

    widget_label_text::widget_label_text(std::string name_param, std::string description)
    {
        guiListTypeName = "labeltext";
        guiListTypeId = 7;
        opName = name_param;
        descriptionText = description;
        if( FONT_LABEL!=NULL)
        {
            int bWid = 0;
            int bHgt = 0;
            FONT_LABEL->get_metrics(name_param.c_str(), &bWid, &bHgt);
            widget_box.w = bWid;
            widget_box.h = bHgt;
        }
        opName = name_param;
        hasLineBreak = true;
    }

    widget_label_text::~widget_label_text()
    {

    }

    std::string widget_label_text::get_data()
    {
        return guiListTypeName+":"+opName+"==|||=="+descriptionText;
    }

    std::string widget_label_text::get_plain_string()
    {
        return "\""+opName+"\"";
    }

    void widget_label_text::load_data(std::string dataString)
    {
        descriptionText = dataString;
    }

    void widget_label_text::process_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam)
    {
        widget_basic::process_self(viewedSpace,cam);
        /*
        if( isHovered)
        {
            gpe::cursor_main_controller->cursor_change(GPE_CURSOR_HAND);
        }
        if( isClicked )
        {
            wasClicked = true;
            if( (int)webUrl.size() > 3)
            {
                gpe::external_open_url(webUrl);
            }
        }
        */
        if( isInUse)
        {
            if( gpe::input->check_kb_down(kb_ctrl) && gpe::input->check_kb_released(kb_c) )
            {
                gpe::input->clipboard_set(opName.c_str() );
            }
        }
    }

    void widget_label_text::render_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam)
    {
        viewedSpace = gpe::camera_find(viewedSpace);
        cam = gpe::camera_find(cam);
        if( (int)opName.size() > 0 && viewedSpace!=NULL && cam!=NULL )
        {
            gpe::gfs->render_text( widget_box.x-cam->x,widget_box.y-cam->y,opName,pawgui::theme_main->main_box_font_color,FONT_LABEL,gpe::fa_left,gpe::fa_top);

            if( isInUse)
            {
                gpe::gcanvas->render_rectangle( widget_box.x-cam->x,widget_box.y-cam->y,widget_box.x+widget_box.w-cam->x,widget_box.y+widget_box.h-cam->y,pawgui::theme_main->main_box_font_url_color,true);
            }
        }
    }

    void widget_label_text::set_name(std::string name_param)
    {
        if( FONT_LABEL!=NULL)
        {
            int bWid = 0;
            int bHgt = 0;
            FONT_LABEL->get_metrics(name_param.c_str(), &bWid, &bHgt);
            widget_box.w = bWid;
            widget_box.h = bHgt;
        }
        opName = name_param;
    }

    //
    //

    widget_label_error::widget_label_error(std::string name_param, std::string description)
    {
        guiListTypeName = "labelerror";
        guiListTypeId = 7;
        opName = name_param;
        descriptionText = description;
        if( FONT_LABEL!=NULL)
        {
            int bWid = 0;
            int bHgt = 0;
            FONT_LABEL->get_metrics(name_param.c_str(), &bWid, &bHgt);
            widget_box.w = bWid;
            widget_box.h = bHgt;
        }
        opName = name_param;
        hasLineBreak = true;
    }

    widget_label_error::~widget_label_error()
    {

    }

    std::string widget_label_error::get_data()
    {
        return guiListTypeName+":"+opName+"==|||=="+descriptionText;
    }

    std::string widget_label_error::get_plain_string()
    {
        return "\""+opName+"\"";
    }

    void widget_label_error::load_data(std::string dataString)
    {
        descriptionText = dataString;
    }

    void widget_label_error::process_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam)
    {
        widget_basic::process_self(viewedSpace,cam);
        /*
        if( isHovered)
        {
            gpe::cursor_main_controller->cursor_change(GPE_CURSOR_HAND);
        }
        if( isClicked )
        {
            wasClicked = true;
            if( (int)webUrl.size() > 3)
            {
                gpe::external_open_url(webUrl);
            }
        }
        */
        if( isInUse)
        {
            if( gpe::input->check_kb_down(kb_ctrl) && gpe::input->check_kb_released(kb_c) )
            {
                gpe::input->clipboard_set(opName.c_str() );
            }
        }
    }

    void widget_label_error::render_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam)
    {
        viewedSpace = gpe::camera_find(viewedSpace);
        cam = gpe::camera_find(cam);
        if( (int)opName.size() > 0 && viewedSpace!=NULL && cam!=NULL )
        {
            gpe::gfs->render_text( widget_box.x-cam->x,widget_box.y-cam->y,opName,pawgui::theme_main->input_error_font_color,FONT_LABEL,gpe::fa_left,gpe::fa_top);

            if( isInUse)
            {
                gpe::gcanvas->render_rectangle( widget_box.x-cam->x,widget_box.y-cam->y,widget_box.x+widget_box.w-cam->x,widget_box.y+widget_box.h-cam->y,pawgui::theme_main->main_box_font_highlight_color,true);
            }
        }
    }

    void widget_label_error::set_name(std::string name_param)
    {
        if( FONT_LABEL!=NULL)
        {
            int bWid = 0;
            int bHgt = 0;
            FONT_LABEL->get_metrics(name_param.c_str(), &bWid, &bHgt);
            widget_box.w = bWid;
            widget_box.h = bHgt;
        }
        opName = name_param;
    }

    //

    widget_label_rotated_90::widget_label_rotated_90(std::string name_param, std::string description)
    {
        guiListTypeName = "labeltext";
        guiListTypeId = 7;
        opName = name_param;
        descriptionText = description;
        if( FONT_LABEL!=NULL)
        {
            int bWid = 0;
            int bHgt = 0;
            FONT_LABEL->get_metrics(name_param.c_str(), &bWid, &bHgt);
            widget_box.w = bHgt;
            widget_box.h = bWid;
        }
        opName = name_param;
        hasLineBreak = true;
    }

    widget_label_rotated_90::~widget_label_rotated_90()
    {

    }

    std::string widget_label_rotated_90::get_data()
    {
        return guiListTypeName+":"+opName+"==|||=="+descriptionText;
    }

    std::string widget_label_rotated_90::get_plain_string()
    {
        return "\""+opName+"\"";
    }

    void widget_label_rotated_90::load_data(std::string dataString)
    {
        descriptionText = dataString;
    }

    void widget_label_rotated_90::process_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam)
    {
        widget_basic::process_self(viewedSpace,cam);
        /*
        if( isHovered)
        {
            gpe::cursor_main_controller->cursor_change(GPE_CURSOR_HAND);
        }
        if( isClicked )
        {
            wasClicked = true;
            if( (int)webUrl.size() > 3)
            {
                gpe::external_open_url(webUrl);
            }
        }
        */
        if( isInUse)
        {
            if( gpe::input->check_kb_down(kb_ctrl) && gpe::input->check_kb_released(kb_c) )
            {
                gpe::input->clipboard_set(opName.c_str() );
            }
        }
    }

    void widget_label_rotated_90::render_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam)
    {
        viewedSpace = gpe::camera_find(viewedSpace);
        cam = gpe::camera_find(cam);
        if( (int)opName.size() > 0 && viewedSpace!=NULL && cam!=NULL )
        {
            gpe::gfs->render_text_rotated( widget_box.x-cam->x,widget_box.y-cam->y+widget_box.h,opName,pawgui::theme_main->main_box_font_color,FONT_LABEL,90);

            if( isInUse)
            {
                gpe::gcanvas->render_rectangle( widget_box.x-cam->x,widget_box.y-cam->y,widget_box.x+widget_box.w-cam->x,widget_box.y+widget_box.h-cam->y,pawgui::theme_main->main_box_font_url_color,true);
            }
        }
    }

    void widget_label_rotated_90::set_name(std::string name_param)
    {
        if( FONT_LABEL!=NULL)
        {
            int bWid = 0;
            int bHgt = 0;
            FONT_LABEL->get_metrics(name_param.c_str(), &bWid, &bHgt);
            widget_box.w = bHgt;
            widget_box.h = bWid;
        }
        opName = name_param;
    }

    widget_label_paragraph::widget_label_paragraph(std::string name_param, std::string paragraphIn, std::string descriptionIn)
    {
        guiListTypeName = "paragraph";
        paragraphWidth = 0;
        needsNewLine = true;
        isFullWidth = true;
        autoResizes= true;
        opName = name_param;
        paragraphText = paragraphIn;
        descriptionText = descriptionIn;
    }

    widget_label_paragraph::~widget_label_paragraph()
    {
        paragraphLines.clear();
        if( FONT_LABEL!=NULL )
        {
            FONT_LABEL->clear_cache();
        }
    }

    void widget_label_paragraph::add_line(std::string newLine)
    {
        paragraphLines.push_back(newLine);
        paragraphWidth = 0;
    }

    void widget_label_paragraph::clear_all_lines()
    {
        paragraphLines.clear();
        paragraphWidth = 0;
    }

    std::string widget_label_paragraph::get_paragraph()
    {
        return paragraphText;
    }

    void widget_label_paragraph::process_self( gpe::shape_rect * viewedSpace, gpe::shape_rect * cam )
    {
        if( viewedSpace!=NULL )
        {
            //if( viewedSpace->w - widget_box.x !=widget_box.w || paragraphWidth == 0 )
            {
                update_paragraph();
            }
            widget_basic::process_self(  viewedSpace, cam );
        }
    }

    void widget_label_paragraph::render_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam )
    {
        viewedSpace = gpe::camera_find(viewedSpace);
        cam = gpe::camera_find(cam);
        if( viewedSpace!=NULL && cam!=NULL )
        {
            if( hAlign == gpe::fa_center)
            {
                for( int i =0; i < (int)paragraphLines.size(); i++)
                {
                    gpe::gfs->render_text( widget_box.x-cam->x + cam->w/2,widget_box.y-cam->y+(padding_default+defaultFontHeight)*i,paragraphLines[i],pawgui::theme_main->main_box_font_color,FONT_LABEL,gpe::fa_center,gpe::fa_top);
                }
            }
            else if( hAlign == gpe::fa_right)
            {
                for( int i =0; i < (int)paragraphLines.size(); i++)
                {
                    gpe::gfs->render_text( widget_box.x-cam->x + widget_box.w,widget_box.y-cam->y+(padding_default+defaultFontHeight)*i,paragraphLines[i],pawgui::theme_main->main_box_font_color,FONT_LABEL,gpe::fa_right,gpe::fa_top);
                }
            }
            else
            {
                for( int i =0; i < (int)paragraphLines.size(); i++)
                {
                    gpe::gfs->render_text( widget_box.x-cam->x,widget_box.y-cam->y+(padding_default+defaultFontHeight)*i,paragraphLines[i],pawgui::theme_main->main_box_font_color,FONT_LABEL,gpe::fa_left,gpe::fa_top);
                }
            }

            if( isInUse)
            {
                gpe::gcanvas->render_rectangle( widget_box.x-cam->x,widget_box.y-cam->y,widget_box.x+paragraphWidth-cam->x,widget_box.y+widget_box.h-cam->y,pawgui::theme_main->main_box_font_url_color,true);
            }
        }
    }

    void widget_label_paragraph::set_name(std::string name_param)
    {

    }

    void widget_label_paragraph::set_width(int newWidth)
    {
        if( widget_box.w!=newWidth)
        {
            widget_box.w = newWidth;
            update_paragraph();
        }
    }

    void widget_label_paragraph::set_height( int newHeight)
    {
        if( widget_box.h!=newHeight)
        {
            widget_box.h = newHeight;
            update_paragraph();
        }
    }

    void widget_label_paragraph::set_max_width( int nMW)
    {
        if( widget_box.w!=nMW)
        {
            widget_box.w = nMW;
            update_paragraph();
        }
    }

    void widget_label_paragraph::set_max_height( int nMH)
    {
        if( widget_box.h!=nMH)
        {
            widget_box.h = nMH;
            update_paragraph();
        }
    }

    void widget_label_paragraph::update_paragraph()
    {
        if( widget_box.w > 0 )
        {
            clear_all_lines();
            if( (int)paragraphText.size() > 0)
            {
                int maxMessageWidth = 0;
                //int maxMessageHeight = 0;
                defaultFontWidth = 0;
                defaultFontHeight = 0;
                int iSubMessage = 0;
                if( FONT_LABEL!=NULL)
                {
                    FONT_LABEL->get_metrics("A",&defaultFontWidth, &defaultFontHeight);
                    FONT_LABEL->clear_cache();
                }

                std::vector < std::string > messageSubTitles;

                if( defaultFontWidth > 0 && defaultFontHeight > 0)
                {
                    maxMessageWidth = ( widget_box.w -padding_default*2)/ defaultFontWidth;

                    if( (int)paragraphText.size() > 0)
                    {
                        stg_ex::wrap_string(paragraphText,messageSubTitles,maxMessageWidth,-1);
                    }

                    maxMessageWidth = 0;
                    if( messageSubTitles.size() <= 0)
                    {
                        add_line("");
                        widget_box.h = 0;
                        paragraphWidth = 0;
                    }
                    else
                    {
                        for( iSubMessage = 0; iSubMessage < (int)messageSubTitles.size(); iSubMessage++)
                        {
                            add_line( messageSubTitles.at(iSubMessage) );
                        }
                        widget_box.h = ( (int)messageSubTitles.size() ) *(padding_default+defaultFontHeight);
                    }
                }
            }
            else
            {
                add_line("");
            }
        }
    }

    void widget_label_paragraph::update_text( std::string newParagraph)
    {
        paragraphText = newParagraph;
        update_paragraph();
    }
    widget_label_title::widget_label_title(std::string name_param, std::string description)
    {
        guiListTypeName = "labeltitle";
        needsNewLine = true;
        opName = name_param;
        descriptionText = description;
        if( FONT_LABEL_TITLE!=NULL)
        {
            int bWid = 0;
            int bHgt = 0;
            FONT_LABEL_TITLE->get_metrics(name_param.c_str(), &bWid, &bHgt);
            widget_box.w = bWid;
            widget_box.h = bHgt;
        }
        opName = name_param;
        hasLineBreak = true;
    }

    widget_label_title::~widget_label_title()
    {

    }

    std::string widget_label_title::get_data()
    {
        return guiListTypeName+":"+opName+"==|||=="+descriptionText;
    }

    std::string widget_label_title::get_plain_string()
    {
        return "\""+opName+"\"";
    }

    void widget_label_title::load_data(std::string dataString)
    {
        descriptionText = dataString;
    }

    void widget_label_title::process_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam)
    {
        widget_basic::process_self(viewedSpace,cam);
        if( isInUse)
        {
            if( gpe::input->check_kb_down(kb_ctrl) && gpe::input->check_kb_released(kb_c) )
            {
                gpe::input->clipboard_set(opName.c_str() );
            }
        }
        /*
        if( isHovered)
        {
            gpe::cursor_main_controller->cursor_change(GPE_CURSOR_HAND);
        }
        if( isClicked )
        {
            wasClicked = true;
            if( (int)webUrl.size() > 3)
            {
                gpe::external_open_url(webUrl);
            }
        }
        */
    }

    void widget_label_title::render_self( gpe::shape_rect * viewedSpace, gpe::shape_rect *cam)
    {
        viewedSpace = gpe::camera_find(viewedSpace);
        cam = gpe::camera_find(cam);
        if( (int)opName.size() > 0 && viewedSpace!=NULL && cam!=NULL )
        {
            gpe::gfs->render_text( widget_box.x-cam->x,widget_box.y+widget_box.h/2-cam->y,opName,pawgui::theme_main->main_box_font_color,FONT_LABEL_TITLE,gpe::fa_left,gpe::fa_middle);

            if( isInUse)
            {
                gpe::gcanvas->render_rectangle( widget_box.x-cam->x,widget_box.y-cam->y,widget_box.x+widget_box.w-cam->x,widget_box.y+widget_box.h-cam->y,pawgui::theme_main->main_box_font_url_color,true);
            }
        }
    }

    void widget_label_title::set_name(std::string name_param)
    {
        guiListTypeName = "labeltexturl";
        if( FONT_LABEL_TITLE!=NULL && name_param!=opName)
        {
            int bWid = 0;
            int bHgt = 0;
            FONT_LABEL_TITLE->get_metrics(name_param.c_str(), &bWid, &bHgt);
            widget_box.w = bWid;
            widget_box.h = bHgt;
        }
        opName = name_param;
    }
}
