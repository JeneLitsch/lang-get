#include "Language.hxx"
#include <mutex>

namespace lang {
	const std::string Language::find(const std::string & key) const {
		if(this->table.contains(key)) {
			return this->table.at(key);
		}
		return key;
	}

	void Language::insert(const std::string & key, const std::string & text) {
		this->table.insert({key, text});
	}

	struct current {
		inline static std::shared_ptr<lang::Language> language;
		inline static std::mutex mutex;
	};

	void set(std::shared_ptr<lang::Language> language) {
		const std::lock_guard lock{current::mutex};
		current::language = std::move(language);
	}

	const std::string get(const std::string & key) {
		const std::lock_guard lock{current::mutex};
		if(current::language) {
			return current::language->find(key);
		}
		else {
			return key;
		}
	}

	const std::string get(const std::string_view key) {
		return get(std::string(key));
	}

	const std::string get(const char * key) {
		return get(std::string(key));
	}
}