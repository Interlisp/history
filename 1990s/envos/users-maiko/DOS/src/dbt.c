#define SRC_WIDTH 64#define SRC_HEIGHT 64#define SIZE unsigned longstatic unsigned char  bits[] = {   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,   0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,   0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x00,   0xff, 0xff, 0xff, 0xf9, 0x10, 0x00, 0x00, 0x0e,   0x00, 0x00, 0x00, 0x09, 0x10, 0x00, 0x00, 0x02,   0x00, 0x00, 0x00, 0x09, 0x10, 0x00, 0x00, 0x02,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9cf, 0xf, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9c, 0xff, 0xf7, 0x00, 0x40, 0x00, 0x00, 0x08,   0x90, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08,   0x90, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08,   0x90, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08,   0x90, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08,   0x90, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08,   0x90, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08,   0x90, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08,   0x90, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08,   0x90, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08,   0x90, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x08,   0x9f, 0xff, 0xff, 0xff, 0x70, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,   0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,   0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,   0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,   0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,   0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}; #include <conio.h>#include <stddef.h>#include <stdlib.h>#include <malloc.h>#include <graph.h>void exitfree( char _huge *buffer ){    hfree( buffer );    exit( !_setvideomode( _DEFAULTMODE ) );}SIZE *tmpbuffer;DOSbitbli(source, source_left, source_top, source_width, source_height,	  dest_left, dest_top)     SIZE *source;     int source_left, source_top, source_width, source_height,       dest_left, dest_top;{  int dest_index = 0;  int source_bottom;  int source_right;  int dest_row, source_row, dest_col, source_col;   int rowlimit;	int pixel;  source_right = source_left + source_width;  source_bottom = source_top + source_height;  /* Adjust source_x to be on word boundrys */  source_left /= 32;  source_right = (source_right+31)/32;  tmpbuffer[dest_index++] = (source_height << 16) + source_width;/*  tmpbuffer[dest_index++] = (SIZE)source_width;  tmpbuffer[dest_index++] = (SIZE)source_height;*/  /* Load the bitimage into the body of the buffer */                         for (source_row = source_top;       source_row < source_bottom;       source_row++) {     for (pixel=0; pixel < 4; pixel++)    for (source_col = ((source_row*source_width)/32) + source_left, rowlimit = source_col + source_right;	 source_col < rowlimit;	 source_col++) {      tmpbuffer[dest_index++] = source[source_col];/*      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];      tmpbuffer[dest_index++] = source[source_col];*/    }  }printarray(tmpbuffer);  _putimage_w(dest_left, dest_top, tmpbuffer, _GPSET );};DOSdspinit(){  struct videoconfig vc;  int size;  /* Init the screen to max resolution. */  if( !_setvideomode( _MAXRESMODE ) )    exit( 1 );  /* Measure the image to be drawn and allocate memory for it. */  tmpbuffer = halloc((size_t)(size=(int)_imagesize_w(0,0,64,64)),		     sizeof( char ));  if ( tmpbuffer == (unsigned long _far *)NULL )    exit( 1 );printf("\n\n\n\n\n\n\n\narray size = %d.\n", size);printf("base = 0x%x\n",(int)tmpbuffer);  };printarray(buff)     SIZE *buff;{/*  int i;  for (i = 0; i < 40; i++) {    printf("[%x]\n", buff[i]);    getch();  } */}    main(){  DOSdspinit();  DOSbitbli(bits, 0, 0, SRC_WIDTH, SRC_HEIGHT, 0, 0);  getch();  exitfree(tmpbuffer);};