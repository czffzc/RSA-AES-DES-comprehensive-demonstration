#include <iostream>
#include <conio.h>
#include <iomanip>
#include "common_tools.h"
using namespace std;
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int menu()
{
	const char* menu[] = {
		"1.读入文件名",
		"2.读入DES初始密钥",
		"3.选择随机素数p、q的长度",
		"4.加密、解密",
		"0.退出",
		NULL	
	};
	char sel;
	bool loop = true;

	while (loop) {
		cout << "     RSA、AES、DES综合演示" << endl;
		cout << "================================" << endl;
		cout << "     1.读入文件名" << endl;
		cout << "     2.读入DES初始密钥" << endl;
		cout << "     3.选择随机素数p、q的长度" << endl;
		cout << "     4.加密、解密" << endl;
		cout << "     0.退出" << endl;
		cout << "================================" << endl<<endl;
		cout << "以下为文件说明，[ ]可通过读入文件名来修改，其余文件名不可修改：" << endl;
		cout << "[m.txt] 用“PKCS7Padding”算法填充得到 m_padding.txt" << endl;
		cout << "m_padding.txt 用k加密得到 c2.txt" << endl;
		cout << "c2.txt 用k解密得到 m_padding_2.txt" << endl;
		cout << "m_padding_2.txt 用“de_PKCS7Padding”算法去填充得到 [result.txt]" << endl<<endl;
		cout << "请选择(直接选4即用默认参数演示)[0..4]：";
		sel = _getche();
		cout << endl;
		if (sel == '0' || !(sel == '1' || sel == '2' || sel=='3'||sel=='4')) {
			loop = false;
		}
		else {
			cout << endl << "开始演示\"" << game6789_get_menuitem(menu, sel) << "\"" << endl << endl;
			return sel-'0';
		}
		if (loop)
			wait_for_end();
	}
	return 0;
}