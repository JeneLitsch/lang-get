#include "Language.hxx"
#include <mutex>

namespace lang {
	const std::string Language::find(const Key & key) const {
		if(this->table.contains(key.sv())) {
			return this->table.find(key.sv())->second;
		}
		return key.str();
	}



	void Language::insert(const std::string & key, const std::string & text) {
		this->table.insert({key, text});
	}



	bool Language::contains(const Key & key) {
		return this->table.contains(key.sv());
	}



	std::vector<std::string> Language::find_missing() const {
		std::vector<std::string> missing_keys;
		auto & needed = internal::KeyManager::keys();
		for(const auto & key : needed) {
			if(!this->table.contains(key)) missing_keys.push_back(key);
		}
		return missing_keys;
	}



	struct current {
		inline static std::shared_ptr<lang::Language> language;
		inline static std::mutex mutex;
	};



	void set(std::shared_ptr<lang::Language> language) {
		const std::lock_guard lock{current::mutex};
		current::language = std::move(language);
	}



	const std::string get(const Key & key) {
		const std::lock_guard lock{current::mutex};
		if(current::language) {
			return current::language->find(key);
		}
		else {
			return key.str();
		}
	}

	const std::string get(const std::string & key) {
		return get(Key{key});
	}

	const std::string get(const std::string_view key) {
		return get(Key{std::string{key}});
	}

	const std::string get(const char * key) {
		return get(Key{key});
	}
}