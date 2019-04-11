Centos6 下使用c++ 调用 python3 包含numpy 例子

1,下载 Anaconda3-2018.12-Linux-x86_64.sh 安装

2，g++ -I/usr/local/anaconda3/include main.cpp -o t1 -L/usr/local/anaconda3/lib -lpython3.7m
