#include <pebble.h>
#include "instructions_layer.h"
#include "external_variables.h"

static Window 								    *s_window;
static ScrollLayer 						    *s_scroll_layer;
static TextLayer 							    *s_text_layer;
//static char* instructions_text; = ;

static void initialise_ui(void)
{
	s_window 									      = window_create();
	GRect bounds 								    = layer_get_bounds(window_get_root_layer(s_window));
  GRect max_text_bounds           = GRect(0, 0, bounds.size.w, 2000);
	s_text_layer 								    = text_layer_create(max_text_bounds);
	s_scroll_layer 								  = scroll_layer_create(bounds);

	text_layer_set_text							(s_text_layer,
                                   "  THIS IS A GAME OF BUYING AND SELLING MEMES.\n\n  YOUR GOAL IS TO PAY OFF YOUR DEBT TO THE MEME SHARK, AND THEN MAKE AS MUCH MONEY AS POSSIBLE.\n\n  ADD FUNDS TO YOUR BANK ACCOUNT TO EARN INTEREST AND KEEP IT SAFE FROM MEME STEALERS.\n\n  WATCH-OUT FOR THE HATERS IF YOU MEME TOO HEAVILY!\n\nPRICE RANGES:\n\n DOGE: 15k-28k\n SPONGEBOB:   5k-12k\n ODNS:         1k-4.2k\n GIFS:       300-720\n BRUH:       70-220\n FAGGOTRY:         10-50");
	text_layer_set_text_alignment   (s_text_layer, GTextAlignmentCenter);
  scroll_layer_set_click_config_onto_window	(s_scroll_layer, s_window);
	scroll_layer_add_child          (s_scroll_layer, text_layer_get_layer(s_text_layer));
	scroll_layer_set_content_size   (s_scroll_layer, text_layer_get_content_size(s_text_layer));
	layer_add_child								  (window_get_root_layer(s_window), scroll_layer_get_layer(s_scroll_layer));
	
#ifdef PBL_ROUND
	scroll_layer_set_paging					(s_scroll_layer, true);
#endif
}

static void destroy_ui(void)
{
  text_layer_destroy              (s_text_layer);
  scroll_layer_destroy            (s_scroll_layer);
	window_destroy								  (s_window);
}

static void handle_window_unload(Window* window)
{
	destroy_ui();
}

void show_instructions_layer(MenuIndex *cell_index)
{
  initialise_ui();
	window_set_window_handlers			(s_window, (WindowHandlers) {.unload = handle_window_unload,});
	window_stack_push							  (s_window, true);
}

void hide_instructions_layer(void)
{
	window_stack_remove							(s_window, true);
}
