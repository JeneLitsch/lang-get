#include "load.hxx"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace lang::load {
	
	namespace {
		bool check(std::istream & in, char chr) {
			return in.peek() == chr;
		}
		
		bool match(std::istream & in, char chr) {
			if(check(in, chr)) {
				in.ignore();
				return true;
			}
			return false;
		}

		char unescape(std::istream & in) {
			switch (in.get()) {
			case 'n': return '\n';
			case 't': return '\t';
			case '"': return '"';
			case '\\': return '\\';
			default: throw std::runtime_error{"Invalid escape sequence"};
			}
		}

		char next(std::istream & in) {
			const auto chr = in.get();
			if(chr == '\\') {
				return unescape(in);
			}
			return static_cast<char>(chr);
		}

		std::string readValue(std::istream & in) {
			in >> std::ws;
			std::string str;
			if(match(in, '"')) {
				while(true) {
					if(match(in, '"')) {
						return str;
					}
					if(in.eof()) {
						throw std::runtime_error("Unterminated string \"");
					}
					str.push_back(next(in));
				}
			}
			else {
				throw std::runtime_error("Expected \"");
			}
		}

		std::pair<std::string, std::string> readEntry(std::istream & in) {
			const auto key = readValue(in);
			if(!match(in >> std::ws, ':')) {
				throw std::runtime_error("Expected :");
			}
			const auto str = readValue(in);
			return {key, str};
		}
		
		void loadFile(Language & language, std::istream & in) {
			while(!in.eof()) {
				std::string line;
				std::getline(in, line);
				if(!std::all_of(line.begin(), line.end(), std::iswspace)) {
					std::stringstream ls {line}; 
					const auto [key, str] = readEntry(ls);
					language.insert(key, str);
				}
			}
		}
	}


	std::unique_ptr<Language> language(	
		const std::string_view & langCode,
		const std::filesystem::path & directory,
		const std::span<const std::filesystem::path> files) {

		auto language = std::make_unique<Language>();
		for(const auto & file : files) {
			const auto filepath = directory / langCode / file;
			if(std::filesystem::exists(filepath)) {
				std::ifstream fin(filepath);
				loadFile(*language, fin);
			}
			else {
				throw std::runtime_error{"Cannot open " + filepath.string()};
			}

		}
		return language;
	}
}