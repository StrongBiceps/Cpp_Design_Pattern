class Singleton {
private:
    // 1. �����ڸ� private���� �����Ͽ� �ܺο��� ���� �ν��Ͻ��� �������� ���ϵ��� �Ѵ�.
    Singleton() {}

    // 2. ���� �����ڿ� ���� �����ڸ� �����Ͽ� ���� ����
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;

public:
    // 3. ������ �ν��Ͻ��� ���� ���� �������� �����Ѵ�. - Lazy Initialization
    static Singleton& getInstance() {
        static Singleton instance; // ������ ������ �ν���Ʈ�� ����Ǵ� ��
        return instance;
    }

    // �߰�������, �� Ŭ������ �޼������ ������ �� �ִ�.
};