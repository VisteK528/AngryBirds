#ifndef ANGRYBIRDS_EXCEPTIONS_HPP
#define ANGRYBIRDS_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace exceptions{
    class BaseException;
    class TexturesLoadingError;
}



class exceptions::BaseException: public std::exception
{
private:
    std::string msg;
public:
    BaseException(const std::string &message): msg(message){};
    const char* what() const noexcept {return msg.c_str();}
};

class exceptions::TexturesLoadingError: public exceptions::BaseException{
public:
    TexturesLoadingError(const std::string &message): BaseException(message){};
};



#endif //ANGRYBIRDS_EXCEPTIONS_HPP
