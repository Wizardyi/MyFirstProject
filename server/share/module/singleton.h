#pragma once

template<typename T>
class Singleton
{
    public:
        static T& Instance()
        {
            if (nullptr == sInstance) {
                sInstance = new T();
            }

            return *sInstance;
        }

        static void Release()
        {
            if (sInstance != nullptr)
            {
                delete sInstance;
                sInstance = nullptr;
            }
        }

    protected:
        Singleton() { }

    private:
        static T* sInstance;
};

template<typename T> T* Singleton<T>::sInstance = nullptr;
