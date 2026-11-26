-- Original Author: GitHub @leowrs (https://github.com/leowrs)

SELECT * FROM 商品 WHERE 制造商 LIKE '南京%';

SELECT DISTINCT d.* FROM 订单 d
JOIN 订单明细 dm ON d.订单编号 = dm.订单编号
JOIN 商品 s ON dm.商品编号 = s.商品编号
WHERE d.订单状态 = 0 AND s.类别 = '会员卡';

SELECT 
    AVG(支付金额) AS 平均金额, 
    SUM(支付金额) AS 总金额, 
    COUNT(订单编号) AS 订单总数 
FROM 订单;