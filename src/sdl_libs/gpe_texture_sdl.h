/*
GPE_Texture.h
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

#ifndef gpe_texture_sdl
#define gpe_texture_sdl

#include "../gpe/gpe_branch.h"
#include "../gpe/gpe_color_manager.h"
#include "../gpe/gpe_common_includes.h"
#include "../gpe/gpe_color.h"
#include "../gpe/gpe_constants.h"
#include "../gpe/gpe_error_logger.h"
#include "../gpe/gpe_globals.h"
#include "../gpe/gpe_texture_base.h"
#include "../other_libs/stg_ex.h"
#include "gpe_renderer_sdl.h"
#include "sdl_surface_ex.h"

namespace gpe
{
    class texture_sdl: public texture_base
    {
        protected:
            SDL_Texture * texImg;
        public:
            texture_sdl();
            ~texture_sdl();
            void change_alpha( Uint8 alpha );
            void change_color( color * newColor);
            void change_color( Uint8 red, Uint8 green, Uint8 blue );
            void change_texture(SDL_Texture * newTexture);
            bool copy_image_source(std::string outDirectoryName);

            renderer_system_sdl * get_gpe_renderer_sdl(renderer_base * renderer);
            SDL_Renderer * get_sdl_renderer(renderer_base * renderer);
            SDL_Texture * get_sdl_texture();
            void load_new_texture( renderer_base * renderer, std::string fileName, int id = -1, bool transparent = true, bool useLinearScaling = false );
            void prerender_circle( renderer_base * renderer, int rad, color * circleColor,  Uint8 alpha = 255,int id = -1, bool transparent = true, bool useLinearScaling = true , bool isOutline = false );
            void prerender_rectangle( renderer_base * renderer, int w, int h, color * newColor, int id = -1, bool transparent = true, bool useLinearScaling = true  , bool isOutline = false);

            texture_base * create_new();

            void render_align(  int x, int y, int hAlign, int vAlign, gpe::shape_rect* clip = NULL, color * rendColor = NULL, int alpha = 255  );
            void render_align_resized(  int x, int y,int newWidth, int newHeight, int hAlign, int vAlign, gpe::shape_rect* clip = NULL, color * rendColor = NULL, int alpha = 255 );
            void render_tex(  int x, int y, gpe::shape_rect* clip = NULL, int alpha = 255  );
            void render_tex_colored(  int x, int y, color * rendColor, int alpha = 255, gpe::shape_rect* clip = NULL  );
            void render_tex_resized(  int x, int y,float newWidth, float newHeight, gpe::shape_rect* clip = NULL, color * rendColor = NULL, int alpha = 255 );
            void render_tex_scaled(  int x, int y,float xScale, float yScale, gpe::shape_rect* clip = NULL, color * rendColor = NULL, int alpha = 255 );
            void render_tex_rotated(  int x, int y, float renderAngle,  color * renderColor = NULL, gpe::shape_rect* clip = NULL , int alpha = 255 );
            void render_tex_rotated_at_point(  int x, int y, float renderAngle, int pointX, int pointY, color * renderColor = NULL, gpe::shape_rect* clip = NULL , int alpha = 255 );
            void render_tex_special(  int x, int y, float renderAngle, int newWidth = -1, int newHeight = -1, color * renderColor = NULL, gpe::shape_rect* clip = NULL , int alpha = 255 );
            void render_tex_special_at_point(  int x, int y, float renderAngle, int pointX, int pointY,int newWidth = -1, int newHeight = -1, color * renderColor = NULL, gpe::shape_rect* clip = NULL , int alpha = 255 );

            void set_alpha( int alpha);
            void set_blend_mode( int newBlendMode);
    };
}
#endif //GPE_TEXTURE_SDL_H
