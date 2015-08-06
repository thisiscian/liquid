#include<liquid.hpp>
#include<iostream>

using std::cout;
using std::endl;

inline void liquid::start() {};
inline void liquid::before_update() {};
inline void liquid::update() {};
inline void liquid::after_update() {};
inline void liquid::stop() {};

int liquid::current_frame=0;

inline float liquid::distance(liquid::Point a, liquid::Point b) {
	return std::sqrt((a.pos.x-b.pos.x)*(a.pos.x-b.pos.x)+(a.pos.y-b.pos.y)*(a.pos.y-b.pos.y));
}

inline GifByteType* liquid::draw() {
	cout << "i'm trying to draw" << endl;
	int size=liquid::width*liquid::height;
	GifByteType *image=new GifByteType[size];
	for(int i=0; i<size; ++i) {
		image[i]=liquid::current_frame%2;
	}
	return image;
};

int main(int argc, char* argv[]) {
	int err;
	GifByteType graphics_control_extension[4]={0,1,0,0};
	GifColorType global_colour_map[4] = { 0,0,0, 255, 255, 255, 125, 0, 0, 125, 0 };
	const char animation_identifier[]="NETSCAPE2.0";
	GifByteType animation_data[3]={1,0,0};

	ColorMapObject *global_colour_table=GifMakeMapObject(4,global_colour_map);
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
	liquid::start();
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
