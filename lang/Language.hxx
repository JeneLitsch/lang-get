#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <memory>
namespace lang {
	class Language {
	public:
		const std::string find(const std::string & key) const;
		void insert(const std::string & key, const std::string & text);
	private:
		std::unordered_map<std::string, std::string> table;
	};

	void set(std::shared_ptr<Language> language);
	const std::string get(const char * key);
	const std::string get(const std::string & key);
	const std::string get(const std::string_view key);
}