#include<iostream>
#include<liquid.hpp>

using std::cout;
using std::endl;

namespace infection {
	int counter=0;
}

int liquid::frames=10;
char* liquid::output_file="infection.gif";

void liquid::start() {
	cout << "liquid::start" << endl;
	cout << "  output_file: " << liquid::output_file << endl;
	cout << "       frames: " << liquid::frames << endl;
}

void liquid::update(int frame_number) {
	cout << "liquid::update" << endl;
	cout << "    frame: " << frame_number << endl;
	cout << "  counter: " << infection::counter++ << endl;
}

void liquid::stop() {
	cout << "liquid::stop" << endl;
}
