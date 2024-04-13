#include <iostream>
#include <string>
#include <curl/curl.h>

std::string readBody(char* body, size_t size) {
    std::string s(body, size);
    return s;
}

size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string httpPost(const std::string& url, const std::string& data) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

void createRepository(const std::string& token, const std::string& repoName) {
    std::string url = "https://api.github.com/user/repos";
    std::string data = "{\"name\":\"" + repoName + "\"}";

    std::string response = httpPost(url, data);
    std::cout << response << std::endl;
}

void uploadFile(const std::string& token, const std::string& repoName, const std::string& filePath) {
    // TODO: Implement file upload functionality
}

int main() {
    std::string token = "your_access_token_here";
    std::string repoName = "my-new-repository";

    createRepository(token, repoName);

    return 0;
}
