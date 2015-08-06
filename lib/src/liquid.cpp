#include<liquid.hpp>
#include<iostream>

using std::cout;
using std::endl;

std::string liquid::output_file="default.gif";
int liquid::number_of_frames=10;
int liquid::height=10;
int liquid::width=10;
int liquid::current_frame=0;
GifColorType* liquid::global_colour_map = new GifColorType[2];
inline void liquid::start() {
	liquid::global_colour_map[0].Red=0;
	liquid::global_colour_map[0].Green=0;
	liquid::global_colour_map[0].Blue=0;
	liquid::global_colour_map[1].Red=255;
	liquid::global_colour_map[1].Green=255;
	liquid::global_colour_map[1].Blue=255;
};
inline void liquid::before_update() {};
inline void liquid::update() {};
inline void liquid::after_update() {};
inline void liquid::stop() {};

inline float liquid::distance(liquid::Point a, liquid::Point b) {
	return std::sqrt((a.pos.x-b.pos.x)*(a.pos.x-b.pos.x)+(a.pos.y-b.pos.y)*(a.pos.y-b.pos.y));
}

inline GifByteType* liquid::draw() {
	int size=liquid::width*liquid::height;
	GifByteType *image=new GifByteType[size];
	for(int i=0; i<size; ++i) {
		image[i]=liquid::current_frame%2;
	}
	return image;
};

int main(int argc, char* argv[]) {
	liquid::start();
	int err;
	GifByteType graphics_control_extension[4]={0,1,0,0};
	const char animation_identifier[]="NETSCAPE2.0";
	GifByteType animation_data[3]={1,0,0};

	int global_colour_table_size=sizeof(liquid::global_colour_map)/sizeof(GifColorType);
	ColorMapObject *global_colour_table=GifMakeMapObject(global_colour_table_size,liquid::global_colour_map);
	ColorMapObject *local_colour_table=GifMakeMapObject(0,NULL);

	std::string full_output_path="gifs/";
	full_output_path+=liquid::output_file;
	GifFileType *gif_file=EGifOpenFileName(full_output_path.c_str(),false,&err);
	EGifSetGifVersion(gif_file,true);
	err=EGifPutScreenDesc(gif_file,liquid::width, liquid::height,2,0,global_colour_table);
	
	//Write animation extension
	EGifPutExtensionLeader(gif_file,0xFF);
	EGifPutExtensionBlock(gif_file,11,(void*)animation_identifier);
	EGifPutExtensionBlock(gif_file,3,(void*)animation_data);
	EGifPutExtensionTrailer(gif_file);

	GifByteType *image;
	for(int i=0; i<liquid::number_of_frames; ++i) {
		liquid::current_frame=i;
		// perform updates on data
		liquid::before_update();
		liquid::update();
		image=liquid::draw();
		liquid::after_update();
		
		// write graphics control extension
		EGifPutExtension(gif_file,0xF9, 0x04, (void*)graphics_control_extension);
		// write image descriptor
		EGifPutImageDesc(gif_file,0,0,liquid::width,liquid::height,false,local_colour_table);
		// write current frame of gif
		EGifPutLine(gif_file,image,liquid::width*liquid::height);
	}
	liquid::stop();
	EGifCloseFile(gif_file,&err);
}
