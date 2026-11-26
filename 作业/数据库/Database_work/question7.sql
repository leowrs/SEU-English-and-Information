-- Original Author: GitHub @leowrs (https://github.com/leowrs)

CREATE VIEW 未购物客户 AS
SELECT * FROM 客户
WHERE 客户编号 NOT IN (SELECT DISTINCT 客户编号 FROM 订单);
GO

DELETE FROM 仓库 WHERE 仓库负责人 IS NULL;

SELECT TOP 100 商品编号, COUNT(订单编号) AS 订购数量
INTO TOP100畅销商品
FROM 订单明细
GROUP BY 商品编号
ORDER BY 订购数量 DESC;
