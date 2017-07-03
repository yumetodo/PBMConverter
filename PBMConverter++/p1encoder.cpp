#include "p1encoder.hpp"

void p1encoder(std::ostream& os, const PBMImage& image)
{
	os
		<< u8"P1" << std::endl
		<< u8"# Created by PBMConverter++(yumetodo <yume-wikijp@live.jp>)" << std::endl
		<< image.width() << u8" " << image.height() << std::endl;
	for (auto&& l : image) {
		bool is_first_line = true;
		for (auto&& p : l) {
			if (!is_first_line) os << u8" ";
			os << ((p) ? u8"1" : u8"0");
			is_first_line = false;
		}
		os << std::endl;
	}
}
