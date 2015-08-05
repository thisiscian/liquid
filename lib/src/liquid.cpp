#include<liquid.hpp>
#include<iostream>
#include<liquid.hpp>

using std::cout;
using std::endl;

inline void liquid::start() {};
inline void liquid::before_update() {};
inline void liquid::update(int frame_number) {};
inline void liquid::after_update() {};
inline void liquid::stop() {};

int main(int argc, char* argv[]) {
	liquid::start();
	for(int i=0; i<liquid::frames; ++i) {
		liquid::before_update();
		liquid::update(i);
		liquid::after_update();
	}
	liquid::stop();
}
