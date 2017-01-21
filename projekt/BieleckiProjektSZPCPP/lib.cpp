#include "lib.h"

bool keyrel(int k)
{
    static bool initialized = false;
    static bool keyp[KEY_MAX];
 
    if(!initialized)
    {
        // Set the keyp (key pressed) flags to false
        for(int i = 0; i < KEY_MAX; i++) keyp[i] = false;
        initialized = true;
    }
 
    // Now for the checking
    // Check if the key was pressed
    if(key[k] && !keyp[k])
    {
        // Set the flag and return
        keyp[k] = true;
        return false;
    }
    else if(!key[k] && keyp[k])
    {
        // The key was released
        keyp[k] = false;
        return true;
    }
    // Nothing happened?
    return false;
}

void drawInfo(BITMAP * diagram, int toDraw, float value, int generationNr,
		float average, float max) {
	char buffer [10];
	sprintf (buffer, "< %d >", toDraw);
	
	char buffer2 [20];
	sprintf (buffer2, "Value: %f", value);
	
	char buffer3 [100];
	sprintf (buffer3, "GENERATION NR %d STATS: Average: %f Max: %f",
		generationNr, average, max);
	
	textout_ex(
             diagram,//Specify bitmap on the screen
             font,//Use a default font
             buffer,//Specify the text to display
             20,//x-coordinate for text
             20,//y-coordinate for text
             makecol(0,0,0),//Color text black
             -1 );//Transparent text background.
    textout_ex(
             diagram,//Specify bitmap on the screen
             font,//Use a default font
             buffer2,//Specify the text to display
             360,//x-coordinate for text
             20,//y-coordinate for text
             makecol(0,0,0),//Color text black
             -1 );//Transparent text background.
   textout_ex(
             diagram,//Specify bitmap on the screen
             font,//Use a default font
             buffer3,//Specify the text to display
             20,//x-coordinate for text
             460,//y-coordinate for text
             makecol(255,255,255),//Color text white
             -1 );//Transparent text background.
}

void deinit(BITMAP *diagram) {
	allegro_exit();
    clear_keybuf();
    destroy_bitmap( diagram );
}

void init(BITMAP *diagram) {
	allegro_init();
	install_keyboard();
	set_color_depth( 16 );
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0 );
	clear_to_color( screen, makecol( 255, 255, 255 ) );
	diagram = create_bitmap( 500, 500 );
	clear_to_color( diagram, makecol( 100, 255, 255 ) );
	blit( diagram, screen, 0, 0, 0, 0, diagram->w, diagram->h );
}
