#include "Key.hxx"

namespace lang {

	std::string_view Key::sv() const {
		return this->key;
	}
	
	
	
	std::string Key::str() const {
		return std::string{this->key};
	}
}