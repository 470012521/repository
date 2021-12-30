
#include <iostream>
#include <mutex>
#include <thread>

int v = 1;
void critical_section(int change_v)
{
    static std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    // ִ�о�������
    v = change_v;
    std::cout << v << std::endl;
    // ���������ͷ�
    lock.unlock();
    // �ڴ��ڼ䣬�κ��˶��������� v �ĳ���Ȩ
    // ��ʼ��һ�龺���������ٴμ���
    lock.lock();
    v += 1;
    std::cout << v << std::endl;
    lock.unlock();
}
int main()
{
    std::thread t1(critical_section, 2), t2(critical_section, 3);
    t1.join();
    t2.join();
    return 0;
}