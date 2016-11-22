#include <allegro.h>
#include <iostream>
#include <math.h>

int size = 500;
int pixTab[500][500];
int laserSize = 5;
int laserPower = 10;
volatile long speed = 0;

BITMAP *kwadrat_z_kropka ()
{
	const int ZIELONY = makecol (0, 255, 0);
	const int CZERWONY = makecol (255, 0, 0);
	BITMAP *bmp = create_bitmap (size, size); // tworzymy bitmapę
	clear (bmp); // czyści bitmapę (na czarno)
	clear_to_color (bmp, makecol (0, 0, 255));
	// prostokąt
	//putpixel (bmp, 100, 100, CZERWONY);
	// punkt
	for ( int ii=0;ii<size;ii++ ) {
		for ( int jj=0;jj<size;jj++ ) {
			int PIX = makecol (pixTab[ii][jj]/10, 0, 255 - pixTab[ii][jj]/10);
			putpixel (bmp, ii, jj, PIX);
		}
	}
	return bmp;
}

void increment_speed()
{
    speed++;
}
END_OF_FUNCTION( increment_speed );

void laser(int x, int y) {
	for ( int ii=-laserSize;ii<=laserSize;ii++ ) {
		for ( int jj=-laserSize;jj<=laserSize;jj++ ) {
			if ( pow(ii,2)+pow(jj,2) < pow(laserSize,2) && pixTab[x+ii][y+jj] < 2450 - laserPower)
				pixTab[x+ii][y+jj] += laserPower;
		}
	}
}

void addToPixTab(int x, int y, int heat) {
	if ( pixTab[x][y] + heat < 2550 )
		pixTab[x][y]+=heat;
	else 
		pixTab[x][y] = 2550;
	
	if ( pixTab[x][y] < 0 )
		pixTab[x][y] = 0;
}

void heatTransfer() {
	int min = 6;
	int lewy,prawy,gorny,dolny,srodek;
	int sl,sp,sg,sd;
	for ( int ii=1;ii<size-1;ii++ ) {
		for ( int jj=1;jj<size-1;jj++ ) {
			lewy = pixTab[ii-1][jj];
			prawy = pixTab[ii+1][jj];
			gorny = pixTab[ii][jj+1];
			dolny = pixTab[ii][jj-1];
			srodek = pixTab[ii][jj];
			sl = lewy - srodek;
			sp = prawy - srodek;
			sg = gorny - srodek;
			sd = dolny - srodek;
			addToPixTab(ii-1,jj,-sl/min);
			addToPixTab(ii+1,jj,-sp/min);
			addToPixTab(ii,jj+1,-sg/min);
			addToPixTab(ii,jj-1,-sd/min);
			tranferHeat(ii-1,jj,ii,jj,sl/min);
			addToPixTab(ii,jj,sl/min);
			addToPixTab(ii,jj,sp/min);
			addToPixTab(ii,jj,sg/min);
			addToPixTab(ii,jj,sd/min);
			
		}
	}
	BITMAP *kwadrat = kwadrat_z_kropka ();
	blit (kwadrat, screen, 0, 0, 0, 0, size, size);// umieszcza kwadrat na screen
}

void przerwanie_myszy (int m)
{
	if (m & MOUSE_FLAG_LEFT_UP && pixTab[mouse_x][mouse_y] < 2450) {
		laser(mouse_x,mouse_y);
		BITMAP *kwadrat = kwadrat_z_kropka ();
		blit (kwadrat, screen, 0, 0, 0, 0, size, size);// umieszcza kwadrat na screen
	}
	else if (m & MOUSE_FLAG_RIGHT_UP) {
		
	}
		
}
END_OF_FUNCTION(przerwanie_myszy)

void initializePixTab() {
	for ( int ii=0;ii<size;ii++ ) {
		for ( int jj=0;jj<size;jj++ ) {
			pixTab[ii][jj] = 0;
		}
	}
}

int main() {
	initializePixTab();
	allegro_init ();
	install_timer ();
	install_keyboard ();
	install_mouse ();
	// Uruchamiamy grafikę w trybie pełnoekranowym 800x600, 16 bpp
	set_color_depth (16);
	// ustawia bpp
	
	if (set_gfx_mode (GFX_AUTODETECT_WINDOWED, 500, 500, 0, 0) != 0)
	{
		std::cout << "Blad inicjowania trybu graficznego!";
		return 1;
	}
	
	set_window_title ("Tytul okna"); // ustawia tytuł okna
	BITMAP *kwadrat = kwadrat_z_kropka ();
	blit (kwadrat, screen, 0, 0, 0, 0, size, size);// umieszcza kwadrat na screen
	show_mouse(screen);
	LOCK_FUNCTION(przerwanie_myszy);
	mouse_callback = przerwanie_myszy;
	
	LOCK_VARIABLE( speed );
	LOCK_FUNCTION( increment_speed );
	install_timer();
	install_int_ex( increment_speed, BPS_TO_TIMER( 30 ) );
	
	while( !key[ KEY_ESC ] ) {
        if( key[ KEY_LEFT ] ) {
			if ( laserSize > 0 )
				laserSize--;
		}
   
		if( key[ KEY_RIGHT ] ) {
			if ( laserSize < 50 )
				laserSize++;
		}
		
		if( key[ KEY_UP ] )  {
			if ( laserPower < 50 )
				laserPower++;
		}
		
		if( key[ KEY_DOWN ] ) {
			if ( laserPower > 0 )
				laserPower--;
		}
		
		rest(1); 
		
		while( speed > 0 ) {
			heatTransfer();
			speed--;
		}
	}
	
	destroy_bitmap (kwadrat);
	allegro_exit ();
	return 0;
}
