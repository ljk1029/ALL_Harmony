#include <iostream>
#include "message.pb.h" // 包含由protoc生成的头文件



// main函数
int main(int argc, char* argv[]) {
    tutorial::Person person; // 使用protobuf生成的类
    person.set_name("John Doe"); // 设置字段值
    person.set_id(1234);
    person.set_email("jdoe@example.com");

    // 序列化成字符串
    std::string serialized_str;
    if (person.SerializeToString(&serialized_str)) {
        std::cout << "Person serialized successfully!" << std::endl;
    }

    // 反序列化
    tutorial::Person person2;
    if (person2.ParseFromString(serialized_str)) {
        std::cout << "Person deserialized successfully!" << std::endl;
    }
    
    return 0;
}