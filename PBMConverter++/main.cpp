#include "p1encoder.hpp"
#include "p4decoder.hpp"
#include <fstream>
#include <iostream>
int main()
{
	try {
		std::cout << "reading image..." << std::flush;
		std::ifstream in("p4img.pbm", std::ios::in | std::ios::binary);
		auto img = p4decoder(in);
		std::cout
			<< "done." << std::endl
			<< "width:" << img.width() << " height:" << img.height() << std::endl
			<< "writing image..." << std::flush;
		std::ofstream out("p1img.pbm", std::ios::out | std::ios::binary);
		p1encoder(out, img);
		std::cout << "done." << std::endl;
	}
	catch (const std::exception& er) {
		std::cerr << std::endl << er.what() << std::endl;
	}
}