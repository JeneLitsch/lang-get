#pragma once

#include <filesystem>
#include <span>
#include "Language.hxx"

namespace lang::load {
	std::unique_ptr<Language> language(
		const std::string_view & langCode,
		const std::filesystem::path & directory,
		const std::span<const std::filesystem::path> files);
}