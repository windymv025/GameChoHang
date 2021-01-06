#include "Graphic.h"
#include <ctime>

//Tọa độ xuất phát của khung hình
#define X0 0
#define Y0 0
#define TOC_DO_DI_CHUYEN 1

#define XMAX 90 //Chieu rộng tối đa của khung hình tính bằng tọa độ
#define YMAX 20 // Chiều dài tối đa của khung hình tính bằng tọa độ

//Kích thước của tường
#define TUONG_HEIGHT 4
#define TUONG_WEIGHT 30

//Kích thước của kho
#define KHO_HEIGHT 5
#define KHO_WEIGHT 5
#define SUC_CHUA_HANG_KHO 200

//Kích thước của xe
#define XE_HEIGHT 2
#define XE_WEIGHT 7
#define SUC_CHUA_HANG_XE 70

//Kích thước của thang
#define THANG_HEIGHT 2
#define THANG_WEIGHT 15
#define SUC_CHUA_HANG_THANG 50
#define TOC_DO_THANG_DI_QUA 1

static int chatHang = 3;

static int HangKho1 = 400;
static int HangKho2 = SUC_CHUA_HANG_KHO;
static int HangKho3 = 0;
static int HangKho4 = 0;

int xe3Nghi = 3;
int xe3ChuaBoHang = 0;
int randomXe3 = rand() % 2;

static int Random;

void VeKhungTuong()
{
    line(X0, Y0 + KHO_HEIGHT, X0 + TUONG_WEIGHT, Y0 + KHO_HEIGHT);
    line(X0, Y0 + TUONG_HEIGHT + KHO_HEIGHT, X0 + TUONG_WEIGHT, Y0 + TUONG_HEIGHT + KHO_HEIGHT);
    line(TUONG_WEIGHT, Y0 + KHO_HEIGHT, TUONG_WEIGHT, TUONG_HEIGHT + KHO_HEIGHT);

    line(XMAX - TUONG_WEIGHT, Y0 + KHO_HEIGHT, XMAX, Y0 + KHO_HEIGHT);
    line(XMAX - TUONG_WEIGHT, Y0 + TUONG_HEIGHT + KHO_HEIGHT, XMAX, Y0 + TUONG_HEIGHT + KHO_HEIGHT);
    line(XMAX - TUONG_WEIGHT, Y0 + KHO_HEIGHT, XMAX - TUONG_WEIGHT, TUONG_HEIGHT + KHO_HEIGHT);

    line(X0, YMAX, XMAX, YMAX);
    for (int i = 0; i < XMAX; i += 5)
    {
        line(i, YMAX, i + 5, YMAX + 5);
        line(i + 5, YMAX, i, YMAX + 5);
    }
}

// 0 la khong can toi, 1 la co the toi
void VeKhoHang(int left, int top, int status)
{
    if (status == 0)
    {
        setcolor(RED);
    }
    else
    {
        setcolor(WHITE);
    }
    line(left, top, left + KHO_WEIGHT, top + KHO_HEIGHT);
    line(left + KHO_WEIGHT, top, left, top + KHO_HEIGHT);
    rectangle(left, top, left + KHO_WEIGHT, top + KHO_HEIGHT);
}

void VeXe(int left, int top)
{
    rectangle(left, top, left + XE_WEIGHT, top + XE_HEIGHT);
    goToXY(left + 1, top + XE_HEIGHT);
    printf_s("O");
    goToXY(left + XE_WEIGHT - 1, top + XE_HEIGHT);
    printf_s("O");
}

// status = 1 co hang, = 0 khong co hang
void VeThang(int left, int top, int status)
{
    for (int i = 0; i < THANG_HEIGHT; i++)
    {
        for (int j = 0; j < THANG_WEIGHT; j++)
        {
            goToXY(left + j, top + i);

            if (i == THANG_HEIGHT - 1)
            {
                printf_s("_");
            }
            else
            {
                printf_s("9");
            }
        }
        goToXY(left, top + i);
        printf_s("|");
        goToXY(left + THANG_WEIGHT - 1, top + i);
        printf_s("|");
    }
    

    if (status == 1)
    {
        goToXY(left + THANG_WEIGHT / 2 - 2, top - 1);
        printf_s("O");
        goToXY(left + THANG_WEIGHT / 2, top - 1);
        printf_s("O");
        goToXY(left + THANG_WEIGHT / 2 + 2, top - 1);
        printf_s("O");
        goToXY(left + THANG_WEIGHT / 2 - 1, top - 2);
        printf_s("o");
        goToXY(left + THANG_WEIGHT / 2 + 1, top - 2);
        printf_s("o");
        goToXY(left + THANG_WEIGHT / 2, top - 3);
        printf_s("0");
    }
    else
    {
        setcolor(BLACK);
        goToXY(left + THANG_WEIGHT / 2 - 2, top - 1);
        printf_s("O");
        goToXY(left + THANG_WEIGHT / 2, top - 1);
        printf_s("O");
        goToXY(left + THANG_WEIGHT / 2 + 2, top - 1);
        printf_s("O");
        goToXY(left + THANG_WEIGHT / 2 - 1, top - 2);
        printf_s("o");
        goToXY(left + THANG_WEIGHT / 2 + 1, top - 2);
        printf_s("o");
        goToXY(left + THANG_WEIGHT / 2, top - 3);
        printf_s("0");
    }
}

// 1 la toi cho thang, -1 la toi kho, 0 dang di chuyen
int kiemTraViTriXe1(int x1)
{
    if (x1 == TUONG_WEIGHT - XE_WEIGHT)
        return 1;
    if (x1 == KHO_WEIGHT + 1)
        return -1;

    return 0;
}

// 1 la toi cho thang, -1 la toi kho, 0 dang di chuyen
int kiemTraViTriXe2(int x2)
{
    if (x2 == XMAX - TUONG_WEIGHT)
        return 1;
    if (x2 == XMAX - KHO_WEIGHT - XE_WEIGHT - 1)
        return -1;

    return 0;
}

// 1 la xuong toi mat dat, -1 la len toi tang hai, 0 dang chuyen dong
int kiemTraViTriThang(int y)
{
    if (y == KHO_HEIGHT)
        return -1;
    if (y == YMAX - THANG_HEIGHT)
        return 1;

    return 0;

}

// 2 la toi cho thang ben phai, 1 la toi kho ben phai, 0 dang di chuyen, -1 la toi kho ben trai, -2 toi thang ben trai
int kiemTraViTriXe3(int x3, int xthang, int yThang)
{
    if (x3 == xthang - XE_WEIGHT - 1 && kiemTraViTriThang(yThang) == 1)
        return 2;
    if (x3 == xthang + THANG_WEIGHT + 1 && kiemTraViTriThang(yThang) == 1)
        return -2;
    if (x3 == XMAX - KHO_WEIGHT - XE_WEIGHT - 1)
        return 1;
    if (x3 == KHO_WEIGHT + 1)
        return -1;

    return 0;
}

void Xe1VaThang(int& huongDiXe1, int& hangXe1, int& xThang, int yThang, int& huongDiThang, int& sttThang, int& hangThang)
{
    if (kiemTraViTriThang(yThang) != -1)
    {
        if (hangXe1 > 0)
            huongDiXe1 = 0;
        else
        {
            huongDiXe1 = -1;
        }
    }
    else
    {
        if (kiemTraViTriThang(yThang) == -1)
        {
            huongDiThang = 0;
            if (xThang > TUONG_WEIGHT + 1 && sttThang == 0)
            {
                xThang -= TOC_DO_THANG_DI_QUA;
            }
            else
            {
                chatHang--;
                if (chatHang < 0)
                {
                    hangXe1 -= SUC_CHUA_HANG_THANG;
                    hangThang = SUC_CHUA_HANG_THANG;
                    sttThang = 1;
                    if (xThang < TUONG_WEIGHT + 8)
                    {
                        xThang += TOC_DO_THANG_DI_QUA;
                    }
                    else
                    {

                        if (hangXe1 <= 0)
                        {
                            hangXe1 = 0;
                            huongDiXe1 = -1;
                        }
                        huongDiThang = 1;

                    }
                    chatHang = 3;
                }
            }

        }
    }
}

void Xe2VaThang(int& huongDiXe2, int& hangXe2, int& xThang, int yThang, int& huongDiThang, int& sttThang, int& hangThang)
{
    if (kiemTraViTriThang(yThang) != -1)
    {
        if (hangXe2 > 0)
            huongDiXe2 = 0;
        else
        {
            huongDiXe2 = -1;
        }
    }
    else
    {
        if (kiemTraViTriThang(yThang) == -1)
        {
            huongDiXe2 = 0;
            huongDiThang = 0;
            if (xThang + THANG_WEIGHT < XMAX - TUONG_WEIGHT - 1 && sttThang == 0)
            {
                xThang += TOC_DO_THANG_DI_QUA;
            }
            else
            {
                chatHang--;
                if (chatHang < 0)
                {
                    hangXe2 -= SUC_CHUA_HANG_THANG;
                    hangThang = SUC_CHUA_HANG_THANG;
                    sttThang = 1;
                    if (xThang > TUONG_WEIGHT + 8)
                    {
                        xThang -= TOC_DO_THANG_DI_QUA;
                    }
                    else
                    {

                        if (hangXe2 <= 0)
                        {
                            hangXe2 = 0;
                            huongDiXe2 = -1;
                        }
                        huongDiThang = 1;

                    }
                    chatHang = 3;
                }
            }

        }
    }
}

void Xe3VaThang(int& xXe3, int& huongDiXe3, int& hangXe3, int& xThang, int yThang, int& huongDiThang, int& sttThang, int& hangThang)
{
    //Xu ly nghỉ lấy hàng của xe 3
    if (kiemTraViTriXe3(xXe3, xThang, yThang) == -1)// kho ben trai
    {
        xe3ChuaBoHang = 0;
        huongDiXe3 = 0;
        randomXe3 = rand() % 2;

        if (xe3Nghi > 0) // Xu ly bo hang vao kho
        {
            xe3Nghi--;
        }

        if (HangKho3 + hangXe3 <= SUC_CHUA_HANG_KHO)
        {
            HangKho3 += hangXe3;
            hangXe3 = 0;
        }
        else
        {
            HangKho3 = SUC_CHUA_HANG_KHO;
            hangXe3 -= SUC_CHUA_HANG_KHO - HangKho3;
        }
    }
    else
    {
        if (kiemTraViTriXe3(xXe3, xThang, yThang) == 1)// kho ben phai
        {
            xe3ChuaBoHang = 0;
            huongDiXe3 = 0;
            randomXe3 = rand() % 2;

            if (xe3Nghi > 0)
            {
                xe3Nghi--;
            }

            if (HangKho4 + hangXe3 <= SUC_CHUA_HANG_KHO)
            {
                HangKho4 += hangXe3;
                hangXe3 = 0;
            }
            else
            {
                HangKho4 = SUC_CHUA_HANG_KHO;
                hangXe3 -= SUC_CHUA_HANG_KHO - HangKho4;
            }
        }
        else
        {
            if (kiemTraViTriXe3(xXe3, xThang, yThang) == 2)
            {
                if (xe3Nghi > 0)
                {
                    huongDiXe3 = 0;
                    huongDiThang = 0;
                    xe3Nghi--;
                }
                else
                {
                    //Sau khi het nghi, thang di len
                    huongDiThang = -1;
                    huongDiXe3 = 1;
                    sttThang = 0;
                }
                xe3ChuaBoHang = 1;
            }
            else
            {
                if (kiemTraViTriXe3(xXe3, xThang, yThang) == -2)
                {
                    if (xe3Nghi > 0)
                    {
                        huongDiXe3 = 0;
                        huongDiThang = 0;
                        xe3Nghi--;
                    }
                    else
                    {
                        //Sau khi het nghi, thang di len
                        huongDiThang = -1;
                        huongDiXe3 = -1;
                        sttThang = 0;
                    }
                    xe3ChuaBoHang = 1;
                }
                else
                {
                    xe3Nghi = 3;
                }
            }
        }

    }

    //Xử lý di chuyển của xe khi nhận hàng
    if (kiemTraViTriThang(yThang) != 1
        &&
        (
            kiemTraViTriXe3(xXe3, xThang, yThang) == -1
            || kiemTraViTriXe3(xXe3, xThang, yThang) == 1)
        )
    {
        huongDiXe3 = 0;
    }
    else
    {
        if (kiemTraViTriThang(yThang) == 1)
        {
            if (xXe3 < xThang - XE_WEIGHT)
            {
                if (xe3ChuaBoHang == 0)
                    huongDiXe3 = 1;
            }
            else
                if (xXe3 > xThang + THANG_WEIGHT)
                {
                    if (xe3ChuaBoHang == 0)
                        huongDiXe3 = -1;
                }
                else
                    if (kiemTraViTriXe3(xXe3, xThang, yThang) == -2 || kiemTraViTriXe3(xXe3, xThang, yThang) == 2) // gap thang
                    {
                        huongDiXe3 = 0;
                        sttThang = 0;
                        hangXe3 += hangThang;
                        hangThang = 0;
                    }
        }
        else // Thang roi khoi vi tri tang 1
        {
            if (yThang < YMAX - XE_HEIGHT)
            {
                if (HangKho3 == SUC_CHUA_HANG_KHO && HangKho4 == SUC_CHUA_HANG_KHO) // Neu kho 3 4 chua day thi random
                {
                    if (randomXe3)
                    {
                        huongDiXe3 = 1;
                    }
                    else
                    {
                        huongDiXe3 = -1;
                    }
                }
                else
                {
                    if (!(HangKho3 == SUC_CHUA_HANG_KHO))
                    {
                        huongDiXe3 = -1;
                    }
                    if (!(HangKho4 == SUC_CHUA_HANG_KHO))
                    {
                        huongDiXe3 = 1;
                    }
                }
            }
        }
    }
}

void VeGiaoDien()
{
    int xXe1 = X0 + KHO_WEIGHT + 5;
    int yXe1 = Y0 + TUONG_HEIGHT - XE_HEIGHT;
    int huongDiXe1 = -1; //1 la ra thang may, -1 la quay ve kho, 0 la dung yen
    int xe1Nghi = 3;
    int hangXe1 = 0;

    int xXe2 = X0 + XMAX - (KHO_WEIGHT + XE_WEIGHT + 5);
    int yXe2 = Y0 + TUONG_HEIGHT - XE_HEIGHT;
    int huongDiXe2 = -1; //1 la ra thang may, -1 la quay ve kho, 0 la dung yen
    int xe2Nghi = 3;
    int hangXe2 = 0;

    int xXe3 = X0 + KHO_WEIGHT + 1;
    int yXe3 = Y0 + YMAX - XE_HEIGHT - 1;
    int huongDiXe3 = 1; //1 la ra thang may, -1 la quay ve kho, 0 la dung yen
    int xe3Nghi = 5;
    int hangXe3 = 0;

    int xThang = X0 + TUONG_WEIGHT + 8;
    int yThang = Y0 + KHO_HEIGHT;
    int huongDiThang = 0; // 1 la di len, -1 la di xuong, 0 la dung yen
    int sttThang = 0; // 1 la co hang, 0 la khong co hang
    int hangThang = 0;

    int sttKho1 = 1;
    int sttKho2 = 1;
    int sttKho3 = 1;
    int sttKho4 = 1;


    while (1)
    {
        if (HangKho1 == 0)
            sttKho1 = 0;
        if (HangKho2 == 0)
            sttKho2 = 0;
        if (HangKho3 == SUC_CHUA_HANG_KHO)
            sttKho3 = 0;
        if (HangKho4 == SUC_CHUA_HANG_KHO)
            sttKho4 = 0;

        VeKhoHang(0, 0, sttKho1);
        VeKhoHang(XMAX - KHO_WEIGHT, 0, sttKho2);
        VeKhoHang(0, YMAX - KHO_HEIGHT, sttKho3);
        VeKhoHang(XMAX - KHO_WEIGHT, YMAX - KHO_HEIGHT, sttKho4);

        setcolor(WHITE);
        VeKhungTuong();


        VeXe(xXe1, yXe1);
        VeXe(xXe2, yXe2);
        VeXe(xXe3, yXe3);
        VeThang(xThang, yThang, sttThang);

        if (HangKho3 == SUC_CHUA_HANG_KHO && HangKho4 == SUC_CHUA_HANG_KHO) // Neu kho day thi thoat chuong trinh
            return;
        if (!sttKho1 && !sttKho2)
            return;
        if (sttKho1 == 0 && huongDiXe1 == -1)
            huongDiXe1 = 0;
        if (sttKho2 == 0 && huongDiXe2 == -1)
            huongDiXe2 = 0;

        delay(100);//Dung 0.5s
        //Xoa vi tri cu
        setcolor(BLACK);

        if (kiemTraViTriThang(yThang) != 1)
            VeThang(xThang, yThang, sttThang);


        /*KIEM TRA XE 1*/
        if (kiemTraViTriXe1(xXe1) == -1)
        {
            if (xe1Nghi > 0) // Xu ly lay hang
            {
                huongDiXe1 = 0;
                xe1Nghi--;
            }
            else
            {

                huongDiXe1 = 1;
                xe1Nghi = 3;

                //Xu ly lay hang kho
                if (HangKho1 > SUC_CHUA_HANG_XE)
                {
                    hangXe1 = SUC_CHUA_HANG_XE;
                    HangKho1 -= hangXe1;
                }
                else
                {
                    hangXe1 = HangKho1;
                    HangKho1 = 0;
                }
            }

        }
        else
        {
            if (kiemTraViTriXe1(xXe1) == 1)
            {
                huongDiXe1 = 0;
                if (kiemTraViTriThang(yThang) != -1)
                    Xe1VaThang(huongDiXe1, hangXe1, xThang, yThang, huongDiThang, sttThang, hangThang);
            }
        }

        /*KIEM TRA XE 2*/
        if (kiemTraViTriXe2(xXe2) == -1)
        {
            if (xe2Nghi > 0) // Xu ly lay hang
            {
                huongDiXe2 = 0;
                xe2Nghi--;
            }
            else
            {
                huongDiXe2 = 1;
                xe2Nghi = 3;

                //Xu ly lay hang kho
                if (HangKho2 > SUC_CHUA_HANG_XE)
                {
                    hangXe2 = SUC_CHUA_HANG_XE;
                    HangKho2 -= hangXe2;
                }
                else
                {
                    hangXe2 = HangKho2;
                    HangKho2 = 0;
                    sttKho2 = 0;
                }
            }
        }
        else
        {
            if (kiemTraViTriXe2(xXe2) == 1)
            {
                huongDiXe2 = 0;

                if (kiemTraViTriThang(yThang) != -1)
                    Xe2VaThang(huongDiXe2, hangXe2, xThang, yThang, huongDiThang, sttThang, hangThang);
            }
        }

        /*KIEM TRA THANG*/

        if (kiemTraViTriThang(yThang) == 1)
        {
            huongDiThang = 0;
            Random = rand() % 2;
        }
        else
        {
            if (kiemTraViTriThang(yThang) == -1) // 1 la xuong toi mat dat, -1 la len toi tang hai, 0 dang chuyen dong
            {
                huongDiThang = 0;
                if (kiemTraViTriXe2(xXe2) == 1 && kiemTraViTriXe1(xXe1) == 1) // Gap thang may
                {
                    huongDiXe1 = 0;
                    huongDiXe2 = 0;
                    if (Random)
                    {
                        Xe1VaThang(huongDiXe1, hangXe1, xThang, yThang, huongDiThang, sttThang, hangThang);

                    }
                    else
                    {
                        Xe2VaThang(huongDiXe2, hangXe2, xThang, yThang, huongDiThang, sttThang, hangThang);
                    }
                }
                else
                {
                    if (kiemTraViTriXe2(xXe2) == 1)
                    {
                        huongDiXe2 = 0;
                        Xe2VaThang(huongDiXe2, hangXe2, xThang, yThang, huongDiThang, sttThang, hangThang);
                    }
                    else
                        if (kiemTraViTriXe1(xXe1) == 1)
                        {
                            huongDiXe1 = 0;
                            Xe1VaThang(huongDiXe1, hangXe1, xThang, yThang, huongDiThang, sttThang, hangThang);
                        }
                }

            }

        }

        /*KIEM TRA XE 3*/

          //Xu ly khi xe 3 gap thang
        Xe3VaThang(xXe3, huongDiXe3, hangXe3, xThang, yThang, huongDiThang, sttThang, hangThang);

        //Xoa vi tri cu
        setcolor(BLACK);

        if (huongDiXe1 != 0)
            VeXe(xXe1, yXe1);

        if (huongDiXe2 != 0)
            VeXe(xXe2, yXe2);

        if (huongDiXe3 != 0)
            VeXe(xXe3, yXe3);

        if (huongDiThang != 0)
            VeThang(xThang, yThang, sttThang);

        xXe1 += huongDiXe1 * TOC_DO_DI_CHUYEN;
        xXe2 += (-huongDiXe2) * TOC_DO_DI_CHUYEN;
        xXe3 += huongDiXe3 * TOC_DO_DI_CHUYEN;
        yThang += huongDiThang * TOC_DO_DI_CHUYEN;
    }
}

int main() {
    srand(time(NULL));
    Random = rand() % 2;
    VeGiaoDien();
    int midx = XMAX / 2;
    int midy = YMAX / 2;
    /* output a message to the screen */
    setcolor(LIGHT_RED);
    outtextxyCenter(midx, midy, "KET THUC TRO CHOI");

    getch();
    return 0;
}