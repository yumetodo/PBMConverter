#include "p4decoder.hpp"
#include <array>
#include <bitset>
#include <limits>
#include <sstream>
#include <stdexcept>

namespace {
	bool skip_comment(std::istream& is) {
		bool re = false;
		for (char c; u8"#"[0] == (c = static_cast<char>(is.get())); re = true) is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		is.unget();
		return re;
	}
	std::pair<std::size_t, std::size_t> read_header(std::istream& is, bool check_type) {
		std::size_t width = 0;
		std::size_t height = 0;
		if(check_type){
			skip_comment(is);
			std::string buf;
			std::getline(is, buf);
			if (u8"P"[0] != buf[0] || u8"4"[0] != buf[1]) throw std::runtime_error("input picture is not PBM(P4).");
		}
		skip_comment(is);
		{
			//Skip charactors that isspace return true
			is >> width >> std::skipws >> height;
		}
		skip_comment(is);
		return{ width, height };
	}
}
PBMImage p4decoder(std::istream& is, bool check_type)
{
	PBMImage re = read_header(is, check_type);
	std::stringstream ss;
	//share stream buffer
	ss << is.rdbuf();
	//read all
	std::string data = ss.str();
	//P4: 1byte contains 8 pixel informarion(max)
	const std::size_t width_byte = re.width() / 8 + (0 != (re.width() % 8));
	//check size
	if (data.size() < (width_byte * re.height())) throw std::out_of_range("We cannot believe header informaion");
	//parse data
	std::size_t data_i = 0;
	for (auto&& line : re) {
		for (std::size_t line_i = 0; line_i < line.width() && data_i < data.size(); ++data_i) {
			const std::bitset<8> bits = data[data_i];
			for (size_t j = 0; j < 8u && line_i < line.width(); ++line_i, ++j) {
				//std::bitset::operator[] access bit from LSB(least significant bit) so that reverse access is required.
				line[line_i] = bits[8 - 1 - j];
			}
		}
	}
	return re;
}
