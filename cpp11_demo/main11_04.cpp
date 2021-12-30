#include <iostream>
#include <future>
#include <thread>
int main()
{
    // ��һ������ֵΪ 7 �� lambda ���ʽ��װ�� task ��
    // std::packaged_task ��ģ�����ΪҪ��װ����������
    std::packaged_task<int()> task([]()
                                   { return 7; });
    // ��� task ������
    std::future<int> result = task.get_future(); // ��һ���߳���ִ�� task
    std::thread(std::move(task)).detach();
    std::cout << "waiting...";
    result.wait(); // �ڴ��������ϣ���������������
    // ���ִ�н��
    std::cout << "done!" << std::endl
              << "future result is " << result.get() << std::endl;
    return 0;
}