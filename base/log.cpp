//
// Created by jm on 4/28/24.
//

#include "log.h"
#include "ngx_conf.h"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

const char* LogLevelName[log::NUM_LOG_LEVELS] = {
        "DEBUG",
        "INFO",
        "WARN",
        "ERROR",
};

void log::ngx_log_init() {
    // 获取当前时间
    // 确定文件名
    // 打开文件流
    try {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm* now_tm = std::localtime(&now_c);

        std::ostringstream oss;
        oss << std::put_time(now_tm, "%Y-%m-%d");
        std::string m_time = oss.str();
        oss.clear();
        oss.str("");
        oss << ngx_conf::getInstance().getString("Log");
        m_name = oss.str();
        if(m_name.empty()) {
            m_name = g_os_argv[0];
            m_name += ".log";
        }

        m_fStream.open( m_time + "_" + m_name, std::ios::app);
        if(!m_fStream.is_open()) {
            throw std::runtime_error("Fail to open log file.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Log initialization failed: " << e.what() << std::endl;
    }
}
