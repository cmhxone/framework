#ifndef _FRAMEWORK_SINGLETON_HEADER_
#define _FRAMEWORK_SINGLETON_HEADER_

template <typename T>
class Singleton
{
protected:
    Singleton()
    {
    }
    virtual ~Singleton()
    {
    }

public:
    static T *GetInstance()
    {
        if (m_pInstance == NULL)
            m_pInstance = new T;
        return m_pInstance;
    };

    static void DestroyInstance()
    {
        if (m_pInstance)
        {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    };

private:
    static T *m_pInstance;
};

template <typename T> T * Singleton<T>::m_pInstance = 0;

#endif