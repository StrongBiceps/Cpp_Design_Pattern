class Singleton {
private:
    // 1. 생성자를 private으로 선언하여 외부에서 직접 인스턴스를 생성하지 못하도록 한다.
    Singleton() {}

    // 2. 복사 생성자와 대입 연산자를 삭제하여 복사 방지
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;

public:
    // 3. 유일한 인스턴스에 대한 전역 접근점을 제공한다. - Lazy Initialization
    static Singleton& getInstance() {
        static Singleton instance; // 실제로 유일한 인스턴트가 저장되는 곳
        return instance;
    }

    // 추가적으로, 이 클래스의 메서드들을 정의할 수 있다.
};