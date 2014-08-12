#include "LibPng.h"
#include <png.h>
#include <string>
#include <stdio.h>

LibPng::LibPng(std::string path):m_path(path)
{
}

int LibPng::Load()
{
	
	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;

    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
	printf("will be loaded %s\n",m_path);
	FILE *fp = fopen(m_path.c_str(), "rb");
    if (!fp)
	{
            printf("[read_png_file] File %s could not be opened for reading", m_path.c_str());
			return 1;
	}
    fread(header, 1, 8, fp);
	if (png_sig_cmp((png_bytep)header, 0, 8))
	{
            printf("[read_png_file] File %s is not recognized as a PNG file", m_path.c_str());
			return 1;
	}


    /* initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
	{
            printf("[read_png_file] png_create_read_struct failed");
			return 1;
	}

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
	{
            printf("[read_png_file] png_create_info_struct failed");
			return 1;
	}

    if (setjmp(png_jmpbuf(png_ptr)))
	{
            printf("[read_png_file] Error during init_io");
			return 1;
	}

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    m_width = png_get_image_width(png_ptr, info_ptr);
    m_height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
	printf ("color type is %d  ", color_type);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);


    /* read file */
    if (setjmp(png_jmpbuf(png_ptr)))
	{
            printf("[read_png_file] Error during read_image");
			return 1;
	}

	png_bytep *  lRowPtrs = NULL;
	png_int_32 lRowSize = png_get_rowbytes(png_ptr,info_ptr);

	row_pointers = new png_byte[lRowSize * m_height];
  lRowPtrs = new png_bytep[m_height];
  for(int i = 0 ; i < m_height; ++i)
  {
	  lRowPtrs[ m_height - (i+1) ] = row_pointers+ i * lRowSize;
  }
  png_read_image(png_ptr, lRowPtrs);
    fclose(fp);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
  delete[] lRowPtrs;
  return 0;

	return 0;
}
