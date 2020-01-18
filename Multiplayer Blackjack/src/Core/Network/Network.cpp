#define CURL_STATICLIB
#include "Network.h"

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")

CURL* init() {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	auto curl = curl_easy_init();
	if (curl) {

		curl_easy_setopt(curl, CURLOPT_URL, "https://student.csc.liv.ac.uk/~sgkbaker/blackjack/blackjack.php");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
	}
	return curl;
}

void destroy(CURL* handler) {
	curl_easy_cleanup(handler);

	curl_global_cleanup();
}

size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

std::string encodeData(CURL* handler, std::unordered_map<std::string, std::string>& data) {
	std::string encoded = "";

	for (auto it = data.begin(); it != data.end(); ++it) {
		encoded += it->first + "=";
		char* d = curl_easy_escape(handler, it->second.c_str(), it->second.length());
		encoded += d;
		encoded += "&";
		curl_free(d);
	}

	return encoded;
}

std::string makeRequest(CURL* handler, std::unordered_map<std::string, std::string>& data) {
	std::string result;
	CURLcode res;

	std::string encode = encodeData(handler, data);

	curl_easy_setopt(handler, CURLOPT_WRITEDATA, &result);
	curl_easy_setopt(handler, CURLOPT_POSTFIELDS, encode.c_str());

	res = curl_easy_perform(handler);

	return result;
}

