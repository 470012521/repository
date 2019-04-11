//c_call_python.cpp
#include<python3.7m/Python.h>
using namespace std;


//把const char *c转 wchar_t * ，作为Py_SetPythonHome()参数匹配
 wchar_t *GetWC(const char *c)
{
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);

    return wc;
}

int main()
{
    //设定参数值
    int a = 0;
    int b = 6;
    //初始化(下面的方法可以在c:\APP\Anaconda3\include\pylifecycle.h中找到)
    //Py_SetProgramName(0);
    //很关键的一步，去掉导入numpy报错
    Py_SetPythonHome(GetWC("/usr/local/anaconda3"));
    Py_Initialize();

    //测试python3的打印语句
    //PyRun_SimpleString("print('Hello Python!')\n");
    //执行import语句，把当前路径加入路径中，为了找到math_test.py
    PyRun_SimpleString("import os,sys");

    PyRun_SimpleString("sys.path.append('./')");
    //测试打印当前路径
    //PyRun_SimpleString("print(os.getcwd())");

    PyObject *pModule;

    PyObject *pFunction;

    PyObject *pArgs;

    PyObject *pRetValue;
    //import mathdemo
    pModule = PyImport_ImportModule("mathdemo");

    if (!pModule) {

        printf("import python failed!!\n");

        return -1;

    }
    //对应math_test.py中的def add_func(a,b)函数
   // pFunction = PyObject_GetAttrString(pModule, "add_func");

    pFunction = PyObject_GetAttrString(pModule, "getDoubleSharkFinPrice");
    if (!pFunction) {

        printf("get python function failed!!!\n");

        return -1;

    }
    //新建python中的tuple对象
    pArgs = PyTuple_New(17);

    PyTuple_SetItem(pArgs, 0, Py_BuildValue("f", 1.0));
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("f", 0.0317));
    PyTuple_SetItem(pArgs, 2, Py_BuildValue("f", 0.2881));
    PyTuple_SetItem(pArgs, 3, Py_BuildValue("i", 100));
    PyTuple_SetItem(pArgs, 4, Py_BuildValue("f", (91/365.0)));
    PyTuple_SetItem(pArgs, 5, Py_BuildValue("f", (91/365.0)));
    PyTuple_SetItem(pArgs, 6, Py_BuildValue("f", 0.04));
    PyTuple_SetItem(pArgs, 7, Py_BuildValue("f", 0.075));
    PyTuple_SetItem(pArgs, 8, Py_BuildValue("f", 0.02));
    PyTuple_SetItem(pArgs, 9, Py_BuildValue("f", 0.03));
    PyTuple_SetItem(pArgs, 10, Py_BuildValue("f", 0.90));
    PyTuple_SetItem(pArgs, 11, Py_BuildValue("f", 1.12));
    PyTuple_SetItem(pArgs, 12, Py_BuildValue("f", 0.98));
    PyTuple_SetItem(pArgs, 13, Py_BuildValue("f", 1.02));
    PyTuple_SetItem(pArgs, 14, Py_BuildValue("s", "000300.SH"));
    PyTuple_SetItem(pArgs, 15, Py_BuildValue("s", "2019-03-25"));
    PyTuple_SetItem(pArgs, 16, Py_BuildValue("s", "2019-06-23"));

    //调用函数
    pRetValue = PyObject_CallObject(pFunction, pArgs);
    //python3中只有long，PyLong_AsLong（python2中是PyInt_AsLong）
    //printf("%d + %d = %ld\n", a, b, PyLong_AsLong(pRetValue));

    //printf(" aaa %ld\n",  PyLong_AsLong(pRetValue));
    char *chResult=NULL;
    PyArg_Parse(pRetValue,"s",&chResult);

    printf("计算结果: %s\n",  chResult);

    Py_DECREF(pModule);


    Py_DECREF(pFunction);

    Py_DECREF(pArgs);

    Py_DECREF(pRetValue);

    if (!pModule) {

        printf("import python failed!!\n");

        return -1;

    }
    //很关键的一步，如果是多次导入PyImport_ImportModule模块
    //只有最后一步才调用Py_Finalize()，此时python全局变量一直保存着
    Py_Finalize();
    //方便查看
//    while (1);

    return 0;
}
