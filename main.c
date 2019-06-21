#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_LOCKED_REGION *region = NULL;

extern void max_filt(unsigned char* input, unsigned char* output, int h, int w, int m);
void init_pix_format();

int main(int argc, char *argv[]){
	init_pix_format();
	char comm[10];
	char pic[20];
	while(true)	{
		printf("type file name with extention ");
		scanf("%s", pic);
		image = al_load_bitmap(pic);
		if (image)
			break;
	}

	int width = al_get_bitmap_width(image);
	int height = al_get_bitmap_height(image);
	display = al_create_display(width, height);

	int byteW = width * 3;
	unsigned char *in_buf = (unsigned char *)malloc(height * byteW);

	region = al_lock_bitmap(image,ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_READWRITE);
	memcpy(in_buf, ((unsigned char *)(region->data)) - (height - 1) * byteW, height * byteW);
	al_unlock_bitmap(image);

	while (true){
		printf("type in mask size ");
		int mask;
		scanf("%d", &mask);
		region = al_lock_bitmap(image, ALLEGRO_PIXEL_FORMAT_RGB_888, ALLEGRO_LOCK_READWRITE);

		max_filt(in_buf, (unsigned char *)(region->data) - (height - 1) * byteW, width, height, mask);

		al_unlock_bitmap(image);
		al_draw_bitmap(image, 0, 0, 0);
		al_flip_display();

		printf("Do you want to filter with anoter mask size?(y/n) ");
		scanf("%s", comm);
		if (comm[0] != 'y')
			break;
	}

	free(in_buf);
	al_destroy_display(display);
	al_destroy_bitmap(image);
	al_shutdown_image_addon();
	return 0;
}

void init_pix_format(){
	al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_BGR_888);
	if (!al_init())	{
		al_show_native_message_box(display, "Error", "Error", "Failed allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}

	if (!al_init_image_addon()){
		al_show_native_message_box(display, "Error", "Error", "ad fail!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
}