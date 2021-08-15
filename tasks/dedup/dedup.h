#pragma once

#include <memory>
#include <vector>
#include <string>

using std::string;

std::vector<std::unique_ptr<string>> Duplicate(const std::vector<std::shared_ptr<string>>& items);

std::vector<std::shared_ptr<string>> DeDuplicate(const std::vector<std::unique_ptr<string>>& items);
