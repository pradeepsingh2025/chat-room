#include <iostream>
#include <string>
#include <cstring>

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

class Message
{
public:
    Message() : bodyLength_(0) {}
    enum
    {
        header = 4,
        maxBytes = 512
    };

    Message(std::string message)
    {
        bodyLength_ = getNewBodyLength(message.size());
        encodeHeader();
        std::memcpy(data + header, message.c_str(), bodyLength_);
    }

    std::string getData()
    {
        int length = header + bodyLength_;
        std::string result(data, length);
        return result;
    }
    std::string getBody()
    {
        std::string dataStr = getData();
        std::string result = dataStr.substr(header, bodyLength_);
        return result;
    }
    bool decodeHeader()
    {
        char new_header[header + 1] = "";
        strncpy(new_header, data, header);
        new_header[header] = '\0';
        int headerValue = atoi(new_header);
        if (headerValue > maxBytes)
        {
            bodyLength_ = 0;
            return false;
        }
        bodyLength_ = headerValue;
        return true;
    }

    void encodeHeader()
    {
        char new_header[header + 1] = "";
        sprintf(new_header, "%4d", static_cast<int>(bodyLength_));
        // sprintf copies any data to new_header (char arrays, buffer) as arrays of characters
        memcpy(data, new_header, header);
    }
    size_t getBodyLenth()
    {
        return bodyLength_;
    }

    size_t getNewBodyLength(size_t length)
    {
        if (length > maxBytes)
        {
            return maxBytes;
        }
        return length;
    }

private:
    char data[header + maxBytes];
    size_t bodyLength_;
};

#endif // MESSAGE_HPP
