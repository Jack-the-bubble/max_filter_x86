#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <allegro5/allegro5.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_LOCKED_REGION *region = NULL;

extern void max_filt(unsigned char* input, unsigned char* output, int h, int w, int m);

extern void max_filt_u(__uint8_t* in, __uint8_t* out, int w, int h,int m);

int main() {

//	init library
//	al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_RGB_888);
//	if (!al_init()) // error
//	{
//		al_show_native_message_box(display, "Error", "Error", "Failed to initialize allegro!",
//								   NULL, ALLEGRO_MESSAGEBOX_ERROR);
//		exit(1);
//	}
//
//	if (!al_init_image_addon()) // error
//	{
//		al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
//								   NULL, ALLEGRO_MESSAGEBOX_ERROR);
//		exit(1);
//	}
//
//	//	get image from user
//	al_destroy_bitmap(image);
//	image = NULL;
//	char name[100];
//	do
//	{
//		printf("Podaj nazwe pliku: ");
//		scanf("%s", name);
//		image = al_load_bitmap(name);
//	} while (!image);
//
//	int width = al_get_bitmap_width(image);
//	int height = al_get_bitmap_height(image);
//
////	init display
//	if (display)
//		al_destroy_display(display);
//
//	display = al_create_display(width, height - 1);
//
//	if (!display)	// error
//	{
//		al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
//								   NULL, ALLEGRO_MESSAGEBOX_ERROR);
//		exit(1);
//	}
//
//
//	int widthInBytes = width * 3;
//	unsigned char *input_buffer = (unsigned char *)malloc(height * widthInBytes);
//
//	region = al_lock_bitmap(image,ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_READWRITE);
//	memcpy(input_buffer, ((unsigned char *)(region->data)) - (height - 1) * widthInBytes, height * widthInBytes);
//	al_unlock_bitmap(image);
//


//	max_filt(input_buffer, (unsigned char *)(region->data) - (height - 1) * widthInBytes, width, height, 1);
	__uint8_t test_tab[48];
	__uint8_t test_tab_2[48];
	for (__uint8_t i = 0; i < 48; ++i) {
		if (i % 12 == 0)
			printf("\n");
		test_tab[i]= i/3;
		test_tab_2[i] = i/3;
		printf("%d ", test_tab[i]);
	}

	max_filt_u(test_tab, test_tab_2, 4, 4, 2);
	printf("finished filtering\n");

	for (int j = 0; j < 48; ++j) {
		if(j%12 == 0)
			printf("\n");
		printf("%d ", test_tab_2[j]);
	}
//
//	al_unlock_bitmap(image);
//
//	al_draw_bitmap(image, 0, 0, 0);
//	al_flip_display();
//
//	printf("Press eny key to finish ");
//	char control[10];
//	scanf("%s", control);
//	free(input_buffer);
//
//	al_destroy_display(display);
//	al_destroy_bitmap(image);
//	al_shutdown_image_addon();
	return 0;
}