-- Original Author: GitHub @leowrs (https://github.com/leowrs)
CREATE DATABASE 电子商务;
GO
USE 电子商务;
GO

CREATE TABLE 仓库 (
    仓库编号 INT IDENTITY(1000,1) PRIMARY KEY,
    仓库地址 NVARCHAR(200),
    仓库负责人 NVARCHAR(50)
);

CREATE TABLE 客户 (
    客户编号 INT IDENTITY(1000,1) PRIMARY KEY,
    姓名 NVARCHAR(50) NOT NULL,
    联系电话 VARCHAR(20) NOT NULL,
    地址 NVARCHAR(200) NOT NULL
);

CREATE TABLE 商品 (
    商品编号 INT IDENTITY(1000,1) PRIMARY KEY,
    名称 NVARCHAR(100),
    类别 NVARCHAR(50),
    制造商 NVARCHAR(100),
    仓库编号 INT FOREIGN KEY REFERENCES 仓库(仓库编号)
);

CREATE TABLE 订单 (
    订单编号 INT IDENTITY(1000,1) PRIMARY KEY,
    产生时间 DATETIME DEFAULT GETDATE(),
    订单状态 INT DEFAULT 0 CHECK (订单状态 IN (0, 1, 2)),
    支付金额 DECIMAL(18, 2),
    客户编号 INT FOREIGN KEY REFERENCES 客户(客户编号)
);

CREATE TABLE 订单明细 (
    订单编号 INT FOREIGN KEY REFERENCES 订单(订单编号),
    商品编号 INT FOREIGN KEY REFERENCES 商品(商品编号),
    PRIMARY KEY (订单编号, 商品编号)
);
GO