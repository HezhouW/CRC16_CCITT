#ifndef HEX2BIN_H
#define HEX2BIN_H
#include <QString>
#include <QDebug>
QString hex2bin(const QString &source)
{
    /**
      *@param[in]   source QString,需要转换的十六进制字符串（带空格）
      *@return      QString,转换好的二进制字符串
      *@note        十六进制字符串转换为二进制比特流
    */
    int num,dec1,dec2;
    bool ok;
    QString temp,bin1,bin2,itostr;
    num=source.length();
    for(int i=0;i<=num/3;i++)
    {
        QString c1,c2;
        c1=source.mid(3*i,1);
        c2=source.mid(3*i+1,1);


        if(!c1.isNull()) dec1=c1.toInt(&ok,16);//c="FF",dec=255;
        else return temp;
        if(!c1.isNull()) dec2=c2.toInt(&ok,16);//c="FF",dec=255;
        else return temp;
        switch(dec1)
        {
        case 0:bin1="0000";break;
        case 1:bin1="0001";break;
        case 2:bin1="0010";break;
        case 3:bin1="0011";break;
        case 4:bin1="0100";break;
        case 5:bin1="0101";break;
        case 6:bin1="0110";break;
        case 7:bin1="0111";break;
        default: bin1=itostr.number(dec1,2);
        }
        switch(dec2)
        {
        case 0:bin2="0000";break;
        case 1:bin2="0001";break;
        case 2:bin2="0010";break;
        case 3:bin2="0011";break;
        case 4:bin2="0100";break;
        case 5:bin2="0101";break;
        case 6:bin2="0110";break;
        case 7:bin2="0111";break;
        default: bin2=itostr.number(dec2,2);
        }
        temp.append(bin1);
        temp.append(bin2);
        qDebug()<<c1<<"\t->"<<bin1;
        qDebug()<<c2 <<"\t->"<<bin2;
    }
    return temp;
}
#endif // HEX2BIN_H
