手动注册

 

手动注册实质上是存储管理员通过手动方式告诉存储系统，HBA卡的WWN属于那一台主机，然后手动在存储上输入主机名称、IP地址和操作系统信息。该输入信息可以是主机真实信息，也可以和主机真实信息无关，输入信息是否正确不影响主机使用。

 



优点：操作简单、无需安装软件

 

缺点：1、由于不同主机的128位WWN比较相似，容易人为注册错误；

2、存储系统上无法查看到主机对分配空间的具体操作，如：LUN格式化后在主机端的盘符信息。

 



操作步骤如下：

 

1、登录到Unisphere，选择需要操作的存储矩阵；

 

2、选择Hosts > Initiators；

 

3、在Initiators 栏，选择需要注册的HBA卡；

 

注：在主机端没有安装Host Agent 和Unisphere Server Utility ，并且网线连接和zoning配置正确的情况下，在Initiators栏HBA卡的Logged状态应为“Yes”，Registered状态应为“No”。

 

4、点击 Register 打开Create Initiator Record 对话框； 

 

5、确认WWN/IQN 和SP Port ID 是否正确；

 

6、在Initiator 类型， 在列表中选择initiator类型或者键入一个支持的initiator；（更多相关信息参考EMC知识文库99467）

 

7、在Failover模型， 选择正确的failover值；（更多相关信息参考EMC知识文库99467）

 

8、在Host Agent Information栏，根据情况进行如下操作：

 

如果HBA卡属于一个存在的主机，选择Existing Host，点击Browse Host，然后在列表中选择这块HBA卡属于的主机。

如果HBA卡属于新主机，选择New Host，输入主机名称和IP地址，选择Selected Host。 

 

9、启动或者关闭ArrayCommPath；（更多相关信息参考EMC知识文库99467）

 

10、在Unit Serial Number栏，选择 Array 或 LUN；（更多相关信息参考EMC知识文库99467）

 

11、点击OK注册HBA卡，然后返回到Initiators 栏中检查对应的HBA卡Registered 状态是否变为Yes。

