## ALL_DOME
### code
- base_code  
模块代码 

- thrid_part_base   
小组件代码 开源库

- thrid_part_dev
驱动代码 开源库


- 树的旋转说明
![image](https://github.com/ljk1029/ALL_Harmony/blob/main/image/img_tree.png)   

- 排序
![image](https://github.com/ljk1029/ALL_Harmony/blob/main/image/img_sort.png)   






## 二、提交类型
## 提交类型
- feat:     新功能（feature）  
- fix:      修补bug  
- refactor: 重构  
- update:   更新  

## 三、C++规范
定义了一些C++的编码规范  

### C++编码规则
- 文件夹名 命名规则  
使用全小写字母。  
多个单词可以使用下划线分隔。  

- 文件名 命名规则  
头文件使用 .h 或 .hpp 后缀，源文件使用 .cpp 后缀。  
使用全小写字母。  
多个单词可以使用下划线分隔。  

- 函数名 命名规则  
小驼峰  

- 变量名 命名规则  
变量类型: 大驼峰  
全局变量: 小写+下划线  
局部变量: 小写+下划线，结尾可加_g  

- 类名、结构体名 命名规则  
类名：   大驼峰，可加Class  
类对象： 小写+下划线  

结构体名：大驼峰, 可加Stu  
结构体对象：小写+下划线，结尾可加_t  


### C++编程规则
- 函数规则 
(1)、  
void fun() {

 }

- 其他命名规则


### 配置文件规则
- json配置规则

- xml配置规则

- yaml配置规则

- idl配置规则

### 生成产物规则
- 生成执行文件规则  
- 生成库文件规则  



## 四、其他说明
### 脚本win/lin字符转换
脚本出现windows字符转化到unix/linux下   
dos2unix build.sh  

### gtest 安装
  1、地址:https://github.com/google/googletest.git  

  2、编译 cmake .. / make  

  3、依赖  
  拷贝生成静态库  
  sudo cp *.a /usr/local/lib  
  拷贝头文件  
  sudo cp -r include/gtest /usr/local/include  
