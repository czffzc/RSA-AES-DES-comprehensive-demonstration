#include <iostream>
#include <conio.h>
#include <iomanip>
#include "common_tools.h"
using namespace std;
/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int menu()
{
	const char* menu[] = {
		"1.�����ļ���",
		"2.����DES��ʼ��Կ",
		"3.ѡ���������p��q�ĳ���",
		"4.���ܡ�����",
		"0.�˳�",
		NULL	
	};
	char sel;
	bool loop = true;

	while (loop) {
		cout << "     RSA��AES��DES�ۺ���ʾ" << endl;
		cout << "================================" << endl;
		cout << "     1.�����ļ���" << endl;
		cout << "     2.����DES��ʼ��Կ" << endl;
		cout << "     3.ѡ���������p��q�ĳ���" << endl;
		cout << "     4.���ܡ�����" << endl;
		cout << "     0.�˳�" << endl;
		cout << "================================" << endl<<endl;
		cout << "����Ϊ�ļ�˵����[ ]��ͨ�������ļ������޸ģ������ļ��������޸ģ�" << endl;
		cout << "[m.txt] �á�PKCS7Padding���㷨���õ� m_padding.txt" << endl;
		cout << "m_padding.txt ��k���ܵõ� c2.txt" << endl;
		cout << "c2.txt ��k���ܵõ� m_padding_2.txt" << endl;
		cout << "m_padding_2.txt �á�de_PKCS7Padding���㷨ȥ���õ� [result.txt]" << endl<<endl;
		cout << "��ѡ��(ֱ��ѡ4����Ĭ�ϲ�����ʾ)[0..4]��";
		sel = _getche();
		cout << endl;
		if (sel == '0' || !(sel == '1' || sel == '2' || sel=='3'||sel=='4')) {
			loop = false;
		}
		else {
			cout << endl << "��ʼ��ʾ\"" << game6789_get_menuitem(menu, sel) << "\"" << endl << endl;
			return sel-'0';
		}
		if (loop)
			wait_for_end();
	}
	return 0;
}