#include <QCoreApplication>
#include <iostream>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "crc16.h"
#include "checkcrc.h"
#include "hex2bin.h"
#include <QDebug>
#include <QByteArray>
#include <QChar>

using namespace std;
/*
 *本文件是用来校验HDLC中CRC校验实现的。
*/
void reverse16(QString &data);//把前16个比特取反
bool CRC32_info(QString data, QString crc);
void Bytemirror(QString &str);
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("one_HDLC.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        cout<<"文件没打开"<<endl;
        exit(1);
    }
    QTextStream datain(&file);
    QString instring;

//    instring = "0111111110111111110000000010000010100000";
//    QString hexchar = "01 00 08 07 06 05 04 03 02 01";
//    QString hexchar = "01 02 03 04 05";
//    instring = hex2bin(hexchar);
//    qDebug()<<instring;
//    Bytemirror(instring);
//    qDebug()<<instring;
//    reverse16(instring);
//    qDebug()<<instring;


    while(!datain.atEnd())
    {
        instring = datain.readLine();
        qDebug()<<instring;
    }
    instring.simplified();

    Bytemirror(instring);

    qDebug()<<instring;
    QString crc= instring.right(16);
    instring.chop(16);
    reverse16(instring);
    cout<<"instring size:"<<instring.size()<<endl;
     qDebug()<<Fcs(instring)<<endl;//这个是正确的！！！

    qDebug()<<crc<<"CRC Byte"<<endl;
//    qDebug()<< CRC32_info(instring,crc);

    return a.exec();
}


bool CRC32_info(QString data, QString crc)
{
    unsigned int count = data.length()/8;
    unsigned char*thisdata=new unsigned char[count];
    for(int i=0;i<count;i++)
    {
        unsigned char temp= 0;
        for(int j=0;j<8;j++)
        {
            if(data.mid(i*8+j,1)=="1")
                temp=(temp<<1)+1;
            else
                temp=temp<<1;
        }
        thisdata[i]=temp;
    }

    unsigned int crc_2=0;
    for(int i=0;i<16;i++)
    {
        //unsigned char temp= 0;

            if(crc.mid(i,1)=="1")
                crc_2=(crc_2<<1)+1;
            else
                crc_2=crc_2<<1;
    }
    unsigned int b= crc_cal_by_byte(thisdata,count);//这三个是正确的！！！但count只能在255个以内
    unsigned int c= crc_cal_by_bit( thisdata,count);
    unsigned int d= crc_cal_by_halfbyte( thisdata,count);
    if(crc_2==b)
        return true;
    else
        return false;
}

void reverse16(QString &data)
{
    if(data.size()<16)
    {
        qDebug()<<"data size less than 16";
        return;
    }
    for(int i=0;i<16;++i)
    {
        if(data[i] == '0') data[i]='1';
        else data[i]='0';
    }
}

void Bytemirror(QString &str)
{
    if(str.length()%8!=0)
    {
        while(str.length()%8!=0)
        {
            str.append("0");
        }
    }

    QChar *t;
    t = str.data();
    for(int i=0;i<str.length()/8;i++)
    {
        for(int j=0;j<4;j++)
        {
          swap(*(8*i+t+j),*(8*i+t+7-j));
        }
//        out<<"afte:"<<temp<<endl;
    }

}
