
/******************************************************************
********************  ������� ��������� ***************************
*******************************************************************

    X� X�
  ^
  | (0,0) (������ ���������� "Picture")
  +---------------------------------------------------> X�
  |                                                 ^
  |        (���������� ���� "Client")               |
  |   (0,0)                      X�                 |
  |     ----------------------->                    |
  |     |               |                           |
  |     |        x..... x  ���� ������������        |
  |     |        ....A. |                           |
  |     |        ...+.. |                           |
  |     |        ...... |                         ��������
  |     ---------x------x                    ������ ("Region")
  |     |          ^                                |
  |     |          |                                |
  |     |         ������� �������� ������           |
  |     V                  ("Draw")                 |
  |       Y�                                        |
  |                                                 V
  +----------------------------------------------------> Y� Y�
  |
  |  0,0 (������ ������ "Map" � ���������
  |       � "��������")
  |
  V        ���������� �.A � ������ X�,Y�; � ����������� X�,Y�
    Y�

******************************************************************/

#ifndef MAPWEB_H
#define MAPWEB_H

#ifndef MAPVERSN_H
 #include "mapversn.h"
#endif

#ifndef MAPTYPE_H
  #include "maptype.h"   // �������� �������� ���������� MAPAPI
#endif

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// +++++ �������� ������� ������� � ����������� ����� ++++++
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern "C"
{
#ifdef WIN32API

 // ��������� ������ ������

_MAPIMP long int _MAPAPI mapGetMapWebVersion();

 // ������� �������� ����������� ����� � ���� BMP
 // � ������� �������� � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // ��������� �������� �����, �������� ���������� rect.
 // ������ ��������� �� ����� ���� ������ ���������� ������ �� �������
 // ����������� ���������
 //  hmap      - ������������� �������� ������,
 //  rect      - ���������� ��������� ����� (Draw)
 //              � ����������� (Picture),
 //  bmpname   - ��� ������������ ����� BMP, 32 ���� �� ������,
 //  bits      - ����� ��� �� ������ (32 ��� 8)
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapToBMP(HMAP hmap, RECT * rect,
                                          const char * bmpname, long int bits);


 // ������� �������� ����������� ����� � ���� BMP
 // � ������� �������� � ������� �������� �
 // �������� �� ����� �������, �������������� �������� �������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // hMap    - ������������� �������� ������
 // rect    - ���������� ��������� ����� (Draw) � ����������� (Picture)
 // select  - ������� ������ ��������, ���� ����� 0, �� �����������
 //           ������� ����������� ������\��������� (��. mapTotalPaintSelect95).
 // color   - ����, ������� ����� ���������� ������� �� �����
 // bmpname - ��� ������������ ����� BMP, 32 ���� �� ������,
 // bits    - ����� ��� �� ������ (32 ��� 8)
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapAndSelectToBMP(HMAP hMap, RECT * rect,
                                                   HSELECT select, COLORREF color,
                                                   const char * bmpname, long int bits);

 // ���������� ������������ ������ � ���� BMP
 // � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // hmap    - ������������� �������� ������,
 // rect    - ���������� ��������� ����� (Draw),
 // info    - ������������� ������� ����� � ������
 // bmpname - ��� ������������ ����� BMP, 32 ���� �� ������,
 // bits    - ����� ��� �� ������ (32 ��� 8)
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintObjectToBMP(HMAP hmap, RECT * rect,
                                             HOBJ info,
                                             const char * bmpname, long int bits);

 // ������� �������� ����������� ����� � ����������� ������� � ���� BMP
 // � ������� �������� � ������� ��������
 // ������ ������� ����������� ������ ��� ��������� Windows !
 // ��������� �������� �����, �������� ���������� rect.
 // ������ ��������� �� ����� ���� ������ ���������� ������ �� �������
 // ����������� ���������
 //  hmap      - ������������� �������� ������,
 //  rect      - ���������� ��������� ����� (Draw)
 //              � ����������� (Picture),
 //  info      - ������������� ������� ����� � ������,
 //  color     - ����, ������� ����� ���������� ������� �� �����
 //  bmpname   - ��� ������������ ����� BMP, 32 ���� �� ������,
 //  bits      - ����� ��� �� ������ (32 ��� 8)
 // ��� ������ � ���������� ���������� ����

_MAPIMP long int _MAPAPI mapPaintMapAndObjectToBMP(HMAP hmap, RECT * rect,
                                                   HOBJ info, COLORREF color,
                                                   const char * bmpname, long int bits);

#endif  // WIN32API

}  // extern "C"

#endif  // MAPWEB_H