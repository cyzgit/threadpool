#ifndef noncopyable_h
#define noncopyable_h

class NonCopyAble {
public:
    NonCopyAble(const NonCopyAble&) = delete;
    void operator = (const NonCopyAble&) = delete;
protected:
    NonCopyAble() = default;
    ~NonCopyAble() = default;
    
};

#endif /* noncopyable_h */
