#include "json.hpp"
using json = nlohmann::json;
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// json序列化示例1
void func1()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";

    cout << js << endl;

    // 网络字符串发送方式
    string sendBuf = js.dump();
    cout << sendBuf.c_str() << endl;
}

// json序列化示例2
void func2()
{
    json js2;
    // 数组
    js2["id"] = {1, 2, 3, 4, 5};
    // 添加key-value值
    js2["name"] = "zhang san";
    // 添加对象
    js2["msg"]["zhang san"] = "hello world";
    js2["msg"]["li si"] = "hello china";
    // 上面等同于下面一次性添加的对象
    //  js2["msg"] = {{"zhang san", "hello world"}, {"li si", "hello china"}};
    cout << js2 << endl;
}

// json序列化示例3 --使用容器
void func3()
{
    json js3;
    // 序列化容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(5);
    vec.push_back(2);

    js3["list"] = vec;
    // cout << js3 << endl;

    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "泰山"});
    m.insert({3, "嵩山"});
    m.insert({4, "衡山"});

    js3["path"] = m;
    // cout << js3 << endl;

    string sendBuf = js3.dump(); // json数据对象==》序列化 json字符串
    cout << sendBuf << endl;
}

// 反序列化
// json序列化示例1
string func4()
{
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing now?";

    cout << js << endl;

    // 网络字符串发送方式
    string sendBuf = js.dump();
    cout << sendBuf.c_str() << endl;

    return sendBuf;
}

// json序列化示例2
string func5()
{
    json js2;
    // 数组
    js2["id"] = {1, 2, 3, 4, 5};
    // 添加key-value值
    js2["name"] = "zhang san";
    // 添加对象
    js2["msg"]["zhang san"] = "hello world";
    js2["msg"]["li si"] = "hello china";
    // 上面等同于下面一次性添加的对象
    js2["msg"] = {{"zhang san", "hello world"}, {"li si", "hello china"}};
    // cout << js2 << endl;
    return js2.dump();
}

// json序列化示例3 --使用容器
string func6()
{
    json js3;
    // 序列化容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(5);
    vec.push_back(2);

    js3["list"] = vec;
    // cout << js3 << endl;

    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "泰山"});
    m.insert({3, "嵩山"});
    m.insert({4, "衡山"});

    js3["path"] = m;
    // cout << js3 << endl;

    string sendBuf = js3.dump(); // json数据对象==》序列化 json字符串
    // cout << sendBuf << endl;
    return sendBuf;
}

int main()
{
    // func1();
    // func2();
    // 数据的反序列化，json字符串==》反序列化数据对象（看作容器，方便访问）
    string recvBuf = func6();
    json jsBuf = json::parse(recvBuf);
    // func4
    //  cout << jsBuf["msg_type"] << endl;
    //  cout << jsBuf["from"] << endl;
    //  cout << jsBuf["to"] << endl;
    //  cout << jsBuf["msg"] << endl;
    // func5
    //  cout << jsBuf["id"] << endl;
    //  auto arr = jsBuf["id"];
    //  cout << arr[2] << endl;
    //  auto msgjs = jsBuf["msg"];
    //  cout << msgjs["zhang san"] << endl;
    //  cout << msgjs["li si"] << endl;
    // func6
    vector<int> vec = jsBuf["list"]; // js对象里面的数组类型，直接放入vector中
    for (int &v : vec)
    {
        cout << v << " ";
    }
    cout << endl;

    map<int, string> m = jsBuf["path"];
    for (auto &p : m)
    {
        cout << p.first << " " << p.second << " ";
    }
    cout << endl;

    return 0;
}
