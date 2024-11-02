#include <iostream>

class PIDController {
private:
    double Kp;             // 比例增益
    double Ki;             // 积分增益
    double Kd;             // 微分增益
    double setpoint;       // 设定值
    double previous_error; // 上一次误差
    double integral;       // 积分项

public:
    // 构造函数
    PIDController(double Kp, double Ki, double Kd, double setpoint) {
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
        this->setpoint = setpoint;
        this->previous_error = 0;
        this->integral = 0;
    }

    // 更新PID控制器状态并计算输出
    double update(double measurement, double dt) {
        double error = setpoint - measurement;
        integral += error * dt;
        double derivative = (error - previous_error) / dt;
        double output = Kp * error + Ki * integral + Kd * derivative;
        std::cout << "p:" <<error << " i:" << integral << " d:" << derivative << std::endl;
        previous_error = error;
        return output;
    }
};

// 模拟获取测量值，加入噪声模拟
double get_measurement(double input) {
    // 模拟真实测量值，加入噪声
    double noise = (rand() % 10 + 1) * 0.1; // 噪声范围在0到1之间
    double measurement = input + noise * ((rand() % 2) ? -1 : 1);
    return measurement;
}

// 模拟获取时间间隔，加入更真实的随机性
double get_dt() {
    double t = (rand() % 5 + 1)/10.0; // 时间间隔在1到5之间
    std::cout << "测量时间间隔：" << t << " 秒" << std::endl;
    return t;
}

int main() {
    // 设置随机种子
    srand(static_cast<unsigned int>(time(nullptr)));
    // 创建PID控制器实例
    PIDController pid(0.5, 0.01, 0.2, 10.0);
    double input = 0;

    // 模拟控制循环
    for (int i = 0; i < 100; ++i) {
        // 获取测量值和时间间隔
        double measurement = get_measurement(input);
        double dt = get_dt();

        // 更新PID控制器并获取控制输出
        double control_output = pid.update(measurement, dt);

        // 应用控制输出（这里只是输出到控制台）
        std::cout << "测量值: " << measurement << ", 控制输出: " << control_output << std::endl;

        input = measurement; // 更新输入为当前测量值
    }

    return 0;
}
