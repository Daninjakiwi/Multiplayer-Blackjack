#define CURL_STATICLIB
#include "Network.h"
#include "Core/Log.hpp"

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
//#pragma comment (lib, "advapi32.lib")

namespace blackjack::core {
	RequestData::RequestData() {
	}

	void RequestData::add(const std::string& name, const std::string& value) {
		data[name] = value;
	}

	Network::Network() : curl_handle_(nullptr) {
		curl_global_init(CURL_GLOBAL_DEFAULT);
		curl_handle_ = curl_easy_init();
		if (curl_handle_) {
			curl_easy_setopt(curl_handle_, CURLOPT_WRITEFUNCTION, my_write);
		}
	}
	Network::~Network() {
		curl_easy_cleanup(curl_handle_);
		curl_global_cleanup();
	}

	void Network::SetUrl(const std::string& url) {
		curl_easy_setopt(curl_handle_, CURLOPT_URL, url.c_str());
	}

	std::string Network::MakeRequest(RequestData& data) {
		std::string result;

		std::string encode = encodeData(curl_handle_, data.data);

		curl_easy_setopt(curl_handle_, CURLOPT_WRITEDATA, &result);
		curl_easy_setopt(curl_handle_, CURLOPT_POSTFIELDS, encode.c_str());

		curl_easy_perform(curl_handle_);

		return result;
	}

	size_t Network::my_write(void* buffer, size_t size, size_t nmemb, void* param)
	{
		std::string& text = *static_cast<std::string*>(param);
		size_t totalsize = size * nmemb;
		text.append(static_cast<char*>(buffer), totalsize);
		return totalsize;
	}

	std::string Network::encodeData(CURL* handler, std::unordered_map<std::string, std::string>& data) {
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
}

