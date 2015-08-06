#ifndef __liquid_gif_hpp__
#define __liquid_gif_hpp__

	#include<cmath>
	#include<gif_lib.h>
	#include<cstdlib>
	#include<ctime>
	#include<string>

	namespace liquid {

		template <typename T> struct v2x {
			T x,y;
		};

		typedef struct v2x<int> v2i;
		typedef struct v2x<float> v2f;

		typedef struct Point {
			v2i pos;
			v2f vel;
			v2f frc;
			float rad;
			int colour;
		} Point;


		extern GifColorType* global_colour_map;
	
		extern int number_of_frames, current_frame;
		extern int width,height;
		extern std::string output_file;

		float distance(Point a, Point b);
		GifByteType* draw();

		void start();
		void before_update();
		void update();
		void after_update();
		void stop();
	};

#endif
