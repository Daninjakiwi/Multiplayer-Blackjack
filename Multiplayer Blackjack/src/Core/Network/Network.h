#pragma once

#include "curl/curl.h"

#include <string>
#include <unordered_map>

size_t my_write(void* buffer, size_t size, size_t nmemb, void* param);
std::string encodeData(CURL* handler, std::unordered_map<std::string, std::string>& data);
std::string makeRequest(CURL* handler, std::unordered_map<std::string, std::string>& data);
CURL* init();
void destroy(CURL* handler);
