/**
 * Contains additional functions for working with the library.
 * @file Utilities.cpp
 * @author qucals
 * @version 0.0.9 02/05/26
 */

#include "Utilities.hpp"
#include <memory>
#include <curl/curl.h>

namespace vk
{

namespace utilities
{

struct CurlHandle {
    CURL* handle;
    
    CurlHandle() : handle(curl_easy_init()) {}
    
    ~CurlHandle() {
        if (handle) {
            curl_easy_cleanup(handle);
        }
    }
    
    CurlHandle(const CurlHandle&) = delete;
    CurlHandle& operator=(const CurlHandle&) = delete;
    
    CurlHandle(CurlHandle&& other) noexcept : handle(other.handle) {
        other.handle = nullptr;
    }
    
    CurlHandle& operator=(CurlHandle&& other) noexcept {
        if (this != &other) {
            if (handle) {
                curl_easy_cleanup(handle);
            }
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }
    
    explicit operator bool() const { return handle != nullptr; }
    CURL* get() const { return handle; }
};


std::string ConvertStrToUrlCode(const std::string& str)
{
    CurlHandle curl;
    
    if (!curl) {
        return str;
    }
    
    char* output = curl_easy_escape(curl.get(), str.c_str(), static_cast<int>(str.length()));
    
    if (!output) {
        return str;  
    }
    
    std::unique_ptr<char, decltype(&curl_free)> escaped(output, curl_free);
    
    return std::string(escaped.get());
}

std::string ToString(int val)
{
#ifdef __CPLUSPLUS_OVER_11
    return std::to_string(val);
#else
    std::ostringstream ostr;
    ostr << val;
    std::string str = ostr.str();
    return str;
#endif
}

std::string ToString(unsigned val)
{
#ifdef __CPLUSPLUS_OVER_11
    return std::to_string(val);
#else
    std::ostringstream ostr;
    ostr << val;
    std::string str = ostr.str();
    return str;
#endif
}

std::string ToString(long val)
{
#ifdef __CPLUSPLUS_OVER_11
    return std::to_string(val);
#else
    std::ostringstream ostr;
    ostr << val;
    std::string str = ostr.str();
    return str;
#endif
}

std::string ToString(unsigned long val)
{
#ifdef __CPLUSPLUS_OVER_11
    return std::to_string(val);
#else
    std::ostringstream ostr;
    ostr << val;
    std::string str = ostr.str();
    return str;
#endif
}

std::string ToString(long long val)
{
#ifdef __CPLUSPLUS_OVER_11
    return std::to_string(val);
#else
    std::ostringstream ostr;
    ostr << val;
    std::string str = ostr.str();
    return str;
#endif
}

std::string ToString(unsigned long long val)
{
#ifdef __CPLUSPLUS_OVER_11
    return std::to_string(val);
#else
    std::ostringstream ostr;
    ostr << val;
    std::string str = ostr.str();
    return str;
#endif
}

std::string ToString(float val)
{
#ifdef __CPLUSPLUS_OVER_11
    return std::to_string(val);
#else
    std::ostringstream ostr;
    ostr << val;
    std::string str = ostr.str();
    return str;
#endif
}

std::string ToString(double val)
{
#ifdef __CPLUSPLUS_OVER_11
    return std::to_string(val);
#else
    std::ostringstream ostr;
    ostr << val;
    std::string str = ostr.str();
    return str;
#endif
}

std::string ToString(long double val)
{
#ifdef __CPLUSPLUS_OVER_11
    return std::to_string(val);
#else
    std::ostringstream ostr;
    ostr << val;
    std::string str = ostr.str();
    return str;
#endif
}

} // namespace utilities

} // namespace vk
