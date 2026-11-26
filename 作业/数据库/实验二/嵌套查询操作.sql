-- Original Author: GitHub @leowrs (https://github.com/leowrs)
-- 1. 查询比所有男生年龄都小的女生姓名。
SELECT 姓名
FROM 学生表
WHERE 性别 = '女' AND 年龄 < ALL (
    SELECT 年龄
    FROM 学生表
    WHERE 性别 = '男'
);
-- 2. 查询没有选修课程C2的学生姓名。
SELECT 姓名
FROM 学生表
WHERE 学号 NOT IN (
    SELECT 学号
    FROM 学生选课表
    WHERE 课程名 = 'C2'
);
