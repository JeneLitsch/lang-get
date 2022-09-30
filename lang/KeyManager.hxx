#pragma once
#include <set>
#include <string>
#include <mutex>

namespace lang::internal {
	class KeyManager {
	public:
		static std::string_view declare(std::string str) {
			std::lock_guard lock{mutex};
			return *known_keys.insert(str).first;
		}

		static const std::set<std::string> & keys() {
			return known_keys;
		}
	private:
		inline static std::mutex mutex;
		inline static std::set<std::string> known_keys;
	};
}