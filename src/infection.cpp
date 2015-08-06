#include<iostream>
#include<liquid.hpp>

using std::cout;
using std::endl;

namespace infection {
	int counter=0;
}

int liquid::height=100;
int liquid::width=100;
int liquid::number_of_frames=10;
const char* liquid::output_file="infection.gif";

void liquid::start() {
	cout << "liquid::start" << endl;
	cout << "  output_file: " << liquid::output_file << endl;
	cout << "       frames: " << liquid::number_of_frames << endl;
}

void liquid::update() {
	cout << "liquid::update" << endl;
	cout << "    frame: " << liquid::current_frame << endl;
	cout << "  counter: " << infection::counter++ << endl;
}

void liquid::stop() {
	cout << "liquid::stop" << endl;
}
