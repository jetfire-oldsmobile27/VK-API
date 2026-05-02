/**
 * Describes the class for working with CURL.
 * @file Request.hpp
 * @author qucals
 * @version 0.0.7 24/08/21
 */

#include "Request.hpp"

namespace vk
{

namespace base
{
std::mutex Request::s_mutex;

std::string Request::Send(CURL* curl,
                          const std::string& url,
                          const std::string& postData)
{
    if (!curl) return "";

    curl_easy_reset(curl);

    char errorBuf[CURL_ERROR_SIZE] = {};
    std::string callbackBuf;

    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER,  errorBuf);
    curl_easy_setopt(curl, CURLOPT_USERAGENT,    USERAGENT);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, NO_APPLY_CURLOPT);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS,    MAXREGIDS);
    curl_easy_setopt(curl, CURLOPT_URL,          url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Request::CurlWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,    &callbackBuf);
    curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

    if (!postData.empty()) {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    } else {
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    }

    CURLcode result = curl_easy_perform(curl);
    return (result == CURLE_OK) ? callbackBuf : std::string(errorBuf);
}



std::size_t Request::CurlWriteData(char* ptr, size_t size,
                                   size_t nmemb, std::string* data)
{
    if (data) {
        data->append(ptr, size * nmemb);
        return size * nmemb;
    }

    return 0;
}

} // namespace base

} // namespace vk