#ifndef INC_PBMCONVERTERPP_P4DECODER_HPP_
#define INC_PBMCONVERTERPP_P4DECODER_HPP_
#include <istream>
#include "image.hpp"

PBMImage p4decoder(std::istream& is, bool check_type = true);
#endif //INC_PBMCONVERTERPP_P4DECODER_HPP_
