#pragma once
#include <string>
#include <unordered_map>
#include "curl/curl.h"

namespace blackjack::core {
	class RequestData {
		friend class Network;
	private:
		std::unordered_map<std::string, std::string> data;
	public:
		RequestData();
		void add(const std::string& name, const std::string& value);
	};

	class Network {
	private:
		CURL* curl_handle_;
	public:
		Network();
		~Network();

		void SetUrl(const std::string& url);
		std::string MakeRequest(RequestData& data);
	private:
		static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param);
		static std::string encodeData(CURL* handler, std::unordered_map<std::string, std::string>& data);
	};
}
