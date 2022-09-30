#pragma once
#include "KeyManager.hxx"

namespace lang {
	class Key {
	public:
		Key(const std::string & str) 
		: key {internal::KeyManager::declare(str)} {}

		Key(const std::string_view & str) 
		: key { internal::KeyManager::declare(std::string{str}) } {}

		Key(const char * str) 
		: key { internal::KeyManager::declare(str) } {}



		std::string_view sv() const;
		std::string str() const;
	private:
		std::string_view key;
	};
}