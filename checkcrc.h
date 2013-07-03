#ifndef CHECKCRC_H
#define CHECKCRC_H
#include <QString>
//这个是正确的！！！

QString Xor_string(QString a,QString b)
{
    /**
     *@param[in] a QString
     *@param[in] b QString
     *@param[out]  QString,字符串a和b异或后的结果
     *@return QString,字符串a和b异或后的结果
     *@note  两个等长的字符串进行异或，输出异或后的结果。
    */
    QString c;
    if(a.mid(0,1)==b.mid(0,1))
        c="0";
    else
        c="1";
    for(int i=1;i<a.size();i++){
        if(a.mid(i,1)==b.mid(i,1))
            c=c+"0";
    else
            c=c+"1";
    }
    return c;
}
QString Fcs( QString bitflow)
{
    /**
     *@param[in] bitflow QString,存储需要被CRC计算的部分
     *@param[out]   QString,由输入的比特流计算得到的FCS串
     *@note     对输入的比特流计算CRC-16，获得FCS串
    */
    //代码具体实现思路：模仿教材对CRC阐释，靠除法获得结果。
    int position;
    QString tmp;

    bitflow=bitflow+"0000000000000000";

    position = 0;
    tmp = bitflow.mid(position,17);
    position = 17;
    if(tmp[0]=='1')
    {
        tmp = Xor_string(tmp,"10001000000100001");//   CRC16-CCITT
    }
    else
    {
        tmp = Xor_string(tmp,"00000000000000000");
    }
    while (position < bitflow.size())
    {
        tmp.remove(0,1);
        tmp += bitflow.mid(position,1);
        if(tmp[0]=='1')
        {
            tmp = Xor_string(tmp,"10001000000100001");//   CRC16-CCITT
        }
        // else
        // {
            // tmp = Xor_string(tmp,"00000000000000000");
        // }
        ++position ;
    }
    return tmp.remove(0,1);
}





#endif // CHECKCRC_H
