#ifndef INC_PBMCONVERTERPP_PBMIMAGE_HPP_
#define INC_PBMCONVERTERPP_PBMIMAGE_HPP_
#include <vector>
#include <deque>
#include <tuple>
#include <utility>
#include <cstdint>
#include <functional>
#include <algorithm>
#include <type_traits>

template<typename PixelType>
class MonocolorImage {
public:
	using pixel_type = PixelType;
	class line_type : private std::conditional_t<std::is_same<bool, pixel_type>::value, std::deque<bool>, std::vector<pixel_type>> {
	private:
		//avoid std::vector<bool>
		using base_type = std::conditional_t<std::is_same<bool, pixel_type>::value, std::deque<bool>, std::vector<pixel_type>>;
	public:
		line_type() = delete;
		line_type(std::size_t size) : base_type(size) {}
		line_type(std::size_t size, bool val) : base_type(size, base_type::value_type(val)) {}
		template <class InputIter>
		line_type(InputIter first, InputIter last) : base_type(first, last, base_type::allocator_type()) {}
		line_type(const line_type& o) : base_type(o) {}
		line_type(line_type&& o) : base_type(std::move(o)) {}

		using base_type::begin;
		using base_type::cbegin;
		using base_type::end;
		using base_type::cend;
		using base_type::rbegin;
		using base_type::crbegin;
		using base_type::rend;
		using base_type::crend;
		using base_type::size;
		using base_type::at;
		using base_type::operator[];
		using base_type::front;
		using base_type::back;
		std::size_t width() const noexcept { return this->size(); }
	};
	using data_type = std::vector<line_type>;
	using iterator = typename data_type::iterator;
	using const_iterator = typename data_type::const_iterator;
	using reverse_iterator = typename data_type::reverse_iterator;
	using const_reverse_iterator = typename data_type::const_reverse_iterator;
private:
	data_type m_data;
public:
	MonocolorImage() = delete;
	MonocolorImage(const MonocolorImage&) = default;
	MonocolorImage(MonocolorImage&&) = default;
	MonocolorImage& operator=(const MonocolorImage&) = default;
	MonocolorImage& operator=(MonocolorImage&&) = default;
	MonocolorImage(std::size_t width, std::size_t height) : m_data(height, line_type(width)) {}
	MonocolorImage(const std::pair<std::size_t, std::size_t>& size) : MonocolorImage(size.first, size.second) {}
	MonocolorImage(const pixel_type* data, std::size_t width, std::size_t height) : MonocolorImage(width, height) {
		std::size_t i = 0;
		for (line_type& line : this->m_data) {
			std::copy_n(data + (height * i), width, line.begin());
			++i;
		}
	}

	std::size_t width() const noexcept
	{
		return (this->m_data.empty()) ? 0 : this->m_data.front().width();
	}
	std::size_t height() const noexcept
	{
		return this->m_data.size();
	}
	iterator begin() { return this->m_data.begin(); }
	const_iterator begin() const { return this->m_data.begin(); }
	const_iterator cbegin() const { return this->m_data.cbegin(); }
	iterator end() { return this->m_data.end(); }
	const_iterator end() const { return this->m_data.end(); }
	const_iterator cend() const { return this->m_data.cend(); }
	reverse_iterator rbegin() { return this->m_data.rbegin(); }
	const_reverse_iterator rbegin() const { return this->m_data.rbegin(); }
	const_reverse_iterator crbegin() const { return this->m_data.crbegin(); }
	reverse_iterator rend() { return this->m_data.rend(); }
	const_reverse_iterator rend() const { return this->m_data.rend(); }
	const_reverse_iterator crend() const { return this->m_data.crend(); }
	line_type& at(std::size_t pos) { return this->m_data.at(pos); }
	const line_type& at(std::size_t pos) const { return this->m_data.at(pos); }
	line_type& operator[](std::size_t pos) noexcept { return this->m_data[pos]; }
	const line_type& operator[](std::size_t pos) const noexcept { return this->m_data[pos]; }
	line_type& fornt() { return this->m_data.front(); }
	const line_type& fornt() const { return this->m_data.front(); }
	line_type& back() { return this->m_data.back(); }
	const line_type& back() const { return this->m_data.back(); }
};
using PBMImage = MonocolorImage<bool>;
using PGMImage = MonocolorImage<std::uint8_t>;

#endif //INC_PBMCONVERTERPP_PBMIMAGE_HPP_
