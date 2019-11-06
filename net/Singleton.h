#ifndef TEST_SINGLETON_H
#define TEST_SINGLETON_H

template <class T>
class Singleton
{
protected:
    Singleton() = default;
    ~Singleton() = default;
public:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
public:
    static T* getInstance() {
        static T* instance = new T();
        return instance;
    }
};

#endif //TEST_SINGLETON_H
