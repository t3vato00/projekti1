#include "product.h"

product::product()
{
}
bool product::check_barcode()
{
	return product::check_barcode(code);
}

bool product::check_barcode(QString barcode)
{
    if(barcode.length() != 12)
    {
        return false;
    }else
    {
	char a[13];
    QByteArray code_array;
    code_array = barcode.toLatin1();
    strncpy(a,code_array.data(),13);
    QString HexNum, checking;
    char temp[13];
    int check_digit;
    for(int i=0;i<=12;i++)
    {
        sprintf(temp,"%x",a[i]);
        HexNum = temp;
        checking = checking + HexNum.right(1);
    }
    int sum_odd=(a[0] - '0')+(a[2] -'0')+(a[4]-'0')+(a[6]-'0')+(a[8]-'0')+(a[10]-'0');
    int sum_even=(a[1]-'0')+(a[3]-'0')+(a[5]-'0')+(a[7]-'0')+(a[9]-'0');
    sum_odd = sum_odd * 3;
    int sum = sum_odd + sum_even;
    int last_digit = sum%10;
    check_digit = 10-last_digit;
    if(check_digit == (a[11]-'0'))
    {
        return true;
    }else
    {
        return false;
    }
    }

}
