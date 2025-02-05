#include <cstddef>
#include <cstring>
#include <iostream>

class mystring {
  private:
    char  *content{};
    size_t length = 0;

  public:
    mystring(const char *c) : length(std::strlen(c)) {
        content = new char[length];
        std::strcpy(content, c);
    }

    size_t size() {
        return length;
    }
    void clear();
};

int main(void) {
    const mystring str("abc");

    std::cout << str.size() << std::endl;
}
