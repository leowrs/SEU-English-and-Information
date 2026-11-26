-- Original Author: GitHub @leowrs (https://github.com/leowrs)
-- 1. 查询选修课程C2的学生学号和成绩，并按成绩降序排列，成绩相同时按学号升序排列。
SELECT 学号, 成绩
FROM 学生选课表
WHERE 课程名 = 'C2'
ORDER BY 成绩 DESC, 学号 ASC;

-- 2. 查询数学系或计算机系，且学号尾数为5或6的学生信息。
SELECT *
FROM 学生表
WHERE (系别 = '数学系' OR 系别 = '计算机系')
  AND (学号 LIKE '%5' OR 学号 LIKE '%6');

