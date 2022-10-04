#pragma once
#include <map>
#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include "Key.hxx"
namespace lang {
	class Language {
	public:
		const std::string find(const Key & key) const;
		void insert(const std::string & key, const std::string & text);
		bool contains(const Key & key);

		std::vector<std::string> find_missing() const;
	private:
		std::map<std::string, std::string, std::less<void>> table;
	};

	void set(std::shared_ptr<Language> language);
	const std::string get(const Key & key);
	// const std::string get(Key && key) = delete;
}