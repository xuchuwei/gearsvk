/*
 * Copyright (c) 2022 Jeff Boody
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>

#define LOG_TAG "vkk"
#include "../../libcc/cc_log.h"
#include "../vkk_ui.h"

/***********************************************************
* public                                                   *
***********************************************************/

vkk_uiInfoPanel_t*
vkk_uiInfoPanel_new(vkk_uiScreen_t* screen, size_t wsize,
                    vkk_uiInfoPanelFn_t* ipfn)
{
	ASSERT(screen);
	ASSERT(ipfn);

	vkk_uiWidgetLayout_t layout =
	{
		.border = VKK_UI_WIDGET_BORDER_MEDIUM,
	};

	vkk_uiWidgetScroll_t scroll =
	{
		.scroll_bar = 1
	};
	vkk_uiScreen_colorScroll0(screen, &scroll.color0);
	vkk_uiScreen_colorScroll1(screen, &scroll.color1);

	cc_vec4f_t color;
	vkk_uiScreen_colorBackground(screen, &color);

	vkk_uiListBoxFn_t lbfn =
	{
		.priv       = ipfn->priv,
		.refresh_fn = ipfn->refresh_fn,
	};

	return (vkk_uiInfoPanel_t*)
	       vkk_uiListBox_new(screen, wsize, &lbfn,
	                         &layout, &scroll,
	                         VKK_UI_LISTBOX_ORIENTATION_VERTICAL,
	                         &color);
}

void vkk_uiInfoPanel_delete(vkk_uiInfoPanel_t** _self)
{
	ASSERT(_self);

	vkk_uiInfoPanel_t* self = *_self;
	if(self)
	{
		vkk_uiListBox_delete((vkk_uiListBox_t**) _self);
	}
}

void vkk_uiInfoPanel_add(vkk_uiInfoPanel_t* self,
                         vkk_uiWidget_t* widget)
{
	ASSERT(self);
	ASSERT(widget);

	vkk_uiListBox_add(&self->base, widget);
}

void vkk_uiInfoPanel_clear(vkk_uiInfoPanel_t* self)
{
	ASSERT(self);

	vkk_uiListBox_clear(&self->base);
}
