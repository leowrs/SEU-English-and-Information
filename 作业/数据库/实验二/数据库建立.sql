-- Original Author: GitHub @leowrs (https://github.com/leowrs)
CREATE DATABASE Experiment2DB;
GO
USE Experiment2DB;
GO
-- 创建学生表
CREATE TABLE 学生表 (
    学号 CHAR(8) PRIMARY KEY,  -- 主键：学号
    姓名 NVARCHAR(50) NOT NULL,  -- 姓名
    性别 CHAR(10) NOT NULL,  -- 性别
    年龄 INT CHECK (年龄 > 0 AND 年龄 < 100),  -- 年龄（带检查约束）
    系别 NVARCHAR(50) NOT NULL  -- 系别
);

-- 创建学生选课表
CREATE TABLE 学生选课表 (
    学号 CHAR(8),  -- 外键：学生表的学号
    课程名 CHAR(10) NOT NULL,  -- 课程名
    成绩 INT CHECK (成绩 >= 0 AND 成绩 <= 100),  -- 成绩（带检查约束）
    PRIMARY KEY (学号, 课程名),  -- 联合主键
    FOREIGN KEY (学号) REFERENCES 学生表 (学号)  -- 外键约束
);
