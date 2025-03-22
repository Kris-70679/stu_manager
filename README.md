## 项目概述

这是一个基于 **Qt6** 框架开发的学生信息管理系统。该系统通过图形用户界面（GUI）提供了基本的学生信息管理功能，包括学生信息的增加、删除、修改、查询和展示。系统使用 **MySQL** 数据库来存储学生信息，并通过 **Qt SQL** 模块与数据库进行交互。

### 主要功能

- **添加学生信息**：可以添加新的学生信息（学号、用户名、密码、出生日期、性别、成绩等）。
- **修改学生信息**：可以修改现有学生的信息。
- **删除学生信息**：可以删除某个学生的记录。
- **查询学生信息**：支持模糊查询，通过学号、用户名、性别等信息查询学生。
- **显示学生信息**：将学生信息以表格形式展示，支持自动调整列宽。

## 技术栈

- **开发框架**：Qt6
- **数据库**：MySQL（部署在 Linux 服务器上）
- **编程语言**：C++
- **IDE**：Qt Creator

## 安装与配置

### 1. 安装 Qt6

首先，确保你已经安装了 Qt6 和 Qt Creator。可以从 Qt 官方网站下载并安装：[Qt 官网](https://www.qt.io/).

### 2. 安装 MySQL 并配置 Linux 服务器

确保你已经在 Linux 上安装并配置好 MySQL 数据库。如果没有安装 MySQL，可以通过以下命令安装：

```
sudo apt-get update
sudo apt-get install mysql-server
```

安装完成后，启动 MySQL 服务并确保其正常运行：

```
sudo service mysql start
```

在 MySQL 中创建数据库和表：

```
CREATE DATABASE mydatabase;

USE mydatabase;

CREATE TABLE students (
    student_id INT PRIMARY KEY,
    username VARCHAR(100),
    password VARCHAR(100),
    birth DATE,
    gender VARCHAR(10),
    score FLOAT
);
```

### 3. 配置 Qt 项目

1. 下载并打开项目文件夹。

2. 使用 Qt Creator 打开项目文件。

3. 在 `mainwindow.cpp` 中，确保数据库连接部分的配置正确。由于数据库部署在 Linux 服务器上，需要提供正确的 IP 地址或主机名：

   ```
   cpp复制编辑db.setHostName("192.168.1.100");  // 替换为 Linux 服务器的 IP 地址
   db.setDatabaseName("mydatabase");  // 替换为你的数据库名
   db.setUserName("test1");           // 替换为你的数据库用户名
   db.setPassword("12345678");        // 替换为你的数据库密码
   ```

### 4. 编译与运行

- 打开 Qt Creator，选择该项目，点击 **Run** 按钮。
- 确保数据库连接成功，程序会自动加载学生信息表并显示在界面上。

## 使用方法

1. **登录界面**：启动程序后，首先会显示登录界面。输入正确的用户名和密码后，进入主界面。
2. **查看学生信息**：在主界面上，可以查看学生的学号、用户名、密码、出生日期、性别和成绩。
3. **添加学生**：点击 "添加" 按钮，填写学生信息并提交。
4. **修改学生信息**：选择一名学生并点击 "修改" 按钮，修改学生的基本信息。
5. **删除学生信息**：选择一名学生并点击 "删除" 按钮，确认删除操作后该学生信息将从数据库中删除。
6. **查询学生**：在查询框中输入学号、用户名或其他信息进行模糊查询。

## 界面截图

### 登录界面
![屏幕截图 2025-03-22 194247](https://github.com/user-attachments/assets/1fa1bfaa-e3f2-4483-a81f-68ea5de04acd)





### 学生信息表
![屏幕截图 2025-03-22 194338](https://github.com/user-attachments/assets/c05d0cca-6886-42a9-b728-34db6cdef204)





## 常见问题

### 数据库连接失败

- 确保提供的 **数据库主机 IP 地址** 和 **端口** 正确。
- 在 Linux 上，确保 **MySQL 服务器** 正在运行，且防火墙或网络设置没有阻止连接。
- 如果 MySQL 安装在远程服务器上，确保该服务器允许远程连接。
