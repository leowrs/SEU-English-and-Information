-- Original Author: GitHub @leowrs (https://github.com/leowrs)
USE master;
GO
CREATE LOGIN ANNA WITH PASSWORD = '1234';
GO

USE 电子商务;
GO
CREATE USER ANNA FOR LOGIN ANNA;
CREATE ROLE MYROLE;
EXEC sp_addrolemember 'MYROLE', 'ANNA';

GRANT SELECT ON 订单 TO MYROLE;
GRANT UPDATE(订单状态) ON 订单 TO MYROLE;
DENY UPDATE(订单状态) ON 订单 TO ANNA; 
GRANT SELECT ON 仓库 TO PUBLIC;         
GO