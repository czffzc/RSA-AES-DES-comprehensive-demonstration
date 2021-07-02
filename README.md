# RSA-AES-DES-comprehensive-demonstration
#####Alice生成RAS密钥：
	1.Alice生成一对RSA公钥(n,b)和私钥(p,q,a)，其中随机素数p，q都为512比特长；或都为1024比特长度；两种长度都需要支持。
	2.Alice把公钥传给Bob。
#####Bob加密文件m并发送给Alice：
	1.输入文件m，m为任意长。CBC模式中，如果m的长度不是分组的倍数时，需要填充，本设计中采用的是PKCS7Padding的填充方式。
	2.生成128比特的随机数k作为临时的会话密钥。
	3.用Alice的公钥加密k得到c_1←k^b  mod n。
	4.用会话密钥k加密文件m得到c_2，其中加密算法为AES，使用CBC模式。
	5.把(c_1,c_2)发给Alice
#####Alice解密恢复文件m：
	1.用Alice的RSA私钥解密c_1得到k。
	2.用k解密c_2得到m。
	3.输出m。
